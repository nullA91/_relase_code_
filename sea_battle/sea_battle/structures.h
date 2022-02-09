#pragma once

#include "constants.h"
#include "libraries.h"

struct field
{
	size_t rows = 30;
	size_t columns = 50;

	char** view = nullptr;

	void create();
	void output(const int& x, const int& y);
};

struct ship
{
	bool orientation = false;

	size_t rows = 1;
	size_t columns = 17;

	char** view = nullptr;

	void create(const size_t& length);
	void location(const int& x, const int& y);
	bool ship_movement(field& _field, int& X, int& Y, size_t& length);
	void ship_turn(const size_t& ship_size, const int& X, const int& Y);
	void drop_anchor(field& _field, const int& x, const int& y);
};