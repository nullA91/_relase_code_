#include "functions.h"

// функции вывода пунктов меню
int menu()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	char symbol = '\0';

	const size_t rows = 4;
	const size_t columns = 15;

	int X = 0;
	int Y = 0;

	int menu_choose = 0;

	char menu_item[rows][columns];

	strcpy_s(menu_item[0], convert_ANSI_string_to_ASCII_string("новая игра"));
	strcpy_s(menu_item[1], convert_ANSI_string_to_ASCII_string("загрузить игру"));
	strcpy_s(menu_item[2], convert_ANSI_string_to_ASCII_string("настройки"));
	strcpy_s(menu_item[3], convert_ANSI_string_to_ASCII_string("выход"));

	X = 100;
	Y = 25;

	SetConsoleTextAttribute(console, FOREGROUND_BLUE);
	full_screen();

	while (true)
	{
		cursor_visible(false, 1);

		Y = 25;

		for (size_t i = 0; i < rows; ++i)
		{
			if (i == menu_choose)
				SetConsoleTextAttribute(console, FOREGROUND_GREEN);
			else
				SetConsoleTextAttribute(console, FOREGROUND_BLUE);

			console_cursor(X, Y);
			std::cout << menu_item[i];
			++Y;
		}

		symbol = _getch();

		if (symbol == arrows)
		{
			symbol = _getch();

			if (symbol == down)
			{
				if (menu_choose < rows - 1)
					++menu_choose;
			}
			else if (symbol == up)
			{
				if (menu_choose > 0)
					--menu_choose;
			}
		}
		else if (symbol == enter)
		{
			SetConsoleTextAttribute(console, 0x000F | NULL);
			system("cls");
			return menu_choose + 1;
		}
	}
}

void color_selection(int& color)
{
	const size_t length = 15;
	const int figure = 3;

	int increment = 0;
	int index = 0;

	char colors[length + 1][length];

	strcpy_s(colors[0], convert_ANSI_string_to_ASCII_string("черный"));
	strcpy_s(colors[1], convert_ANSI_string_to_ASCII_string("синий"));
	strcpy_s(colors[2], convert_ANSI_string_to_ASCII_string("зеленый"));
	strcpy_s(colors[3], convert_ANSI_string_to_ASCII_string("голубой"));
	strcpy_s(colors[4], convert_ANSI_string_to_ASCII_string("красный"));
	strcpy_s(colors[5], convert_ANSI_string_to_ASCII_string("розовый"));
	strcpy_s(colors[6], convert_ANSI_string_to_ASCII_string("оранжевый"));
	strcpy_s(colors[7], convert_ANSI_string_to_ASCII_string("светло серый"));
	strcpy_s(colors[8], convert_ANSI_string_to_ASCII_string("серый"));
	strcpy_s(colors[9], convert_ANSI_string_to_ASCII_string("светло синий"));
	strcpy_s(colors[10], convert_ANSI_string_to_ASCII_string("светло зеленый"));
	strcpy_s(colors[11], convert_ANSI_string_to_ASCII_string("светло голубой"));
	strcpy_s(colors[12], convert_ANSI_string_to_ASCII_string("светло красный"));
	strcpy_s(colors[13], convert_ANSI_string_to_ASCII_string("светло розовый"));
	strcpy_s(colors[14], convert_ANSI_string_to_ASCII_string("желтый"));
	strcpy_s(colors[15], convert_ANSI_string_to_ASCII_string("белый"));

	increment = figure + 2;

	std::cout << top_left_corner;
	for (size_t i = 0; i < length + increment; ++i)
		std::cout << horizontal_border;
	std::cout << top_right_corner << std::endl;

	for (size_t i = 0; i < length + 1; ++i)
	{
		increment = (i < pow(figure, 2)) ? figure + 2 : figure + 1;

		std::cout << vertical_border;
		std::cout << i + 1 << ". " << colors[i];
		for (size_t j = strlen(colors[i]) + figure; j < length + increment; ++j)
			std::cout << space;
		std::cout << vertical_border << std::endl;
	}

	increment = figure + 2;

	std::cout << bottom_left_corner;
	for (size_t i = 0; i < length + increment; ++i)
		std::cout << horizontal_border;
	std::cout << bottom_right_corner << std::endl;

	std::cout << convert_ANSI_string_to_ASCII_string("введите порядковый номер цвета: ");
	std::cin >> index;

	system("cls");

	color = 0x000 + --index;
}
// функции расстановки кораблей
void auto_placement(field& _field)
{
	srand(time(NULL));

	ship _ship;

	int X = 0;
	int Y = 0;
	int ship_size = 0;

	static int ships = 10;

	bool orientations[2] = { false, true };

	ship_size = 4;

	while (ships)
	{
		_ship.orientation = orientations[rand() % 2];
		_ship.create(ship_size);

		if (_ship.orientation == false)
		{
			X = columns_indexes[rand() % (size - ship_size + 1)];
			Y = rows_indexes[rand() % size];

			if (placement_permission(_field, X, Y, ship_size, _ship.orientation))
			{
				_ship.drop_anchor(_field, X, Y);
				--ships;

				if (ships == 9 || ships == 7 || ships == 4)
					--ship_size;
			}
			else
			{
				for (size_t i = 0; i < _ship.rows; ++i)
					delete[] _ship.view[i];
				delete[] _ship.view;
			}
		}
		else
		{
			X = columns_indexes[rand() % size];
			Y = rows_indexes[rand() % (size - ship_size + 1)];

			if (placement_permission(_field, X, Y, ship_size, _ship.orientation))
			{
				_ship.drop_anchor(_field, X, Y);
				--ships;

				if (ships == 9 || ships == 7 || ships == 4)
					--ship_size;
			}
			else
			{
				for (size_t i = 0; i < _ship.rows; ++i)
					delete[] _ship.view[i];
				delete[] _ship.view;
			}
		}
	}
}

