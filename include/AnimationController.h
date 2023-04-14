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

#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <utility>
#include <vector>
#include <SFML/System/Clock.hpp>
#include "GraphAlgorithm.h"
#include "GraphModel.h"

class AnimationController {
 private:
  sf::Clock clock;
  bool processing_animation = false;
  GraphAlgorithm *algorithm;
  sf::Time animation_step_duration;
  GraphModel *graph;

 public:
  void stopAnimation() { processing_animation = false; }
  // TODO(KhrTim): animation can be changed dynamically
  // if i move this into function
  AnimationController(GraphAlgorithm *algorithm, GraphModel *graph);
  bool processingAnimation() { return processing_animation; }
  void setAnimationStepDuration(int duration_ms);
  void startAnimation();
  std::vector<std::pair<std::pair<int, int>, bool>> getStep();
  void setAlgorithm(GraphAlgorithm *graph_algorithm);
  void update();
  ~AnimationController();
};

#endif  // ANIMATION_CONTROLLER_H
