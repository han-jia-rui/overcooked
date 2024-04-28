#include <common.h>
#include <iostream>
#include <math.h>
#include <motion.h>

const double StopDistance = 0.3;
const double InteractDistance = 1.2;

double dist(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

string Move(Player_T player, double x, double y) {
  string s = "Move ";
  if (player.coord.x < x - StopDistance)
    s += "R";
  if (player.coord.x > x + StopDistance)
    s += "L";
  if (player.coord.y > y + StopDistance)
    s += "U";
  if (player.coord.y < y - StopDistance)
    s += "D";
  return s;
}

string Pick(Player_T palyer, Entity_T entity) {
  string s = "";
  Coordinate_T coord = getNearestPosition(entity.coord.x, entity.coord.y);
  cerr << "x = " << coord.x << ", y = " << coord.y << endl;
  s = Move(palyer, coord.x, coord.y);
  return s;
}
