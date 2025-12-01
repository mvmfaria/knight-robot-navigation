#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

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

class Storage {
private:
    int height;
    int width;
    Coordinate target;
    std::vector<Cell> grid;

public:
    Storage(int h, int w, Coordinate target) : height(h), width(w), target(target), grid(h * w, Cell::EMPTY) {
        if (isValid(target)) {
            SetCell(getIndex(target), Cell::TARGET);
        }
    }

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    Coordinate getTarget() const {
        return target;
    }

    int getIndex(Coordinate coord) const {
        return coord.y * width + coord.x; 
    }

    Cell getCell(int pos) const {
        return grid[pos];
    }

    void SetCell(int pos, Cell value) {
        grid[pos] = value;
    }

    bool isValid(Coordinate coord) const {
        if (coord.x < 0 || coord.x > getWidth() - 1) {
            return false;
        }

        if (coord.y < 0 || coord.y > getHeight() - 1) {
            return false;
        }

        if (getCell(getIndex(coord)) == Cell::OBSTACLE) {
            return false;
        }

        return true;
    }

};

class Robot {
private:
    int x;
    int y;

public:
    Robot(int initialX, int initialY) : x(initialX), y(initialY) {}

    Coordinate getPosition() const {
        return {x, y};
    }

    static std::vector<Coordinate> getKnightMoves(Coordinate pos) {
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

    // double getEuclideanDistanceTo(Coordinate begin, Coordinate end) {
    //     return sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2));
    // }

    // bool isAtTarget(Coordinate target) {
    //     return (x == target.x && y == target.y);
    // }

    void moveTo(Coordinate coord) {
        this->x = coord.x;
        this->y = coord.y;
    }
};

Coordinate getCoordinateFromIndex(int index, int width) {
    return {index % width, index / width};
}

std::vector<Coordinate> bfs(const Storage& storage, const Robot& robot) {
    int size = storage.getWidth() * storage.getHeight();
    Coordinate target = storage.getTarget();
    
    std::vector<bool> visited(size, false);
    std::vector<int> parent(size, -1);

    std::queue<Coordinate> q;

    int startIndex = storage.getIndex(robot.getPosition());
    q.push(robot.getPosition());
    visited[startIndex] = true;

    bool found = false;

    while (!q.empty()) {
        Coordinate current = q.front();
        q.pop();

        if (current == target) {
            found = true;
            break;
        }

        int currentIndex = storage.getIndex(current);

        std::vector<Coordinate> moves = robot.getKnightMoves(current);
        for (const auto& next : moves) {
            if (storage.isValid(next)) {
                int nextIndex = storage.getIndex(next);
                
                if (!visited[nextIndex]) {
                    visited[nextIndex] = true;
                    parent[nextIndex] = currentIndex;
                    q.push(next);
                }
            }
        }
    }

    std::vector<Coordinate> path;
    if (found) {
        int currentIdx = storage.getIndex(target);
        int startIdx = storage.getIndex(robot.getPosition());
        
        while (currentIdx != startIdx) {
            path.push_back(getCoordinateFromIndex(currentIdx, storage.getWidth()));
            currentIdx = parent[currentIdx];
        }
        path.push_back(robot.getPosition());
        std::reverse(path.begin(), path.end());
    }

    return path;
}

int main() {
    Coordinate target = {7, 7}; 
    Storage storage(8, 8, target);
    
    storage.SetCell(storage.getIndex({5, 5}), Cell::OBSTACLE);

    Coordinate start = {0, 0};
    Robot robot = Robot(start.x, start.y);

    std::cout << "Calculando rota de (" << start.x << "," << start.y << ") para (" 
              << target.x << "," << target.y << ")..." << std::endl;

    std::vector<Coordinate> path = bfs(storage, robot);

    if (path.empty()) {
        std::cout << "Nenhum caminho encontrado ou ja esta no alvo!" << std::endl;
    } else {
        std::cout << "Caminho encontrado com " << path.size() - 1 << " passos: " << std::endl;
        
        for (const auto& step : path) {
            robot.moveTo(step);
            std::cout << "(" << step.x << ", " << step.y << ")" << std::endl;
        }
    }

    return 0;
}