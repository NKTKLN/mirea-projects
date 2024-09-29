def main() -> None:
    arr = [86, 90, 27, 29, 38, 30, 40]
    my_dict = [None] * 7

    for num in arr:
        key = num % 7
        d = 1
        while my_dict[key] is not None:
            key += d

            if key >= len(arr)-1:
                d = -1
                key -= 1

        my_dict[key] = num

    print(my_dict)


if __name__ == "__main__":
    main()
