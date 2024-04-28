#include <common.h>
#include <move.h>
#include <string>

const double StopDistance = 0.27;

string move(Player_T player, double x, double y) {
  string s = "Move ";
  if (player.x < x - StopDistance)
    s += "R";
  if (player.x > x + StopDistance)
    s += "L";
  if (player.y > y + StopDistance)
    s += "U";
  if (player.y < y - StopDistance)
    s += "D";
  return s;
}
