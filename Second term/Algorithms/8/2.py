from random import choice


def gcd(a: int, b: int) -> int:
    if b == 0:
        return a

    return gcd(b, a % b)


def gcd_extended(a: int, b: int) -> tuple[int, int, int]:
    if b == 0:
        return a, 1, 0

    gcd, x, y = gcd_extended(b, a % b)
    return gcd, y, x - (a // b) * y


def mod_inverse(n: int, x: int) -> int:
    inv_x = gcd_extended(n, x)[2]
    if inv_x <= 0:
        inv_x += n
    return inv_x


def mod_extended(x: int, y: int, n: int) -> int:
    if y == 0:
        return 1

    z = mod_extended(x, y // 2, n)

    if y % 2 == 0:
        return (z * z) % n

    return (x * z * z) % n


def generate_keys(p: int, q: int) -> tuple[tuple[int, int], tuple[int, int]]:
    n = p * q
    phi = (p - 1) * (q - 1)

    e = 3
    for ferm_number in [5, 17, 257, 65537]:
        if ferm_number < phi:
            e = ferm_number

    d = mod_inverse(phi, e)

    return (e, n), (d, n)


def encrypt(message: str, key: tuple[int, int]):
    e, n = key
    encrypted_message = [mod_extended(ord(char), e, n) for char in message]
    return encrypted_message


def decrypt(encrypted_message: str, key: tuple[int, int]):
    d, n = key
    decrypted_message = [chr(mod_extended(char, d, n))
                         for char in encrypted_message]
    return "".join(decrypted_message)


def get_primes(n: int):
    sieve = [True] * n
    primes = []
    for p in range(2, n):
        if sieve[p]:
            primes.append(p)
            for i in range(p * p, n, p):
                sieve[i] = False
    return primes


def main() -> None:
    primes = get_primes(100000)
    p = choice(primes)
    q = choice(primes)
    while p == q:
        q = choice(primes)

    message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    public, private = generate_keys(p, q)
    encrypted_message = encrypt(message, public)
    decrypted_message = decrypt(encrypted_message, private)

    print("Public key: ", public)
    print("Private key:", private)
    print("Original message: ", message)
    print("Encrypted message:", "".join(map(str, encrypted_message)))
    print("Decrypted message:", decrypted_message)


if __name__ == "__main__":
    main()
