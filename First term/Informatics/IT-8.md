# Рабочая тетрадь № 6

## Задачи № 1

### № 1

```python
def function(string: str) -> str:
    half_length = len(string) // 2
    return string[:half_length][::-1] + string[half_length:][::-1]

some_string = "привет"
print(function(some_string))
```

### № 2

```python
def is_valid_bracket_structure(expression: str) -> bool:
    stack = []
    bracket_pairs = {')': '(', '}': '{', ']': '['}

    for char in expression:
        if char in bracket_pairs.values():
            stack.append(char)
        elif char in bracket_pairs.keys():
            if not stack or bracket_pairs[char] != stack.pop():
                return False

    return not stack 


expression = ")(, ())((), (, )))), ((())" # "(), (())(), ()(), ((()))"
if is_valid_bracket_structure(expression):
    print("Скобочная структура правильная.")
else:
    print("Скобочная структура неправильная.")
```

## Задачи № 2

### № 1

```python
import random

class Warrior:
    def __init__(self, name: str, health: int = 100):
        self.name = name
        self.health = health

    def attack(self, enemy: Warrior):
        print(f"{self.name} атакует {enemy.name}")
        enemy.health -= 20
        print(f"У {enemy.name} осталось {enemy.health} единиц здоровья")


warrior1 = Warrior("Воин 1")
warrior2 = Warrior("Воин 2")

while warrior1.health > 0 and warrior2.health > 0:
    attacker = random.choice([warrior1, warrior2])
    defender = warrior2 if attacker == warrior1 else warrior1

    attacker.attack(defender)

if warrior1.health <= 0:
    print(f"{warrior2.name} одержал победу!")
elif warrior2.health <= 0:
    print(f"{warrior1.name} одержал победу!")
else:
    print("Бой окончен в ничью.")
```