void manually_placement(field& _field)
{
	srand(time(NULL));

	ship _ship;

	size_t ship_length = 0;

	static int ships = 10;

	int X = 0;
	int Y = 0;

	ship_length = 4;

	X = columns_indexes[4];
	Y = rows_indexes[4];

	_ship.create(ship_length);

RAND:
	if (_ship.orientation == false)
	{
		X = columns_indexes[rand() % (size - ship_length)];
		Y = rows_indexes[rand() % size];
	}
	else
	{
		X = columns_indexes[rand() % size];
		Y = rows_indexes[rand() % (size - ship_length)];
	}

	while (ships)
	{
		_field.output(NULL, NULL);
		_ship.location(X, Y);

		if (_ship.ship_movement(_field, X, Y, ship_length))
		{
			--ships;
			goto RAND;
		}

		if (!ships)
		{
			for (size_t i = 0; i < _ship.rows; ++i)
				delete[] _ship.view[i];
			delete[] _ship.view;
		}
	}
}

bool placement_permission(field& _field, const int& x, const int& y, const size_t& ship_size, bool orientation)
{
	bool returned_value = true;

	int iteration_vertical = 0;
	int iteration_horizontal = 0;

	int decrement_horizontal = 0;
	int decrement_vertical = 0;

	int X = 0;
	int Y = 0;

	if (orientation == false)
	{
		X = 0;
		Y = 0;

		if (x == columns_indexes[NULL])
		{
			decrement_horizontal = 0;
			iteration_horizontal = ship_size + 1;
			X = x - decrement_horizontal;
		}
		else if (x == columns_indexes[size - ship_size])
		{
			decrement_horizontal = step_col;
			iteration_horizontal = ship_size + 1;
			X = x - decrement_horizontal;
		}
		else
		{
			decrement_horizontal = step_col;
			iteration_horizontal = ship_size + 2;
			X = x - decrement_horizontal;
		}
		////////////////////////////////////////
		if (y == rows_indexes[NULL])
		{
			decrement_vertical = 0;
			iteration_vertical = 2;
			Y = y - decrement_vertical;
		}
		else if (y == rows_indexes[size - 1])
		{
			decrement_vertical = step_row;
			iteration_vertical = 2;
			Y = y - decrement_vertical;
		}
		else
		{
			decrement_vertical = step_row;
			iteration_vertical = 3;
			Y = y - decrement_vertical;
		}

		for (size_t i = 0; i < iteration_vertical; ++i)
		{
			for (size_t j = 0; j < iteration_horizontal; ++j)
			{
				if (static_cast<unsigned char>(_field.view[Y][X]) == ship_part)
				{
					returned_value = false;
					break;
				}
				X += step_col;
			}
			X = x - decrement_horizontal;
			Y += step_row;
		}
	}
	else
	{
		X = 0;
		Y = 0;

		if (y == rows_indexes[NULL])
		{
			decrement_vertical = 0;
			iteration_vertical = ship_size + 1;
			Y = y - decrement_vertical;
		}
		else if (y == rows_indexes[size - ship_size])
		{
			decrement_vertical = step_row;
			iteration_vertical = ship_size + 1;
			Y = y - decrement_vertical;
		}
		else
		{
			decrement_vertical = step_row;
			iteration_vertical = ship_size + 2;
			Y = y - decrement_vertical;
		}
		/////////////////////////////////////
		if (x == columns_indexes[NULL])
		{
			decrement_horizontal = 0;
			iteration_horizontal = 2;
			X = x - decrement_horizontal;
		}
		else if (x == columns_indexes[size - 1])
		{
			decrement_horizontal = step_col;
			iteration_horizontal = 2;
			X = x - decrement_horizontal;
		}
		else
		{
			decrement_horizontal = step_col;
			iteration_horizontal = 3;
			X = x - decrement_horizontal;
		}

		for (size_t i = 0; i < iteration_vertical; ++i)
		{
			for (size_t j = 0; j < iteration_horizontal; ++j)
			{
				if (static_cast<unsigned char>(_field.view[Y][X]) == ship_part)
				{
					returned_value = false;
					break;
				}
				X += step_col;
			}
			X = x - decrement_horizontal;
			Y += step_row;
		}
	}

	return returned_value;
}
// функции стрельбы
int shoot_player(field& _field_cpu, field& _field_player_empty)
{
	static int parts = 1;

	char x = 0;
	int X = 0;
	int Y = 0;
	int returned_value = 0;

	console_cursor(0, 32);
	std::cout << convert_ANSI_string_to_ASCII_string("введите координату по оси x: ");
	std::cin >> x;
	X = columns_indexes[static_cast<int>(x) - 65];
	std::cout << convert_ANSI_string_to_ASCII_string("введите координату по оси y: ");
	std::cin >> Y;
	Y = rows_indexes[Y - 1];

	if (static_cast<unsigned char>(_field_cpu.view[Y][X]) == ship_part)
	{
		_field_cpu.view[Y][X] = 'X';
		_field_player_empty.view[Y][X] = 'X';

		parts = parts + ship_parts(_field_cpu, X, Y);
		--parts;

		if (parts)
		{
			returned_value = 1;
		}
		else
		{
			parts = 1;
			returned_value = -1;
		}
	}
	else
	{
		_field_player_empty.view[Y][X] = 'O';
		returned_value = 0;
	}

	return returned_value;
}

