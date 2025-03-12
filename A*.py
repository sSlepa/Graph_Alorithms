import heapq 

class Graph: 
    def __init__(self): 
        self.graph = {} 
    
    def add_edge(self, node, neighbor, cost): 
        if node not in self.graph:
            self.graph[node] = [] 
        self.graph[node].append((neighbor, cost)) 
    
    def astar_search(self, start, goal, heuristic): 
        open_list = [(heuristic(start), 0, start, [])]  # (f(x), g(x), node, path)
        closed_set = set() 
        g_values = {node: float('inf') for node in self.graph} 
        g_values[start] = 0 
    
        while open_list: 
            _, cost, current_node, route = heapq.heappop(open_list) 
    
            if current_node == goal: 
                print("Best Route:", route + [current_node]) 
                print("Cost:", cost) 
                return route + [current_node], cost # Returnează traseul și costul
    
            if current_node in closed_set:
                continue  # Sărim peste nodurile deja verificate
    
            closed_set.add(current_node) 
    
            for neighbor, edge_cost in self.graph.get(current_node, []): 
                if neighbor in closed_set: 
                    continue  # Sărim peste vecinii deja evaluați
    
                current_cost = g_values[current_node] + edge_cost 
    
                if current_cost < g_values[neighbor]:  # Dacă găsim un cost mai mic
                    g_values[neighbor] = current_cost 
                    f_value = current_cost + heuristic(neighbor) 
                    heapq.heappush(open_list, (f_value, current_cost, neighbor, route + [current_node])) 
    
        print("Goal not reachable")
        return None, float('inf')  # Dacă nu există drum posibil
