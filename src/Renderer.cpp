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

#include "../include/Renderer.h"
#include <iostream>

Renderer::Renderer(RenderSettings* render_settings,
                  sf::RenderWindow *new_render_window,
                  sf::Font *new_font,
                  AnimationController *animation_controller) {
  render_window = new_render_window;
  font = new_font;
  this->animation_controller = animation_controller;
  this->render_settings = render_settings;
}

void Renderer::update_world_parameters(sf::Vector2f new_camera_offset,
                                      sf::Vector2i new_world_offset,
                                      sf::Vector2f new_camera_zoom,
                                      sf::Vector2f new_mouse_position) {
  cameraOffset = new_camera_offset;
  worldOffset = new_world_offset;
  cameraZoom = new_camera_zoom;
  mouse_position = new_mouse_position;
}

void Renderer::updateMousePosition(sf::Vector2f new_mouse_position) {
  mouse_position = new_mouse_position;
}

void Renderer::addModel(Model *new_model) {
  models.push_back(new_model);
  objects_points.push_back(new_model->getModelPoints());
}

std::vector<sf::Vertex> Renderer::drawGrid(
    std::vector<sf::Vector2f> worldCoordiantes,
    sf::Color grid_color) {
  std::vector<sf::Vertex> screenVertecies;

  for (auto point : worldCoordiantes) {
    screenVertecies.push_back(
      sf::Vertex(worldToScreen(point, cameraOffset, cameraZoom), grid_color));
  }
  return screenVertecies;
}

std::vector<sf::Text> Renderer::labelNodesWithNumbers(
    std::vector<sf::Vector2f> graph_points) {
  std::vector<sf::Text> labels;
  for (int i_node = 0; i_node < graph_points.size() / 2; i_node++) {
    labels.push_back(
      drawTextOnPosition(std::to_string(i_node), graph_points[i_node * 2]));
  }
  return labels;
}

std::vector<sf::Text> Renderer::labelEdgesWithNumbers(
    std::vector<sf::Vector2f> graph_points,
    std::unordered_map<int, std::vector<std::pair<int, int>>>
    graph_connections) {
  std::vector<sf::Text> labels;
  // TODO(KhrTim): can be done better?
  std::vector<std::pair<int, int>> visited_edges;
  for (auto const &i_node : graph_connections) {
    sf::Vector2f i_node_position = graph_points[i_node.first * 2];
    for (auto const &j_node : i_node.second) {
      if (std::find(std::begin(visited_edges),
                    std::end(visited_edges),
                    std::make_pair(i_node.first, j_node.first)) ==
                    visited_edges.end()) {
        visited_edges.push_back(std::make_pair(i_node.first, j_node.first));
        visited_edges.push_back(std::make_pair(j_node.first, i_node.first));

        sf::Vector2f j_node_position = graph_points[j_node.first * 2];
        int edge_weight = j_node.second;

        sf::Vector2f middle_point = j_node_position +
            (i_node_position - j_node_position) / 2.f;

        labels.push_back(
          drawTextOnPosition(std::to_string(edge_weight), middle_point));
      }
    }
  }
  return labels;
}

sf::Text Renderer::drawTextOnPosition(const std::string &text,
                                      sf::Vector2f world_position) {
  sf::Text ouput;
  ouput.setFont(*font);
  ouput.setString(text);
  // TODO(KhrTim): not zoomable
  ouput.setCharacterSize(26);
  ouput.setFillColor(render_settings->textColor());
  // TODO(KhrTim): not zoomable
  world_position.y -= 15;
  world_position.x -= 7;

  ouput.setPosition(worldToScreen(world_position, cameraOffset, cameraZoom));
  return ouput;
}

