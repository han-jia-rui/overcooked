#include <common.h>
#include <frame.h>
#include <iostream>
#include <sstream>

int Order_cnt;
vector<Order_T> Order;
int Sales;

static void Order_update(stringstream &ss) {
  string s;
  ss >> Order_cnt;
  Order.resize(Order_cnt);
  for (int i = 0; i < Order_cnt; i++) {
    ss >> Order[i].Frame_left >> Order[i].price;
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
    Player[i].entity.container = Container_T::None;
    Player[i].entity.entity.clear();
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
      if (s == ";" || s == "@" || s == "*" || s == ":")
        continue;
      Player[i].entity.entity.push_back(s);
    }
  }
}

static void Entity_update(stringstream &ss) {
  string s;
  ss >> Entity_cnt;
  /* 读入实体坐标 */
  for (int i = 0; i < Entity_cnt; i++) {
    ss >> Entity[i].coord.x >> Entity[i].coord.y;
    getline(ss, s);
    std::stringstream tmp(s);
    Entity[i].container = Container_T::None;
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

      if (s == ":" || s == "@" || s == "*")
        continue;

      if (s == ";") {
        tmp >> Entity[i].currentFrame >> s >> Entity[i].totalFrame;
        assert(s == "/");
        break;
      }

      Entity[i].entity.push_back(s);

      if (s == "Plate")
        Entity[i].container = Container_T::Plate;
      else if (s == "Pan")
        Entity[i].container = Container_T::Pan;
      else if (s == "Pot")
        Entity[i].container = Container_T::Pot;
      else if (s == "DirtyPlates") {
        Entity[i].container = Container_T::DirtyPlates;
        tmp >> Entity[i].sum;
      }
    }
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
