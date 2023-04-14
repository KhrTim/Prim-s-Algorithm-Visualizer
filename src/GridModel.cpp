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

#include "../include/GridModel.h"


std::vector<sf::Vector2f> GridModel::getModelPoints() {
    setModelType(ModelType::Grid);
    return drawCheckedField(40.f, 500);
}

std::vector<sf::Vector2f> GridModel::drawCheckedField(float width,
                                                      int numOfLines) {
  std::vector<sf::Vector2f> field;

  float centerOffset = numOfLines * width / 2;

  for (int x = 0; x <= numOfLines; ++x) {
    field.push_back(sf::Vector2f(
        static_cast<float>(x * width - centerOffset),
        centerOffset));
    field.push_back(sf::Vector2f(
        static_cast<float>(x * width - centerOffset),
        -centerOffset));
  }
  for (int y = 0; y <= numOfLines; ++y) {
    field.push_back(sf::Vector2f(
        centerOffset,
        static_cast<float>(y * width - centerOffset)));
    field.push_back(sf::Vector2f(
        -centerOffset,
        static_cast<float>(y * width - centerOffset)));
  }
  return field;
}

std::vector<ModelType::ModelType> GridModel::getModelTypes() {
  std::vector<ModelType::ModelType> model_types;
  model_types.push_back(ModelType::Grid);
  return model_types;
}
