#include "Reader.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
    
Input Reader::load(const std::string& filename) {
    std::ifstream arquivo(filename);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + filename);
    }

    Input data;
    int obstacleCount;

    arquivo >> data.height >> data.width;
    arquivo >> data.start.x >> data.start.y;
    arquivo >> data.target.x >> data.target.y;
    arquivo >> obstacleCount;

    for (int i = 0; i < obstacleCount; ++i) {
        Coordinate obs;
        arquivo >> obs.x >> obs.y;
        data.obstacles.push_back(obs);
    }

    arquivo.close();
    return data;
}