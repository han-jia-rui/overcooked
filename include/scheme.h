#ifndef SCHEME_H
#define SCHEME_H

#include <common.h>
#include <task.h>

#define CheckAlive                                                             \
  do {                                                                         \
    if (player.live != 0)                                                      \
      return;                                                                  \
  } while (0)

void Scheme1(Player_T &player);
void Scheme2(Player_T &player);

#endif // !SCHEME_H
