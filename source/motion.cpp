#include <common.h>
#include <iostream>
#include <math.h>
#include <motion.h>

const double StopDistance = 0.5;
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
  if (!player.entity.name.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  Move(player, coord.x, coord.y);
  if (player.action == "Move ") {
    player.action = "PutOrPick ";
    switch (coord.face) {
    case Face_T::UP:
      player.action += "D";
      break;
    case Face_T::DOWN:
      player.action += "U";
      break;
    case Face_T::LEFT:
      player.action += "R";
      break;
    case Face_T::RIGHT:
      player.action += "L";
      break;
    }
  }
  cerr << player.action << endl;
}

void Put(Player_T &player, Coordinate_T coordnate) {
  player.action = "";
  if (player.entity.name.empty())
    return;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  Move(player, coord.x, coord.y);
  if (player.action == "Move ") {
    player.action = "PutOrPick ";
    switch (coord.face) {
    case Face_T::UP:
      player.action += "D";
      break;
    case Face_T::DOWN:
      player.action += "U";
      break;
    case Face_T::LEFT:
      player.action += "R";
      break;
    case Face_T::RIGHT:
      player.action += "L";
      break;
    }
  }
}
