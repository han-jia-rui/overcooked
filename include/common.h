#ifndef COMMON_H
#define COMMON_H

#include <cassert>
#include <cmath>
#include <enum.h>
#include <string>
#include <unordered_set>
#include <vector>

struct Coordinate_T {
  double x, y;
  Direction face;
  Coordinate_T(double x, double y) : x(x), y(y) {}
  Coordinate_T() : x(0), y(0) {}
  bool operator==(const Coordinate_T &coord) const {
    return x == coord.x && y == coord.y;
  }
  double dist(const Coordinate_T &coord) const {
    return sqrt((x - coord.x) * (x - coord.x) + (y - coord.y) * (y - coord.y));
  }
};

struct node {
  int x, y;

  node() : x(0), y(0) {}
  node(int x, int y) : x(x), y(y) {}
  node &operator+=(const node &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  bool operator==(const node &rhs) const { return x == rhs.x && y == rhs.y; }
  bool bound(int w, int h) { return x >= 0 && x < w && y >= 0 && y < h; }
  int direction(const node &rhs) const {
    if (x == rhs.x) {
      return 0;
    } else if (y == rhs.y) {
      return 1;
    }
    return -1;
  }
};

struct Tile_T {
  Tile_Kind kind;
  Coordinate_T coord;
  void set(int x, int y, Tile_Kind tile_kind) {
    coord.x = x;
    coord.y = y;
    kind = tile_kind;
  }
  bool movable() { return kind == Tile_Kind::Floor; }
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
  bool fixed;
  std::unordered_set<std::string> food_list;
  int frame_cur, frame_total;
  int sum;
  void clear() {
    coord.x = coord.y = 0;
    fixed = false;
    container = Container_Kind::None;
    food_list.clear();
    frame_cur = frame_total = 0;
    sum = 0;
  }
  bool empty() {
    return container == Container_Kind::None && food_list.empty();
  }
  bool findfood(const std::string &food) {
    return this->food_list.find(food) != this->food_list.end();
  }
  void set(std::stringstream &ss);
  bool checkOrder(Order_T order) {
    if (order.require.size() != food_list.size())
      return false;
    for (auto rs : order.require) {
      if (!findfood(rs))
        return false;
    }
    return true;
  }
  bool is(Container_Kind kind) { return container == kind; }
};

struct Action_T {
  Action_Kind action;
  std::string direction;
  void clear() {
    action = Action_Kind::None;
    direction = "";
  }
  void set(Action_Kind action_kind) { this->action = action_kind; }
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
  void clear() {
    coord.x = coord.y = 0;
    vx = vy = 0;
    live = 0;
    entity.clear();
    action.clear();
  }
};

// init.cpp
extern int width, height;
extern Tile_T Map[100][100];
extern std::vector<Ingredient_T> Ingredient;
extern std::vector<Recipe_T> Recipe;
extern int Frame_total, randomizeSeed;
extern std::vector<Order_T> OrderTable;
extern std::vector<Player_T> Player;
extern std::vector<Entity_T> Entity;

// frame.cpp
extern std::vector<Order_T> Order;
extern int Sales;
extern bool map[100][100];

// common.cpp
std::vector<Tile_T> getTile(Tile_Kind tile_kind);
Tile_T getFirstTile(Tile_Kind tile_kind);
Coordinate_T getNearestPosition(Coordinate_T coord);
Coordinate_T getNextPosition(Coordinate_T st, Coordinate_T ed);
bool isTileUsed(Tile_T tile);

#endif
