n, m = map(int, input().split())
matrix = [list(map(int, input().split())) for _ in range(n)]

result = []

top = 0
bottom = n - 1
left = 0
right = m - 1

while top <= bottom and left <= right:
    # Верхняя строка слева направо
    for i in range(left, right + 1):
        result.append(matrix[top][i])
    top += 1
    
    # Правый столбец сверху вниз
    for i in range(top, bottom + 1):
        result.append(matrix[i][right])
    right -= 1
    
    # Нижняя строка справа налево (если есть)
    if top <= bottom:
        for i in range(right, left - 1, -1):
            result.append(matrix[bottom][i])
        bottom -= 1
    
    # Левый столбец снизу вверх (если есть)
    if left <= right:
        for i in range(bottom, top - 1, -1):
            result.append(matrix[i][left])
        left += 1

print(' '.join(map(str, result)))
