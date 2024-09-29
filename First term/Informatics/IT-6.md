# Рабочая тетрадь № 6

## Задачи № 3

### № 1

```python
word = intput()

if word[::-1] == word:
    print("Палиндром")
else:
    print("Не палиндром")
```

### № 2

```python
word = intput()

print(word.lower())
```

### № 3

```python
word = intput()

print(word.upper())
```

### № 4

```python
word = intput()

for num in 0,1,2,3,4,5,6,7,8,9:
    if str(num) in word:
        print("Есть")
        break
else:
    print("Нет")
```

### № 5

```python
word = intput()

print(" ".join(list(word)))
```

### № 6

```python
c = "C"

print(ord(c))
```

## Задачи № 4

### № 1

```python
print(list(range(0, 101, 17)))
```

### № 2

```python
w = []
c = []
for _ in range(5):
    w.appen(input())
    c.append(w[-1])

print(w, c)
```

## Задачи № 5

### № 1

```python
a = set([1,2,3,4])
b = set([4,34,2,6])

print(a | b)
print(a & b)
print(a - b)
```
