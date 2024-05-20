#include <cctype>
#include <frame.h>
#include <iostream>
#include <sstream>

int Order_cnt;
vector<Order_T> Order;
int Sales;

// 玩家可移动地图
bool map[100][100];
void updateMap() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (Map[i][j] == Tile_Kind::Floor)
        map[i][j] = true;
      else
        map[i][j] = false;
    }
  }
  for (auto player : Player) {
    if (player.live != 0)
      continue;
    map[(int)player.coord.y][(int)player.coord.x] = false;
  }
}

static void Order_update(stringstream &ss) {
  string s;
  ss >> Order_cnt;
  Order.clear();
  Order.resize(Order_cnt);
  for (int i = 0; i < Order_cnt; i++) {
    ss >> Order[i].frame_left >> Order[i].price;
    Order[i].require.clear();
    getline(ss, s);
    std::stringstream tmp(s);
    while (tmp >> s) {
      Order[i].require.push_back(s);
    }
  }
}

static void Player_update(stringstream &ss) {
  string s;
  ss >> Player_cnt;
  assert(Player_cnt == 2);
  for (int i = 0; i < Player_cnt; i++) {
    ss >> Player[i].coord.x >> Player[i].coord.y >> Player[i].vx >>
        Player[i].vy >> Player[i].live;
    getline(ss, s);
    stringstream tmp(s);
    Player[i].entity.clear();
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
    while (tmp >> s) {
      if (s == ";" || s == "@" || s == "*" || s == ":" || s == "/" ||
          isdigit(s[0]))
        continue;
      if (s == "Plate")
        Player[i].entity.container = Container_Kind::Plate;
      else if (s == "Pan")
        Player[i].entity.container = Container_Kind::Pan;
      else if (s == "Pot")
        Player[i].entity.container = Container_Kind::Pot;
      else if (s == "DirtyPlates") {
        Player[i].entity.container = Container_Kind::DirtyPlates;
        tmp >> Player[i].entity.sum;
      } else {
        Player[i].entity.food.push_back(s);
      }
    }
  }
}

static void Entity_update(stringstream &ss) {
  string s;
  ss >> Entity_cnt;
  Entity.clear();
  Entity.resize(Entity_cnt);
  for (int i = 0; i < Entity_cnt; i++) {
    Entity[i].set(ss);
  }
}

void frame_update(int Frame_cur) {
  string s;
  getline(cin, s, '\0');
  stringstream ss(s);

  if (cin.rdbuf()->in_avail() > 0) {
    cerr << "Warning: skipping frame " << Frame_cur
         << " to catch up with the game" << endl;
    assert(0);
  }

  ss >> s;
  assert(s == "Frame");
  int Frame_now;
  ss >> Frame_now;
  assert(Frame_now == Frame_cur);

  int Frame_remain;
  ss >> Frame_remain >> Sales;
  assert(Frame_remain + Frame_cur == Frame_total);

  Order_update(ss);

  Player_update(ss);

  Entity_update(ss);
}
