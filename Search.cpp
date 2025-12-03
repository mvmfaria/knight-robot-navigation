#include "Search.h"
#include <queue>
#include <algorithm>

std::vector<int> bfs(const Storage& storage, const Robot& robot) {
    int size = storage.getSize();
    std::vector<int> parents(size, -1);

    std::queue<Coordinate> q;

    Coordinate startNode = robot.getPosition();
    int startIndex = storage.getIndex(startNode);
    q.push(startNode);

    parents[startIndex] = startIndex;

    while (!q.empty()) {
        Coordinate currentNode = q.front();
        int currentIndex = storage.getIndex(currentNode);
        q.pop();

        if (storage.getCell(currentNode) == Cell::TARGET) {
            return parents;
        }
        
        std::vector<Coordinate> moves = Robot::getKnightMoves(currentNode);
        for (const auto& move : moves) {
            if (storage.isValid(move)) {
                int nextIndex = storage.getIndex(move);

                if (parents[nextIndex] == -1) {
                    parents[nextIndex] = currentIndex;
                    q.push(move);
                }
            }
        }
    }

    return parents;
}

std::vector<Coordinate> path(const Storage& storage, const std::vector<int>& parents, Coordinate start, Coordinate target) {
    std::vector<Coordinate> result;
    int targetIndex = storage.getIndex(target);
    int startIndex = storage.getIndex(start);

    if (parents[targetIndex] == -1) {
        return result;
    }

    for (int at = targetIndex; at != startIndex; at = parents[at]) {
        result.push_back(storage.getCoordinateFromIndex(at));
    }

    result.push_back(start);
    
    std::reverse(result.begin(), result.end());

    return result;
}