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

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Renderer.h"
#include "../include/GridModel.h"
#include "../include/GraphModel.h"
#include "../include/Line.h"
#include "../include/UserActionController.h"
#include "../include/PrimsAlgorithm.h"
#include "../include/AnimationController.h"
#include "../include/RenderSettings.h"

int main() {
  RenderSettings render_settings;
  render_settings.setAnimationStepEdgeColor(sf::Color(252, 163, 17));

  sf::RenderWindow window;
  window.create(sf::VideoMode(1200, 800), "Prim's algorithm visualization");
  window.setFramerateLimit(120);

  sf::Font font;
  if (!font.loadFromFile("./assets/Ubuntu-L.ttf")) {
      std::cout << "[ERROR] Font was not loaded\n";
  }
  PrimsAlgorithm prim;
  GraphModel graph;
  AnimationController animation_controller(&prim, &graph);
  animation_controller.setAnimationStepDuration(600);
  Renderer renderer(&render_settings, &window, &font, &animation_controller);
  Line line;
  GridModel grid;
  renderer.addModel(&grid);
  renderer.linkGraph(&graph);
  renderer.addModel(&graph);
  renderer.addModel(&line);

  UserActionController action_controller(&renderer, &graph,
                                          &animation_controller);
  action_controller.addLineObject(&line);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
      }
      action_controller.update(window);
    }
    renderer.drawScene();
    animation_controller.update();
  }
}
