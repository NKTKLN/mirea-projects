def main() -> None:
    # Config
    first_arr = [1, 2, 3, 4, 5]
    second_arr = [0, 2, 4, 6, 8]

    # Main code
    some_dict = {}
    ans = set()
    for index in range(max(len(first_arr), len(second_arr))):
        if index < len(first_arr):
            first_number = first_arr[index]

            if some_dict.get(first_number) is None:
                some_dict[first_number] = 1
            elif some_dict[first_number] == 2:
                ans.add(first_number)

        if index < len(second_arr):
            second_number = second_arr[index]

            if some_dict.get(second_number) is None:
                some_dict[second_number] = 2
            elif some_dict[second_number] == 1:
                ans.add(second_number)

    print(list(ans))


if __name__ == "__main__":
    main()
