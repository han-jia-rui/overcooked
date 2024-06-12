#include <cctype>
#include <frame.h>
#include <iostream>
#include <sstream>

std::vector<Order_T> Order;
int Sales;

// 玩家可移动地图
bool map[100][100];
void Map_update() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      map[i][j] = Map[i][j].movable();
    }
  }
  for (auto &player : Player) {
    if (player.live != 0)
      continue;
    int ix = static_cast<int>(player.coord.x);
    int iy = static_cast<int>(player.coord.y);
    map[ix][iy] = false;
  }
}

static void Order_update(std::stringstream &ss) {
  int Order_cnt;
  ss >> Order_cnt;
  Order.clear();
  Order.resize(Order_cnt);

  std::string s;
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

static void Player_update(std::stringstream &ss) {
  int Player_cnt;
  ss >> Player_cnt;
  assert(Player_cnt == 2);

  std::string s;
  for (auto &player : Player) {
    player.clear();
    ss >> player.coord.x >> player.coord.y >> player.vx >> player.vy >>
        player.live;
    getline(ss, s);
    std::stringstream tmp;
    tmp << player.coord.x << " " << player.coord.y << " " << s;
    player.entity.set(tmp);
  }
}

static void Entity_update(std::stringstream &ss) {
  int Entity_cnt;
  ss >> Entity_cnt;
  Entity.clear();
  Entity.resize(Entity_cnt);

  for (auto &entity : Entity) {
    entity.clear();
    entity.set(ss);
  }
}

void frame_update(int Frame_cur) {
  std::string s;
  getline(std::cin, s, '\0');
  std::stringstream ss(s);

  if (std::cin.rdbuf()->in_avail() > 0) {
    std::cerr << "Warning: skipping frame " << Frame_cur
              << " to catch up with the game" << std::endl;
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

  Map_update();
}
