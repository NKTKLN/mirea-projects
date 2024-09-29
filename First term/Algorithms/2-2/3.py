def main() -> None:
    n = int(input())

    number = 1
    numbers = []
    while len(numbers) < n:
        num = number
        for divider in 2, 3, 5:
            while num % divider == 0:
                num //= divider

        if num == 1:
            numbers.append(number)

        number += 1

    print(numbers[n-1])


if __name__ == "__main__":
    main()
