# Рабочая тетрадь № 1

## Задачи № 1

### № 1

```math
4 mb = 4 * 1024 * 1024 * 8 bit = 33554432 bit
```

### № 2

```math
2 gb = 2 * 1024 * 1024 * 1024 byte = 2147483648 byte
```

### № 3

```math
6291456 byte = 6291456 / 1024 / 1024 mb = 6 mb
```

## Задачи № 2

### № 1

```math
log2(26) = 5 bit
```

### № 2

```math
log2(5) = 3 bit
```

### № 3

```math
log2(21) = 5 bit
```

## Задачи № 3

### № 1

```math
-0.5 * log2(0.5) = 0.5
-0.5 * log2(0.5) = 0.5

H = 0.5 + 0.5 = 1
```

### № 2

```math
-1/6 * log2(1/6) = 0.431
-1/6 * log2(1/6) = 0.431
-1/6 * log2(1/6) = 0.431
-1/6 * log2(1/6) = 0.431
-1/6 * log2(1/6) = 0.431
-1/6 * log2(1/6) = 0.431

H = 0.431 + 0.431 + 0.431 + 0.431 + 0.431 + 0.431 = 2586
```

### № 3

```math
-0.6 * log2(0.6) = 0.442
-0.4 * log2(0.4) = 0.529

H = 0.442 + 0.529 = 0.971
```

## Задачи № 4

### № 1

```math
77
```

### № 2

```math
u
```

### № 3

```math
73 74 75 64 65 6E 74
```

## Задачи № 5

### № 1

```math
110010010
```

### № 2

```math
101000011
```

### № 3

```math
Да
```

## Задачи № 6

### № 1

```math
00111011

000 000 111 111 111 000 111 111
```

### № 2

```math
001 011 010 110 011 010 001 111 

01011001
```

### № 3

```math
CCz oYo mdm ppS uRu tpt wee Qrr __* Rss acc iBi eee nn% Fcc jee

Computer_science
```

## Задачи № 7

### № 1

```math
B 1010100
C 0011110
  0110101

3
```

### № 2

```math
A 0101010
B 1010100
C 0011110

ρ(A,B)

A 0101010
B 1010100
  0000001

6

ρ(A,C)

A 0101010
C 0011110
  1001011

3

ρ(B,C)

B 1010100
C 0011110
  0110101

3

ρ(A,B) ≤ ρ(A,C) + ρ(C,B) - Да
ρ(A,C) ≤ ρ(A,B) + ρ(B,C) - Да
ρ(B,C) ≤ ρ(B,A) + ρ(A,C) - Да

Да
```

### № 3

```math
d = min(6, 3, 3) = 3

3 >= 2n + 1

n = 1
```

## Тест

1. 1
2. 3
3. 2
4. 4
5. 4
6. 2
7. 3
8. 1
9. 3
10. 4

## Задачи № 8

### № 1

```python
print("Калинин Никита Викторович ЭФБО-09-23")
```

### № 2

```python
a = int(input())
b = int(input())

print(a + b)
```

### № 3

```python
a = float(input())

print(x ** 5 - 2 * x ** 3 + 1)
```

## Задачи № 9

### № 1

```python
strange = [[], 1]

print(type(strange))
```

### № 2

```python
for x in 0, 1:
    for y in 0, 1:
        if (x or y)  and  (not(x) or y)  and  not(x and y):
            print(x, y)
```

### № 3

```python
some_list = []

for i in range(4):
    some_list.append(i)

for i in some_list[::-1]:
    print(i)
```

## Задачи № 10

### № 1

```python
from math import log, ceil

def hartly(n: int) -> float:
    return ceil(log(n, 2))

print(hartly(int(input())))
```

### № 2

```python
from math import log

def entropy(p1, p2: float) -> float:
    h1 = -1 * p1 * log(p1, 2)
    h2 = -1 * p2 * log(p2, 2)
    
    return h1 + h2

a = float(input())
b = float(input())

print(entropy(a, b))
```

### № 3

```python
from math import tan, cos, sin, e, log

def some_func(x: float) -> float:
    return tan(cos(x) * sin(2 * x) / x * e**x) ** log(x, 7)

x = float(input())
print(some_func(x))
```

### № 4

```python
def parity_bit(string: str) -> str:
    if string.count("1") % 2 == 0:
        return string + "0"

    return string + "1"

s = input()

print(parity_bit(s))
```
