#pragma once
#include <vector>
#include "Types.h"

class Robot {
private:
    Coordinate position;

public:
    Robot(Coordinate initial);
    Coordinate getPosition() const;
    
    static std::vector<Coordinate> getKnightMoves(Coordinate pos);
};