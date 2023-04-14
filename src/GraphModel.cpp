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

// TODO(KhrTim): move to header
#include <iostream>
#include <algorithm>
#include "GraphModel.h"

void GraphModel::addNode(sf::Vector2f pos) {
  graph.push_back(std::make_shared<Node>(pos));
  model_types.push_back(ModelType::Node);
  setDirty();
}

std::unordered_map<int, std::vector<std::pair<int, int>>>
GraphModel::getGraphConnections() {
  return graph_connections;
}

void GraphModel::replaceGraphEdges(
    std::unordered_map<int,
    std::vector<std::pair<int, int>>> new_edges) {
    // TODO(KhrTim): potentially dangerous function. Check
  graph_connections = new_edges;
}

void GraphModel::connectNodes(int node_1, int node_2) {
  if ((node_1 != node_2) && (node_1 < graph.size()) &&
        (node_1 >= 0) && (node_2 < graph.size()) && (node_2 >= 0)) {
    if (!nodesConncted(node_1, node_2)) {
      graph_connections[node_1].push_back(std::make_pair(node_2, 0));
      graph_connections[node_2].push_back(std::make_pair(node_1, 0));
      has_connections = true;
    }
  }
}

void GraphModel::disconnectNodes(int node_1, int node_2) {
    if ((node_1 != node_2) && (node_1 < graph.size()) &&
          (node_1 >= 0) && (node_2 < graph.size()) && (node_2 >= 0)) {
      if (nodesConncted(node_1, node_2)) {
        graph_connections[node_1].erase(
            std::find_if(
              graph_connections[node_1].begin(),
              graph_connections[node_1].end(),
              [&node_2](std::pair<int, int> cur_node) {
                return cur_node.first == node_2; }));
        graph_connections[node_2].erase(
            std::find_if(
              graph_connections[node_2].begin(),
              graph_connections[node_2].end(),
              [&node_1](std::pair<int, int> cur_node){
                return cur_node.first == node_1; }));
      }
    }
}

int GraphModel::getEdgeWeight(int node_a, int node_b) {
  if (nodesConncted(node_a, node_b)) {
    auto found_node = std::find_if(
      graph_connections[node_a].begin(),
      graph_connections[node_a].end(),
      [&node_b](std::pair<int, int> cur_node) {
        return cur_node.first == node_b; });
    return (*found_node).second;
  }
  return -1;
}


// TODO(KhrTim): add function for easy iteration over edges
void GraphModel::setEdgeWeight(int node_a, int node_b, int weight) {
    if (weight < 0) return;
    // TODO(KhrTim): used too often. Move to separate function
    if (nodesConncted(node_a, node_b)) {
        auto found_node_a = std::find_if(
          graph_connections[node_a].begin(),
          graph_connections[node_a].end(),
          [&node_b](std::pair<int, int> cur_node){
            return cur_node.first == node_b; });
        auto found_node_b = std::find_if(
          graph_connections[node_b].begin(),
          graph_connections[node_b].end(),
          [&node_a](std::pair<int, int> cur_node){
            return cur_node.first == node_a; });
        (*found_node_a).second = weight;
        (*found_node_b).second = weight;
    }
}


bool GraphModel::nodesConncted(int node_1, int node_2) {
    if (graph_connections.find(node_1) != graph_connections.end()) {
        if (std::find_if(graph_connections[node_1].begin(),
                          graph_connections[node_1].end(),
                          [&node_2](std::pair<int, int> cur_node) {
                          return cur_node.first == node_2; })
                          != graph_connections[node_1].end()) {
            return true;
        }
    }
    return false;
}

std::vector<sf::Vector2f> GraphModel::getModelPoints() {
  std::vector<sf::Vector2f> graph_points;
  for (int i_element = 0; i_element < graph.size(); ++i_element) {
    std::vector<sf::Vector2f> figure_points =
                              (*graph[i_element]).getModelPoints();
    graph_points.insert(
      std::end(graph_points),
      std::begin(figure_points),
      std::end(figure_points));
  }
  return graph_points;
}

void GraphModel::moveNode(sf::Vector2f drag_begin, sf::Vector2f drag_end) {
  for (auto entity : graph) {
    if (entity.get()->getModelType() == ModelType::Node) {
      // TODO(KhrTim): is it possible to remove dynamic typing?
      Node *n = dynamic_cast<Node *>(entity.get());
      if (nodeCaptured(drag_begin, n->getPosition(), n->getRadius())) {
        setDirty();
        sf::Vector2f delta = drag_end - drag_begin;
        n->changePosition(drag_begin + delta);
        break;
      }
    }
  }
}

// TODO(KhrTim): rename
void GraphModel::processConnectionLine(sf::Vector2f begin, sf::Vector2f end) {
  int begin_node = -1;
  int end_node = -1;

  for (int i_node = 0; i_node < graph.size(); ++i_node) {
    auto entity = graph[i_node];

    if (entity.get()->getModelType() == ModelType::Node) {
      Node *n = dynamic_cast<Node *>(entity.get());
      if (nodeCaptured(begin, n->getPosition(), n->getRadius())) {
        begin_node = i_node;
      } else if (nodeCaptured(end, n->getPosition(), n->getRadius())) {
        end_node = i_node;
      }
    }
  }
  connectNodes(begin_node, end_node);
  setDirty();
}

void GraphModel::removeNode(int node_num) {
  if (node_num < 0 || node_num >= graph.size())
    return;

  if (graph_connections.find(node_num) != graph_connections.end()) {
    auto nodes_to_unlink = graph_connections[node_num];
    for (auto const &node : nodes_to_unlink) {
        disconnectNodes(node_num, node.first);
    }
  }
  if (graph_connections.size() == 0) {
    has_connections = false;
  } else {
    for (auto i_node : graph_connections) {
      for (int j_node = 0; j_node < graph_connections[i_node.first].size();
             ++j_node) {
        if (graph_connections[i_node.first][j_node].first > node_num) {
          graph_connections[i_node.first][j_node].first -= 1;
        }
      }
    }

    for (int i_node = node_num + 1; i_node < graph.size(); i_node++) {
      if (graph_connections.find(i_node) != graph_connections.end()) {
        graph_connections[i_node - 1] = graph_connections[i_node];
        graph_connections.erase(i_node);
      }
    }
  }
  graph.erase(graph.begin() + node_num);
  if (graph.size() == 0)
    has_connections = false;
  setDirty();
}

bool GraphModel::nodeCaptured(sf::Vector2f drag_begin,
                              sf::Vector2f node_origin,
                              float radius) {
  return (sqrt(pow((node_origin.x - drag_begin.x), 2) +
               pow((node_origin.y - drag_begin.y), 2)) <= radius);
}

std::vector<ModelType::ModelType> GraphModel::getModelTypes() {
    return model_types;
}
