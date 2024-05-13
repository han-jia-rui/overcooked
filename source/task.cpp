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