int ship_parts(const field& _field, const int& x, const int& y)
{
	int returned_value = 0;

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;

	// ось X
	if (x == columns_indexes[NULL])
	{
		right = x + step_col;
		left = x;
	}
	else if (x == columns_indexes[size - 1])
	{
		left = x - step_col;
		right = x;
	}
	else
	{
		right = x + step_col;
		left = x - step_col;
	}
	// ось Y
	if (y == rows_indexes[NULL])
	{
		down = y + step_row;
		up = y;
	}
	else if (y == rows_indexes[size - 1])
	{
		up = y - step_row;
		down = y;
	}
	else
	{
		up = y - step_row;
		down = y + step_row;
	}
	// проверка близлежащих координат
	if (static_cast<unsigned char>(_field.view[up][x]) == ship_part)
		++returned_value;
	if (static_cast<unsigned char>(_field.view[down][x]) == ship_part)
		++returned_value;
	if (static_cast<unsigned char>(_field.view[y][left]) == ship_part)
		++returned_value;
	if (static_cast<unsigned char>(_field.view[y][right]) == ship_part)
		++returned_value;

	return returned_value;
}
//
void shoot_random(int& X, int& Y)
{
	static bool Initialization = true;

	static unsigned int coordinates[size][size];

	int index_row = 0;
	int index_col = 0;

	int length;
	// ..
	if (Initialization)
	{
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				coordinates[i][j] = columns_indexes[j];
			}
		}
		Initialization = false;
	}
	// ..
