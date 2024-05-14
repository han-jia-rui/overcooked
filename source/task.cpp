#include <cassert>
#include <iostream>
#include <string>
#include <task.h>
#include <vector>

#define CheckAction                                                            \
  do {                                                                         \
    if (!player.action.empty())                                                \
      return;                                                                  \
  } while (0)

void Chop(Player_T &player, Recipe_T recipe) {
  assert(recipe.operation == Operation_Kind::Chop);
  vector<Tile_T> tmp = getTile(Tile_Kind::ChoppingStation, player.coord);
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
    // Interact(player, stove.coord);
  }
  CheckAction;
  getFood(player, recipe.before);
  CheckAction;
  Put(player, stove.coord);
}

bool checkOrder(vector<string> require, vector<string> cur) {
  for (auto rs : require) {
    bool flag = false;
    for (auto cs : cur) {
      if (rs == cs) {
        flag = true;
        break;
      }
    }
    if (!flag)
      return false;
  }
  return true;
}

void getFood(Player_T &player, string food) {
  if (player.entity.food.size() == 1 && player.entity.food[0] == food)
    return;
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

void service(Player_T &player, Order_T order) {
  vector<Tile_T> tmp = getTile(Tile_Kind::ServiceWindow, Coordinate_T());
  Tile_T ServiceWindow = tmp[0];
  if (player.entity.container == Container_Kind::Plate &&
      checkOrder(order.require, player.entity.food))
    Put(player, ServiceWindow.coord);
  CheckAction;
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate &&
        checkOrder(order.require, entity.food)) {
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
  vector<Tile_T> tmp = getTile(Tile_Kind::Stove, Coordinate_T());
  for (auto Stove : tmp) {
    bool flag = false;
    for (auto entity : Entity) {
      if (entity.coord.x == Stove.coord.x && entity.coord.y == Stove.coord.y) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      Put(player, Stove.coord);
      return;
    }
  }
}

void prepareOrder(Player_T &player) {
  putStove(player);
  CheckAction;
  for (auto order : Order) {
    service(player, order);
    CheckAction;
  }
  CheckAction;
  int order_cnt = 0;
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate) {
      for (auto food : Order[order_cnt].require) {
        if (!entity.findfood(food)) {
          cerr << "Get " << food << " from plate\n";
          getFood(player, food);
          CheckAction;
          cerr << "Put " << food << " to plate\n";
          if (player.entity.findfood(food))
            Put(player, entity.coord);
          CheckAction;
        }
      }
      order_cnt++;
      // break;
    }
  }
}

void washPlate(Player_T &player) {
  vector<Tile_T> tmp = getTile(Tile_Kind::Sink, Coordinate_T());
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
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::DirtyPlates) {
      Pick(player, entity.coord);
      break;
    }
  }
  CheckAction;
  Put(player, Sink.coord);
}
