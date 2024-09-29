# Рабочая тетрадь № 3

## Задачи № 1

### № 1

```math
132 dec / 2 = 66 0
66      / 2 = 33 0
33      / 2 = 17 1
17      / 2 = 8  1
8       / 2 = 4  0
4       / 2 = 2  0
2       / 2 = 1  0
1       / 2 = 0  1

136 dec = 10001100 bin

0000000010001100
```

### № 2

```math
0000000000000000 bin = 0 dec

1111111111111111 bin = 65535 dec
```

## Задачи № 2

### № 1

```math
12 dec = 1100 bin 

0.0001100
0.0001100
0.0001100
```

### № 2

```math
35 dec = 100011 bin 

1.00100011
1.11011100
1.11011101
```

### № 3

```math
1.1011100
1.1111011

1111011 bin = 123 dec

-123
```

## Задачи № 3

### № 1

```math
A dec = 78  B dec = 56

A bin = +1001110
B bin = +0111000

[A]п = [A]ок = [A]дк = 0.1001110
[B]п = [B]ок = [B]дк = 0.0111000


0.1001110
0.0111000
---------
0.10000110

10000110 bin = 134 dec
```

## Тест № 3

1. B (прямой, обратный или дополнительный код)
2. C (выглядит одинаково в прямом, обратном и дополнительном кодах)
3. A (обратный код)
4. A (из обратного кода прибавлением единицы к младшему разряду без переноса в знаковый разряд)
5. B (прямой код)
6. A (00001110)
7. D (–118)
8. B (+39)
9. A (10111111)
10. 10011001

## Задачи № 4

### № 1

```python
from math import *

def f(x, y: float) -> float:
    return log(abs(sin(x+y)))

x = float(input())
y = float(input())

print(f(x, y))
```

### № 2

```python
from math import *

def (x, y: float) -> float:
    if sin(x + y) <= -0.5:
        return arctg(abs(x * y) ** (1/3) * (x * e ** y))

    if -0.5 < sin(x + y) < 0.5:
        return 3 * log(abs(x * y), 3)

    if sin(x + y) >= 0.5:
        return x ** 3 + y ** 1.5

x = float(input())
y = float(input())

print(f(x, y))
```

### № 3

```python
from math import *

def f(x: float) -> float:
    return cos(e * x) ** 3 + sin(abs(x))

a = float(input())
b = float(input())

hx = float(input())

for x in range(a, b+1, hx):
    print(f(x))
```
