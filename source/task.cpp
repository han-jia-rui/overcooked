#include <iostream>
#include <string>
#include <task.h>
#include <unordered_set>
#include <vector>

#define CheckAction                                                            \
  do {                                                                         \
    if (!player.action.empty())                                                \
      return;                                                                  \
  } while (0)

void gotoTile(Player_T &player, Tile_Kind tile) {
  std::vector<Tile_T> tmp = getTile(tile, player.coord);
  Tile_T target = tmp[0];
  Coordinate_T coord = getNearestPosition(target.coord);
  Move(player, coord);
}

void Chop(Player_T &player, Recipe_T recipe) {
  assert(recipe.operation == Operation_Kind::Chop);
  std::vector<Tile_T> tmp = getTile(Tile_Kind::ChoppingStation, player.coord);
  Tile_T ChoppingStation = tmp[0];
  for (auto entity : Entity) {
    if (entity.findfood(recipe.before) &&
        entity.coord.x == ChoppingStation.coord.x &&
        ChoppingStation.coord.y == entity.coord.y) {
      Interact(player, ChoppingStation.coord);
      break;
    }
  }
  CheckAction;
  getFood(player, recipe.before);
  CheckAction;
  Put(player, ChoppingStation.coord);
}

void PanOrPot(Player_T &player, Recipe_T recipe) {
  assert(recipe.operation == Operation_Kind::Pot ||
         recipe.operation == Operation_Kind::Pan);
  Entity_T stove;
  for (auto entity : Entity) {
    if (recipe.operation == Operation_Kind::Pot &&
        entity.container == Container_Kind::Pot) {
      stove = entity;
      break;
    }
    if (recipe.operation == Operation_Kind::Pan &&
        entity.container == Container_Kind::Pan) {
      stove = entity;
      break;
    }
  }
  assert(stove.container == Container_Kind::Pot ||
         stove.container == Container_Kind::Pan);
  if (stove.findfood(recipe.before)) {
    return;
  }
  CheckAction;
  getFood(player, recipe.before);
  CheckAction;
  Put(player, stove.coord);
}

bool checkGet(Entity_T entity, std::string food_target) {
  if (entity.findfood(food_target))
    return true;
  for (auto recipe : Recipe) {
    if (food_target == recipe.after) {
      return checkGet(entity, recipe.before);
    }
  }
  return false;
}

void getFood(Player_T &player, std::string food) {
  if (player.entity.food.size() == 1 && player.entity.findfood(food))
    return;
  if (player.entity.food.size() == 1 && !checkGet(player.entity, food)) {
    return;
  }
  for (auto entity : Entity) {
    if (entity.findfood(food) && entity.container != Container_Kind::Plate) {
      Pick(player, entity.coord);
      break;
    }
  }
  CheckAction;
  for (auto ingredient : Ingredient) {
    if (food == ingredient.name) {
      Pick(player, ingredient.coord);
      break;
    }
  }
  CheckAction;
  for (auto recipe : Recipe) {
    if (food == recipe.after) {
      switch (recipe.operation) {
      case Operation_Kind::Chop:
        Chop(player, recipe);
        break;
      case Operation_Kind::Pan:
      case Operation_Kind::Pot:
        PanOrPot(player, recipe);
        break;
      }
      break;
    }
  }
}

bool checkOrder(std::vector<std::string> require, Entity_T entity) {
  for (auto rs : require) {
    if (!entity.findfood(rs))
      return false;
  }
  return true;
}

void service(Player_T &player, Order_T order) {
  std::vector<Tile_T> tmp = getTile(Tile_Kind::ServiceWindow, Coordinate_T());
  Tile_T ServiceWindow = tmp[0];
  if (player.entity.container == Container_Kind::Plate &&
      checkOrder(order.require, player.entity))
    Put(player, ServiceWindow.coord);
  CheckAction;
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate &&
        checkOrder(order.require, entity)) {
      Pick(player, entity.coord);
      break;
    }
  }
}

void putStove(Player_T &player) {
  if (!player.entity.food.empty())
    return;
  if (player.entity.container != Container_Kind::Pot &&
      player.entity.container != Container_Kind::Pan)
    return;
  std::vector<Tile_T> tmp = getTile(Tile_Kind::Stove, Coordinate_T());
  for (auto Stove : tmp) {
    bool used = false;
    for (auto entity : Entity) {
      if (entity.coord == Stove.coord) {
        used = true;
        break;
      }
    }
    if (!used) {
      Put(player, Stove.coord);
      return;
    }
  }
}

void Scheme1(Player_T &player) {
  putStove(player);
  CheckAction;

  // for (auto order : Order) {
  //   service(player, Order[0]);
  //   CheckAction;
  // }
  // CheckAction;
  int plate_cnt = 0;
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate) {
      for (auto food : Order[plate_cnt].require) {
        if (!entity.findfood(food)) {
          std::cerr << "Get " << food << " from plate\n";
          getFood(player, food);
          CheckAction;
          std::cerr << "Put " << food << " to plate\n";
          if (player.entity.findfood(food))
            Put(player, entity.coord);
          CheckAction;
        }
      }
      break;
    }
  }
  CheckAction;
}

void Scheme2(Player_T &player) {
  if (player.entity.container != Container_Kind::DirtyPlates) {
    for (auto order : Order) {
      service(player, Order[0]);
      CheckAction;
    }
  }
  CheckAction;
  std::vector<Tile_T> tmp = getTile(Tile_Kind::Sink, Coordinate_T());
  Tile_T Sink = tmp[0];
  if (player.entity.empty()) {
    for (auto entity : Entity) {
      if (entity.container == Container_Kind::DirtyPlates &&
          entity.coord.x == Sink.coord.x && Sink.coord.y == entity.coord.y) {
        Interact(player, entity.coord);
        break;
      }
    }
  }
  CheckAction;
  if (player.entity.container == Container_Kind::None) {
    for (auto entity : Entity) {
      if (entity.container == Container_Kind::DirtyPlates) {
        Pick(player, entity.coord);
        break;
      }
    }
  }
  CheckAction;
  if (player.entity.container == Container_Kind::DirtyPlates &&
      player.entity.sum >= 1) {
    Put(player, Sink.coord);
  }
  CheckAction;
}
