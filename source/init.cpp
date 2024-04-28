#include <common.h>
#include <init.h>
#include <iostream>
#include <sstream>

Map_T Map;
int Ingredient_cnt;
vector<Ingredient_T> Ingredient;
int Recipe_cnt;
vector<Recipe_T> Recipe;
int totalTime, randomizeSeed, totalOrderCount;
struct Order_T totalOrder[20 + 5];
int orderCount;
struct Order_T Order[20 + 5];
int k;
struct Player_T Players[2 + 5];
int entityCount;
struct Entity_T Entity[20 + 5];
int remainFrame, Fund;

void init_read() {
  string s;
  int frame;

  /* 读取初始地图信息 */
  getline(std::cin, s, '\0');
  stringstream ss(s);

  ss >> Map.width >> Map.height;
  cerr << "Map size: " << Map.width << "x" << Map.height << endl;
  for (int i = 0; i < Map.height; i++)
    for (int j = 0; j < Map.width; j++)
      ss >> Map.map[i][j];

  /* 读入原料箱：位置、名字、以及采购单价 */
  ss >> Ingredient_cnt;
  Ingredient.reserve(Ingredient_cnt);
  for (int i = 0; i < Ingredient_cnt; i++) {
    // ss >> s;
  //   assert(s == "IngredientBox");
  //   ss >> Ingredient[i].x >> Ingredient[i].y >> Ingredient[i].name >>
  //       Ingredient[i].price;
  }
  //
  // /* 读入配方：加工时间、加工前的字符串表示、加工容器、加工后的字符串表示 */
  // ss >> Recipe_cnt;
  // Recipe.reserve(Recipe_cnt);
  // for (int i = 0; i < Recipe_cnt; i++) {
  //   ss >> Recipe[i].time >> Recipe[i].nameBefore >> Recipe[i].operation >>
  //       Recipe[i].nameAfter;
  // }
  //
  // /* 读入总帧数、当前采用的随机种子、一共可能出现的订单数量 */
  // ss >> totalTime >> randomizeSeed >> totalOrderCount;
  //
  // /* 读入订单的有效帧数、价格、权重、订单组成 */
  // for (int i = 0; i < totalOrderCount; i++) {
  //   ss >> totalOrder[i].validFrame >> totalOrder[i].price >>
  //       totalOrder[i].frequency;
  //   getline(ss, s);
  //   std::stringstream tmp(s);
  //   while (tmp >> s)
  //     totalOrder[i].recipe.push_back(s);
  // }
  //
  // /* 读入玩家信息：初始坐标 */
  // ss >> k;
  // assert(k == 2);
  // for (int i = 0; i < k; i++) {
  //   ss >> Players[i].x >> Players[i].y;
  //   Players[i].containerKind = Container_T::None;
  //   Players[i].entity.clear();
  // }
  //
  // /* 读入实体信息：坐标、实体组成 */
  // ss >> entityCount;
  // for (int i = 0; i < entityCount; i++) {
  //   ss >> Entity[i].x >> Entity[i].y >> s;
  //   Entity[i].entity.push_back(s);
  // }
}

bool frame_read(int nowFrame) {
  string s;
  stringstream ss;
  int frame;
  std::getline(std::cin, s, '\0');
  ss.str(s);
  /*
    如果输入流中还有数据，说明游戏已经在请求下一帧了
    这时候我们应该跳过当前帧，以便能够及时响应游戏。
  */
  if (std::cin.rdbuf()->in_avail() > 0) {
    std::cerr << "Warning: skipping frame " << nowFrame
              << " to catch up with the game" << std::endl;
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
  ss >> orderCount;
  for (int i = 0; i < orderCount; i++) {
    ss >> Order[i].validFrame >> Order[i].price;
    Order[i].recipe.clear();
    getline(ss, s);
    std::stringstream tmp(s);
    while (tmp >> s) {
      Order[i].recipe.push_back(s);
    }
  }
  ss >> k;
  assert(k == 2);
  /* 读入玩家坐标、x方向速度、y方向速度、剩余复活时间 */
  for (int i = 0; i < k; i++) {
    ss >> Players[i].x >> Players[i].y >> Players[i].X_Velocity >>
        Players[i].Y_Velocity >> Players[i].live;
    getline(ss, s);
    std::stringstream tmp(s);
    Players[i].containerKind = Container_T::None;
    Players[i].entity.clear();
    while (tmp >> s) {
      /*
          若若该玩家手里有东西，则接下来一个分号，分号后一个空格，空格后为一个实体。
          以下是可能的输入（省略前面的输入）：
           ;  : fish
           ; @  : fish
           ; @ Plate : fish
           ; Plate
           ; DirtyPlates 1
          ...
      */

      /* 若你不需要处理这些，可直接忽略 */
      if (s == ";" || s == ":" || s == "@" || s == "*")
        continue;

      /*
          Todo: 其他容器
      */
      if (s == "Plate")
        Players[i].containerKind = Container_T::Plate;
      else if (s == "DirtyPlates")
        Players[i].containerKind = Container_T::DirtyPlates;
      else
        Players[i].entity.push_back(s);
    }
  }

  ss >> entityCount;
  /* 读入实体坐标 */
  for (int i = 0; i < entityCount; i++) {
    ss >> Entity[i].x >> Entity[i].y;
    getline(ss, s);
    std::stringstream tmp(s);
    Entity[i].containerKind = Container_T::None;
    Entity[i].entity.clear();
    Entity[i].currentFrame = Entity[i].totalFrame = 0;
    Entity[i].sum = 1;
    while (tmp >> s) {
      /*
          读入一个实体，例子：
          DirtyPlates 2
          fish
          DirtyPlates 1 ; 15 / 180

      */

      /* 若你不需要处理这些，可直接忽略 */
      if (s == ":" || s == "@" || s == "*")
        continue;
      if (s == ";") {
        tmp >> Entity[i].currentFrame >> s >> Entity[i].totalFrame;
        assert(s == "/");
        break;
      }

      /*
          Todo: 其他容器
      */
      if (s == "Plate")
        Entity[i].containerKind = Container_T::Plate;
      else if (s == "DirtyPlates") {
        Entity[i].containerKind = Container_T::DirtyPlates;
        tmp >> Entity[i].sum;
      } else
        Entity[i].entity.push_back(s);
    }
  }
  return false;
}
