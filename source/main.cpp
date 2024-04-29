#include <frame.h>
#include <init.h>
#include <motion.h>
#include <iostream>
#include <common.h>

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
    if(Player[0].entity.empty())
    Pick(Player[0], Ingredient[0].coord);
    else {
      for(auto entity : Entity){
        if(entity.container == Container_T::Plate && entity.entity.size() == 1){
          Put(Player[0], entity.coord);
          break;
        }
      }
    }

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    string action = Player[0].action + '\n' + Player[1].action + '\n';
    cout << action;

    /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
    cout.flush();
  }
}
