import heapq 

class Graph: 
    def __init__(self): 
        self.graph = {} 

    def add_edge(self, node, neighbor, cost): 
        if node not in self.graph: 
            self.graph[node] = [] 
        self.graph[node].append((neighbor, cost)) 

    def ida_star_search(self, start, goal, heuristic): 
        threshold = heuristic(start)  # Initial threshold based on heuristic value of the start node

        while True: 
            result, cost, route = self.depth_limited_search(start, goal, heuristic, threshold, 0, []) 

            if result == 'FOUND': 
                return True, cost, route 
            if result == float('inf'): 
                return False, float('inf'), [] 

            threshold = cost  # Increase the threshold for the next iteration

    def depth_limited_search(self, node, goal, heuristic, threshold, g_value, route): 
        f_value = g_value + heuristic(node)  # f(x) = g(x) + h(x)

        if f_value > threshold: 
            return f_value, f_value, []  # Exceeds the current threshold 

        if node == goal: 
            return 'FOUND', g_value, route + [node]  # Goal found 

        min_cost = float('inf')  # Initialize minimum cost as infinity
        best_route = []  # To track the best path found

        for neighbor, edge_cost in self.graph.get(node, []): 
            new_g_value = g_value + edge_cost 
            result, new_threshold, new_route = self.depth_limited_search(
                neighbor, goal, heuristic, threshold, new_g_value, route + [node]
            )

            if result == 'FOUND': 
                return 'FOUND', new_threshold, new_route 
            if result < min_cost: 
                min_cost = result  # Update min_cost to the smallest threshold exceeded
                best_route = new_route  # Update the best route

        return min_cost, min_cost, best_route  # Return updated threshold and best path found


# Example Usage
def heuristic(node):
    h_values = {'A': 10, 'B': 8, 'C': 5, 'D': 7, 'E': 3, 'F': 6, 'G': 0}
    return h_values.get(node, float('inf'))  # Default to infinity if node not in heuristic map

graph = Graph()
graph.add_edge('A', 'B', 3)
graph.add_edge('A', 'C', 6)
graph.add_edge('B', 'D', 2)
graph.add_edge('B', 'E', 5)
graph.add_edge('C', 'F', 2)
graph.add_edge('C', 'G', 4)
graph.add_edge('E', 'G', 2)
graph.add_edge('F', 'G', 1)

found, cost, path = graph.ida_star_search('A', 'G', heuristic)

if found:
    print(f"Path found: {path} with cost {cost}")
else:
    print("No path found")
