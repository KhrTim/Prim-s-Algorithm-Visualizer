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

#ifndef GRAPH_MODEL_H
#define GRAPH_MODEL_H

#include <math.h>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include "Model.h"
#include "Node.h"

class GraphModel : public Model {
  std::unordered_map<int, std::vector<std::pair<int, int>>> graph_connections;
  bool has_connections = false;
  std::vector<ModelType::ModelType> model_types;
  bool nodeCaptured(sf::Vector2f drag_begin,
                    sf::Vector2f node_origin, float radius);

 public:
  int getEdgeWeight(int node_a, int node_b);
  void setEdgeWeight(int node_a, int node_b, int weight);
  void processConnectionLine(sf::Vector2f begin, sf::Vector2f end);
  void removeNode(int node_num);
  bool hasConnections() { return has_connections; }
  GraphModel() { setModelType(ModelType::Graph); }
  std::vector<std::shared_ptr<Model>> graph;
  void addNode(sf::Vector2f pos);
  std::unordered_map<int, std::vector<std::pair<int, int>>>
      getGraphConnections();
  void replaceGraphEdges(
      std::unordered_map<int, std::vector<std::pair<int, int>>> new_edges);
  void connectNodes(int node_1, int node_2);
  void disconnectNodes(int node_1, int node_2);
  bool nodesConncted(int node_1, int node_2);
  std::vector<sf::Vector2f> getModelPoints() override;
  std::vector<ModelType::ModelType> getModelTypes() override;
  void moveNode(sf::Vector2f drag_begin, sf::Vector2f drag_end);
  ~GraphModel() {}
};

#endif  // GRAPH_MODEL_H
