#pragma once

const unsigned int size = 10;

const unsigned int step_row = 3; // шаг строки
const unsigned int step_col = 5; // шаг столбца

const unsigned int rows_indexes[size] = { 1, 4, 7, 10, 13, 16, 19, 22, 25, 28 }; // массив содержащий индексы строк(видимого игрового поля)
const unsigned int columns_indexes[size] = { 2, 7, 12, 17, 22, 27, 32, 37, 42, 47 }; // массив содержащий индексы столбцов(видимого игрового поля)

// alt символы верхних углов																					 // alt ñèìâîëû âåðõíèõ óãëîâ
const unsigned char top_left_corner = 201; // alt символ верхнего левого угла
const unsigned char top_right_corner = 187; // alt символ верхнего правого угла
// alt символы нижних углов											
const unsigned char bottom_left_corner = 200; // alt символ нижнего левого угла
const unsigned char bottom_right_corner = 188; // alt символ нижнего правого угла
// alt символ верхней и нижней границы											   
const unsigned char horizontal_border = 205;
// alt символ левой и правой границы
const unsigned char vertical_border = 186;

// символ пробела
const unsigned char space = 32;
// клавиша enter
const unsigned char enter = 13;

// символ части корабля
const unsigned char ship_part = static_cast<char>(254);

// стрелки на клавиатуре
const signed char arrows = -32;

const unsigned char up = 72;
const unsigned char down = 80;
const unsigned char left = 75;
const unsigned char right = 77;
