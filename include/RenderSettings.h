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


#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

#include <SFML/Graphics.hpp>

class RenderSettings {
  sf::Color helper_line_color;
  sf::Color edge_color;
  sf::Color node_color;
  sf::Color unvisited_node_color;
  sf::Color node_outline_color;
  sf::Color animation_step_edge_color;
  sf::Color animation_step_unseen_edge_color;
  sf::Color background_color;
  sf::Color grid_color;
  sf::Color text_color;


 public:
  RenderSettings(/* args */);
  sf::Color helperLineColor();
  sf::Color edgeColor();
  sf::Color nodeColor();
  sf::Color nodeOutlineColor();
  sf::Color animationStepEdgeColor();
  sf::Color animationStepUnseenEdgeColor();
  sf::Color backGroundColor();
  sf::Color gridColor();
  sf::Color unvisitedNodeColor();
  sf::Color textColor();


  void setTextColor(sf::Color new_color);
  void setUnvisitedNodeColor(sf::Color new_color);
  void setHelperLineColor(sf::Color new_color);
  void setEdgeColor(sf::Color new_color);
  void setNodeColor(sf::Color new_color);
  void setNodeOutlineColor(sf::Color new_color);
  void setAnimationStepEdgeColor(sf::Color new_color);
  void setAnimationStepUnseenEdgeColor(sf::Color new_color);
  void setBackGroundColor(sf::Color new_color);
  void setGridColor(sf::Color new_color);


  ~RenderSettings();
};


#endif  // RENDER_SETTINGS_H