RowSelection:
	index_row = rand() % size;
	length = length_int_array(coordinates[index_row]);
	if (length)
	{
		index_col = rand() % length;
		Y = rows_indexes[index_row];
		X = coordinates[index_row][index_col];
		
		for (int i = index_col; i < length - 1; ++i)
		{
			coordinates[index_row][i] = coordinates[index_row][(i + 1)];
		}
		coordinates[index_row][(length - 1)] = -1;
	}
	else
	{
		goto RowSelection;
	}
}
//
bool shoot_cpu(field& _field_player, field& _field_cpu_empty)
{
	static bool Initialization = true;

	static unsigned int hit = 0;
	static unsigned int coordinates[size][size];

	int index_row = 0;
	int index_col = 0;
	int X = 0;
	int Y = 0;

	int length;
	   // ################################################## //
	  //********* инициализация двумерного массива *********//
	 //********* координатами отресумого поля *************//
	// ################################################## //
	if (Initialization)
	{
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				coordinates[i][j] = columns_indexes[j];
			}
		}
		Initialization = false;
	}
	  // ################################################# //
	 //********************** конец **********************//
	// ################################################# //

	static bool random = true;

	  // ################################################# //
	 //**************** случайный выстрел ****************//
	// ################################################# //
	if (random)
	{
	RowSelection:
		index_row = rand() % size;
		length = length_int_array(coordinates[index_row]);
		if (length)
		{
			index_col = rand() % length;
			Y = rows_indexes[index_row];
			X = coordinates[index_row][index_col];

			for (int i = index_col; i < length - 1; ++i)
			{
				coordinates[index_row][i] = coordinates[index_row][(i + 1)];
			}
			coordinates[index_row][(length - 1)] = -1;
		}
		else
		{
			goto RowSelection;
		}
	}
	 // ################################################# //
	//********************** конец **********************//
   // ################################################# //



	  // ################################################# //
	 //**************** прицельный выстрел ***************//
	// ################################################# //
	else
	{
		static int long_coord[4] = { Y - step_row, X - step_col, Y + step_row, X + step_col };
		static int short_coord[2];
		static int shoot = 0;
		static bool long_short = true;

		if (shoot == 0)
		{
			short_coord[0] = Y - step_row;
			short_coord[1] = Y + step_row * hit;
		}
		else if (shoot == 2)
		{
			short_coord[0] = Y + step_row;
			short_coord[1] = Y - step_row * hit;
		}
		else if (shoot == 1)
		{
			short_coord[0] = X - step_col;
			short_coord[1] = X + step_col * hit;
		}
		else if (shoot == 3)
		{
			short_coord[0] = X + step_col;
			short_coord[1] = X - step_col * hit;
		}

		if(hit == 1) {}
	}

	if (static_cast<unsigned char>(_field_player.view[Y][X]) == ship_part)
	{
		_field_player.view[Y][X] = 'X';

		if (ship_parts(_field_player, X, Y))
		{
			random = false;
			++hit;
		}
		else
		{
			random = true;
			hit = 0;
		}

		return true;
	}
	else
	{
		_field_player.view[Y][X] = 'O';

		return false;
	}
}
//
int shoot_aimed(field& _field_player, int& X, int& Y, const static int& hit)
{	
	static int directions[4] = { 0, 1, 2, 3 };
	static int coordinates[4] = { Y - step_row, X - step_col, Y + step_row, X + step_col };

	int direction = 0;
	int scatter = 4;
	int returned_value = 0;
	int coordinate = 0;
	int index = 0;
	
	if (hit == 1)
	{
		scatter = 4;
		DIRECTION:
		index = rand() % scatter;

		if (directions[index] != -1)
		{
			direction = directions[index];
			coordinate = coordinates[direction];
			
			if (direction % 2 == 0)
			{
				if (static_cast<unsigned char>(_field_player.view[coordinate][X]) == ship_part)
				{
					Y = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}
				// координата по оси Y
			}
			else
			{
				if (static_cast<unsigned char>(_field_player.view[Y][coordinate]) == ship_part)
				{
					X = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}
				// координата по оси Х
			}
		}
		else
		{
			goto DIRECTION;
		}
	}
	else
	{
		if (direction == 1)
		{
			DIR1:
			index = rand() % scatter;
			if (directions[index] != -1)
			{
				if (direction == directions[index])
				{
					coordinate = X - step_col;
				}
				else
				{
					coordinate = X + step_col * hit;
				}
				if (static_cast<unsigned char>(_field_player.view[Y][coordinate]) == ship_part)
				{
					X = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}

			}
			else
				goto DIR1;
		}
		else if (direction == 3)
		{
		DIR3:
			index = rand() % scatter;
			if (directions[index] != -1)
			{
				if (direction == directions[index])
				{
					coordinate = X + step_col;
				}
				else
				{
					coordinate = X - step_col * hit;
				}
				if (static_cast<unsigned char>(_field_player.view[Y][coordinate]) == ship_part)
				{
					X = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}

			}
			else
				goto DIR3;
		}
		else if (direction == 2)
		{
		DIR2:
			index = rand() % scatter;
			if (directions[index] != -1)
			{
				if (direction == directions[index])
				{
					coordinate = Y + step_row;
				}
				else
				{
					coordinate = Y - step_row * hit;
				}
				if (static_cast<unsigned char>(_field_player.view[Y][coordinate]) == ship_part)
				{
					Y = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}

			}
			else
				goto DIR2;
		}
		else if (direction == 0)
		{
		DIR0:
			index = rand() % scatter;
			if (directions[index] != -1)
			{
				if (direction == directions[index])
				{
					coordinate = Y + step_row;
				}
				else
				{
					coordinate = Y - step_row * hit;
				}
				if (static_cast<unsigned char>(_field_player.view[Y][coordinate]) == ship_part)
				{
					Y = coordinate;
					if (ship_parts(_field_player, X, Y))
					{
						return 1;
					}
					else
					{
						for (size_t i = 0; i < 4; ++i)
							directions[i] = i;
						return -1;
					}
				}
				else
				{
					directions[index] = -1;
					return 0;
				}

			}
			else
				goto DIR0;
		}
	}
}
//
int length_int_array(const static unsigned int* array)
{
	int length = 0;

	for (size_t i = 0; i < size; ++i)
	{
		if (array[i] == -1)
			return length;
		else
			++length;
	}

	return length;
}
// функции преобразования строки с русскими символами для правильного вывода в консоли
char* convert_ANSI_string_to_ASCII_string(const char string[])
{
	char* _new_string = new char[strlen(string) + 2];

	int i = 0;

	while (string[i] != '\0')
	{
		unsigned char symbol = string[i];

		if ((symbol >= 192) && (symbol <= 255))
			if (symbol < 240)
				_new_string[i] = string[i] - 64;
			else
				_new_string[i] = string[i] - 16;
		else
			_new_string[i] = string[i];
		i++;
	}

	_new_string[i] = '\0';

	return _new_string;
}

