#include <scheme.h>

void Scheme1(Player_T &player) {
  CheckAlive;
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
          // std::cerr << "Get " << food << " from plate\n";
          getFood(player, food);
          CheckAction;
          // std::cerr << "Put " << food << " to plate\n";
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
