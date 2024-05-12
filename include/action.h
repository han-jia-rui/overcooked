#ifndef ACTION_H
#define ACTION_H

#include <common.h>

void Move(Player_T &player, double x, double y);
void Pick(Player_T &player, Coordinate_T coordnate);
void Put(Player_T &player, Coordinate_T coordnate);
void Interact(Player_T &player, Coordinate_T coordnate);

#endif
