def binary_search(arr: list) -> int:
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if len(arr) - 1 == mid or mid == 0:
            return mid

        if arr[mid-1] < arr[mid] > arr[mid+1]:
            return mid

        if arr[mid] >= arr[mid+1]:
            high = mid - 1
            continue

        low = mid + 1

    return None


def checkIfPeakExist(arr: list) -> bool:
    for index in range(len(arr)):
        is_exist = True

        for first in range(index-1):
            if not arr[first] < arr[first+1]:
                is_exist = False

        for second in range(index, len(arr)-1):
            if not arr[second] > arr[second+1]:
                is_exist = False

        if is_exist:
            if index == 0 or index == len(arr)-1:
                return 0

            return arr[index]

    return 0


def main() -> None:
    # Config
    arr = [2, 3, 7, 4, 3, 2, -1, -2, -3, -4, -5, -6, -8]
    # arr = [-8, -6, -5, -4, -3, -2, -1, 2, 3, 4, 3, 2]
    # arr = [1, 2, 3, 4, 5, 4, 3, 2, 1]

    # Main code
    if not checkIfPeakExist(arr):
        print("Не является горным списком.")
        return

    ans = binary_search(arr)

    print("Ответ:", arr[ans])
    print("Индекс:", ans)


if __name__ == "__main__":
    main()
