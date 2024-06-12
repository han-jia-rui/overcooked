#include <algorithm>
#include <cassert>
#include <common.h>
#include <cstring>
#include <queue>
#include <sstream>

static int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
static node dir[4] = {node(0, -1), node(0, 1), node(-1, 0), node(1, 0)};

node bfs(node start, node end) {
  int vis[100][100];
  node pred[100][100];
  memset(vis, 0, sizeof(vis));
  std::queue<node> q;
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
        pred[next.x][next.y] = cur;
        q.push(next);
      }
    }
  }
  if (!vis[end.x][end.y]) {
    return start;
  }
  // Get the first change of direction
  std::vector<node> path;
  for (node at = end; at != start; at = pred[at.x][at.y]) {
    path.push_back(at);
  }
  reverse(path.begin(), path.end());
  for (int i = 0; i < path.size(); i++) {
    map[path[i].x][path[i].y] = false;
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
  ret = Coordinate_T(static_cast<double>(tmp.x) + 0.5,
                     static_cast<double>(tmp.y) + 0.5);
  return ret;
}

Coordinate_T getNearestPosition(Coordinate_T coord) {
  Coordinate_T ret;
  node pos(coord.x, coord.y);
  int ix = coord.x, iy = coord.y;

  if (Map[ix][iy].movable()) {
    ret.x = static_cast<double>(ix) + 0.5;
    ret.y = static_cast<double>(iy) + 0.5;
    ret.face = Direction(0);
    return ret;
  }

  for (int i = 0; i < 4; i++) {
    int nx = ix + dx[i], ny = iy + dy[i];
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
      if (Map[nx][ny].movable()) {
        ret.x = static_cast<double>(nx) + 0.5;
        ret.y = static_cast<double>(ny) + 0.5;
        ret.face = Direction(i);
        return ret;
      }
    }
  }

  assert(0);
}

std::vector<Tile_T> getTile(Tile_Kind tile_kind) {
  std::vector<Tile_T> ret;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (Map[j][i].kind == tile_kind) {
        ret.push_back(Map[j][i]);
      }
    }
  }
  return ret;
}

Tile_T getFirstTile(Tile_Kind tile_kind) {
  std::vector<Tile_T> tmp = getTile(tile_kind);
  if (!tmp.empty())
    return tmp[0];
  assert(0);
  return Tile_T();
}

std::string Action_T::toString() {
  std::string ret = action2str(action);
  ret += " " + direction;
  return ret;
}

/*
Example Input:
    @ Plate : fish
    : fish
    DirtyPlates 1 ; 15 / 180
*/
void Entity_T::set(std::stringstream &ss) {
  this->clear();
  ss >> coord.x >> coord.y;
  std::string s;
  getline(ss, s);
  std::stringstream tmp(s);
  sum = 1;
  while (tmp >> s) {
    if (s == ";" || s == "@" || s == "*" || s == ":" || s == "/" ||
        isdigit(s[0]))
      continue;
    Container_Kind container_tmp = str2container(s);
    if (container_tmp != Container_Kind::None) {
      if (container_tmp == Container_Kind::DirtyPlates)
        tmp >> sum;
      container = container_tmp;
      continue;
    }
    food_list.insert(s);
  }
}

bool isTileUsed(Tile_T tile) {
  bool used = false;
  for (auto entity : Entity) {
    if (entity.coord == tile.coord) {
      used = true;
      break;
    }
  }
  return used;
}
