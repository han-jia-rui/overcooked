#include <cassert>
#include <task.h>

#define CheckAction                                                            \
  do {                                                                         \
    if (!player.action.empty())                                                \
      return;                                                                  \
  } while (0)

void Operate(Player_T &player, string food, Operation_Kind Operation) {}

void getFood(Player_T &player, string food) {
  player.action.clear();
  for (auto ingredient : Ingredient) {
    if (food == ingredient.name) {
      Pick(player, ingredient.coord);
      break;
    }
  }
  CheckAction;
  for (auto recipe : Recipe) {
    if (food == recipe.after) {
      getFood(player, recipe.before);
      CheckAction;
      Operate(player, recipe.before, recipe.operation);
      CheckAction;
      break;
    }
  }
}

void prepareOrder(Player_T &player, Order_T order) {
    Tile_T ServiceWindow = getTile(Tile_Kind::ServiceWindow, Coordinate_T());
    if (player.entity.container == Container_Kind::Plate &&
        player.entity.food.size() > 0)
      Put(player, ServiceWindow.coord);
    else {
      for (auto entity : Entity) {
        if (entity.container == Container_Kind::Plate &&
            entity.food.size() > 0) {
          Pick(player, entity.coord);
          break;
        }
      }
    }
    if (player.action.empty() && player.entity.food.empty()) {
      for (auto order : Order) {
        for (auto ingredient : Ingredient) {
          if (order.require[0] == ingredient.name)
            Pick(player, ingredient.coord);
          if (!player.action.empty())
            break;
        }
        if (!player.action.empty())
          break;
      }
    } else if (player.action.empty()) {
      for (auto entity : Entity) {
        if (entity.container == Container_Kind::Plate &&
            entity.food.size() == 0) {
          Put(player, entity.coord);
          break;
        }
      }
    }
}

void washPlate(Player_T &player) {
  Tile_T Sink = getTile(Tile_Kind::Sink, Coordinate_T());
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