char* convert_ANSI_string_to_ASCII_string(char string[])
{
	char* _new_string = new char[strlen(string) + 2];

	int i = 0;

	while (string[i] != '\0')
	{
		unsigned char symbol = string[i];

		if ((symbol >= 192) && (symbol <= 255))
			if (symbol < 240)
				_new_string[i] = string[i] - 64;
			else
				_new_string[i] = string[i] - 16;
		else
			_new_string[i] = string[i];
		i++;
	}

	_new_string[i] = '\0';

	return _new_string;
}
// ну удаление //
// ### END ### //
// ну удаление //
void draw_border(const int& x, const int& y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int shift = 4;

	int color_border = 0x0000;
	int color_background = 0x0000;

	std::cout << convert_ANSI_string_to_ASCII_string("цвет границы\n");
	color_selection(color_border);
	std::cout << convert_ANSI_string_to_ASCII_string("цвет фона границы\n");
	color_selection(color_background);

	color_background <<= shift;

	SetConsoleTextAttribute(console, color_border | color_background);

	int X = 0;
	int Y = 0;

	X = x;
	Y = y;

	for (size_t j = 0; j < 3; ++j)
	{
		Y = NULL;
		for (size_t i = 0; i < 30; ++i)
		{
			console_cursor(X, Y);
			std::cout << ship_part;
			++Y;
		}
		++X;
	}
}


