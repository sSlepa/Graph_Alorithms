class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, node, neighbor, cost):
        if node not in self.graph:
            self.graph[node] = []
        self.graph[node].append((neighbor, cost))

    def rbfs(self, node, goal, f_limit, heuristic, current_cost):
        if node == goal:
            return [goal], current_cost

        successors = self.generate_successors(node, heuristic, current_cost)
        
        if not successors:
            return [], float('inf')

        while True:
            successors.sort(key=lambda x: x[1])  # Sort successors by cost
            best = successors[0]  # The best node is the one with the lowest cost

            if best[1] > f_limit:
                return [], best[1]

            alternative = successors[1][1] if len(successors) > 1 else float('inf')

            result, cost = self.rbfs(
                best[0], goal, min(f_limit, alternative), heuristic, current_cost + best[1]
            )

            if result:
                return [node] + result, cost

            successors.remove(best)

    def generate_successors(self, node, heuristic, current_cost):
        successors = []
        for neighbor, cost in self.graph.get(node, []):
            f_value = max(heuristic(neighbor), current_cost + cost)
            successors.append((neighbor, f_value))
        return successors

    def recursive_best_first_search(self, start, goal, heuristic):
        f_limit = float('inf')
        path, cost = self.rbfs(start, goal, f_limit, heuristic, 0)
        return path, cost


# Exemplu de utilizare:
graph = Graph()
graph.add_edge('A', 'B', 4)
graph.add_edge('A', 'C', 8)
graph.add_edge('B', 'D', 3)
graph.add_edge('B', 'E', 5)
graph.add_edge('C', 'F', 7)
graph.add_edge('D', 'G', 1)
graph.add_edge('G', 'D', 1)
graph.add_edge('E', 'H', 2)
graph.add_edge('H', 'E', 2)
graph.add_edge('F', 'I', 6)
graph.add_edge('I', 'F', 6)

heuristic = {'A': 12, 'B': 8, 'C': 6, 'D': 4, 'E': 3, 'F': 6, 'G': 1, 'H': 1, 'I': 1}

start_node = 'A'
goal_node = 'I'

path, cost = graph.recursive_best_first_search(start_node, goal_node, heuristic.get)

if path:
    print(f"Optimal path from '{start_node}' to '{goal_node}':")
    print(" -> ".join(path))
    print(f"Total cost: {cost}")
else:
    print(f"No path found from '{start_node}' to '{goal_node}'.")
