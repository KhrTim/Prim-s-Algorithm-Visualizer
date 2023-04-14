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

#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

class GraphAlgorithm {
 protected:
  std::unordered_map<int, std::vector<std::pair<int, int>>> weighted_graph;
  std::vector<sf::Vector2f> graph_nodes;
  std::vector<std::vector<std::pair<std::pair<int, int>, bool>>>
  algorithm_steps;
  int cur_step;

 public:
  void clearSteps();
  bool hasSteps() { return algorithm_steps.size() > cur_step; }
  GraphAlgorithm() {}
  // TODO(KhrTim) might crash if execution started before loading
  void loadWeightedGraph(
    std::unordered_map<int, std::vector<std::pair<int, int>>>
    new_weighted_graph,
    std::vector<sf::Vector2f> new_graph_nodes);

  std::vector<std::pair<std::pair<int, int>, bool>> getStep();
  virtual std::unordered_map<int, std::vector<std::pair<int, int>>>
  getMST() = 0;
  void nextStep() { cur_step++; }
  virtual void execute() = 0;
};

#endif  // GRAPH_ALGORITHM_H
