from random import randint


def main() -> None:
    inf = float("inf")
    graph = [
        [inf,  44,  46,  32, inf,  37],
        [44, inf,  45, inf,  30, inf],
        [46,  45, inf, inf, inf,  15],
        [32, inf, inf, inf,  17,  22],
        [inf,  30, inf,  17, inf, inf],
        [37, inf,  15,  22, inf, inf],
    ]

    index = randint(0, len(graph)-1)
    indexes = [index]
    while len(indexes) < len(graph):
        min_val_index = indexes[-1]
        for index in range(len(graph)):
            if index in indexes:
                continue

            if graph[indexes[-1]][index] <= graph[indexes[-1]][min_val_index]:
                min_val_index = index

        indexes.append(min_val_index)
    indexes.append(indexes[0])
    length = 0
    for index in range(1, len(indexes)):
        length += graph[indexes[index-1]][indexes[index]]
        print(f" {graph[indexes[index-1]][indexes[index]] :^5}", end="")

    print()
    print(" --> ".join(map(str, indexes)))
    print("Length:", length)


if __name__ == "__main__":
    main()
