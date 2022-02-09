#include "functions_console.h"
#include "structures.h"

void field::create()
{
	int index_right_corner = 0; // целочисленная переменная при делении по модулю на которую содержится индекс где должен быть размещен правый угол
								// для верхней и нижней части клеток

	size_t index_row = 0; // индекс строки
	size_t index_col = 0; // индекс столбца

						  // цикл выделяет нужное количество памяти для двумерного динамического массива
	view = new char*[rows]; // количество строк в массиве
	for (size_t i = 0; i < rows; ++i)
	{
		view[i] = new char[columns]; // количество столбцов в массиве
	}
	///////////////////////////////////

	// цикл заполняет массив нужными символами
	for (index_row = 0; index_row < rows;)
	{
		// верхняя часть клеток
		index_right_corner = 4;

		for (index_col = 0; index_col < columns; ++index_col)
		{
			if (index_col % step_col == NULL)
				view[index_row][index_col] = top_left_corner;
			else if (index_col % index_right_corner == NULL)
			{
				view[index_row][index_col] = top_right_corner;
				index_right_corner += step_col;
			}
			else
				view[index_row][index_col] = horizontal_border;
		}
		///////////////////////////////////////////
		++index_row;
		// средняя часть клеток
		index_right_corner = 4;
		for (index_col = 0; index_col < columns; ++index_col)
		{

			if (index_col % step_col == NULL)
				view[index_row][index_col] = vertical_border;
			else if (index_col % index_right_corner == NULL)
			{
				view[index_row][index_col] = vertical_border;
				index_right_corner += step_col;
			}
			else
				view[index_row][index_col] = space;
		}
		///////////////////////////////////////////
		++index_row;
		// нижняя часть клеток
		index_right_corner = 4;
		for (index_col = 0; index_col < columns; ++index_col)
		{
			if (index_col % step_col == 0)
				view[index_row][index_col] = bottom_left_corner;
			else if (index_col % index_right_corner == 0)
			{
				view[index_row][index_col] = bottom_right_corner;
				index_right_corner += step_col;
			}
			else
				view[index_row][index_col] = horizontal_border;
		}
		//////////////////////////////////////////
		++index_row;
	}
}

void field::output(const int& x, const int& y)
{
	const int _rows = 10;
	const unsigned _cols = 6;

	int index = 0;
	int X = 0;
	int Y = 0;

	unsigned char letter = 65;

	char symbol = '\0';

	const char RomanNumerals[_rows][_cols] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };

	cursor_visible(false, NULL);
	X = x;
	Y = y;

	for (size_t i = 0; i < rows; ++i)
	{
		X = x;
		for (size_t j = 0; j < columns; ++j)
		{
			console_cursor(X, Y);
			std::cout << view[i][j];
			++X;
		}

		if (i == rows_indexes[index])
		{
			std::cout << ' ' << RomanNumerals[index];
			++index;
		}

		std::cout << std::endl;
		++Y;
	}

	index = 0;
	X = x + 2;

	for (size_t i = 0; i < columns; ++i)
	{
		if (i == columns_indexes[index])
		{
			console_cursor(X, rows);
			std::cout << letter;
			++letter;
			++index;
			X += step_col;
		}
	}

	std::cout << std::endl;
}
