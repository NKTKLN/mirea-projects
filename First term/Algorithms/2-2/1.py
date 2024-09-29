def main() -> None:
    n = int(input())

    index = 0
    while 2 ** index < n:
        index += 1

    print(int(2 ** index == n))


if __name__ == "__main__":
    main()
