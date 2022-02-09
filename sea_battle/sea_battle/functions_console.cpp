#include "functions_console.h"
#include "functions.h"

// ������� ������������� ������ � ������� � ������ �����
void console_cursor(int X, int Y)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // ���������� ��� ��������� � ������� �������
	COORD cursor = { X, Y }; // ��������� c��������� ���������� X � Y � ������� ������� ����� ���������� ������ � �������

							 // ������� ���� ���������� ������� �� ���������
	if (!console)
		console = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� ������� � �������� ��� � ���������� console

	SetConsoleCursorPosition(console, cursor); // ������� ������������� ������ � ������ ������� � �������
}
////////////////////////////////////////////////////////

// ������� ������� ��� ����������� ������� � �������
void cursor_visible(bool show, short size)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // ���������� ��� ��������� � ������� �������
	CONSOLE_CURSOR_INFO cursor; // ������ ����������� �� ������ �������(�������� ������ ��������� ������� � ���������)

								// ������� ���� ���������� ������� �� ���������
	if (!console)
		console = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� ������� � �������� ��� � ���������� console

	GetConsoleCursorInfo(console, &cursor); // ������� ��������� ���������� � �������� � ���� ������� ��� ��������� ����������� �������

	cursor.bVisible = show; // �������� ��������� �������
	cursor.dwSize = size;   // �������� ������ �������

	SetConsoleCursorInfo(console, &cursor); // ������� ������������� ������ � ��� ������� ��� ��������� ����������� �������
}
////////////////////////////////////////////////////////

// ������� ������������� ������� �� ���� �����
void full_screen()
{
	HWND window = GetForegroundWindow();

	ShowWindow(window, SW_SHOWMAXIMIZED);
}
////////////////////////////////////////////////////////

// ������� ������������� �������� ��������� ����
void console_header(const char* string)
{
	SetConsoleTitle(string);
}
////////////////////////////////////////////////////////

// ������� �������� ���� ������ � ���� ����������� ����
void console_text_background_color()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	const int shift = 4;

	int color_foreground = 0x0000;
	int color_background = 0x0000;

	std::cout << convert_ANSI_string_to_ASCII_string("���� �������� � �������� ����\n");
	color_selection(color_foreground);
	std::cout << convert_ANSI_string_to_ASCII_string("���� ����\n");
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