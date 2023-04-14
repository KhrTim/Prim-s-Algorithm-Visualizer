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

#ifndef RENDERER_H
#define RENDERER_H

#include <math.h>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <set>
#include <SFML/Graphics.hpp>
#include "GraphAlgorithm.h"
#include "AnimationController.h"
#include "Model.h"
#include "Utils.h"
#include "GraphModel.h"
#include "RenderSettings.h"

class Renderer {
  sf::Vector2f cameraOffset = sf::Vector2f(0.f, 0.f);
  sf::Vector2i worldOffset = sf::Vector2i(0, 0);
  sf::Vector2f cameraZoom = sf::Vector2f(1.f, 1.f);
  sf::Vector2f mouse_position;
  std::vector<Model *> models;
  sf::RenderWindow *render_window;
  GraphModel *graph;
  sf::Font *font;
  std::vector<std::vector<sf::Vector2f>> objects_points;
  std::vector<std::vector<sf::Vertex>> objects_vertices;
  bool dirty_frame;
  GraphAlgorithm *graph_algorithm;
  std::vector<std::pair<std::pair<int, int>, bool>> algorithm_execution_steps;
  int cur_step = -1;
  AnimationController *animation_controller;
  RenderSettings* render_settings;

 public:
  Renderer(RenderSettings* render_settings,
          sf::RenderWindow *new_render_window,
          sf::Font *new_font, AnimationController *animation_controller);
  void update_world_parameters(sf::Vector2f new_camera_offset,
                              sf::Vector2i new_world_offset,
                              sf::Vector2f new_camera_zoom,
                              sf::Vector2f new_mouse_position);

  void updateMousePosition(sf::Vector2f new_mouse_position);

  void addModel(Model *new_model);

  std::vector<sf::Vertex> drawGrid(std::vector<sf::Vector2f> worldCoordiantes,
                                    sf::Color gridColor);

  std::vector<sf::Text> labelNodesWithNumbers(
      std::vector<sf::Vector2f> graph_points);

  std::vector<sf::Text> labelEdgesWithNumbers(
      std::vector<sf::Vector2f> graph_points,
      std::unordered_map<int,
      std::vector<std::pair<int, int>>> graph_connections);

  std::vector<sf::Vertex> drawDashedLine(sf::Vector2f start,
                                        sf::Vector2f end,
                                        float thickness, sf::Color color);

  sf::Text drawTextOnPosition(const std::string &text,
                              sf::Vector2f world_position);

  std::vector<sf::Vertex> drawGraphConnections();

  std::vector<sf::Vertex> drawLineWithThickness(sf::Vector2f start,
                                                sf::Vector2f end,
                                                float thickness,
                                                sf::Color color);

  void drawScene();

  sf::CircleShape drawNode(sf::Vector2f origin,
                          float radius, sf::Color node_color);

  void setGraphAlgorithm(GraphAlgorithm *graph_algorithm) {
    this->graph_algorithm = graph_algorithm;
  }

  void linkGraph(GraphModel *g);

  bool circle_hovered(sf::Vector2f origin, float radius);

  ~Renderer();
};

#endif  // RENDERER_H
