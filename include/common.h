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

struct Coordinate_T {
  double x, y;
};

struct Ingredient_T {
  string name;
  Coordinate_T coord;
  int price;
};

struct Recipe_T {
  int time;
  string nameBefore, nameAfter;
  string operation;
};

struct Order_T {
  int Frame_left;
  int price;
  int frequency;
  vector<string> require;
};

struct Player_T {
  Coordinate_T coord;
  double vx;
  double vy;
  int live;
  Container_T container_hold;
  vector<string> entity;
};

struct Entity_T {
  Coordinate_T coord;
  Container_T container;
  vector<string> entity;
  int currentFrame, totalFrame;
  int sum;
};

// init.cpp
extern int width, height;
extern vector<vector<Tile_T>> map;
extern int Ingredient_cnt;
extern vector<Ingredient_T> Ingredient;
extern int Recipe_cnt;
extern vector<Recipe_T> Recipe;
extern int Frame_total, randomizeSeed;
extern int OrderTable_cnt;
extern vector<Order_T> OrderTable;
extern int Player_cnt;
extern vector<Player_T> Player;
extern int Entity_cnt;
extern vector<Entity_T> Entity;

// frame.cpp
extern int Order_cnt;
extern vector<Order_T> Order;
extern int Grade;

// common.cpp
Tile_T getTileKind(char ch);
inline char getAbbrev(Tile_T kind);

#endif
