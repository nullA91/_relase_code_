#pragma once

#include "functions_console.h"

#include "constants.h"
#include "libraries.h"
#include "structures.h"

// функции вывода пунктов меню
int menu(); // функция вывода пунктов меню при старте игры(возвращает порядковую целочисленную позицию пункта меню)
void color_selection(int& color); // функция вывода вариантов выбора цвета
// функции расстановки кораблей
void manually_placement(field& _field); // функция расстановки кораблей в ручную
void auto_placement(field& _field); // функция расстановки кораблей автоматически
bool placement_permission(field& _field, const int& x, const int& y, const size_t& ship_size, bool orientation); // функция выдает разрешение на размещение корабля в указанной позиции(чтобы корабли не прилегали друг к другу)
// функции стрельбы
int shoot_player(field& _field_cpu, field& _field_player_empty); // функция стрельбы игрока
int ship_parts(const field& _field_cpu, const int& x, const int& y); // функция определения оставшихся частей корабля до его потопления
// CPU ??
void shoot_random(int& X, int& Y); // функция стрельбы cpu
//aimed_shot();
int shoot_aimed(field& _field_player, int& X, int& Y, const static int& hit);
bool shoot_cpu(field& _field_player, field& _field_cpu_empty);
int length_int_array(const static unsigned int* array);
// функции преобразования строки с русскими символами для правильного вывода в консоли
char* convert_ANSI_string_to_ASCII_string(const char string[]); // функция конвертации ANSI строки в строку формата ASCII пренимающая константную строку
char* convert_ANSI_string_to_ASCII_string(char string[]); // функция конвертации ANSI строки в строку формата ASCII пренимающая неконстантную строку
// ну удаление //
// ### END ### //
// ну удаление //
void draw_border(const int& x, const int& y); // функция не используется