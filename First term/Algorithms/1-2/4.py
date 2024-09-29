def binary_search(arr: list, item: int) -> int:
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == item:
            break

        if arr[mid] > item:
            high = mid - 1
            continue

        low = mid + 1
    
    if arr[mid] < item:
        mid += 1
    
    return mid


def main() -> None:
    # Config
    arr = [5, 2, 6, 1, 9, 4, 3, 2, 4, 5]

    # Main code
    sorted_arr = [arr[-1]]
    ans = [0]
    
    for num_index in range(len(arr)-2, -1, -1):
        index = binary_search(sorted_arr, arr[num_index])
        
        sorted_arr.insert(index, arr[num_index])

        ans.append(index)
    print(ans[::-1])


if __name__ == "__main__":
    main()
