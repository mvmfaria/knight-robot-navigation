#pragma once
#include <vector>
#include "Types.h"
#include "Storage.h"
#include "Robot.h"
    
std::vector<int> bfs(const Storage& storage, const Robot& robot);

std::vector<Coordinate> path(const Storage& storage, const std::vector<int>& parents, Coordinate start, Coordinate target);