#include <common.h>
#include <move.h>
#include <string>

string move(Player_T player, double x, double y) {
  string s = "Move ";
  if (player.x < x - 0.3)
    s += "R";
  if (player.x > x + 0.3)
    s += "L";
  if (player.y > y + 0.3)
    s += "U";
  if (player.y < y - 0.3)
    s += "D";
  return s;
}
