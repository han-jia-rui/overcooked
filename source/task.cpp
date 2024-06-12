#include <task.h>

void gotoTile(Player_T &player, Tile_Kind tile) {
  std::vector<Tile_T> tmp = getTile(tile, player.coord);
  Tile_T target = tmp[0];
  Coordinate_T coord = getNearestPosition(target.coord);
  Move(player, coord);
}

void Chop(Player_T &player, Recipe_T recipe) {
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
  Check(stove.findfood(recipe.before));
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
  Check(player.entity.food_list.size() == 1 && player.entity.findfood(food));
  Check(player.entity.food_list.size() == 1 && !checkGet(player.entity, food));
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
  Check(!player.entity.food_list.empty());
  Check(player.entity.container != Container_Kind::Pot &&
        player.entity.container != Container_Kind::Pan);
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

