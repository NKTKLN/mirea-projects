from string import ascii_lowercase


def substitution_cipher(alphabet: str, replacement_alphabet: str, message: str) -> str:
    new_message = ""
    for char in message:
        is_upper = char.isupper()
        char = char.lower()

        if char not in alphabet:
            new_message += char
            continue

        new_char = replacement_alphabet[alphabet.find(char)]
        new_message += new_char.upper() if is_upper else new_char

    return new_message


def main() -> None:
    input_message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    alphabet = ascii_lowercase
    replacement_alphabet = "goydsipeluavcrjwxznhbqftmk"

    encrypted_message = substitution_cipher(alphabet, replacement_alphabet, input_message)
    print("Encrypted message:", encrypted_message)

    decrypted_message = substitution_cipher(replacement_alphabet, alphabet, encrypted_message)
    print("Decrypted message:", decrypted_message)


if __name__ == "__main__":
    main()
