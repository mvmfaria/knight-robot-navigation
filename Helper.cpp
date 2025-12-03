#include "Helper.h"
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

void Reader::save(const std::string& filename, const std::vector<Coordinate>& path) {
    std::ofstream arquivo(filename);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi gerar o arquivo com a solução!");
    }

    if (path.empty()) {
        arquivo << "Para essa configuração, não é possível encontrar um caminho!" << std::endl;
        arquivo.close();
        return;
    }

    for (const auto& coord : path) {
        arquivo << coord.x << " " << coord.y << std::endl;
    }

    arquivo.close();
}