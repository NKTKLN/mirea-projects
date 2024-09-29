from string import ascii_lowercase


def caesar_cipher(alphabet: str, key: int, message: str) -> str:
    new_message = ""
    for char in message:
        is_upper = char.isupper()
        char = char.lower()

        if char not in alphabet:
            new_message += char
            continue

        index_of_new_char = (alphabet.find(char) + key) % len(alphabet)
        new_char = alphabet[index_of_new_char]
        new_message += new_char.upper() if is_upper else new_char

    return new_message


def main() -> None:
    input_message = input("Please enter text: ")
    key = int(input("Please enter key: "))
    alphabet = ascii_lowercase

    encrypted_message = caesar_cipher(alphabet, key, input_message)
    print("Encrypted message:", encrypted_message)

    decrypted_message = caesar_cipher(alphabet, -key, encrypted_message)
    print("Decrypted message:", decrypted_message)


if __name__ == "__main__":
    main()
