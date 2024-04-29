#include <common.h>
#include <init.h>
#include <iostream>
#include <sstream>

int width, height;
vector<vector<Tile_Kind>> map;
Tile_T ChoppingStation, ServiceWindow, Stove;
int Ingredient_cnt;
vector<Ingredient_T> Ingredient;
int Recipe_cnt;
vector<Recipe_T> Recipe;
int Frame_total, randomizeSeed;
int OrderTable_cnt;
vector<Order_T> OrderTable;
int Player_cnt;
vector<Player_T> Player;
int Entity_cnt;
vector<Entity_T> Entity;

static void read() {
  string s;
  int frame;

  /* 读取初始地图信息 */
  getline(std::cin, s, '\0');
  stringstream ss(s);

  ss >> width >> height;
  map.resize(height);
  for (int i = 0; i < height; i++) {
    map[i].resize(width);
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char ch;
      ss >> ch;
      map[j][i] = getTileKind(ch);
      if(map[j][i] == Tile_Kind::ServiceWindow){
        ServiceWindow.coord.x = j;
        ServiceWindow.coord.y = i;
        ServiceWindow.tile_kind = map[j][i];
      }
    }
  }

  /* 读入原料箱：位置、名字、以及采购单价 */
  ss >> Ingredient_cnt;
  Ingredient.resize(Ingredient_cnt);
  for (int i = 0; i < Ingredient_cnt; i++) {
    ss >> s;
    assert(s == "IngredientBox");
    ss >> Ingredient[i].coord.x >> Ingredient[i].coord.y >>
        Ingredient[i].name >> Ingredient[i].price;
  }

  /* 读入配方：加工时间、加工前的字符串表示、加工容器、加工后的字符串表示 */
  ss >> Recipe_cnt;
  Recipe.resize(Recipe_cnt);
  for (int i = 0; i < Recipe_cnt; i++) {
    ss >> Recipe[i].time >> Recipe[i].nameBefore >> Recipe[i].operation >>
        Recipe[i].nameAfter;
  }

  /* 读入总帧数、当前采用的随机种子、一共可能出现的订单数量 */
  ss >> Frame_total >> randomizeSeed;

  ss >> OrderTable_cnt;
  /* 读入订单的有效帧数、价格、权重、订单组成 */
  OrderTable.resize(OrderTable_cnt);
  for (int i = 0; i < OrderTable_cnt; i++) {
    ss >> OrderTable[i].Frame_left >> OrderTable[i].price >>
        OrderTable[i].frequency;
    getline(ss, s);
    std::stringstream tmp(s);
    while (tmp >> s)
      OrderTable[i].require.push_back(s);
  }

  /* 读入玩家信息：初始坐标 */
  ss >> Player_cnt;
  assert(Player_cnt == 2);
  Player.resize(Player_cnt);
  for (int i = 0; i < Player_cnt; i++) {
    ss >> Player[i].coord.x >> Player[i].coord.y;
    Player[i].entity.container = Container_T::None;
    Player[i].entity.entity.clear();
  }

  /* 读入实体信息：坐标、实体组成 */
  ss >> Entity_cnt;
  Entity.resize(Entity_cnt);
  for (int i = 0; i < Entity_cnt; i++) {
    ss >> Entity[i].coord.x >> Entity[i].coord.y >> s;
    Entity[i].entity.push_back(s);
  }
}

void init() { read(); }
