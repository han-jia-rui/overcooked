#include <action.h>
#include <frame.h>
#include <init.h>
#include <iostream>
#include <task.h>

int main() {
  std::ios::sync_with_stdio(false);
  std::cerr.tie(nullptr);
  std::cerr << std::nounitbuf;

  init();

  for (int i = 0; i < Frame_total; i++) {
    frame_update(i);

    /* 输出当前帧的操作，此处仅作示例 */
    std::cout << "Frame " << i << "\n";
    Player[0].action.clear();
    Player[1].action.clear();

    if (Player[0].live == 0)
      Scheme1(Player[0]);
    if (Player[1].live == 0)
      Scheme2(Player[1]);

    /* 合成一个字符串再输出，否则输出有可能会被打断 */
    std::string action =
        Player[0].action.toString() + '\n' + Player[1].action.toString() + '\n';
    std::cout << action;

    std::cerr.flush();
    std::cout.flush();
  }
}
