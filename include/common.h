#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <string>
#include <vector>
using namespace std;

enum class Container_T {
  None,
  Pan,
  Pot,
  Plate,
  DirtyPlates,
};

enum class Tile_T {
  None,
  Void,
  Floor,
  Wall,
  Table,
  IngredientBox,
  Trashbin,
  ChoppingStation,
  ServiceWindow,
  Stove,
  PlateReturn,
  Sink,
  PlateRack,
};

struct Ingredient_T {
  int x, y, price;
  string name;
};

struct Recipe_T {
  int time;
  string nameBefore, nameAfter;
  string kind;
};

struct Order_T {
  int validFrame;
  int price;
  int frequency;
  vector<std::string> recipe;
};

struct Player_T {
  double x, y;
  double X_Velocity;
  double Y_Velocity;
  int live;
  Container_T containerKind;
  vector<std::string> entity;
};

struct Entity_T {
  double x, y;
  Container_T containerKind;
  vector<std::string> entity;
  int currentFrame, totalFrame;
  int sum;
};

Tile_T getTileKind(char kindChar);

inline char getAbbrev(Tile_T kind);

#endif
