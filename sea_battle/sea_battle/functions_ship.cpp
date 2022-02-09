#include "functions_console.h"
#include "functions.h"
#include "structures.h"

void ship::create(const size_t& length)
{
	if (orientation == false)
	{
		rows = 1;

		(length == 1) ? columns = 2 : (length == 2) ? columns = 7 : (length == 3) ? columns = 12 : columns = 17;

		view = new char*[rows];
		view[NULL] = new char[columns];

		for (size_t i = 0; i < columns; ++i)
		{
			(i % step_col == 0) ? view[NULL][i] = ship_part : (i == 2 || i == 3 || i == 7 || i == 8 || i == 12 || i == 13) ? view[NULL][i] = vertical_border : view[NULL][i] = space;
		}
		view[NULL][columns - 1] = '\0';
	}
	else
	{
		columns = 2;

		(length == 1) ? rows = 1 : (length == 2) ? rows = 4 : (length == 3) ? rows = 7 : rows = 10;

		view = new char*[rows];
		for (size_t i = 0; i < rows; ++i)
		{
			view[i] = new char[columns];
		}

		for (size_t i = 0; i < rows; ++i)
		{
			(i % 3 == 0) ? view[i][0] = ship_part : horizontal_border;
			view[i][1] = '\0';
		}
	}
}

void ship::location(const int& x, const int& y)
{
	if (orientation == false)
	{
		console_cursor(x, y);

		for (size_t i = 0; i < columns; ++i)
		{
			std::cout << view[NULL][i];
		}

		console_cursor(NULL, 31);
	}
	else
	{
		int X = x;
		int Y = y;

		for (size_t i = 0; i < rows; ++i)
		{
			console_cursor(X, Y);
			std::cout << view[i][NULL];
			++Y;
		}

		console_cursor(NULL, 31);
	}
}

bool ship::ship_movement(field& _field, int& X, int& Y, size_t& length)
{
	bool anchor = false;

	static int counter = 10;

	char symbol = '\0';

	cursor_visible(false, 1);

	symbol = _getch();

	if (orientation == false)
	{
		if (symbol == arrows)
		{
			symbol = _getch();

			if (symbol == down)
			{
				if (Y < rows_indexes[size - 1])
					Y += step_row;
			}
			else if (symbol == up)
			{
				if (Y > rows_indexes[NULL])
					Y -= step_row;
			}
			else if (symbol == left)
			{
				if (X > columns_indexes[NULL])
					X -= step_col;
			}
			else if (symbol == right)
			{
				if (X < columns_indexes[size - length])
					X += step_col;
			}
		}
		else if (symbol == space)
		{
			ship_turn(length, X, Y);
		}
		else if (symbol == enter)
		{
			if (placement_permission(_field, X, Y, length, orientation) == true)
			{
				anchor = true;

				drop_anchor(_field, X, Y);
				--counter;

				if (counter == 9 || counter == 7 || counter == 4)
					--length;

				create(length);
			}
		}
	}
	else
	{
		if (symbol == arrows)
		{
			symbol = _getch();

			if (symbol == down)
			{
				if (Y < rows_indexes[size - length])
					Y += step_row;
			}
			else if (symbol == up)
			{
				if (Y > rows_indexes[NULL])
					Y -= step_row;
			}
			else if (symbol == left)
			{
				if (X > columns_indexes[NULL])
					X -= step_col;
			}
			else if (symbol == right)
			{
				if (X < columns_indexes[size - 1])
					X += step_col;
			}
		}
		else if (symbol == space)
		{
			ship_turn(length, X, Y);
		}
		else if (symbol == enter)
		{
			if (placement_permission(_field, X, Y, length, orientation) == true)
			{
				anchor = true;

				drop_anchor(_field, X, Y);
				--counter;


				if (counter == 9 || counter == 7 || counter == 4)
					--length;

				create(length);
			}
		}
	}

	return anchor;
}

void ship::ship_turn(const size_t& ship_size, const int& X, const int& Y)
{
	if (orientation == false)
	{
		if (Y <= rows_indexes[size - ship_size])
		{
			delete[]view;
			(orientation) ? orientation = false : orientation = true;
			create(ship_size);
		}
	}
	else
	{
		if (X <= columns_indexes[size - ship_size])
		{
			delete[]view;
			(orientation) ? orientation = false : orientation = true;
			create(ship_size);
		}
	}
}
void ship::drop_anchor(field& _field, const int& x, const int& y)
{
	if (orientation == false)
	{
		for (size_t i = 0; i < columns; ++i)
		{
			_field.view[y][x + i] = ship::view[NULL][i];
		}
		delete[]view;
	}
	else
	{
		for (size_t i = 0; i < rows; ++i)
		{
			_field.view[y + i][x] = ship::view[i][NULL];
		}

		for (size_t i = 0; i < rows; ++i)
			delete[]view[i];
		delete[]view;
	}
}