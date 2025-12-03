#include <iostream>
#include <exception>
#include "Types.h"
#include "Storage.h"
#include "Robot.h"
#include "Search.h"
#include "Helper.h"

int main() {
    try {
        Input level = Reader::load("exemplo.txt");

        Storage storage(level.height, level.width, level.target, level.obstacles);
        
        Robot robot(level.start);

        std::vector<int> parents = bfs(storage, robot);
        
        std::vector<Coordinate> solution = path(storage, parents, robot.getPosition(), level.target);

        Reader::save("solucao.txt", solution);

        std::cout << "Solução salva em: solucao.txt" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Algo deu errado: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}