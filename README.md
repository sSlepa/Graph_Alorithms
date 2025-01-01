# Graphs and Trees Algorithms Repository

This repository contains a collection of algorithms and data structures related to graphs, trees, and several personal problem-solving implementations. The repository is structured to provide efficient and well-documented solutions for a variety of computational challenges.

## Contents

### Algorithms

1. **2-SAT Solver (`2Sat.cpp`)**
   - Implementation of the 2-Satisfiability problem using implication graphs.

2. **Shortest Paths and Related Algorithms**
   - **Dijkstra's Algorithm(Astar) (`astar.cpp`)**: Heuristic-based shortest path algorithm.
   - **Bellman-Ford Algorithm (`bellman.cpp`)**: Handles graphs with negative weights.
   - **Johnson's Algorithm (`johnson.cpp`)**: Solves all-pairs shortest paths efficiently.
   - **Yen's Algorithm (`Yenk.cpp`)**: Finds K shortest paths in a graph.

3. **Maximum Flow (`maxflow.cpp`)**
   - Implementation of a maximum flow algorithm, solving network flow problems.

4. **Longest Path in Directed Acyclic Graph (`Longest Path DaG.cpp`)**
   - Computes the longest path in a directed acyclic graph.

### Data Structures

1. **Trie (`Trie.cpp`)**
   - A compact and efficient tree-based structure for string manipulation and storage.

2. **Splay Tree (`splay_tree.c`)**
   - A self-adjusting binary search tree that improves access time for frequently accessed elements.

### Personal Projects and Problem Solutions

1. **Mars Exploration (`Marsx.cpp`)**
   - A custom solution for a problem involving space exploration and graph traversal.

2. **StarDust Problem (`StarDust.cpp`)**
   - A creative implementation of a graph-related problem with a unique twist.

3. **Dynamic Paths (`Drumuri2.cpp`)**
   - Solves a problem involving dynamic path finding in specific graph conditions.

4. **Custom Problem 4 (`joc4.cpp`)**
   - A personal challenge or competition problem implementation.

## Usage

Each file is a standalone implementation of the respective algorithm or problem solution. The code is written in C++, except for `splay_tree.c`, which is in C. To compile and run any file, use the following command:

```bash
# Replace filename.cpp with the desired file
g++ -std=c++17 -o output filename.cpp
./output
```

## Contribution

Contributions are welcome! If you have improvements, new algorithms, or additional problem solutions, feel free to create a pull request.
