
def main() -> None:
    # Config
    input_string = "minimum"

    # Main code
    some_dict = {}

    for char in input_string:
        if some_dict.get(char) is None:
            some_dict[char] = 1
            continue
        some_dict[char] += 1

    for char in input_string:
        if some_dict[char] == 1:
            print(char)
            break


if __name__ == "__main__":
    main()

