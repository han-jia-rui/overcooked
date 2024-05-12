#include <cmath>
#include <common.h>
#include <motion.h>

const double StopDistance = 0.4;
const double InteractDistance = 1.2;

double dist(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Move(Player_T &player, double x, double y) {
  player.action = "Move ";
  if (player.coord.x < x - StopDistance)
    player.action += "R";
  if (player.coord.x > x + StopDistance)
    player.action += "L";
  if (player.coord.y > y + StopDistance)
    player.action += "U";
  if (player.coord.y < y - StopDistance)
    player.action += "D";
}

void Pick(Player_T &player, Coordinate_T coordnate) {
  player.action = "";
  if (!player.entity.food.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  Move(player, coord.x, coord.y);
  if (player.action == "Move ") {
    player.action = "PutOrPick ";
    switch (coord.face) {
    case Direction::UP:
      player.action += "D";
      break;
    case Direction::DOWN:
      player.action += "U";
      break;
    case Direction::LEFT:
      player.action += "R";
      break;
    case Direction::RIGHT:
      player.action += "L";
      break;
    }
  }
}

void Put(Player_T &player, Coordinate_T coordnate) {
  player.action = "";
  if (player.entity.food.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  Move(player, coord.x, coord.y);
  if (player.action == "Move ") {
    player.action = "PutOrPick ";
    switch (coord.face) {
    case Direction::UP:
      player.action += "D";
      break;
    case Direction::DOWN:
      player.action += "U";
      break;
    case Direction::LEFT:
      player.action += "R";
      break;
    case Direction::RIGHT:
      player.action += "L";
      break;
    }
  }
}

void Interact(Player_T &player, Coordinate_T coordnate) {
  player.action = "";
  if (!player.entity.food.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  Move(player, coord.x, coord.y);
  if (player.action == "Move ") {
    player.action = "Interact ";
    switch (coord.face) {
    case Direction::UP:
      player.action += "D";
      break;
    case Direction::DOWN:
      player.action += "U";
      break;
    case Direction::LEFT:
      player.action += "R";
      break;
    case Direction::RIGHT:
      player.action += "L";
      break;
    }
  }
}
