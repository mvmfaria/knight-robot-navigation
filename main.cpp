#include <iostream>
#include <exception>
#include "Types.h"
#include "Storage.h"
#include "Robot.h"
#include "Search.h"
#include "Reader.h"

int main() {
    try {
        Input level = Reader::load("exemplo.txt");

        Storage storage(level.height, level.width, level.target, level.obstacles);
        
        Robot robot(level.start);

        std::vector<int> parents = bfs(storage, robot);
        
        // Aqui você chamaria o buildPath...
        // std::vector<Coordinate> path = buildPath(storage, parents, robot.getPosition(), level.target);

        std::cout << "Solução salva em: ." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Algo deu errado: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}