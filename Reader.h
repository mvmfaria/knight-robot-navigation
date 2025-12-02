#pragma once
#include <string>
#include <vector>
#include "Types.h"

struct Input {
    int height;
    int width;
    Coordinate start;
    Coordinate target;
    std::vector<Coordinate> obstacles;
};

class Reader {
public:
    static Input load(const std::string& filename);
};