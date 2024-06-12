#ifndef ENUM_H
#define ENUM_H

#include <string>

enum class Container_Kind {
  None,
  Pan,         // 煎锅
  Pot,         // 煮锅
  Plate,       // 盘子
  DirtyPlates, // 脏盘子
};

enum class Action_Kind {
  None,
  Move,
  Pick,
  Put,
  Interact,
};

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

enum class Operation_Kind {
  Chop, // 切菜
  Pan,  // 煎
  Pot,  // 煮
};

enum class Tile_Kind {
  Void,            // 悬崖
  Floor,           // 地板
  Wall,            // 墙
  Table,           // 工作台
  IngredientBox,   // 食材箱
  Trashbin,        // 垃圾箱
  ChoppingStation, // 切菜台
  ServiceWindow,   // 出菜口
  Stove,           // 灶台
  PlateReturn,     // 盘子回收口
  Sink,            // 洗碗台
  PlateRack,       // 盘子架
};

Tile_Kind char2tile(char ch);
std::string action2str(Action_Kind action);
Container_Kind str2container(const std::string s);
std::string operation2str(Operation_Kind operation);

#endif
