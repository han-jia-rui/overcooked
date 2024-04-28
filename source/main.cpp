#include <frame.h>
#include <init.h>
#include <move.h>
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
    string player0_Action = move(Player[0], 9, 9);
    string player1_Action = "Move D";

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    string action = player0_Action + '\n' + player1_Action + '\n';
    cout << action;

    /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
    cout.flush();
  }
}
