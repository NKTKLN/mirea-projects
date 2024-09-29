def main() -> int:
    a = int(input())

    if a < 10:
        return a

    numbers = []
    for divider in range(9, 1, -1):
        while a % divider == 0:
            a //= divider
            numbers.append(divider)

    if a >= 10:
        return 0

    return int("".join(map(str, sorted(numbers))))


if __name__ == "__main__":
    print(main())
