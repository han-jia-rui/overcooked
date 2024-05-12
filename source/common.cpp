#include <common.h>

static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

Coordinate_T getNearestPosition(int ix, int iy) {
  Coordinate_T ret;
  if (map[ix][iy] == Tile_Kind::Floor) {
    ret.x = double(ix) + 0.5;
    ret.y = double(iy) + 0.5;
    ret.face = Direction(0);
    return ret;
  } else {
    for (int i = 0; i < 4; i++) {
      int nx = ix + dx[i], ny = iy + dy[i];
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        if (map[nx][ny] == Tile_Kind::Floor) {
          ret.x = double(nx) + 0.5;
          ret.y = double(ny) + 0.5;
          ret.face = Direction(i);
          return ret;
        }
      }
    }
  }
  assert(0);
}

Tile_Kind getTileKind(char ch) {
  if (isalpha(ch) && isupper(ch))
    return Tile_Kind::IngredientBox;
  else
    switch (ch) {
    case '_':
      return Tile_Kind::Void;
    case '.':
      return Tile_Kind::Floor;
    case '*':
      return Tile_Kind::Table;
    case 't':
      return Tile_Kind::Trashbin;
    case 'c':
      return Tile_Kind::ChoppingStation;
    case '$':
      return Tile_Kind::ServiceWindow;
    case 's':
      return Tile_Kind::Stove;
    case 'p':
      return Tile_Kind::PlateReturn;
    case 'k':
      return Tile_Kind::Sink;
    case 'r':
      return Tile_Kind::PlateRack;
    default:
      assert(0);
    }
}

// char getAbbrev(Tile_Kind kind) {
//   switch (kind) {
//   case Tile_Kind::IngredientBox:
//     return 'i';
//   case Tile_Kind::Trashbin:
//     return 't';
//   case Tile_Kind::ChoppingStation:
//     return 'c';
//   case Tile_Kind::ServiceWindow:
//     return '$';
//   case Tile_Kind::Stove:
//     return 's';
//   case Tile_Kind::PlateReturn:
//     return 'p';
//   case Tile_Kind::Sink:
//     return 'k';
//   case Tile_Kind::PlateRack:
//     return 'r';
//   default:
//     assert(0);
//   }
// }