std::vector<sf::Vertex> Renderer::drawGraphConnections() {
  std::set<std::pair<int, int>> visited_edges;
  std::vector<sf::Vertex> connections;
  auto graph_connections = graph->getGraphConnections();
  auto graph_points = graph->getModelPoints();
  if (!animation_controller->processingAnimation()) {
    for (auto const &node : graph_connections) {
      sf::Vector2f start_point = graph_points[node.first * 2];
      for (auto const &connectee : node.second) {
        int connecte_node = connectee.first;
        sf::Vector2f end_point = graph_points[connecte_node * 2];

        std::vector<sf::Vertex> line_vertices =
          drawLineWithThickness(start_point, end_point, 8,
                                render_settings->edgeColor());
        connections.insert(std::end(connections),
                          std::begin(line_vertices),
                          std::end(line_vertices));
      }
    }
  } else {
    auto cur_step = animation_controller->getStep();
    for (auto const &node : graph_connections) {
      sf::Vector2f start_point = graph_points[node.first * 2];
      for (auto const &connectee : node.second) {
        int connecte_node = connectee.first;
        if (visited_edges.find(std::make_pair(connecte_node, node.first))==
                                visited_edges.end()) {
          visited_edges.insert(std::make_pair(connecte_node, node.first));
          visited_edges.insert(std::make_pair(node.first, connecte_node));

          sf::Vector2f end_point = graph_points[connecte_node * 2];
          auto it = std::find_if(cur_step.begin(),
                                  cur_step.end(),
          [&](std::pair<std::pair<int, int>, bool> step_node) {
            return (step_node.first.first == node.first &&
                    step_node.first.second == connecte_node) ||
                    (step_node.first.second == node.first &&
                    step_node.first.first == connecte_node); });
          if (it != cur_step.end()) {
            int idx = std::distance(cur_step.begin(), it);
            if (cur_step[idx].second == true) {
              std::vector<sf::Vertex> line_vertices =
              drawLineWithThickness(start_point,
                                    end_point, 8,
                                    render_settings->edgeColor());

              connections.insert(std::end(connections),
                                  std::begin(line_vertices),
                                  std::end(line_vertices));
            } else {
              std::vector<sf::Vertex> line_vertices =
              drawLineWithThickness(start_point,
                                    end_point, 8,
                                    render_settings->animationStepEdgeColor());

              connections.insert(std::end(connections),
                                std::begin(line_vertices),
                                std::end(line_vertices));
            }
          } else {
            std::vector<sf::Vertex> line_vertices =
                drawDashedLine(start_point,
                              end_point, 2,
                              render_settings->animationStepUnseenEdgeColor());

            connections.insert(std::end(connections),
                              std::begin(line_vertices),
                              std::end(line_vertices));
          }
        }
      }
    }
  }
  return connections;
}

std::vector<sf::Vertex> Renderer::drawDashedLine(sf::Vector2f start,
                                                  sf::Vector2f end,
                                                  float thickness,
                                                  sf::Color color) {
  std::vector<sf::Vertex> vertices;
  sf::Vector2f direction = end - start;
  sf::Vector2f unitDirection = direction /
                              std::sqrt(direction.x * direction.x +
                                        direction.y * direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

  sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

  sf::Vector2f dash_start = start;
  sf::Vector2f dash_end = dash_start + (unitDirection * 20.f);
  if (end.x < start.x) {
    while (dash_end.x > end.x) {
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_start + offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_end + offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_end - offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_start - offset, cameraOffset, cameraZoom), color));
      dash_start = dash_end + (unitDirection * 20.f);
      dash_end = dash_start + (unitDirection * 20.f);
    }
  } else {
    while (dash_end.x < end.x) {
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_start + offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_end + offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_end - offset, cameraOffset, cameraZoom), color));
      vertices.push_back(
        sf::Vertex(
          worldToScreen(dash_start - offset, cameraOffset, cameraZoom), color));
      dash_start = dash_end + (unitDirection * 20.f);
      dash_end = dash_start + (unitDirection * 20.f);
    }
  }
  return vertices;
}

