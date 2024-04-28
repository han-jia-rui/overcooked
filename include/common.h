#ifndef ENUM_H
#define ENUM_H
#include <cassert>
#include <cctype>

enum class Container_T {
  None,
  Pan,
  Pot,
  Plate,
  DirtyPlates,
};

enum class Tile_T {
  None,
  Void,
  Floor,
  Wall,
  Table,
  IngredientBox,
  Trashbin,
  ChoppingStation,
  ServiceWindow,
  Stove,
  PlateReturn,
  Sink,
  PlateRack,
};

Tile_T getTileKind(char kindChar);

inline char getAbbrev(Tile_T kind);

#endif
