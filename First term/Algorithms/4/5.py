def main() -> None:
    # Config
    arr = ["а", "b", "с", "d", "с", "е", "f"]

    # Main code
    some_dict = {}
    for index in range(len(arr)):
        if some_dict.get(arr[index]) is not None:
            print(arr[index])
            break
        
        some_dict[arr[index]] = index


if __name__ == "__main__":
    main()
