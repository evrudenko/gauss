#ifndef _GAUSS_TOOLS_HPP_
#define _GAUSS_TOOLS_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * Приводит строку row в удобную для дальнейшей обработки форму.
 * Удаляет лишние пробелы.
*/
string format_row(string row);

/*
 * Приводит матрицу в файле filename в удобную для дальнейшей обработки
 * форму, использует функцию format_row(). Ширина матрицы определяется
 * шириной первой строки матрицы в файле, не соответствующие ей последующие
 * строки пропускаются. В параметры num_rows и num_cols сохраняется количество
 * строк и столбцов считанной матрицы соответственно. Считанная матрица
 * возвращается строкой.
*/
string format_matrix(string filename, int *num_rows, int *num_cols);

/*
 * Функция формирует матрицу на основе полученной от функции format_matrix
 * строки. ВЫДЕЛЯЕТ ПОД НЕЕ ПОМЯТЬ. В параметры num_rows и num_cols сохраняется
 * количество строк и столбцов считанной матрицы соответственно. Считанная
 * матрица возвращается строкой.
*/
float** read_matrix(string filename, int *num_rows, int *num_cols);

/*
 * Функция проверяет строки матрицы на линейную зависимость.
 * Прим. Возможно, стоило использовать дискриминант..
*/
bool is_linear_relationship(float **M, int num_rows, int num_cols);

/*
 * Функция копирует значения матрицы from_M в значения матрицы to_M. Количество
 * строк и столбцов матриц определяется параметрами num_rows и num_cols соответственно.
 * Функция НЕ ВЫДЕЛЯЕТ ПАМЯТЬ!
*/
void copy_matrix(float **from_M, int num_rows, int num_cols, float **to_M);

/*
 * Функция возвращает решенную по методу Гаусса систему матрицы M.
 * Параметры num_rows и num_cols задают количество строк и столбцов матрицы
 * M соответственно. Функция ВЫДЕЛЯЕТ ПАМЯТЬ.
*/
float** gauss_convert(float **M, int num_rows, int num_cols);

// Функция выводит в консоль матрицу M, размерности num_rows * num_cols.
void list_matrix(float **M, int num_rows, int num_cols);

#endif