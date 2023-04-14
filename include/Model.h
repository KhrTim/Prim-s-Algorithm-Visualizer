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

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <SFML/Graphics.hpp>

namespace ModelType {
  enum ModelType {
    Grid,
    Graph,
    Node,
    Line,
  };
}

class Model {
 private:
  bool dirty;
  ModelType::ModelType model_type;
  bool hiden = false;

 public:
  sf::PrimitiveType primitive_type;
  void setModelType(ModelType::ModelType new_model_type) {
      model_type = new_model_type;
  }
  ModelType::ModelType getModelType() {
      return model_type;
  }
  void hide() {hiden = true;}
  void show() {hiden = false;}
  bool isHidden() {return hiden;}
  Model();
  bool isDirty() { return dirty; }
  void setDirty() { dirty = true; }
  void setClean() { dirty = false; }
  virtual std::vector<sf::Vector2f> getModelPoints() = 0;
  virtual std::vector<ModelType::ModelType> getModelTypes() = 0;
  virtual ~Model();
};

#endif  // MODEL_H_
