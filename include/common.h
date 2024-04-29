#ifndef COMMON_H
#define COMMON_H

#include <cassert>
#include <queue>
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

enum class Task_Kind {
  None,
  Pick,
  Put,
  Interact,
  Wait,
};

enum class Face_T {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

enum class Tile_Kind {
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
  Face_T face;
};

struct Tile_T {
  Tile_Kind tile_kind;
  Coordinate_T coord;
  int status;
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

struct Entity_T {
  Coordinate_T coord;
  Container_T container;
  vector<string> name;
  int currentFrame, totalFrame;
  int sum;
};

struct Task_T {
  Task_Kind task_kind = Task_Kind::None;
  Entity_T entity;
  Ingredient_T ingredient;
};

struct Player_T {
  Coordinate_T coord;
  double vx;
  double vy;
  int live;
  Entity_T entity;
  Task_T task;
  string action;
};

// init.cpp
extern int width, height;
extern vector<vector<Tile_Kind>> map;
extern Tile_T ChoppingStation, ServiceWindow, Stove, Sink;
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

extern queue<Task_T> Task;

// frame.cpp
extern int Order_cnt;
extern vector<Order_T> Order;
extern int Sales;

// common.cpp
Tile_Kind getTileKind(char ch);
inline char getAbbrev(Tile_Kind kind);
Coordinate_T getNearestPosition(int x, int y);

#endif
