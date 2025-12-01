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