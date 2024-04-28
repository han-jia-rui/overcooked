#include <common.h>
#include <motion.h>

const double StopDistance = 0.3;

string Move(Player_T player, double x, double y) {
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

string Pick(Player_T palyer, Entity_T entity){
  string s = "";
  return s;
}
