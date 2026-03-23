# LAB3: Graph-Related Algorithms
- Problem A is a topological sort problem. The problem can be solved by using DFS and memorize the in and out time.
- Problem B needs to convert a pre-order representation of a binary tree to a post-order one. I use stack and loop to solve it in B.cpp. However, this question can also be solve by using recursive.
- Problem C is a strongly conponent problem. It can be solve by dfs one time, record the finish time, and dfs again on the reverse graph.
- Problem E wants us to find a path on a positive-edges graph. However, we can pick at most three edges on the path to get a discount. This problem can be solve by creating 3 layers of graph and use edges with discount weight to connect each layer. Then use dijkstra algorithm to solve the normal shortest path problem.
- Problem F is a simulation problem. The problem want us to simulate some snakes moving on a tree.
- Problem G wants us to implement a minimum spanning tree.
  