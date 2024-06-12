#include <iostream>
#include <task.h>

void gotoTile(Player_T &player, Tile_Kind tile_kind) {
  Tile_T target = getFirstTile(tile_kind);
  Coordinate_T coord = getNearestPosition(target.coord);
  Move(player, coord);
}

void Chop(Player_T &player, Recipe_T recipe) {
  Tile_T ChoppingStation = getFirstTile(Tile_Kind::ChoppingStation);
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
        entity.is(Container_Kind::Pot)) {
      stove = entity;
      break;
    }
    if (recipe.operation == Operation_Kind::Pan &&
        entity.is(Container_Kind::Pan)) {
      stove = entity;
      break;
    }
  }
  Check(!stove.findfood(recipe.before));
  CheckAction;
  getFood(player, recipe.before);
  CheckAction;
  Put(player, stove.coord);
}

bool checkGet(Entity_T entity, std::string food_target) {
  if (entity.food_list.empty())
    return true;
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
  Check(!player.entity.findfood(food));
  Check(checkGet(player.entity, food));
  for (auto entity : Entity) {
    if (entity.findfood(food) && !entity.is(Container_Kind::Plate)) {
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
  Tile_T ServiceWindow = getFirstTile(Tile_Kind::ServiceWindow);
  if (player.entity.is(Container_Kind::Plate) &&
      player.entity.checkOrder(order))
    Put(player, ServiceWindow.coord);
  CheckAction;

  Check(player.entity.container == Container_Kind::None);
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate && entity.checkOrder(order)) {
      Pick(player, entity.coord);
      CheckAction;
    }
  }
}

void putStove(Player_T &player) {
  Check(player.entity.food_list.empty());
  Check(player.entity.is(Container_Kind::Pot) ||
        player.entity.is(Container_Kind::Pan));
  std::vector<Tile_T> tmp = getTile(Tile_Kind::Stove);
  for (auto Stove : tmp) {
    if (!isTileUsed(Stove)) {
      Put(player, Stove.coord);
      return;
    }
  }
}
