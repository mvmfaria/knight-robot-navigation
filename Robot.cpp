#include "Robot.h"

Robot::Robot(Coordinate initial) : position(initial) {}

Coordinate Robot::getPosition() const {
    return position;
}

std::vector<Coordinate> Robot::getKnightMoves(Coordinate pos) {
    return {
        {pos.x + 1, pos.y + 2},
        {pos.x + 1, pos.y - 2},
        {pos.x - 1, pos.y + 2},
        {pos.x - 1, pos.y - 2},
        {pos.x + 2, pos.y + 1},
        {pos.x + 2, pos.y - 1},
        {pos.x - 2, pos.y + 1},
        {pos.x - 2, pos.y - 1}
    };
}