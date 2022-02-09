#include "functions_console.h"
#include "functions.h"
#include "structures.h"

int main(int arg_c, char* arg_v[])
{
	srand(time(NULL));
	start();

	field field_player;
	field field_player_empty;

	size_t X = 0;
	size_t Y = 0;

	field_player.create();
	field_player_empty.create();

	manually_placement(field_player);
	auto_placement(field_player_empty);

	field_player.output(0, 0);
	field_player_empty.output(60, 0);

	system("pause");
	return 0;
}