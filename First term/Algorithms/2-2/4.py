import heapq


def main() -> None:
    # Config
    arr = [1, 2, 3, 5]
    k = 3

    # Main code
    heap = [(arr[0]/arr[j], 0, j) for j in range(1, len(arr))]
    heapq.heapify(heap)

    for _ in range(k):
        val, i, j = heapq.heappop(heap)
        if i < len(arr) - 1:
            heapq.heappush(heap, (arr[i+1]/arr[j], i+1, j))
  
    print([arr[i], arr[j]])


if __name__ == "__main__":
    main()

# O(k * log(n)), где n - длина массива arr
