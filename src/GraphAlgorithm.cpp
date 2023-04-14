// A part of Prim's Algorithm Visualizer program
// Copyright (C) 2023  Khairulov Timur (KhrTim)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../include/GraphAlgorithm.h"

void GraphAlgorithm::clearSteps() {
    algorithm_steps.clear();
}

void GraphAlgorithm::loadWeightedGraph(
  std::unordered_map<int, std::vector<std::pair<int, int>>>
  new_weighted_graph, std::vector<sf::Vector2f> new_graph_nodes) {
    weighted_graph = new_weighted_graph;
    graph_nodes = new_graph_nodes;
}

std::vector<std::pair<std::pair<int, int>, bool>> GraphAlgorithm::getStep() {
  if (hasSteps()) {
    return algorithm_steps[cur_step];
  } else {
    std::vector<std::pair<std::pair<int, int>, bool>> empty;
    return empty;
  }
}
