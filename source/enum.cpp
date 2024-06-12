#include <common.h>
#include <cstring>
#include <enum.h>

Tile_Kind char2tile(const char ch) {
  if (isalpha(ch) && isupper(ch)) {
    return Tile_Kind::IngredientBox;
  } else {
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
}

std::string action2str(const Action_Kind action) {
  std::string str;
  switch (action) {
  case Action_Kind::Move:
    str = "Move";
    break;
  case Action_Kind::Pick:
    str = "PutOrPick";
    break;
  case Action_Kind::Put:
    str = "PutOrPick";
    break;
  case Action_Kind::Interact:
    str = "Interact";
    break;
  default:
    str = "";
    break;
  }
  return str;
}

Container_Kind str2container(const std::string s) {
  Container_Kind container;
  if (s == "Plate")
    container = Container_Kind::Plate;
  else if (s == "Pan")
    container = Container_Kind::Pan;
  else if (s == "Pot")
    container = Container_Kind::Pot;
  else if (s == "DirtyPlates")
    container = Container_Kind::DirtyPlates;
  else
    container = Container_Kind::None;
  return container;
}

Operation_Kind str2operation(const std::string s) {
  Operation_Kind operation;
  if (s == "-chop->") {
    operation = Operation_Kind::Chop;
  } else if (s == "-pan->") {
    operation = Operation_Kind::Pan;
  } else if (s == "-pot->") {
    operation = Operation_Kind::Pot;
  } else {
    assert(0);
  }
  return operation;
}

std::string container2str(const Container_Kind container) {
  std::string str;
  switch (container) {
  case Container_Kind::Plate:
    str = "Plate";
    break;
  case Container_Kind::Pan:
    str = "Pan";
    break;
  case Container_Kind::Pot:
    str = "Pot";
    break;
  case Container_Kind::DirtyPlates:
    str = "DirtyPlates";
    break;
  default:
    str = "None";
    break;
  }
  return str;
}
