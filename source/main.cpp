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

    std::cout << "Frame " << i << "\n";

    Scheme1(Player[0]);
    Scheme2(Player[1]);

    std::string action =
        Player[0].action.toString() + '\n' + Player[1].action.toString() + '\n';
    std::cout << action;

    std::cerr.flush();
    std::cout.flush();
  }
}
