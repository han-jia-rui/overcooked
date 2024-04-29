#include <common.h>
#include <frame.h>
#include <init.h>
#include <iostream>
#include <motion.h>

int main() {
  ios::sync_with_stdio(false);
  cerr.tie(nullptr);
  cerr << std::nounitbuf;

  init();

  for (int i = 0; i < Frame_total; i++) {
    frame_update(i);

    /* 输出当前帧的操作，此处仅作示例 */
    cout << "Frame " << i << "\n";
    Player[0].action = "";
    Player[1].action = "";
    if (Player[0].entity.container == Container_T::Plate &&
        Player[0].entity.name.size() > 1)
      Put(Player[0], ServiceWindow.coord);
    else {
      for (auto entity : Entity) {
        if (entity.container == Container_T::Plate && entity.name.size() > 1) {
          Pick(Player[0], entity.coord);
          break;
        }
      }
    }
    if (Player[0].action == "" && Player[0].entity.name.empty())
      Pick(Player[0], Ingredient[0].coord);
    else if (Player[0].action == "") {
      for (auto entity : Entity) {
        if (entity.container == Container_T::Plate && entity.name.size() == 1) {
          Put(Player[0], entity.coord);
          break;
        }
      }
    }

    if (Player[1].action == "" && Player[1].entity.name.empty()) {
      for (auto entity : Entity) {
        if (entity.container == Container_T::DirtyPlates &&
            entity.name.size() == 1 && entity.coord.x == Sink.coord.x &&
            Sink.coord.y == entity.coord.y) {
          Interact(Player[1], entity.coord);
          break;
        }
      }

    } else if(Player[1].action == "") {
      for (auto entity : Entity) {
        if (entity.container == Container_T::DirtyPlates &&
            entity.name.size() == 1) {
          Pick(Player[1], entity.coord);
          break;
        }
      }
    } else if (Player[1].action == "") {
      Put(Player[1], Sink.coord);
    }

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    string action = Player[0].action + '\n' + Player[1].action + '\n';
    cout << action;

    /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
    cout.flush();
  }
}
