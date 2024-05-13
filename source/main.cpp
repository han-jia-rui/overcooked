#include <action.h>
#include <frame.h>
#include <init.h>
#include <iostream>
#include <task.h>

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

    if (Player[0].live == 0)
      prepareOrder(Player[0], Order[0]);
    if (Player[1].live == 0)
      washPlate(Player[1]);

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    string action =
        Player[0].action.toString() + '\n' + Player[1].action.toString() + '\n';
    cout << action;

    cerr.flush();
    cout.flush();
  }
}
