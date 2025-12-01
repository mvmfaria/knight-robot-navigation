#pragma once
#include <vector>
#include "Types.h"

class Storage {
private:
    int height;
    int width;
    Coordinate target;
    std::vector<Cell> grid;

public:
    Storage(int h, int w, Coordinate target);
    int getHeight() const;
    int getWidth() const;
    int getSize() const;
    Coordinate getTarget() const;
    int getIndex(Coordinate coord) const;
    Coordinate getCoordinateFromIndex(int index) const;
    Cell getCell(Coordinate coord) const;
    void setCell(int pos, Cell value);
    bool isValid(Coordinate coord) const;
};