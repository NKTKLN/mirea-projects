# Рабочая тетрадь № 7

## Задачи № 1

### № 1

```math
А) 0, 0, 0, 5 
Б) 0, 0, 5, 0 
В) 10, 10, 20, 6
```

### № 2

```math
1) s1 = 1, n = 1, n = 2, s = 1,5
2) s1 = 1, n = 2, n = 3, s1 = 1,8
3) 1,8 3 4 2,08 
4) 2,08 4 5 2,8
```

### № 3

```math
5
```

### № 4

```math
А) z = 1
Б) z = 1,9375
```

## Задачи № 2

### № 1

![image](./src/Screenshot%202023-12-02%20094710.png)

### № 2

![image](./src/Screenshot%202023-12-02%20094736.png)

### № 3

![image](./src/Screenshot%202023-12-02%20094750.png)

## Задачи № 3

### № 1

```python
n = 10
b = 2
k = a // b
l = n % b
print("Остаток:", k)
print("Целая часть:", l)
```

### № 2

```python
def Sign(x):
    if x < 0:
        return -1
    elif x > 0:
        return 1
    return 0
```

### № 3

```python
word = str(input())

if word == word[::-1]:
  print("yes")
else:
  print("no")
```

### № 4

```python
sec = int(input())
 
day = 86400
hour = 3600
minute = 60
second = 1

print(sec // day, (sec % day) // hour, ((sec % day) % hour) // minute, ((sec % day) % hour) % minute, sep=':')
```

### № 5

```python
def fibonacci_of(n):
    if n in {0, 1}:
        return n
    return fibonacci_of(n - 1) + fibonacci_of(n - 2)
 

print(fibonacci_of(int(input())))
```
