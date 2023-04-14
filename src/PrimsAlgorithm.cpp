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
#include "../include/PrimsAlgorithm.h"

template <
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>>
class RandomAccessMinHeap : public std::priority_queue<T, Container, Compare> {
 public:
  using std::priority_queue<T, Container, Compare>::priority_queue;
  typedef typename std::priority_queue<
      T,
      Container,
      Compare>::container_type::const_iterator const_iterator;

  std::vector<T> getCurrentValues() const {
    std::vector<T> res;
    res.insert(res.begin(), this->c.cbegin(), this->c.cend());
    return res;
  }
};

// TODO(KhrTim): make weightedEdge class
bool contains(const std::set<int> &vertex_set, int v) {
  if (vertex_set.find(v) != vertex_set.end())
    return true;
  return false;
}

std::unordered_map<int, std::vector<std::pair<int, int>>>
PrimsAlgorithm::getMST() {
  // TODO(KhrTim): test
  // TODO(KhrTim): simpify
  std::unordered_map<int, std::vector<std::pair<int, int>>> mst;
  for (auto const &edge : algorithm_steps.back()) {
    if (edge.second == true) {
      auto it = std::find_if(
        weighted_graph[edge.first.first].begin(),
        weighted_graph[edge.first.first].end(),
        [edge](std::pair<int, int> node) {
          return node.first == edge.first.second;});
      int dist = std::distance(weighted_graph[edge.first.first].begin(), it);
      int weight = weighted_graph[edge.first.first][dist].second;

      mst[edge.first.first].push_back(
                            std::make_pair(edge.first.second, weight));
      mst[edge.first.second].push_back(
                            std::make_pair(edge.first.first, weight));
    }
  }
  return mst;
}

void PrimsAlgorithm::execute() {
  cur_step = 0;
  std::vector<std::pair<int, int>> added_edges;
  std::set<int> visited;

  int begin_elem = weighted_graph.begin()->first;
  // remove from unvisited
  auto cmp = [](std::pair<std::pair<int, int>, int> first,
                std::pair<std::pair<int, int>, int> second) {
                  return first.second > second.second; };
  RandomAccessMinHeap<std::pair<std::pair<int, int>, int>,
                      std::vector<std::pair<std::pair<int, int>, int>>,
                      decltype(cmp)> min_edge_heap(cmp);

  for (const auto &adj : weighted_graph[begin_elem]) {
    visited.insert(begin_elem);
    algorithm_steps.push_back(
        {std::make_pair(std::make_pair(begin_elem, adj.first), false)});
    min_edge_heap.push(
        std::make_pair(std::make_pair(begin_elem, adj.first), adj.second));
  }
  while (min_edge_heap.size() > 0) {
    // I assume that SECOND node is ALWAYS one that was NOT VISITED
    auto min_edge = min_edge_heap.top();
    min_edge_heap.pop();
    while ((contains(visited, min_edge.first.first) &&
            contains(visited, min_edge.first.second)) &&
            min_edge_heap.size() > 0) {
      min_edge = min_edge_heap.top();
      min_edge_heap.pop();
    }

    if (!contains(visited, min_edge.first.first) ||
        !contains(visited, min_edge.first.second)) {
      if (contains(visited, min_edge.first.first)) {
        visited.insert(min_edge.first.second);
      } else if (contains(visited, min_edge.first.second)) {
        visited.insert(min_edge.first.first);
      }
      added_edges.push_back(std::make_pair(min_edge.first.first,
                                            min_edge.first.second));
      std::vector<std::pair<std::pair<int, int>, bool>>
                                  cur_step_added_edges;
      for (auto const &added_edge : added_edges) {
        cur_step_added_edges.push_back(std::make_pair(added_edge, true));
      }
      algorithm_steps.push_back(cur_step_added_edges);

      auto left_edges = min_edge_heap.getCurrentValues();
      for (auto i_edge : left_edges) {
        if (!contains(visited, i_edge.first.first) ||
            !contains(visited, i_edge.first.second)) {
          algorithm_steps.push_back(cur_step_added_edges);
          algorithm_steps[algorithm_steps.size() - 1].push_back(
              std::make_pair(
              std::make_pair(i_edge.first.first, i_edge.first.second), false));
        }
      }

      if (weighted_graph.find(min_edge.first.second) != weighted_graph.end()) {
        for (const auto &adj : weighted_graph[min_edge.first.second]) {
          if (!contains(visited, adj.first)) {
            algorithm_steps.push_back(cur_step_added_edges);
            algorithm_steps[algorithm_steps.size() - 1].push_back(
              std::make_pair(
                std::make_pair(min_edge.first.second, adj.first), false));
            min_edge_heap.push(
              std::make_pair(
                std::make_pair(min_edge.first.second, adj.first), adj.second));
          }
        }
      }
    }
  }
}
