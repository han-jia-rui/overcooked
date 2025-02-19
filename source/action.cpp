#include <action.h>
#include <iostream>
#include <string>

constexpr double Distance = 0.5;
constexpr double Acceleration = 25;
constexpr double Radius = 0.1;
constexpr double InteractDistance = 0.3;
// constexpr double Velocity = 0;

void setDirection(Player_T &player, Coordinate_T coord) {
  switch (coord.face) {
  case Direction::UP:
    player.action.direction += "D";
    break;
  case Direction::DOWN:
    player.action.direction += "U";
    break;
  case Direction::LEFT:
    player.action.direction += "R";
    break;
  case Direction::RIGHT:
    player.action.direction += "L";
    break;
  }
}

void Move(Player_T &player, Coordinate_T target) {
  player.action.set(Action_Kind::Move);
  Coordinate_T next = getNextPosition(player.coord, target);
  double x_stop = player.vx * player.vx / (2 * Acceleration) + Radius;
  double y_stop = player.vy * player.vy / (2 * Acceleration) + Radius;
  // Stop
  if (std::abs(player.coord.x - next.x) > Distance &&
      std::abs(player.coord.y - next.y) > Radius) {
    next.x = static_cast<int>(player.coord.x) + 0.5;
    next.y = static_cast<int>(player.coord.y) + 0.5;
  }
  if (std::abs(player.coord.y - next.y) > Distance &&
      std::abs(player.coord.x - next.x) > Radius) {
    next.x = static_cast<int>(player.coord.x) + 0.5;
    next.y = static_cast<int>(player.coord.y) + 0.5;
  }
  // std::cerr << "Player " << player.coord.x << " " << player.coord.y
            // << std::endl;
  // std::cerr << "Move " << next.x << " " << next.y << std::endl;
  // Set direction
  if (next.x - player.coord.x > x_stop) {
    player.action.direction += "R";
  }
  if (player.coord.x - next.x > x_stop) {
    player.action.direction += "L";
  }
  if (player.coord.y - next.y > y_stop) {
    player.action.direction += "U";
  }
  if (next.y - player.coord.y > y_stop) {
    player.action.direction += "D";
  }
  // std::cerr << player.action.toString() << std::endl;
}

void Pick(Player_T &player, Coordinate_T target) {
  Coordinate_T coord = getNearestPosition(target);
  if (player.coord.dist(coord) < InteractDistance) {
    player.action.set(Action_Kind::Pick);
    setDirection(player, coord);
    return;
  }
  Move(player, coord);
}

void Put(Player_T &player, Coordinate_T target) {
  if (player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(target);
  if (player.coord.dist(coord) < InteractDistance) {
    player.action.set(Action_Kind::Put);
    setDirection(player, coord);
    return;
  }
  Move(player, coord);
}

void Interact(Player_T &player, Coordinate_T target) {
  if (!player.entity.empty())
    return;
  Coordinate_T coord = getNearestPosition(target);
  if (player.coord.dist(coord) < InteractDistance) {
    player.action.set(Action_Kind::Interact);
    setDirection(player, coord);
    return;
  }
  Move(player, coord);
}
