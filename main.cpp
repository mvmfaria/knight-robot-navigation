#include <iostream>
#include "Types.h"
#include "Storage.h"
#include "Robot.h"
#include "Search.h"

int main() {
    Coordinate target = {7, 7}; 
    Storage storage(8, 8, target);

    Coordinate start = {0, 0};
    Robot robot(start);

    std::vector<int> parentMap = bfs(storage, robot);

    std::cout << "Test" << std::endl;

    return 0;
}