class Graph:
    def __init__(self) -> None:
        self.graph = []

    def add_edge(self, first_index: int, second_index: int, length: int) -> None:
        if len(self.graph) <= first_index and len(self.graph) <= second_index:
            return

        self.graph[first_index][second_index] = length
        self.graph[second_index][first_index] = length

    def remove_edge(self, first_index: int, second_index: int) -> None:
        self.add_edge(first_index, second_index, 0)

    def print_matrix(self) -> None:
        node_count = len(self.graph)
        if node_count == 0:
            return
        
        print("  |", *range(node_count))
        print("--+" + "--" * node_count)
        for index in range(node_count):
            print(index, "|", *self.graph[index])

    def print_list(self) -> None:
        for first_index in range(len(self.graph)):
            edges = self.graph[first_index]
            print(f"{first_index :>2}: ", end="")
            for second_index in range(len(edges)):
                if edges[second_index]:
                    print(f"{second_index} ({edges[second_index]})  ", end="")
            print()

    def create_empty_graph(self, node_count: int) -> None:
        self.graph = [[0 for _ in range(node_count)] for _ in range(node_count)]

    def save(self) -> None:
        if len(self.graph) == 0:
            return

        with open("graph.txt", "w") as file:
            file.write(f"{len(self.graph)}\n")
            for index in range(len(self.graph)):
                file.write(" ".join(map(str, self.graph[index])) + "\n")
            file.close()

    def first_import_type(self, file_name: str) -> None:
        with open(file_name, "r") as file:
            node_count = int(file.readline())
            self.create_empty_graph(node_count)
            while True:
                line = file.readline().split()
                if len(line) < 2:
                    break

                for second_index in line[1:]:
                    self.add_edge(int(line[0]), int(second_index), 1)
            file.close()

    def second_import_type(self, file_name: str) -> None:
        with open(file_name, "r") as file:
            node_count = int(file.readline())
            self.create_empty_graph(node_count)
            while True:
                line = file.readline().split()
                if len(line) != 3:
                    break
                
                self.add_edge(int(line[0]), int(line[1]), int(line[2]))
            file.close()

    def third_import_type(self, file_name: str) -> None:
        with open(file_name, "r") as file:
            node_count = int(file.readline())
            self.create_empty_graph(node_count)
            for first_index in range(node_count):
                line = file.readline().split()
                for second_index in range(node_count):
                    self.add_edge(first_index, second_index, int(line[second_index]))
            file.close()


def main() -> None:
    g = Graph()
    print("Import of the first graph type (А)")
    g.first_import_type("first_type_graph.txt")
    g.print_matrix()

    print("Import of the second graph type (Б)")
    g.second_import_type("second_type_graph.txt")
    g.print_matrix()

    print("Import of the third graph type (В)")
    g.third_import_type("third_type_graph.txt")
    g.print_matrix()
    
    print("Print the graph as a list")
    g.print_list()

    print("Adding a new edge 1-2 with length 6")
    g.add_edge(1, 2, 6)
    g.print_matrix()

    print("Removing the edge 3-4")
    g.remove_edge(3, 4)
    g.print_matrix()

    print("Saving a new graph")
    g.save()


if __name__ == "__main__":
    main()
