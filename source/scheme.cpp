#include <iostream>
#include <scheme.h>

void Scheme1(Player_T &player) {
  CheckAlive;
  for (auto order : Order) {
    service(player, Order[0]);
    CheckAction;
  }
  CheckAction;
  putStove(player);
  CheckAction;

  int plate_cnt = 0;
  for (auto entity : Entity) {
    if (entity.container == Container_Kind::Plate) {
      for (auto food : Order[plate_cnt].require) {
        if (!entity.findfood(food)) {
          getFood(player, food);
          CheckAction;
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
  CheckAlive;
  Tile_T Sink = getFirstTile(Tile_Kind::Sink);
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
