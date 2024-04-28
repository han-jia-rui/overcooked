#include <common.h>

static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

Coordinate_T getNearestPosition(int ix, int iy) {
  Coordinate_T ret;
  if (map[ix][iy] == Tile_T::Floor) {
    ret.x = double(ix) + 0.5;
    ret.y = double(iy) + 0.5;
    ret.face = Face_T(0);
    return ret;
  } else {
    for (int i = 0; i < 4; i++) {
      int nx = ix + dx[i], ny = iy + dy[i];
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        if (map[nx][ny] == Tile_T::Floor) {
          ret.x = double(nx) + 0.5;
          ret.y = double(ny) + 0.5;
          ret.face = Face_T(i);
          return ret;
        }
      }
    }
  }
  assert(0);
}

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
      assert(0);
    }
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
}
