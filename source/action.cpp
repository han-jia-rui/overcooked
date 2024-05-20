#include "common.h"
#include <action.h>
#include <cmath>

const double StopDistance = 0.4;
const double InteractDistance = 1.2;

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

void Move(Player_T &player, Coordinate_T target) {
  if (target.x - player.coord.x > StopDistance) {
    player.action.set(Action_Kind::Move);
    player.action.direction += "R";
    return;
  }
  if (player.coord.x - target.x > StopDistance) {
    player.action.set(Action_Kind::Move);
    player.action.direction += "L";
    return;
  }
  if (player.coord.y - target.y > StopDistance)
    player.action.direction += "U";
  if (target.y - player.coord.y > StopDistance)
    player.action.direction += "D";
  if (player.action.direction.empty())
    player.action.clear();
}

void Pick(Player_T &player, Coordinate_T target) {
  Coordinate_T coord = getNearestPosition(target);
  Move(player, coord);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Pick);
    setDirection(player, coord);
  }
}

void Put(Player_T &player, Coordinate_T target) {
  if (player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(target);
  Move(player, coord);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Put);
    setDirection(player, coord);
  }
}

void Interact(Player_T &player, Coordinate_T target) {
  if (!player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(target);
  Move(player, coord);
  if (player.action.empty()) {
    player.action.set(Action_Kind::Interact);
    setDirection(player, coord);
  }
}
