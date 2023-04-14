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

#include "../include/RenderSettings.h"

RenderSettings::RenderSettings(/* args */) {
  helper_line_color = sf::Color();
  edge_color = sf::Color(0, 102, 102);
  node_color = sf::Color(0, 153, 153);
  unvisited_node_color = sf::Color(128, 128, 128);
  node_outline_color = sf::Color(0, 255, 255);
  animation_step_edge_color = sf::Color(0, 204, 204);
  animation_step_unseen_edge_color = sf::Color(128, 128, 128);
  background_color = sf::Color(0, 0, 0, 255);
  grid_color = sf::Color(70, 70, 70);
  text_color = sf::Color::White;
}

sf::Color RenderSettings::helperLineColor() { return helper_line_color; }
sf::Color RenderSettings::edgeColor() { return edge_color; }
sf::Color RenderSettings::nodeColor() { return node_color; }
sf::Color RenderSettings::nodeOutlineColor() { return node_outline_color; }
sf::Color RenderSettings::animationStepEdgeColor() {
  return animation_step_edge_color; }
sf::Color RenderSettings::animationStepUnseenEdgeColor() {
  return animation_step_unseen_edge_color; }
sf::Color RenderSettings::backGroundColor() { return background_color; }
sf::Color RenderSettings::gridColor() { return grid_color; }
sf::Color RenderSettings::unvisitedNodeColor() { return unvisited_node_color; }
sf::Color RenderSettings::textColor() { return text_color; }

void RenderSettings::setTextColor(sf::Color new_color) {
  text_color = new_color; }
void RenderSettings::setUnvisitedNodeColor(sf::Color new_color) {
  unvisited_node_color = new_color; }
void RenderSettings::setHelperLineColor(sf::Color new_color) {
  helper_line_color = new_color; }
void RenderSettings::setEdgeColor(sf::Color new_color) {
  edge_color = new_color; }
void RenderSettings::setNodeColor(sf::Color new_color) {
  node_color = new_color; }
void RenderSettings::setNodeOutlineColor(sf::Color new_color) {
  node_outline_color = new_color; }
void RenderSettings::setAnimationStepEdgeColor(sf::Color new_color) {
  animation_step_edge_color = new_color; }
void RenderSettings::setAnimationStepUnseenEdgeColor(sf::Color new_color) {
  animation_step_unseen_edge_color = new_color; }
void RenderSettings::setBackGroundColor(sf::Color new_color) {
  background_color = new_color; }
void RenderSettings::setGridColor(sf::Color new_color) {
  grid_color = new_color; }

RenderSettings::~RenderSettings() {
}
