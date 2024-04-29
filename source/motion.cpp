#include <common.h>
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

string Pick(Player_T player, Coordinate_T coordnate) {
  string s = "";
  if (!player.entity.empty())
    return s;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  s = Move(player, coord.x, coord.y);
  if (s == "Move ") {
    s = "PutOrPick ";
  }
  switch (coord.face) {
  case Face_T::UP:
    s += "D";
    break;
  case Face_T::DOWN:
    s += "U";
    break;
  case Face_T::LEFT:
    s += "R";
    break;
  case Face_T::RIGHT:
    s += "L";
    break;
  }
  return s;
}

string Put(Player_T player, Coordinate_T coordnate) {
  string s = "";
  if (player.entity.empty())
    return s;
  Coordinate_T coord = getNearestPosition(coordnate.x, coordnate.y);
  s = Move(player, coord.x, coord.y);
  if (s == "Move ") {
    s = "PutOrPick ";
  }
  switch (coord.face) {
  case Face_T::UP:
    s += "D";
    break;
  case Face_T::DOWN:
    s += "U";
    break;
  case Face_T::LEFT:
    s += "R";
    break;
  case Face_T::RIGHT:
    s += "L";
    break;
  }
  return s;
}

string getIngredient(Player_T player, Ingredient_T ingredient) {
  string s = "";
  if (!player.entity.empty())
    return s;
  Coordinate_T coord =
      getNearestPosition(ingredient.coord.x, ingredient.coord.y);
  s = Move(player, coord.x, coord.y);
  if (s == "Move ") {
    s = "PutOrPick ";
  }
  switch (coord.face) {
  case Face_T::UP:
    s += "D";
    break;
  case Face_T::DOWN:
    s += "U";
    break;
  case Face_T::LEFT:
    s += "R";
    break;
  case Face_T::RIGHT:
    s += "L";
    break;
  }
  return s;
}
