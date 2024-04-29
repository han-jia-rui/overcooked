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
    Pick(Player[0], Ingredient[0].coord);
    Move(Player[1], 1.5, 8);

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
  cerr << "player0 : " << Player[0].action << " player1 : " << Player[1].action << endl;
    string action = Player[0].action + '\n' + Player[1].action + '\n';
    cout << action;

    /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
    cout.flush();
  }
}
