#pragma once

const unsigned int size = 10;

const unsigned int step_row = 3; // ��� ������
const unsigned int step_col = 5; // ��� �������

const unsigned int rows_indexes[size] = { 1, 4, 7, 10, 13, 16, 19, 22, 25, 28 }; // ������ ���������� ������� �����(�������� �������� ����)
const unsigned int columns_indexes[size] = { 2, 7, 12, 17, 22, 27, 32, 37, 42, 47 }; // ������ ���������� ������� ��������(�������� �������� ����)

																					 // alt ������� ������� �����
const unsigned char top_left_corner = 201; // alt ������ �������� ������ ����
const unsigned char top_right_corner = 187; // alt ������ �������� ������� ����
											// alt ������� ������ �����
const unsigned char bottom_left_corner = 200; // alt ������ ������� ������ ����
const unsigned char bottom_right_corner = 188; // alt ������ ������� ������� ����
											   // alt ������ ������� � ������ �������
const unsigned char horizontal_border = 205;
// alt ������ ����� � ������ �������
const unsigned char vertical_border = 186;

// ������ �������
const unsigned char space = 32;
// ������� enter
const unsigned char enter = 13;

// ������ ����� �������
const unsigned char ship_part = static_cast<char>(254);

// ������� �� ����������
const signed char arrows = -32;

const unsigned char up = 72;
const unsigned char down = 80;
const unsigned char left = 75;
const unsigned char right = 77;