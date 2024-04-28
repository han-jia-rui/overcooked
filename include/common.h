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

extern int width, height;
extern vector<vector<int>> map;
extern int Ingredient_cnt;
extern vector<Ingredient_T> Ingredient;
extern int Recipe_cnt;
extern vector<Recipe_T> Recipe;
extern int totalTime, randomizeSeed, totalOrderCount;
extern struct Order_T totalOrder[20 + 5];
extern int orderCount;
extern struct Order_T Order[20 + 5];
extern int k;
extern struct Player_T Players[2 + 5];
extern int entityCount;
extern struct Entity_T Entity[20 + 5];
extern int remainFrame, Fund;

Tile_T getTileKind(char kindChar);

inline char getAbbrev(Tile_T kind);

#endif
