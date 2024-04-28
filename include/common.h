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
  string name;
  int x, y, price;
};

struct Recipe_T {
  int time;
  string nameBefore, nameAfter;
  string operation;
};

struct Order_T {
  int validFrame;
  int price;
  int frequency;
  vector<string> require;
};

struct Player_T {
  double x, y;
  double X_Velocity;
  double Y_Velocity;
  int live;
  Container_T containerKind;
  vector<string> entity;
};

struct Entity_T {
  double x, y;
  Container_T containerKind;
  vector<string> entity;
  int currentFrame, totalFrame;
  int sum;
};

// init.cpp
extern int width, height;
extern vector<vector<char>> map;
extern int Ingredient_cnt;
extern vector<Ingredient_T> Ingredient;
extern int Recipe_cnt;
extern vector<Recipe_T> Recipe;
extern int totalFrame, randomizeSeed;
extern int OrderTable_cnt;
extern vector<Order_T> OrderTable;
extern int Player_cnt;
extern vector<Player_T> Player;
extern int Entity_cnt;
extern vector<Entity_T> Entity;

// frame.cpp
extern int Order_cnt;
extern vector<Order_T> Order;
extern int remainFrame, Fund;

// common.cpp
Tile_T getTileKind(char kindChar);
inline char getAbbrev(Tile_T kind);

#endif
