#ifndef MOVE_H
#define MOVE_H

#include <common.h>

string Move(Player_T player, double x, double y);
string Pick(Player_T player, Coordinate_T coordnate);
string Put(Player_T player, Coordinate_T coordnate);
string getIngredient(Player_T player, Ingredient_T ingredient);

#endif
