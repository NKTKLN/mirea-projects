def dijkstra(graph: list[list[int]], start_node: int, end_node: int) -> list[int]:
    dist = graph[start_node].copy()
    queue = list(range(len(dist)))
    routes = [[] if dist[index] == float("inf") else [start_node] for index in range(len(dist))]
    while len(queue) > 0:
        min_index = queue[0]
        for node in queue:
            if dist[node] < dist[min_index]:
                min_index = node
        queue.remove(min_index)

        for node in queue:
            new_dist = dist[min_index] + graph[min_index][node]
            if dist[node] > new_dist:
                dist[node] = new_dist
                routes[node] = routes[min_index] + [min_index]

    return routes[end_node] + [end_node]


def main() -> None:
    inf = float("inf")
    graph = [
        [  0,   7,   4, inf, inf, inf],
        [inf,   0,   4, inf,   2, inf],
        [inf, inf,   0,   4,   8, inf],
        [inf, inf, inf,   0, inf,  12],
        [inf, inf, inf,   4,   0,   5],
        [inf, inf, inf, inf, inf,   0]
    ]

    start_node = 0
    end_node = 5

    flow_sum = 0
    while True:
        min_flow = inf
        route = dijkstra(graph, start_node, end_node)
        if len(route) == 1:
            break

        for index in range(len(route)-1):
            min_flow = min(min_flow, graph[route[index]][route[index+1]])

        flow_sum += min_flow

        for index in range(len(route)-1):
            graph[route[index]][route[index+1]] -= min_flow
            graph[route[index+1]][route[index]] = min_flow

            if graph[route[index]][route[index+1]] == 0:
                graph[route[index]][route[index+1]] = inf
    
    print("Sum:",flow_sum)


if __name__ == "__main__":
    main()