std::vector<sf::Vertex> Renderer::drawLineWithThickness(sf::Vector2f start,
    sf::Vector2f end, float thickness,
    sf::Color color) {
  std::vector<sf::Vertex> vertices;
  sf::Vector2f direction = end - start;
  sf::Vector2f unitDirection = direction /
                              std::sqrt(direction.x * direction.x +
                                        direction.y * direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

  sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

  vertices.push_back(
    sf::Vertex(
      worldToScreen(start + offset, cameraOffset, cameraZoom), color));
  vertices.push_back(
    sf::Vertex(
      worldToScreen(end + offset, cameraOffset, cameraZoom), color));
  vertices.push_back(
    sf::Vertex(
      worldToScreen(end - offset, cameraOffset, cameraZoom), color));
  vertices.push_back(
    sf::Vertex(
      worldToScreen(start - offset, cameraOffset, cameraZoom), color));

  return vertices;
}

sf::CircleShape Renderer::drawNode(sf::Vector2f origin,
                                  float radius,
                                  sf::Color node_color) {
  sf::CircleShape node(radius);
  node.setFillColor(node_color);
  if (circle_hovered(origin, radius)) {
    node.setOutlineThickness(2.f);
    node.setOutlineColor(render_settings->nodeOutlineColor());
  } else {
    node.setOutlineThickness(0.f);
  }
  origin.x -= radius;
  origin.y -= radius;
  node.setPosition(worldToScreen(origin, cameraOffset, cameraZoom));
  return node;
}

void Renderer::linkGraph(GraphModel *g) {
  graph = g;
}

bool Renderer::circle_hovered(sf::Vector2f origin, float radius) {
  return (sqrt(pow((origin.x - mouse_position.x), 2) +
              pow((origin.y - mouse_position.y), 2)) <= radius);
}

void Renderer::drawScene() {
  for (int i_model = 0; i_model < models.size(); ++i_model) {
    auto model = models[i_model];
    if (model->isDirty()) {
      objects_points[i_model] = model->getModelPoints();
      model->setClean();
    }
  }

  render_window->clear(render_settings->backGroundColor());
  for (int i_model = 0; i_model < models.size(); ++i_model) {
    auto model = models[i_model];
    if (model->getModelType() == ModelType::Grid) {
      render_window->draw(&drawGrid(objects_points[i_model],
                                    render_settings->gridColor())[0],
                          objects_points[i_model].size(),
                          sf::Lines);
    } else if (model->getModelType() == ModelType::Graph) {
      auto graph_points = model->getModelPoints();
      // TODO(KhrTim): swich places
      if (graph->hasConnections()) {
        auto graph_connections = drawGraphConnections();
        for (int i_connection = 0; i_connection < graph_connections.size() / 4;
                i_connection++) {
          render_window->draw(&graph_connections[i_connection * 4], 4,
                              sf::Quads);
        }
        auto edges_labels = labelEdgesWithNumbers(graph_points,
                                                  graph->getGraphConnections());
        for (auto const &edge_label : edges_labels) {
          render_window->draw(edge_label);
        }
      }
      // TODO(KhrTim): put init into cycle
      int i_point = 0;
      std::vector<std::pair<std::pair<int, int>, bool>> st;
      if (animation_controller->processingAnimation())
        st = animation_controller->getStep();
      std::vector<sf::Text> node_labels = labelNodesWithNumbers(graph_points);
      for (i_point = 0; i_point < graph_points.size() / 2; ++i_point) {
        // TODO(KhrTim): simpify Node class
        if (animation_controller->processingAnimation()) {
          if (std::find_if(
              st.begin(),
              st.end(),
              [=](std::pair<std::pair<int, int>, bool> cur_edge){
                return (cur_edge.first.first == i_point) ||
                        (cur_edge.first.second == i_point) &&
                        (cur_edge.second == true); }) != st.end()) {
            render_window->draw(
              drawNode(graph_points[i_point * 2],
                      graph_points[i_point * 2 + 1].x,
                      render_settings->nodeColor()));
          } else {
            render_window->draw(
              drawNode(graph_points[i_point * 2],
                      graph_points[i_point * 2 + 1].x,
                      render_settings->unvisitedNodeColor()));
          }
        } else {
          render_window->draw(
            drawNode(graph_points[i_point * 2],
                    graph_points[i_point * 2 + 1].x,
                    render_settings->nodeColor()));
        }
        render_window->draw(node_labels[i_point]);
      }
    } else if (model->getModelType() == ModelType::Line) {
      if (!model->isHidden()) {
        render_window->draw(
          &drawLineWithThickness(objects_points[i_model][0],
                                objects_points[i_model][1], 8.f,
                                sf::Color(255, 255, 255))[0], 4, sf::Quads);
      }
    }
  }
  render_window->display();
}

Renderer::~Renderer() {
}
