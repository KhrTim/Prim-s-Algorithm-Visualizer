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

#ifndef USER_ACTION_CONTROLLER_H
#define USER_ACTION_CONTROLLER_H

#include <memory>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Utils.h"
#include "Line.h"
#include "AnimationController.h"

class UserActionController {
  sf::Vector2f camera_offset;
  sf::Vector2i mouse_previous_position;
  bool left_button_pressed_last_frame;
  bool drag_line = false;
  bool z_pressed_last_frame = false;
  sf::Vector2f drag_line_begin;
  sf::Vector2f cameraZoom;
  Renderer *world_renderer;
  GraphModel *graph;
  Line *helper_line;
  GraphAlgorithm *graph_algorithm;
  sf::Clock clock;
  int animation_step_duration_ms = 800;
  AnimationController *animation_controller;

 public:
  void setAnumationStepDuration(int duration_ms) {
    animation_step_duration_ms = duration_ms; }
  void setAlgorithm(GraphAlgorithm *new_algorithm) {
    graph_algorithm = new_algorithm; }
  UserActionController(Renderer *renderer,
                      GraphModel *graph_model,
                      AnimationController *animation_controller);

  bool lineIntersection(sf::Vector2f start,
                        sf::Vector2f end,
                        sf::Vector2f position,
                        float line_thickness);

  bool pointInsideRectangle(sf::Vector2f A,
                            sf::Vector2f B,
                            sf::Vector2f C,
                            sf::Vector2f D,
                            sf::Vector2f point);

  int findDelitionNode(std::vector<sf::Vector2f> graph_points,
                      sf::Vector2f mouse_position);
  bool circleIntersection(sf::Vector2f circle_origin,
                          float radius, sf::Vector2f mouse_position);

  void addLineObject(Line *line);
  void addDigitToEdgeWeigth(int node_1, int node_2, int digit);
  void removeDigitFromEdgeWeigth(int node_1, int node_2);
  std::pair<int, int> findDelitionEdge(
      std::vector<sf::Vector2f> graph_points,
      std::unordered_map<int, std::vector<std::pair<int, int>>>
      graph_connections,
      sf::Vector2f mouse_position);
  void update(const sf::RenderWindow &render_window);

  void setDefaultParams();

  ~UserActionController();
};

#endif  // USER_ACTION_CONTROLLER_H
