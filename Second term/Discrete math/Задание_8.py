def main() -> None:
    inf = float("inf")
    graph = [
        [  0,   7, inf, inf,   4, inf],
        [  7,   0,   5, inf, inf,   2],
        [inf,   5,   0,  11, inf,   6],
        [inf, inf,  11,   0,   8,   9],
        [  4, inf, inf,   8,   0,   3],
        [inf,   2,   6,   9,   3,   0],
    ]

    start_node = 0

    dist = graph[start_node].copy()
    queue = list(range(len(dist)))
    routes = [[] if dist[index] == inf else [start_node] for index in range(len(dist))]
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

    for index in range(len(routes)):
        if index == start_node:
            continue

        print(f"{start_node} --> {index} ({dist[index] :>2}):", end=" ")
        print(" --> ".join(map(str, routes[index] + [index])))


if __name__ == "__main__":
    main()
