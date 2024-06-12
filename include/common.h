#ifndef COMMON_H
#define COMMON_H

#include <cassert>
#include <enum.h>
#include <string>
#include <unordered_set>
#include <vector>

struct Coordinate_T;

// class Map_T {
// private:
//   vector<vector<Tile_Kind>> map;
//   int height, weight;
// public:
//   Map_T(int height, int weight) : height(height), weight(weight) {
//     map.resize(height);
//     for (int i = 0; i < height; i++) {
//       map[i].resize(weight);
//     }
//   }
//   Tile_Kind getTileKind(int x, int y) {
//     return map[x][y];
//   }
//   void setTileKind(int x, int y, Tile_Kind tile_kind) {
//     map[x][y] = tile_kind;
//   }
//   vector<Tile_T> getTile(Tile_Kind tile_kind, Coordinate_T coord) {
//     vector<Tile_T> ret;
//     Tile_T tmp;
//     for (int i = 0; i < height; i++) {
//       for (int j = 0; j < weight; j++) {
//         if (map[j][i] == tile_kind) {
//           tmp.tile_kind = tile_kind;
//           tmp.coord.x = j;
//           tmp.coord.y = i;
//           ret.push_back(tmp);
//         }
//       }
//     }
//     return ret;
//   }
// };

struct Coordinate_T {
  double x, y;
  Direction face;
  bool operator==(const Coordinate_T &coord) const {
    return x == coord.x && y == coord.y;
  }
};

struct Tile_T {
  Tile_Kind tile_kind;
  Coordinate_T coord;
  int status;
};

struct Ingredient_T {
  std::string name;
  Coordinate_T coord;
  int price;
};

struct Recipe_T {
  int frame;
  std::string before, after;
  Operation_Kind operation;
};

struct Order_T {
  int frame_left;
  int price;
  int frequency;
  std::vector<std::string> require;
};

struct Entity_T {
  Coordinate_T coord;
  Container_Kind container;
  std::unordered_set<std::string> food;
  int frame_cur, frame_total;
  int sum;
  void clear() {
    coord.x = coord.y = 0;
    container = Container_Kind::None;
    food.clear();
    frame_cur = frame_total = 0;
    sum = 0;
  }
  bool empty() { return container == Container_Kind::None && food.empty(); }
  bool findfood(const std::string &food) {
    return this->food.find(food) != this->food.end();
  }
  void set(std::stringstream &ss);
};

struct Action_T {
  Action_Kind action;
  std::string direction;
  void clear() {
    action = Action_Kind::None;
    direction = "";
  }
  void set(Action_Kind action) { this->action = action; }
  bool empty() { return action == Action_Kind::None; }
  std::string toString();
};

struct Player_T {
  Coordinate_T coord;
  double vx;
  double vy;
  int live;
  Entity_T entity;
  Action_T action;
};

// init.cpp
extern int width, height;
extern Tile_Kind Map[100][100];
extern int Ingredient_cnt;
extern std::vector<Ingredient_T> Ingredient;
extern int Recipe_cnt;
extern std::vector<Recipe_T> Recipe;
extern int Frame_total, randomizeSeed;
extern int OrderTable_cnt;
extern std::vector<Order_T> OrderTable;
extern int Player_cnt;
extern std::vector<Player_T> Player;
extern int Entity_cnt;
extern std::vector<Entity_T> Entity;

// frame.cpp
extern int Order_cnt;
extern std::vector<Order_T> Order;
extern int Sales;
extern bool map[100][100];

// common.cpp
std::vector<Tile_T> getTile(Tile_Kind tile_kind, Coordinate_T coord);
Coordinate_T getNearestPosition(Coordinate_T coord);
Coordinate_T getNextPosition(Coordinate_T st, Coordinate_T ed);

#endif
