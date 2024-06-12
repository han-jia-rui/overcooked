#ifndef TASK_H
#define TASK_H

#include <action.h>
#include <common.h>
#include <string>

#define Check(x)                                                               \
  do {                                                                         \
    if (!(x))                                                                  \
      return;                                                                  \
  } while (0)

#define CheckAction                                                            \
  do {                                                                         \
    if (!player.action.empty())                                                \
      return;                                                                  \
  } while (0)

void getFood(Player_T &player, std::string food);
void Chop(Player_T &player, Recipe_T recipe);
void PanOrPot(Player_T &player, Recipe_T recipe);
void service(Player_T &player, Order_T order);
void putStove(Player_T &player);

#endif // !TASK_H
