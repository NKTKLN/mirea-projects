# Рабочая тетрадь № 5

## Задачи № 1

### № 1

```math
¬( ( x ∧ y ) ∨ ̅z ) ≡ ¬( z → x ) ∨ ¬( z → y )
¬( x ∧ y ) ∧ z ≡ ¬( ̅z ∨ x ) ∨ ¬( ̅z ∨ y )
( ̅x ∨ ̅y ) ∧ z ≡ ( z ∧ ̅x ) ∨ ( z ∧ ̅y )
( ̅x ∨ ̅y ) ∧ z ≡ z ∧ ( ̅x ∨ ̅y )
( ̅x ∨ ̅y ) ∧ z ≡ ( ̅x ∨ ̅y ) ∧ z
```

### № 2

```math
¬( ( x ∧ y ) ∨ ̅z) ≡ ¬( z → x ) ∨ ¬( z → y )

x y z  f1 f2 
0 0 0  0  0
0 0 1  1  1
0 1 1  1  1
0 1 0  0  0
1 0 0  0  0
1 0 1  1  1
1 1 0  0  0
1 1 1  0  0
```

### № 3

```math
F(x,y,z) = ( ̅z → x ) ↔ ( ̅x │ y )

x y z  f
0 0 0  0
0 0 1  1
0 1 1  0
0 1 0  1
1 0 0  1
1 0 1  1
1 1 0  1 
1 1 1  1

ДНФ: ( y ∧ ̅z ) ∨ ( ̅y ∧ z ) ∨ x 
КНФ: ( x ∨ ̅y ∨ z ) ∧ ( x ∨ y ∨ z )
```

### № 4

```math
A = ( x → y ) ∧ ( x → ̅y ) ∧ x 
A = ( ̅x ∨ y ) ∧ ( ̅x ∨ ̅y ) ∧ x 
A = ( ̅x ∨ ( y ∧ ̅y ) ) ∧ x 
A = ( ̅x ∨ 0 ) ∧ x 
A = ̅x ∧ x 
A = 0
```

## Задачи № 2

### № 1

```math
1) x ∧ y ∨ x ∧ y ∨ ̅x ∧ ̅y
   ( x ∧ y ) ∨ ( ̅x ∧ ̅y )
   ( x ∧ y ) ∨ ( ̅x ∧ ̅y )
   x ↔ y
2) ( x ∨ ̅y ) ∧ ( ̅x ∨ y ) ∧ ( ̅x ∨ ̅y )
   ( x ∨ ̅y ) ∧ ̅x
   ( x ∧ ̅x ) ∨ ( ̅y ∧ ̅x )
   0 ∨ ¬( y ∧ x )
   y | x
```

### № 2

```math
( x1 ∨ x2 ∨ x3 ) ∧ ( ̅x1 ∨ ̅x2 ∨ x3 ) ∧ ( x1 ∨ x2 ∨ ̅x3 ) ∧ ( ̅x1 ∨ ̅x2 ∨ ̅x3 ) 
```

### № 3

```math
1) ( x ∨ ̅x )
2) ( ̅x ∧ ̅y ) ∨ ( x ∧ y ) ∨ ( ̅x ∧ y ) ∨ ( x ∧ ̅y )
```

### № 4

```math
1) ( x ∧ ̅x )
2) ( ̅x ∨ ̅y ) ∧ ( x ∨ y ) ∧ ( ̅x ∨ y ) ∧ ( x ∨ ̅y )
```

### № 5

```math
CДНФ: ( x ∧ y ∧ z ) ∨ ( ̅x ∧ y ∧ z ) ∨ ( ̅x ∧ ̅y ∧ z ) 
CКНФ: ( x ∨ y ∨ z ) ∧ ( x ∨ ̅y ∨ z ) ∧ ( ̅x ∨ y ∨ z ) ∧ ( ̅x ∨ y ∨ ̅z ) ∧ ( ̅x ∨ ̅y ∨ z )
```

## Тест № 5

1. 4
2. 1
3. 1
4. 2
5. 1
6. 3
7. 4
8. 2
9. 2
10. 4

## Задачи № 3

### № 1

```python
a = int(input())
if 100 <= a < 1000 and a % 5 == 0:
    print("Является")
else:
    print("Не является")
```

### № 2

```python
a = int(input())
b = int(input())
c = int(input())

if (a % 2) + (b % 2) + (c % 2) <= 1:
    print("2 и более")
else:
    print("Меньше 2")

```

### № 3

```python
x, y = float(input()), float(input())

if (x >= 0 and x**2 + y**2 <= 1) or (y <= 1 and x >= 0 and y >= x - 1):
    print("Yes")
else:
    print("No")

```

### № 4

```python
import math as m


x, y = float(input()), float(input())

if (y <= m.sin(x) and 0 <= y <= 0.5 and 0 <= x <= m.pi):
    print("Yes")
else:
    print("No")
```

### № 5

```python
x, y = float(input()), float(input())
if (x <= 0 and x**2 + y**2 <= 1) or (x**2 + y**2 <= 1 and y >= x):
    print("Yes")
else:
    print("No")

```

## Задачи № 4

### № 1

```python
# 3
x, y = float(input()), float(input())

if (x >= 0 and x**2 + y**2 <= 1) or (y <= 1 and x >= 0 and y >=// x - 1):
    print("Yes")
else:
    print("No")

# 4
import math as m


x, y = float(input()), float(input())

if (y <= m.sin(x) and 0 <= y <= 0.5 and 0 <= x <= m.pi):
    print("Yes")
else:
    print("No")

# 5
x, y = float(input()), float(input())
 
if (x <= 0 and x**2 + y**2 <= 1) or (x**2 + y**2 <= 1 and y >= x):
    print("Yes")
else:
    print("No")

```
