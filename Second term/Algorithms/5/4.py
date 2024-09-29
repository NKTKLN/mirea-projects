class Gost(object):
    def __init__(self, key, sbox):
        self._key = 0
        self._subkeys = None
        self.key = key
        self.sbox = sbox

    @property
    def key(self) -> int:
        return self._key

    @key.setter
    def key(self, key: str) -> None:
        assert len(key) <= 32

        encoded_key = key.encode("ascii")
        for index in range(31, -1, -1):
            self._key |= encoded_key[index] << (index * 8)

        self._subkeys = [(self._key >> (32 * index)) & 0xFFFFFFFF for index in range(8)]

    def _function(self, part: int, key: int) -> int:
        part = (part + key) % (1 << 32)
        temp = 0
        for index in range(8):
            temp |= ((self.sbox[index][(part >> (4 * index)) & 0b1111]) << (4 * index))
        
        return ((temp >> 11) | (temp << 21)) & 0xFFFFFFFF

    def encrypt_part(self, message_part: int) -> int:
        left = message_part >> 32
        right = message_part & 0xFFFFFFFF

        for index in range(24):
            left, right = right, left ^ self._function(right, self._subkeys[index % 8])

        for index in range(8):
            left, right = right, left ^ self._function(right, self._subkeys[7 - index])
        
        return (left << 32) | right

    def decrypt_part(self, crypted_message_part: int) -> int:
        left = crypted_message_part >> 32
        right = crypted_message_part & 0xFFFFFFFF

        for index in range(8):
            left, right = right ^ self._function(left, self._subkeys[index]), left

        for index in range(24):
            left, right = right ^ self._function(left, self._subkeys[(7 - index) % 8]), left
        
        return (left << 32) | right

    def encrypt(self, message: str) -> int:
        encoded_message = message.encode("ascii")

        encrypted_message = 0
        for part_index in range(len(message) // 8 + 1 * (len(message) % 8 != 0)):
            binary_part = 0
            for letter_index in range(8):
                letter = 0x0000
                if (letter_index + part_index * 8 < len(message)):
                    letter = encoded_message[letter_index + part_index * 8]
                binary_part = (binary_part << 8)  | letter
            encrypted_message = (encrypted_message << 64) | self.encrypt_part(binary_part)

        return encrypted_message

    def decrypt(self, encrypted_message: int) -> str:
        decrypted_message = ""
        for index in range(len(bin(encrypted_message)[2:]) // 64, -1, -1):
            binary_part = (encrypted_message >> (64 * index)) & 0xFFFFFFFFFFFFFFFF
            decrypted_binary_part = self.decrypt_part(binary_part)
            for letter_index in range(8):
                decrypted_message += chr((decrypted_binary_part >> ((7 - letter_index) * 8)) & 0xFF)

        return decrypted_message


def main():
    sbox = [
        [0x4, 0xA, 0x9, 0x2, 0xD, 0x8, 0x0, 0xE, 0x6, 0xB, 0x1, 0xC, 0x7, 0xF, 0x5, 0x3],
        [0xE, 0xB, 0x4, 0xC, 0x6, 0xD, 0xF, 0xA, 0x2, 0x3, 0x8, 0x1, 0x0, 0x7, 0x5, 0x9],
        [0x5, 0x8, 0x1, 0xD, 0xA, 0x3, 0x4, 0x2, 0xE, 0xF, 0xC, 0x7, 0x6, 0x0, 0x9, 0xB],
        [0x7, 0xD, 0xA, 0x1, 0x0, 0x8, 0x9, 0xF, 0xE, 0x4, 0x6, 0xC, 0xB, 0x2, 0x5, 0x3],
        [0x6, 0xC, 0x7, 0x1, 0x5, 0xF, 0xD, 0x8, 0x4, 0xA, 0x9, 0xE, 0x0, 0x3, 0xB, 0x2],
        [0x4, 0xB, 0xA, 0x0, 0x7, 0x2, 0x1, 0xD, 0x3, 0x6, 0x8, 0x5, 0x9, 0xC, 0xF, 0xE],
        [0xD, 0xB, 0x4, 0x1, 0x3, 0xF, 0x5, 0x9, 0x0, 0xA, 0xE, 0x7, 0x6, 0x8, 0x2, 0xC],
        [0x1, 0xF, 0xD, 0x0, 0x5, 0x7, 0xA, 0x4, 0x9, 0x2, 0x3, 0xE, 0x6, 0xB, 0x8, 0xC]
    ]
    message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    key = "zqHqtbGwB41OOsm5EeGmG0VKeJWrnhML"

    gost = Gost(key, sbox)
    crypted_message = gost.encrypt(message)
    encrypted_message = gost.decrypt(crypted_message)

    print("Original message:  ", message)
    print("Crypted:           ", crypted_message)
    print("Encrypted message: ", encrypted_message)

if __name__ == "__main__":
    main()
