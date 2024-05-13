#include <cassert>
#include <common.h>
#include <iostream>
#include <sstream>
#include <vector>

static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

Coordinate_T getNearestPosition(Coordinate_T coord) {
  Coordinate_T ret;
  int ix = coord.x, iy = coord.y;
  if (Map[ix][iy] == Tile_Kind::Floor) {
    ret.x = double(ix) + 0.5;
    ret.y = double(iy) + 0.5;
    ret.face = Direction(0);
    return ret;
  } else {
    for (int i = 0; i < 4; i++) {
      int nx = ix + dx[i], ny = iy + dy[i];
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        if (Map[nx][ny] == Tile_Kind::Floor) {
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

vector<Tile_T> getTile(Tile_Kind tile_kind, Coordinate_T coord) {
  vector<Tile_T> ret;
  Tile_T tmp;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (Map[j][i] == tile_kind) {
        tmp.tile_kind = tile_kind;
        tmp.coord.x = j;
        tmp.coord.y = i;
        ret.push_back(tmp);
      }
    }
  }
  return ret;
}

string Action_T::toString() {
  string ret;
  switch (action) {
  case Action_Kind::Move:
    ret = "Move";
    break;
  case Action_Kind::Pick:
    ret = "PutOrPick";
    break;
  case Action_Kind::Put:
    ret = "PutOrPick";
    break;
  case Action_Kind::Interact:
    ret = "Interact";
    break;
  default:
    ret = "";
    break;
  }
  ret += " " + direction;
  return ret;
};

void Entity_T::set(stringstream &ss) {
  this->clear();
  ss >> coord.x >> coord.y;
  string s;
  getline(ss, s);
  stringstream tmp(s);
  sum = 1;
  while (tmp >> s) {
    /*
        @ Plate : fish
        : fish
        DirtyPlates 1 ; 15 / 180
    */

    if (s == ":" || s == "@" || s == "*")
      continue;

    if (s == ";") {
      tmp >> frame_cur >> s >> frame_total;
      assert(s == "/");
      break;
    }

    if (s == "Plate")
      container = Container_Kind::Plate;
    else if (s == "Pan")
      container = Container_Kind::Pan;
    else if (s == "Pot")
      container = Container_Kind::Pot;
    else if (s == "DirtyPlates") {
      container = Container_Kind::DirtyPlates;
      tmp >> sum;
    } else {
      food.push_back(s);
    }
  }
}
