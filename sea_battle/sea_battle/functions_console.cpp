#include "functions_console.h"
#include "functions.h"

// функция устанавливает курсор в консоли в нужное место
void console_cursor(int X, int Y)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // переменная для обращения к объекту консоли
	COORD cursor = { X, Y }; // структура cодержащая координаты X и Y в позицию которых будет установлен курсор в консоли

							 // условие если дескриптор консоли не определен
	if (!console)
		console = GetStdHandle(STD_OUTPUT_HANDLE); // получить дескриптор консоли и записать его в переменную console

	SetConsoleCursorPosition(console, cursor); // функция устанавливает курсор в нужную позицию в консоли
}
////////////////////////////////////////////////////////

// функция скрытия или отображения курсора в консоли
void cursor_visible(bool show, short size)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // переменная для обращения к объекту консоли
	CONSOLE_CURSOR_INFO cursor; // объект ссылающийся на курсор консоли(содержит методы установки размера и видимости)

								// условие если дескриптор консоли не определен
	if (!console)
		console = GetStdHandle(STD_OUTPUT_HANDLE); // получить дескриптор консоли и записать его в переменную console

	GetConsoleCursorInfo(console, &cursor); // функция извлекает информацию о размерах и виде курсора для заданного дескриптора консоли

	cursor.bVisible = show; // изменяем видимость курсора
	cursor.dwSize = size;   // изменяем размер курсора

	SetConsoleCursorInfo(console, &cursor); // функция устанавливает размер и вид курсора для заданного дескриптора консоли
}
////////////////////////////////////////////////////////

// функция разворачивает консоль на весь экран
void full_screen()
{
	HWND window = GetForegroundWindow();

	ShowWindow(window, SW_SHOWMAXIMIZED);
}
////////////////////////////////////////////////////////

// функция устанавливает название заголовка окна
void console_header(const char* string)
{
	SetConsoleTitle(string);
}
////////////////////////////////////////////////////////

// функция изменяет цвет текста и фона консольного окна
void console_text_background_color()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int shift = 4;

	int color_foreground = 0x0000;
	int color_background = 0x0000;

	std::cout << convert_ANSI_string_to_ASCII_string("цвет кораблей и игрового поля\n");
	color_selection(color_foreground);
	std::cout << convert_ANSI_string_to_ASCII_string("цвет фона\n");
	color_selection(color_background);

	color_background <<= shift;

	SetConsoleTextAttribute(console, color_foreground | color_background);
}
////////////////////////////////////////////////////////

void start() // ???
{
	int choise = 0;

	console_header("Sea Battle");
	choise = menu();


	if (choise == 3)
		console_text_background_color();
	else if (choise == 4)
		exit(0);

	system("cls");
	full_screen();
}

//color_background = color_background << shift;
