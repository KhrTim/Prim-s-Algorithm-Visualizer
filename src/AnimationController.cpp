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

#include "../include/AnimationController.h"

AnimationController::AnimationController(GraphAlgorithm *algorithm,
                                        GraphModel *graph) {
  this->algorithm = algorithm;
  this->graph = graph;
  animation_step_duration = sf::milliseconds(300);
}

void AnimationController::setAnimationStepDuration(int duration_ms) {
  animation_step_duration = sf::milliseconds(duration_ms);
}

void AnimationController::startAnimation() {
  algorithm->clearSteps();
  auto edges = graph->getGraphConnections();
  if (edges.size() > 0) {
      algorithm->loadWeightedGraph(graph->getGraphConnections(),
                                    graph->getModelPoints());
    algorithm->execute();
    processing_animation = true;
    clock.restart();
  }
}

std::vector<std::pair<std::pair<int, int>, bool>>
AnimationController::getStep() {
  return algorithm->getStep();
}

void AnimationController::setAlgorithm(GraphAlgorithm *graph_algorithm) {
  algorithm = graph_algorithm;
}

void AnimationController::update() {
  if (processing_animation && clock.getElapsedTime().asMilliseconds() >
        animation_step_duration.asMilliseconds()) {
    if (algorithm->hasSteps()) {
      algorithm->nextStep();
    } else {
      processing_animation = false;
      graph->replaceGraphEdges(algorithm->getMST());
    }
    clock.restart();
  }
}

AnimationController::~AnimationController() {
}
