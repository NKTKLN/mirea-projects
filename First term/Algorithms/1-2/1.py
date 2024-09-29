def binary_search(arr: list, item: int) -> (int, bool):
    is_found = False
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == item:
            is_found = True
            break

        if arr[mid] > item:
            high = mid - 1
            continue

        low = mid + 1
    
    if arr[mid] < item:
        mid += 1
    
    return mid, is_found


def main() -> None:
    # Config
    arr = [1, 2, 3, 4, 5, 7, 8]
    item = 6

    # Main code
    ans = binary_search(arr, item)

    print("Index: ", ans[0])
    print("Before:", arr)

    if not ans[1]:
        arr.insert(ans[0], item)
        print("After: ", arr)


if __name__ == "__main__":
    main()
