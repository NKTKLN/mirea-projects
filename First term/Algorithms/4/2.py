def main(string: str) -> None:
    some_dict = {}
    for char in string:
        if some_dict.get(char) is None:
            some_dict[char] = 1
            continue

        some_dict[char] += 1

    for key in some_dict.keys():
        print(f"'{key}': {some_dict[key]}")


if __name__ == "__main__":
    main("hello world")
