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

#ifndef NODE_H
#define NODE_H
#include <vector>
#include "Model.h"
#include <SFML/Graphics.hpp>

class Node : public Model {
  sf::Vector2f node_position;
  float radius;

 public:
  explicit Node(sf::Vector2f pos) : node_position{pos}, radius{30.f} {
    setModelType(ModelType::Node);
  }
  void setPosition(sf::Vector2f new_position) { node_position = new_position; }
  sf::Vector2f getPosition() { return node_position; }
  std::vector<sf::Vector2f> getModelPoints() override {
    std::vector<sf::Vector2f> node;
    node.push_back(node_position);
    node.push_back(sf::Vector2f(radius, radius));
    return node;
  }
  float getRadius() { return radius; }
  void changePosition(sf::Vector2f new_position) {
    node_position = new_position; }
  std::vector<ModelType::ModelType> getModelTypes() override;
  ~Node() {}
};

#endif  // NODE_H
