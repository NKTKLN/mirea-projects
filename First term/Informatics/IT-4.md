# Рабочая тетрадь № 4

## Задачи № 1

### № 1

```math
AvB⇒A~B

a b f
0 0 0
1 1 1
0 1 0
1 0 0

A̅v¬(B~A)⊕B

a b f
0 0 1
1 1 1
1 0 0
0 1 1

AvB⇒C

a b c f
0 0 0 1
0 0 1 1
0 1 1 1
1 0 1 1
1 1 1 1
0 1 0 0
1 0 0 0
1 1 0 0
```

### № 2

```math
(4)
```

### № 3

```math
(2)
```

### № 4

```math
(4)
```

### № 5

```math
4
```

### № 6

```math
1 0 0 0 
```

### № 7

```math
C, 2
```

## Тест № 3

1. 2 (Таблица истинности)
2. 1 (¬А&¬В)
3. 2 (Сергей)
4. 1 (¬A ∨ ¬B ∨ ¬C)
5. 4 (X ∨ Y ∨ Z)
6. 4 (2)
7. 3 (3)
8. 30
9. 10
10. M, B

## Задачи № 4

### № 1

```python
k = int(input())
n = int(input())

print(2 << k-1 + 2 << n-1)
```

### № 2

```python
n = int(input())

if (n > 0 and (n & (n - 1))) == 0:
    print("Yes")
else:
    print("No")
```

### № 3

```python
a = int(input())
k = int(input())

print(a | (1 << k))
```

### № 4

```python
n = int(input())
k = int(input())

ans = n & ~((1 << k) - 1)

print(ans)
print(bin(n & ~((1 << k) - 1)))
```
