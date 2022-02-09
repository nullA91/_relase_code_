#pragma once

#include "functions_console.h"

#include "constants.h"
#include "libraries.h"
#include "structures.h"

// ������� ������ ������� ����
int menu(); // ������� ������ ������� ���� ��� ������ ����(���������� ���������� ������������� ������� ������ ����)
void color_selection(int& color); // ������� ������ ��������� ������ �����
// ������� ����������� ��������
void manually_placement(field& _field); // ������� ����������� �������� � ������
void auto_placement(field& _field); // ������� ����������� �������� �������������
bool placement_permission(field& _field, const int& x, const int& y, const size_t& ship_size, bool orientation); // ������� ������ ���������� �� ���������� ������� � ��������� �������(����� ������� �� ��������� ���� � �����)
// ������� ��������
int shoot_player(field& _field_cpu, field& _field_player_empty); // ������� �������� ������
int ship_parts(const field& _field_cpu, const int& x, const int& y); // ������� ����������� ���������� ������ ������� �� ��� ����������
// CPU ??
void shoot_random(int& X, int& Y); // ������� �������� cpu
//aimed_shot();
int shoot_aimed(field& _field_player, int& X, int& Y, const static int& hit);
bool shoot_cpu(field& _field_player, field& _field_cpu_empty);
int length_int_array(const static unsigned int* array);
// ������� �������������� ������ � �������� ��������� ��� ����������� ������ � �������
char* convert_ANSI_string_to_ASCII_string(const char string[]); // ������� ����������� ANSI ������ � ������ ������� ASCII ����������� ����������� ������
char* convert_ANSI_string_to_ASCII_string(char string[]); // ������� ����������� ANSI ������ � ������ ������� ASCII ����������� ������������� ������
// �� �������� //
// ### END ### //
// �� �������� //
void draw_border(const int& x, const int& y); // ������� �� ������������