#include <common.h>
#include <init.h>
#include <iostream>
#include <sstream>
#include <vector>

int width, height;
vector<vector<char>> map;
int Ingredient_cnt;
vector<Ingredient_T> Ingredient;
int Recipe_cnt;
vector<Recipe_T> Recipe;
int totalFrame, randomizeSeed;
int OrderTable_cnt;
vector<Order_T> OrderTable;
int Order_cnt;
vector<Order_T> Order;
int Player_cnt;
vector<Player_T> Player;
int Entity_cnt;
vector<Entity_T> Entity;
int remainFrame, Fund;

void init_read() {
  string s;
  int frame;

  /* 读取初始地图信息 */
  getline(std::cin, s, '\0');
  stringstream ss(s);

  ss >> width >> height;
  map.resize(height);
  for (int i = 0; i < height; i++) {
    map[i].resize(width);
    for (int j = 0; j < width; j++)
      ss >> map[i][j];
  }

  /* 读入原料箱：位置、名字、以及采购单价 */
  ss >> Ingredient_cnt;
  Ingredient.resize(Ingredient_cnt);
  for (int i = 0; i < Ingredient_cnt; i++) {
    ss >> s;
    assert(s == "IngredientBox");
    ss >> Ingredient[i].x >> Ingredient[i].y >> Ingredient[i].name >>
        Ingredient[i].price;
  }

  /* 读入配方：加工时间、加工前的字符串表示、加工容器、加工后的字符串表示 */
  ss >> Recipe_cnt;
  Recipe.resize(Recipe_cnt);
  for (int i = 0; i < Recipe_cnt; i++) {
    ss >> Recipe[i].time >> Recipe[i].nameBefore >> Recipe[i].operation >>
        Recipe[i].nameAfter;
  }

  /* 读入总帧数、当前采用的随机种子、一共可能出现的订单数量 */
  ss >> totalFrame >> randomizeSeed;

  ss >> OrderTable_cnt;
  /* 读入订单的有效帧数、价格、权重、订单组成 */
  OrderTable.resize(OrderTable_cnt);
  for (int i = 0; i < OrderTable_cnt; i++) {
    ss >> OrderTable[i].validFrame >> OrderTable[i].price >> OrderTable[i].frequency;
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
    ss >> Player[i].x >> Player[i].y;
    Player[i].containerKind = Container_T::None;
    Player[i].entity.clear();
  }

  /* 读入实体信息：坐标、实体组成 */
  ss >> Entity_cnt;
  Entity.resize(Entity_cnt);
  for (int i = 0; i < Entity_cnt; i++) {
    ss >> Entity[i].x >> Entity[i].y >> s;
    Entity[i].entity.push_back(s);
  }
}

bool frame_read(int nowFrame) {
  string s;
  stringstream ss;
  int frame;
  getline(cin, s, '\0');
  ss.str(s);
  /*
    如果输入流中还有数据，说明游戏已经在请求下一帧了
    这时候我们应该跳过当前帧，以便能够及时响应游戏。
  */
  if (cin.rdbuf()->in_avail() > 0) {
    cerr << "Warning: skipping frame " << nowFrame
              << " to catch up with the game" << endl;
    return true;
  }
  ss >> s;
  // cerr<< "string = " << s << endl;
  assert(s == "Frame");
  int currentFrame;
  ss >> currentFrame;
  assert(currentFrame == nowFrame);
  ss >> remainFrame >> Fund;
  /* 读入当前的订单剩余帧数、价格、以及配方 */
  // ss >> Order_cnt;
  // for (int i = 0; i < Order_cnt; i++) {
  //   ss >> Order[i].validFrame >> Order[i].price;
  //   Order[i].require.clear();
  //   getline(ss, s);
  //   std::stringstream tmp(s);
  //   while (tmp >> s) {
  //     Order[i].require.push_back(s);
  //   }
  // }
  // ss >> Player_cnt;
  // assert(Player_cnt == 2);
  // /* 读入玩家坐标、x方向速度、y方向速度、剩余复活时间 */
  // for (int i = 0; i < Player_cnt; i++) {
  //   ss >> Player[i].x >> Player[i].y >> Player[i].X_Velocity >>
  //       Player[i].Y_Velocity >> Player[i].live;
  //   getline(ss, s);
  //   std::stringstream tmp(s);
  //   Player[i].containerKind = Container_T::None;
  //   Player[i].entity.clear();
  //   while (tmp >> s) {
  //     /*
  //         若若该玩家手里有东西，则接下来一个分号，分号后一个空格，空格后为一个实体。
  //         以下是可能的输入（省略前面的输入）：
  //          ;  : fish
  //          ; @  : fish
  //          ; @ Plate : fish
  //          ; Plate
  //          ; DirtyPlates 1
  //         ...
  //     */
  //
  //     /* 若你不需要处理这些，可直接忽略 */
  //     if (s == ";" || s == ":" || s == "@" || s == "*")
  //       continue;
  //
  //     /*
  //         Todo: 其他容器
  //     */
  //     if (s == "Plate")
  //       Player[i].containerKind = Container_T::Plate;
  //     else if (s == "DirtyPlates")
  //       Player[i].containerKind = Container_T::DirtyPlates;
  //     else
  //       Player[i].entity.push_back(s);
  //   }
  // }
  //
  // ss >> Entity_cnt;
  // /* 读入实体坐标 */
  // for (int i = 0; i < Entity_cnt; i++) {
  //   ss >> Entity[i].x >> Entity[i].y;
  //   getline(ss, s);
  //   std::stringstream tmp(s);
  //   Entity[i].containerKind = Container_T::None;
  //   Entity[i].entity.clear();
  //   Entity[i].currentFrame = Entity[i].totalFrame = 0;
  //   Entity[i].sum = 1;
  //   while (tmp >> s) {
  //     /*
  //         读入一个实体，例子：
  //         DirtyPlates 2
  //         fish
  //         DirtyPlates 1 ; 15 / 180
  //
  //     */
  //
  //     /* 若你不需要处理这些，可直接忽略 */
  //     if (s == ":" || s == "@" || s == "*")
  //       continue;
  //     if (s == ";") {
  //       tmp >> Entity[i].currentFrame >> s >> Entity[i].totalFrame;
  //       assert(s == "/");
  //       break;
  //     }
  //
  //     /*
  //         Todo: 其他容器
  //     */
  //     if (s == "Plate")
  //       Entity[i].containerKind = Container_T::Plate;
  //     else if (s == "DirtyPlates") {
  //       Entity[i].containerKind = Container_T::DirtyPlates;
  //       tmp >> Entity[i].sum;
  //     } else
  //       Entity[i].entity.push_back(s);
  //   }
  // }
  return false;
}
