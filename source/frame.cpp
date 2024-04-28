#include <common.h>
#include <frame.h>
#include <iostream>
#include <sstream>

int Order_cnt;
vector<Order_T> Order;
int Grade;

void frame_update(int Frame_cur) {
  string s;
  stringstream ss;
  getline(cin, s, '\0');
  ss.str(s);
  /*
    如果输入流中还有数据，说明游戏已经在请求下一帧了
    这时候我们应该跳过当前帧，以便能够及时响应游戏。
  */
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
  ss >> Frame_remain >> Grade;
  assert(Frame_remain + Frame_cur == Frame_total);
  /* 读入当前的订单剩余帧数、价格、以及配方 */
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
  ss >> Player_cnt;
  assert(Player_cnt == 2);
  /* 读入玩家坐标、x方向速度、y方向速度、剩余复活时间 */
  for (int i = 0; i < Player_cnt; i++) {
    ss >> Player[i].x >> Player[i].y >> Player[i].vx >>
        Player[i].vy >> Player[i].live;
    getline(ss, s);
    stringstream tmp(s);
    Player[i].Container_hold = Container_T::None;
    Player[i].entity.clear();
    Player[i].entity.push_back(s);
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
  }

  ss >> Entity_cnt;
  /* 读入实体坐标 */
  for (int i = 0; i < Entity_cnt; i++) {
    ss >> Entity[i].x >> Entity[i].y;
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
        Entity[i].container = Container_T::Plate;
      else if (s == "DirtyPlates") {
        Entity[i].container = Container_T::DirtyPlates;
        tmp >> Entity[i].sum;
      } else
        Entity[i].entity.push_back(s);
    }
  }
}
