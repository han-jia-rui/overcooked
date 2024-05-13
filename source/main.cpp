#include <action.h>
#include <frame.h>
#include <init.h>
#include <task.h>
#include <iostream>

int main() {
  ios::sync_with_stdio(false);
  cerr.tie(nullptr);
  cerr << std::nounitbuf;

  init();

  for (int i = 0; i < Frame_total; i++) {
    frame_update(i);

    /* 输出当前帧的操作，此处仅作示例 */
    cout << "Frame " << i << "\n";
    Player[0].action.clear();
    Player[1].action.clear();
    Tile_T ServiceWindow = getTile(Tile_Kind::ServiceWindow, Coordinate_T());
    if (Player[0].entity.container == Container_Kind::Plate &&
        Player[0].entity.food.size() > 0)
      Put(Player[0], ServiceWindow.coord);
    else {
      for (auto entity : Entity) {
        if (entity.container == Container_Kind::Plate &&
            entity.food.size() > 0) {
          Pick(Player[0], entity.coord);
          break;
        }
      }
    }
    if (Player[0].action.empty() && Player[0].entity.food.empty()) {
      for (auto order : Order) {
        for (auto ingredient : Ingredient) {
          if (order.require[0] == ingredient.name)
            Pick(Player[0], ingredient.coord);
          if (!Player[0].action.empty())
            break;
        }
        if (!Player[0].action.empty())
          break;
      }
    } else if (Player[0].action.empty()) {
      for (auto entity : Entity) {
        if (entity.container == Container_Kind::Plate &&
            entity.food.size() == 0) {
          Put(Player[0], entity.coord);
          break;
        }
      }
    }

    washPlate(Player[1]);

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    string action =
        Player[0].action.toString() + '\n' + Player[1].action.toString() + '\n';
    cout << action;

    cerr.flush();
    cout.flush();
  }
}
