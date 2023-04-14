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

#include "../include/Utils.h"

sf::Vector2f worldToScreen(sf::Vector2f worldCoords,
                            sf::Vector2f cameraOffset,
                            sf::Vector2f cameraZoom) {
  return sf::Vector2f((worldCoords.x - cameraOffset.x) * cameraZoom.x,
                      (worldCoords.y - cameraOffset.y) * cameraZoom.y);
}


sf::Vector2f screenToWorld(sf::Vector2f screenCoords,
                            sf::Vector2f cameraOffset,
                            sf::Vector2f cameraZoom) {
  return sf::Vector2f(screenCoords.x / cameraZoom.x + cameraOffset.x,
                      screenCoords.y / cameraZoom.y + cameraOffset.y);
}
