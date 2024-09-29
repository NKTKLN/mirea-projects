def gcd_extended(a: int, b: int) -> tuple[int, int, int]:
    if b == 0:
        return a, 1, 0
    
    gcd, x, y = gcd_extended(b, a % b)
    return gcd, y, x - (a // b) * y


def main() -> None:
    print(gcd_extended(240, 46))


if __name__ == "__main__":
    main()
