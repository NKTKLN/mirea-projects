import numpy as np


def min_zero_row(zero_mat, mark_zero):
    min_row = [99999, -1]

    for row_num in range(zero_mat.shape[0]):
        if np.sum(zero_mat[row_num] == True) > 0 and min_row[0] > np.sum(zero_mat[row_num] == True):
            min_row = [np.sum(zero_mat[row_num] == True), row_num]

    zero_index = np.where(zero_mat[min_row[1]] == True)[0][0]
    mark_zero.append((min_row[1], zero_index))
    zero_mat[min_row[1], :] = False
    zero_mat[:, zero_index] = False


def mark_matrix(mat):
    cur_mat = mat
    zero_bool_mat = (cur_mat == 0)
    zero_bool_mat_copy = zero_bool_mat.copy()

    marked_zero = []
    while (True in zero_bool_mat_copy):
        min_zero_row(zero_bool_mat_copy, marked_zero)

    marked_zero_row = []
    marked_zero_col = []
    for i in range(len(marked_zero)):
        marked_zero_row.append(marked_zero[i][0])
        marked_zero_col.append(marked_zero[i][1])

    non_marked_row = list(set(range(cur_mat.shape[0])) - set(marked_zero_row))

    marked_cols = []
    check_switch = True
    while check_switch:
        check_switch = False
        for i in range(len(non_marked_row)):
            row_array = zero_bool_mat[non_marked_row[i], :]
            for j in range(row_array.shape[0]):
                if row_array[j] == True and j not in marked_cols:
                    marked_cols.append(j)
                    check_switch = True

        for row_num, col_num in marked_zero:
            if row_num not in non_marked_row and col_num in marked_cols:
                non_marked_row.append(row_num)
                check_switch = True

    marked_rows = list(set(range(mat.shape[0])) - set(non_marked_row))

    return (marked_zero, marked_rows, marked_cols)


def adjust_matrix(mat, cover_rows, cover_cols):
    cur_mat = mat
    non_zero_element = []

    for row in range(len(cur_mat)):
        if row not in cover_rows:
            for i in range(len(cur_mat[row])):
                if i not in cover_cols:
                    non_zero_element.append(cur_mat[row][i])
    min_num = min(non_zero_element)

    for row in range(len(cur_mat)):
        if row not in cover_rows:
            for i in range(len(cur_mat[row])):
                if i not in cover_cols:
                    cur_mat[row, i] = cur_mat[row, i] - min_num

    for row in range(len(cover_rows)):
        for col in range(len(cover_cols)):
            cur_mat[cover_rows[row], cover_cols[col]] = cur_mat[cover_rows[row], cover_cols[col]] + min_num
    
    return cur_mat


def hungarian_algorithm(mat):
    dim = mat.shape[0]
    cur_mat = mat

    for row_num in range(mat.shape[0]):
        cur_mat[row_num] = cur_mat[row_num] - np.min(cur_mat[row_num])

    for col_num in range(mat.shape[1]):
        cur_mat[:, col_num] = cur_mat[:, col_num] - np.min(cur_mat[:, col_num])
    
    zero_count = 0
    while zero_count < dim:
        ans_pos, marked_rows, marked_cols = mark_matrix(cur_mat)
        zero_count = len(marked_rows) + len(marked_cols)

        if zero_count < dim:
            cur_mat = adjust_matrix(cur_mat, marked_rows, marked_cols)

    return ans_pos


def ans_calculation(mat, ans_pos):
    total = 0
    ans_mat = np.zeros((mat.shape[0], mat.shape[1]))
    for i in range(len(ans_pos)):
        total += mat[ans_pos[i][0], ans_pos[i][1]]
        ans_mat[ans_pos[i][0], ans_pos[i][1]] = mat[ans_pos[i][0], ans_pos[i][1]]
    
    return total, ans_mat


def main():
    cost_matrix = np.array([
        [7, 3, 6, 9, 5],
        [7, 5, 7, 5, 6],
        [7, 6, 8, 8, 9],
        [3, 1, 6, 5, 7],
        [2, 4, 9, 9, 5]
    ])

    ans_pos = hungarian_algorithm(cost_matrix.copy())
    ans, ans_mat = ans_calculation(cost_matrix, ans_pos)
    print(f"Result min: {ans:.0f}\n{ans_mat}")

    profit_matrix = np.array([
        [7, 3, 6, 9, 5],
        [7, 5, 7, 5, 6],
        [7, 6, 8, 8, 9],
        [3, 1, 6, 5, 7],
        [2, 4, 9, 9, 5]
    ])
    max_value = np.max(profit_matrix)
    cost_matrix = max_value - profit_matrix
    
    ans_pos = hungarian_algorithm(cost_matrix.copy())
    ans, ans_mat = ans_calculation(profit_matrix, ans_pos)
    print(f"Result max: {ans:.0f}\n{ans_mat}")


if __name__ == '__main__':
    main()
