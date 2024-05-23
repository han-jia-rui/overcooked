#include <algorithm>
#include <common.h>
#include <cstring>
#include <queue>
#include <sstream>

static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
struct node {
  int x, y;
  node() : x(0), y(0) {} // default constructor

  node(int x, int y) : x(x), y(y) {}

  node &operator+=(const node &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  bool operator==(const node &rhs) const { return x == rhs.x && y == rhs.y; }

  bool bound(int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
  }

  int direction(const node &rhs) const {
    if (x == rhs.x) {
      return 0;
    } else if (y == rhs.y) {
      return 1;
    }
    return -1;
  }
};
static node dir[4] = {node(0, -1), node(0, 1), node(-1, 0), node(1, 0)};

node bfs(node start, node end) {
  int vis[100][100];
  node pred[100][100]; // predecessor map
  memset(vis, 0, sizeof(vis));
  queue<node> q;
  q.push(start);
  while (!q.empty()) {
    node cur = q.front();
    q.pop();
    if (cur.x == end.x && cur.y == end.y) {
      break;
    }
    for (int i = 0; i < 4; i++) {
      node next = cur;
      next += dir[i];
      if (next.bound(width, height) && !vis[next.x][next.y] &&
          map[next.x][next.y]) {
        vis[next.x][next.y] = vis[cur.x][cur.y] + 1;
        pred[next.x][next.y] = cur; // record the predecessor
        q.push(next);
      }
    }
  }
  if (!vis[end.x][end.y]) {
    return start;
  }
  // Get the first change of direction
  vector<node> path;
  for (node at = end; at != start; at = pred[at.x][at.y]) {
    path.push_back(at);
  }
  reverse(path.begin(), path.end());
  for (int i = 0; i < path.size(); i++) {
    if (start.direction(path[i]) == -1) {
      return path[i - 1];
    }
  }
  return path.back();
}

Coordinate_T getNextPosition(Coordinate_T st, Coordinate_T ed) {
  node start(st.x, st.y), end(ed.x, ed.y);
  if (start == end)
    return ed;
  node tmp;
  tmp = bfs(start, end);
  assert(tmp.direction(start) != -1);
  Coordinate_T ret;
  ret = Coordinate_T(static_cast<double>(tmp.x + 0.5),
                     static_cast<double>(tmp.y + 0.5));
  return ret;
}

Coordinate_T getNearestPosition(Coordinate_T coord) {
  Coordinate_T ret;
  node pos(coord.x, coord.y);
  int ix = coord.x, iy = coord.y;
  if (Map[ix][iy] == Tile_Kind::Floor) {
    ret.x = static_cast<double>(ix) + 0.5;
    ret.y = static_cast<double>(iy) + 0.5;
    ret.face = Direction(0);
    return ret;
  } else {
    for (int i = 0; i < 4; i++) {
      int nx = ix + dx[i], ny = iy + dy[i];
      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        if (Map[nx][ny] == Tile_Kind::Floor) {
          ret.x = static_cast<double>(nx) + 0.5;
          ret.y = static_cast<double>(ny) + 0.5;
          ret.face = Direction(i);
          return ret;
        }
      }
    }
  }
  assert(0);
}

Tile_Kind getTileKind(char ch) {
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
}

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
    else {
      if (s == "DirtyPlates") {
        container = Container_Kind::DirtyPlates;
        tmp >> sum;
      } else {
        food.push_back(s);
      }
    }
  }
}
