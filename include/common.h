#ifndef COMMON_H
#define COMMON_H

#include <cassert>
#include <queue>
#include <string>
#include <vector>
using namespace std;

enum class Container_Kind {
  None,
  Pan,         // 煎锅
  Pot,         // 煮锅
  Plate,       // 盘子
  DirtyPlates, // 脏盘子
};

enum class Task_Kind {
  None,
  Pick,
  Put,
  Interact,
  Wait,
};

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

enum class Operation_Kind {
  Chop, // 切菜
  Pan, // 煎
  Pot, // 煮
};

enum class Tile_Kind {
  Void,            // 悬崖
  Floor,           // 地板
  Wall,            // 墙
  Table,           // 工作台
  IngredientBox,   // 食材箱
  Trashbin,        // 垃圾箱
  ChoppingStation, // 切菜台
  ServiceWindow,   // 出菜口
  Stove,           // 灶台
  PlateReturn,     // 盘子回收口
  Sink,            // 洗碗台
  PlateRack,       // 盘子架
};

struct Coordinate_T {
  double x, y;
  Direction face;
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
  int frame;
  string before, after;
  Operation_Kind operation;
};

struct Order_T {
  int frame_left;
  int price;
  int frequency;
  vector<string> require;
};

struct Entity_T {
  Coordinate_T coord;
  Container_Kind container;
  vector<string> food;
  int frame_cur, frame_total;
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
