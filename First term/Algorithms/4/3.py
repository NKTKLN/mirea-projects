def main() -> None:
    # Config
    arr = [-1, 2, 3, 4, 7]
    n = 5

    # Main code
    some_dict = {}
    for index in range(len(arr)):
        key = n - arr[index]
        if some_dict.get(key) is not None:
            print(some_dict[key], index)
            break

        if some_dict.get(arr[index]) is None:
            some_dict[arr[index]] = index


if __name__ == "__main__":
    main()
