#include "Storage.h"

Storage::Storage(int h, int w, Coordinate target, std::vector<Coordinate>& obstacles) : height(h), width(w), target(target), grid(h * w, Cell::EMPTY) {
    if (isValid(target)) {
        setCell(target, Cell::TARGET);
    }

    for (const auto& obs : obstacles) {
        if (isValid(obs) && obs != target) {
            setCell(obs, Cell::OBSTACLE);
        }
    }
}

int Storage::getHeight() const {
    return height;
}

int Storage::getWidth() const {
    return width;
}

int Storage::getSize() const {
    return height * width;
}

Coordinate Storage::getTarget() const {
    return target;
}

int Storage::getIndex(Coordinate coord) const {
    return coord.y * width + coord.x; 
}

Cell Storage::getCell(Coordinate coord) const {
    return grid[getIndex(coord)];
}

void Storage::setCell(Coordinate coord, Cell value) {
    grid[getIndex(coord)] = value;
}

bool Storage::isValid(Coordinate coord) const {
    if (coord.x < 0 || coord.x > getWidth() - 1) {
        return false;
    }

    if (coord.y < 0 || coord.y > getHeight() - 1) {
        return false;
    }

    if (getCell(coord) == Cell::OBSTACLE) {
        return false;
    }

    return true;
}