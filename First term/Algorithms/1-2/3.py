def binary_search(arr: list) -> int:
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == 0:
            break

        if arr[mid] > 0:
            high = mid - 1
            continue

        low = mid + 1
    
    return mid


def main() -> None:
    # Config
    arr = [-5, -4, -3, -2, 2, 3, 4]

    # Main code
    if len(arr) == 0:
        print("Пустой список.")
        return

    index = binary_search(arr)

    neg = index
    pos = len(arr) - neg

    if arr[index] < 0:
        neg += 1
    
    if arr[index] <= 0:
        pos -= 1
    
    print(neg, pos)


if __name__ == "__main__":
    main()
