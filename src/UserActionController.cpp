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

#include "../include/UserActionController.h"

UserActionController::UserActionController(
    Renderer *renderer,
    GraphModel *graph_model,
    AnimationController *animation_controller) {
  graph = graph_model;
  world_renderer = renderer;
  camera_offset = sf::Vector2f(0.f, 0.f);
  mouse_previous_position = sf::Vector2i(0, 0);
  cameraZoom = sf::Vector2f(1.f, 1.f);
  this->animation_controller = animation_controller;
}

void UserActionController::addLineObject(Line *line) {
  helper_line = line;
}

std::pair<int, int> UserActionController::findDelitionEdge(
    std::vector<sf::Vector2f> graph_points,
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph_connections,
    sf::Vector2f mouse_position) {
  for (auto const &node : graph_connections) {
    sf::Vector2f start_point = graph_points[node.first * 2];
    for (auto const &connectee : node.second) {
      int connecte_node = connectee.first;
      sf::Vector2f end_point = graph_points[connecte_node * 2];
      // TODO(KhrTim): get thickness from renderer
      if (lineIntersection(start_point, end_point, mouse_position, 8.f)) {
        return std::make_pair(node.first, connecte_node);
      }
    }
  }
  return std::make_pair(-1, -1);
}

bool UserActionController::lineIntersection(
    sf::Vector2f start,
    sf::Vector2f end,
    sf::Vector2f mouse_position,
    float line_thickness) {
  sf::Vector2f direction = end - start;
  sf::Vector2f unitDirection = direction /
                              std::sqrt(direction.x * direction.x +
                                        direction.y * direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

  sf::Vector2f offset = (line_thickness / 2.f) * unitPerpendicular;

  if (pointInsideRectangle(start - offset,
                          start + offset,
                          end + offset,
                          end - offset,
                          mouse_position))
    return true;
  return false;
}

// should be class member?
// needs description?
bool UserActionController::pointInsideRectangle(sf::Vector2f A,
                                                sf::Vector2f B,
                                                sf::Vector2f C,
                                                sf::Vector2f D,
                                                sf::Vector2f point) {

  float ABCD = 0.5f * abs((A.y - C.y) * (D.x - B.x) +
                          (B.y - D.y) * (A.x - C.x));
  float ABP = 0.5f * abs(A.x * (B.y - point.y) + B.x *
                          (point.y - A.y) + point.x * (A.y - B.y));
  float BCP = 0.5f * abs(B.x * (C.y - point.y) + C.x *
                          (point.y - B.y) + point.x * (B.y - C.y));
  float CDP = 0.5f * abs(C.x * (D.y - point.y) + D.x *
                          (point.y - C.y) + point.x * (C.y - D.y));
  float DAP = 0.5f * abs(D.x * (A.y - point.y) + A.x *
                          (point.y - D.y) + point.x * (D.y - A.y));

  return (abs(ABCD - (ABP + BCP + CDP + DAP)) < 0.1);
}

void UserActionController::addDigitToEdgeWeigth(int node_1,
                                                int node_2,
                                                int digit) {
  int cur_weight = graph->getEdgeWeight(node_1, node_2);
  if (cur_weight == 0) {
    graph->setEdgeWeight(node_1, node_2, digit);
  } else {
    cur_weight *= 10;
    cur_weight += digit;
    graph->setEdgeWeight(node_1, node_2, cur_weight);
  }
}

void UserActionController::removeDigitFromEdgeWeigth(int node_1, int node_2) {
  int cur_weight = graph->getEdgeWeight(node_1, node_2);
  if (cur_weight == 0)
    return;

  if (cur_weight < 10) {
    graph->setEdgeWeight(node_1, node_2, 0);
  } else {
    cur_weight /= 10;
    graph->setEdgeWeight(node_1, node_2, cur_weight);
  }
}

// TODO(KhrTim): rename
int UserActionController::findDelitionNode(
    std::vector<sf::Vector2f> graph_points,
    sf::Vector2f mouse_position) {
  float circle_radius = graph_points[1].x;
  for (int i_cirlce = 0; i_cirlce < graph_points.size() / 2; i_cirlce++) {
    if (circleIntersection(graph_points[i_cirlce * 2],
                          circle_radius, mouse_position)) {
      return i_cirlce;
    }
  }
  return -1;
}

bool UserActionController::circleIntersection(
    sf::Vector2f circle_origin,
    float radius, sf::Vector2f mouse_position) {
  return (sqrt(pow((circle_origin.x - mouse_position.x), 2) +
              pow((circle_origin.y - mouse_position.y), 2)) <= radius);
}

void UserActionController::update(const sf::RenderWindow &render_window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
    setDefaultParams();

    camera_offset.x -= (sf::Mouse::getPosition(render_window).x -
                        mouse_previous_position.x);
    camera_offset.y -= (sf::Mouse::getPosition(render_window).y -
                        mouse_previous_position.y);

    mouse_previous_position = sf::Mouse::getPosition(render_window);

    world_renderer->update_world_parameters(
                    camera_offset,
                    mouse_previous_position,
                    cameraZoom,
                    screenToWorld(
                      sf::Vector2f(mouse_previous_position),
                      camera_offset, cameraZoom));

  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (left_button_pressed_last_frame) {
      sf::Vector2i mouse_current_position =
                  sf::Mouse::getPosition(render_window);

      graph->moveNode(screenToWorld(sf::Vector2f(mouse_previous_position),
                                    camera_offset, cameraZoom),
                      screenToWorld(sf::Vector2f(mouse_current_position),
                                    camera_offset, cameraZoom));
    }
    setDefaultParams();
    left_button_pressed_last_frame = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    if (!animation_controller->processingAnimation() &&
        clock.getElapsedTime().asMilliseconds() > 100) {
      sf::Vector2i mouse_current_position =
          sf::Mouse::getPosition(render_window);
      graph->addNode(
        screenToWorld(
          sf::Vector2f(mouse_current_position), camera_offset, cameraZoom));
      clock.restart();
    }
    setDefaultParams();
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    if (!animation_controller->processingAnimation()) {
      if (z_pressed_last_frame && !drag_line) {
        drag_line_begin =
          screenToWorld(
            sf::Vector2f(
              sf::Mouse::getPosition(render_window)),
              camera_offset, cameraZoom);
        drag_line = true;
      } else if (z_pressed_last_frame) {
        helper_line->show();
        helper_line->setPosition(
            drag_line_begin,
            screenToWorld(
              sf::Vector2f(
                sf::Mouse::getPosition(render_window)),
                camera_offset, cameraZoom));
      }
      z_pressed_last_frame = true;
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
    setDefaultParams();
    if (!animation_controller->processingAnimation()) {
      auto graph_connections = graph->getGraphConnections();
      auto graph_points = graph->getModelPoints();
      // check if they're not empty!!
      if (graph_points.size() > 0) {
        int node_to_delete = findDelitionNode(graph_points,
                              screenToWorld(
                                sf::Vector2f(
                                  sf::Mouse::getPosition(render_window)),
                                  camera_offset, cameraZoom));

        if (node_to_delete != -1) {
          graph->removeNode(node_to_delete);
        } else if (graph_connections.size() > 0) {
          auto edge_to_delete = findDelitionEdge(graph_points,
                                                graph_connections,
                                  screenToWorld(
                                    sf::Vector2f(
                                      sf::Mouse::getPosition(render_window)),
                                      camera_offset, cameraZoom));

          if (edge_to_delete.first != -1) {
            graph->disconnectNodes(edge_to_delete.first, edge_to_delete.second);
          }
        }
      }
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
      if (!animation_controller->processingAnimation() &&
            clock.getElapsedTime().asMilliseconds() > 100) {
        setDefaultParams();
        auto graph_connections = graph->getGraphConnections();
        auto graph_points = graph->getModelPoints();
        auto edge_to_delete = findDelitionEdge(graph_points, graph_connections,
                                    screenToWorld(
                                      sf::Vector2f(
                                        sf::Mouse::getPosition(render_window)),
                                        camera_offset, cameraZoom));
        if (edge_to_delete.first != -1) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            removeDigitFromEdgeWeigth(edge_to_delete.first,
                                      edge_to_delete.second);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 0);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 1);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 2);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 3);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 4);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 5);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 6);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 7);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 8);
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
            addDigitToEdgeWeigth(edge_to_delete.first,
                                edge_to_delete.second, 9);
          }
        }
        // TODO(KhrTim): remove number_inserted flag
        clock.restart();
      }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
  // TODO(KhrTim): repalce number_inserted with timer
    if (!animation_controller->processingAnimation()) {
      setDefaultParams();
      animation_controller->startAnimation();
    }
  } else {
    if (z_pressed_last_frame) {
      std::vector<sf::Vector2f> line_coords = helper_line->getModelPoints();
      graph->processConnectionLine(line_coords[0], line_coords[1]);
    }
    setDefaultParams();
  }
  mouse_previous_position = sf::Mouse::getPosition(render_window);
  world_renderer->updateMousePosition(
    screenToWorld(
      sf::Vector2f(mouse_previous_position), camera_offset, cameraZoom));
}

void UserActionController::setDefaultParams() {
  helper_line->hide();
  drag_line = false;
  left_button_pressed_last_frame = false;
  z_pressed_last_frame = false;
}

UserActionController::~UserActionController() {
}
