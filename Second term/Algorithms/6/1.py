from random import randint 
 
 
def main() -> None: 
    inf = float("inf") 
    names = [ 
        "Пр-т Вернадского, 78", 
        "Пр-т Вернадского, 86", 
        "Стромынка, 20", 
        "Малая Пироговская, 1", 
        "5-я улица Соколиной горы, 22", 
        "Усачева, 7" 
    ] 
    graph = [ 
        [inf,  1.97, 21.6, 10.7, 22.3, 10.4], 
        [1.97, inf,  22.3, 11.4, 23,   11.1], 
        [21.6, 22.3, inf,  11.5, 5.2,  12], 
        [10.7, 1.4,  11.5, inf,  13.4, 0.68], 
        [22.3, 23,   5.2,  13.4, inf,  13.8], 
        [10.4, 11.1, 12,   0.68, 13.8, inf] 
    ] 
 
    node = randint(0, 5) 
    indexes = [node] 
    edges = [] 
 
    while len(indexes) < len(graph): 
        new_edge = (indexes[0], indexes[0]) 
        for node in indexes: 
            for new_node in range(len(graph)): 
                if new_node in indexes: 
                    continue 
 
                if graph[node][new_node] < graph[new_edge[0]][new_edge[1]]: 
                    new_edge = (node, new_node) 
 
        edges.append(new_edge) 
        indexes.append(new_edge[1]) 
 
    for edge in edges: 
        print(f"{names[edge[0]] :>28} --> {names[edge[1]]}") 
     
    print("Length:", sum([graph[edge[1]][edge[0]] for edge in edges])) 
 
 
if __name__ == "__main__": 
    main()
