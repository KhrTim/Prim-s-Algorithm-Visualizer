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

#include "../include/Line.h"

std::vector<sf::Vector2f> Line::getModelPoints() {
  std::vector<sf::Vector2f> points;
  points.push_back(start);
  points.push_back(end);
  return points;
}

void Line::setPosition(sf::Vector2f start, sf::Vector2f end) {
  this->start = start;
  this->end = end;
  setDirty();
}

std::vector<ModelType::ModelType> Line::getModelTypes() {
  std::vector<ModelType::ModelType> model_types;
  model_types.push_back(getModelType());
  return model_types;
}
