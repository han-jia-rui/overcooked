#include <cassert>
#include <common.h>
#include <iostream>

Tile_T getTileKind(char ch) {
  if (isalpha(ch) && isupper(ch))
    return Tile_T::IngredientBox;
  else
    switch (ch) {
    case '_':
      return Tile_T::Void;
    case '.':
      return Tile_T::Floor;
    case '*':
      return Tile_T::Table;
    case 't':
      return Tile_T::Trashbin;
    case 'c':
      return Tile_T::ChoppingStation;
    case '$':
      return Tile_T::ServiceWindow;
    case 's':
      return Tile_T::Stove;
    case 'p':
      return Tile_T::PlateReturn;
    case 'k':
      return Tile_T::Sink;
    case 'r':
      return Tile_T::PlateRack;
    default:
      cerr << "Wrong Char :" << ch << endl;
      assert(0);
    }
  assert(0);
}

char getAbbrev(Tile_T kind) {
  switch (kind) {
  case Tile_T::IngredientBox:
    return 'i';
  case Tile_T::Trashbin:
    return 't';
  case Tile_T::ChoppingStation:
    return 'c';
  case Tile_T::ServiceWindow:
    return '$';
  case Tile_T::Stove:
    return 's';
  case Tile_T::PlateReturn:
    return 'p';
  case Tile_T::Sink:
    return 'k';
  case Tile_T::PlateRack:
    return 'r';
  default:
    assert(0);
  }
  assert(0);
}
