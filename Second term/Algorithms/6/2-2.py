def remover(nodes: list[int], graph: list[list[int]], pnode: int) -> None:
    for node in range(len(graph[pnode])):
        if node in nodes and graph[pnode][node]:
            nodes.remove(node)
            remover(nodes, graph, node)


def main() -> None:
    graph = [
        [1, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 1],
        [0, 0, 0, 0, 1, 1],
        [1, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 1, 0, 1, 0, 0],
    ]

    nodes = [0, 1, 2, 3, 4, 5, 6, 7]
    count = 0
    while len(nodes) != 0:
        count += 1
        index = nodes[0]
        nodes.remove(index)
        remover(nodes, graph, index)

    print("Connectivity score:", count)


if __name__ == "__main__":
    main()
