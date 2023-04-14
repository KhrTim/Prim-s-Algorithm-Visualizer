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

#ifndef PRIMS_ALGORITHM_H
#define PRIMS_ALGORITHM_H

#include <queue>
#include <utility>
#include <set>
#include <unordered_map>
#include <vector>
#include "GraphAlgorithm.h"

class PrimsAlgorithm : public GraphAlgorithm {
 public:
  std::unordered_map<int, std::vector<std::pair<int, int>>> getMST() override;
  void execute() override;
};

#endif  // PRIMS_ALGORITHM_H
