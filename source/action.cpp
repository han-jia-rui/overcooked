#include "common.h"
#include <action.h>
#include <cmath>

const double StopDistance = 0.28;
const double InteractDistance = 1.2;

// double dist(double x1, double y1, double x2, double y2) {
//   return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
// }
//
void setDirection(Player_T &player, Coordinate_T coord) {
    switch (coord.face) {
    case Direction::UP:
      player.action.direction += "D";
      break;
    case Direction::DOWN:
      player.action.direction += "U";
      break;
    case Direction::LEFT:
      player.action.direction += "R";
      break;
    case Direction::RIGHT:
      player.action.direction += "L";
      break;
    }
}

void Move(Player_T &player, double x, double y) {
  player.action.set(Action_Kind::Move);
  if (player.coord.x < x - StopDistance)
    player.action.direction += "R";
  if (player.coord.x > x + StopDistance)
    player.action.direction += "L";
  if (player.coord.y > y + StopDistance)
    player.action.direction += "U";
  if (player.coord.y < y - StopDistance)
    player.action.direction += "D";
  if(player.action.direction.empty())
    player.action.clear();
}

void Pick(Player_T &player, Coordinate_T coordnate) {
  Coordinate_T coord = getNearestPosition(coordnate);
  Move(player, coord.x, coord.y);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Pick);
    setDirection(player, coord);
  }
}

void Put(Player_T &player, Coordinate_T coordnate) {
  if (player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate);
  Move(player, coord.x, coord.y);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Put);
    setDirection(player, coord);
  }
}

void Interact(Player_T &player, Coordinate_T coordnate) {
  if (!player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate);
  Move(player, coord.x, coord.y);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Interact);
    setDirection(player, coord);
  }
}