/*
static bool flag = true;

static int directions[4] = { 0, 1, 2, 3 };

int* coordinates = nullptr;

size_t scatter = 0;
static int coordinate = 0;
static int direction = 0;

if (hit == 1)
{
scatter = 4;
coordinates = new int[scatter];
coordinates[0] = Y - step_row;
coordinates[1] = X - step_col;
coordinates[2] = Y + step_row;
coordinates[3] = X + step_col;

DIRECTION:
direction = directions[rand() % scatter];
if (direction != -1)
{
if (direction % 2 == 0)
{
Y = coordinates[direction];
}
else
{
X = coordinates[direction];
}

directions[direction] = -1;
}
else
{
goto DIRECTION;
}
}
else
{
if (coordinates != nullptr)
delete[] coordinates;

scatter = 2;
coordinates = new int[scatter];

if (direction == 0)
{
coordinates[0] = Y - step_row;
coordinates[1] = Y + step_row * hit;

if(flag)
coordinate = rand() % scatter;
else
{
if (coordinate)
coordinate = 0;
else
coordinate = 1;
}

Y = coordinates[coordinate];

flag = !flag;

delete[] coordinates;
}
else if (direction == 2)
{
static bool flag = true;

coordinates[0] = Y - step_row * hit;
coordinates[1] = Y + step_row;

if (flag)
coordinate = rand() % scatter;
else
{
if (coordinate)
coordinate = 0;
else
coordinate = 1;
}

Y = coordinates[coordinate];

flag = !flag;

delete[] coordinates;
}
else if (direction == 1)
{
static bool flag = true;

coordinates[0] = X - step_col;
coordinates[1] = X + step_col * hit;

if (flag)
coordinate = rand() % scatter;
else
{
if (coordinate)
coordinate = 0;
else
coordinate = 1;
}

X = coordinates[coordinate];

flag = !flag;

delete[] coordinates;
}
else if (direction == 3)
{
static bool flag = true;

coordinates[0] = X - step_col * hit;
coordinates[1] = X + step_col;

if (flag)
coordinate = rand() % scatter;
else
{
if (coordinate)
coordinate = 0;
else
coordinate = 1;
}

X = coordinates[coordinate];

flag = !flag;

delete[] coordinates;
}
}

*/
/*
if (static_cast<unsigned char>(_field_player.view[Y][X]) == ship_part)
{
	_field_cpu_empty.view[Y][X] = 'X';
	++hit;
	flag = true;
	if (flag)
	{
		if (ship_parts(_field_player, X, Y))
		{
			if (hit == 1)
			{
				int coord[4] = { Y - step_row, X - step_col, Y + step_row, X + step_col };
				shoot = rand() % 4;
				if (shoot == 0)
				{
					--index_row;
					for (int i = index_col; i < length - 1; ++i)
					{
						coordinates[index_row][i] = coordinates[index_row][(i + 1)];
					}
					coordinates[index_row][(length - 1)] = -1;
					if (static_cast<unsigned char>(_field_player.view[shoot][X]) == ship_part)
					{
						_field_cpu_empty.view[Y][X] = 'X';

					}
					else
					{
						_field_cpu_empty.view[Y][X] = 'Y';
					}
				}
			}
		}
		else
		{
			hit = 0;
			goto RowSelection;
		}
	}
}
else
{
	flag = false;
	_field_cpu_empty.view[Y][X] = 'O';
}
*/