#include <cassert>
#include <common.h>
#include <enum.h>
#include <init.h>
#include <iostream>
#include <sstream>

int width, height;
Tile_T Map[100][100];
std::vector<Ingredient_T> Ingredient;
std::vector<Recipe_T> Recipe;
int Frame_total, randomizeSeed;
std::vector<Order_T> OrderTable;
std::vector<Player_T> Player;
std::vector<Entity_T> Entity;

static void read() {
  std::string s;
  getline(std::cin, s, '\0');
  std::stringstream ss(s);

  /* 读取初始地图信息 */
  ss >> width >> height;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char ch;
      ss >> ch;
      Map[j][i].set(j, i, char2tile(ch));
    }
  }

  int Ingredient_cnt;
  ss >> Ingredient_cnt;
  Ingredient.resize(Ingredient_cnt);
  for (int i = 0; i < Ingredient_cnt; i++) {
    ss >> s;
    assert(s == "IngredientBox");
    ss >> Ingredient[i].coord.x >> Ingredient[i].coord.y >>
        Ingredient[i].name >> Ingredient[i].price;
  }

  int Recipe_cnt;
  ss >> Recipe_cnt;
  Recipe.resize(Recipe_cnt);
  for (int i = 0; i < Recipe_cnt; i++) {
    ss >> Recipe[i].frame >> Recipe[i].before;
    ss >> s;
    Recipe[i].operation = str2operation(s);
    ss >> Recipe[i].after;
  }

  ss >> Frame_total >> randomizeSeed;

  int OrderTable_cnt;
  ss >> OrderTable_cnt;
  OrderTable.resize(OrderTable_cnt);
  for (int i = 0; i < OrderTable_cnt; i++) {
    ss >> OrderTable[i].frame_left >> OrderTable[i].price >>
        OrderTable[i].frequency;
    getline(ss, s);
    std::stringstream tmp(s);
    while (tmp >> s)
      OrderTable[i].require.push_back(s);
  }

  int Player_cnt;
  ss >> Player_cnt;
  assert(Player_cnt == 2);
  Player.resize(Player_cnt);
  for (auto &player : Player) {
    player.clear();
    ss >> player.coord.x >> player.coord.y;
  }

  int Entity_cnt;
  ss >> Entity_cnt;
  Entity.resize(Entity_cnt);
  for (int i = 0; i < Entity_cnt; i++) {
    Entity[i].set(ss);
  }
}

void init() { read(); }
