#pragma once

enum class Cell {
    EMPTY,
    OBSTACLE,
    TARGET
};

struct Coordinate {
    int x; 
    int y; 

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }
};