class Node():
    def __init__(self, count, data, left=None, right=None) -> None:
        self.count = count
        self.data = data
        self.left = left
        self.right = right


def create_coding_formats(node: Node, encoding_format: dict[str, str], decoding_format: dict[str, str], bits="") -> None:
    if node is None:
        return

    if node.data is not None:
        encoding_format[node.data] = bits
        decoding_format[bits] = node.data

    create_coding_formats(node.left, encoding_format, decoding_format, bits + "0")
    create_coding_formats(node.right, encoding_format, decoding_format, bits + "1")


def get_unique_letters(message: str) -> list[Node]:
    nodes = []
    for letter in set(message):
        node = Node(message.count(letter), letter)
        nodes.append(node)
    
    nodes.sort(key=lambda node: node.count, reverse=True)

    return nodes


def huffman_algorithm(nodes: list[Node]) -> tuple[dict[str, str], dict[str, str], Node]:
    while len(nodes) > 1:
        first_node = nodes.pop()
        second_node = nodes.pop()
        new_node = Node(first_node.count + second_node.count,
                        None, first_node, second_node)
        nodes.append(new_node)
        nodes.sort(key=lambda node: node.count, reverse=True)

    encoding_format = {}
    decoding_format = {}
    create_coding_formats(nodes[0], encoding_format, decoding_format)

    return encoding_format, decoding_format, nodes[0]


def encode(message: str, encoding_format: dict[str, str]) -> str:
    encoded_message = ""
    for letter in message:
        encoded_message += encoding_format[letter]

    return encoded_message


def decode(encoded_message: int, decoding_format: dict[str, str]) -> str:
    decoded_message = ""
    bits = ""
    for bit in encoded_message:
        bits += bit
        if decoding_format.get(bits) is not None:
            decoded_message += decoding_format[bits]
            bits = ""

    return decoded_message


def print_tree(node: Node, message: str, depth: int = 0) -> None:
    if node is None:
        return
    
    print_tree(node.right, message, depth + 1)
    print(" " * depth * 5, f"{node.data or '*'} ({node.count / len(message) :.7f})", sep="")
    print_tree(node.left, message, depth + 1)


def main() -> None:
    print("Введите текст, содержащий не менее двух символов...")

    message = input()
    unique_letters = get_unique_letters(message)

    print("Полученный список:")
    for node in unique_letters:
        print(f"{node.data} ({node.count / len(message) :.7f})", end=" ---> ")
    print("\nПостроим дерево...")

    new_encoding_fromat, new_decoding_format, huffman_tree = huffman_algorithm(unique_letters)

    print_tree(huffman_tree, message)
    print("---------------------------------------------")
    print("Приступим к кодировке введенного текста...")

    encoded_message = encode(message, new_encoding_fromat)

    print("Код перед Вами...", encoded_message)
    print(f"Коэффициент сжатия: {len(encoded_message) / (len(message) * 8) * 100 :.4f}%")

    decoded_message = decode(encoded_message, new_decoding_format)

    print("Ранее было зашифровано...", message)
    print("Расшифровано...", decoded_message)


if __name__ == "__main__":
    main()
