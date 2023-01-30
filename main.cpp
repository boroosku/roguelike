#include <iostream>
#include <string>
#include <deque>
#include <time.h>
#include <conio.h>
#include <vector>

using namespace std;

int main()
{
	srand(time(NULL));

	string start_message = "you feel an evil presence watching you...";
	string game_over_message = "Game over. Thanks for playing!";
	string wall_hit_message = "you walked onto wall...";
	string move_message = "movement is life";
	string shoot_message = "pew! pew! reloading!";
	string reload_message = "you can't shoot when you are reloading...";
	string wall_shoot_message = "why did you shoot the wall?";
	string look_up = "you look up";
	string look_left = "you look left";
	string look_right = "you look right";
	string look_down = "you look down";

exit:
	int x = 5 + rand() % 10;
	int y = 10 + rand() % 15;

	int fireballs_size = 0;
	deque<string> fireballs_direction;
	deque<int> fireballs_x;
	deque<int> fireballs_y;

	int slimes_size = 5 + rand() % 8;
	deque<int> slimes_x(slimes_size);
	deque<int> slimes_y(slimes_size);

	vector<vector<char>> map;
	for (int i = 0; i < x; i++)
	{
		vector<char> v;
		for (int j = 0; j < y; j++) {
			if (i == 0 || j == 0 || i == x - 1 || j == y - 1) {
					v.push_back('#');
			} else {
				v.push_back('.');
			}
		}
		map.push_back(v);
	}

	string previous_move = "pass";
	string player_direction = look_down;
	int player_x = 1 + rand() % (x - 2);
	int player_y = 1 + rand() % (y - 2);
	map[player_x][player_y] = '@';

	while (true) {
		int exit_x = 1 + rand() % (x - 2);
		int exit_y = 1 + rand() % (y - 2);
		if (map[exit_x][exit_y] == '.') {
			map[exit_x][exit_y] = '<';
			break;
		}
	}

	for (int i = 0; i < slimes_size; i++) {
		while (true) {
			slimes_x[i] = 1 + rand() % (x - 2);
			slimes_y[i] = 1 + rand() % (y - 2);
			if (map[slimes_x[i]][slimes_y[i]] == '.') {
				map[slimes_x[i]][slimes_y[i]] = 'S';
				break;
			}
		}
	}

	char button;

	cout << player_direction << endl << start_message << endl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "w - up" << endl << "s - down" << endl << "a - left" << endl << "d - right" << endl << endl << "z - shoot" << endl << "q - quit" << endl;


	do {
		button = _getch();
		system("cls");

		int new_x = player_x;
		int new_y = player_y;
		string new_direction;

		for (int i = 0; i < fireballs_size; i++) {
			int fireball_x = fireballs_x[i];
			int fireball_y = fireballs_y[i];

			if (fireballs_direction[i] == look_up) {
				fireball_x--;
			}
			if (fireballs_direction[i] == look_down) {
				fireball_x++;
			}
			if (fireballs_direction[i] == look_right) {
				fireball_y++;
			}
			if (fireballs_direction[i] == look_left) {
				fireball_y--;
			}
			if (map[fireball_x][fireball_y] == '.') {
				map[fireball_x][fireball_y] = '*';
				map[fireballs_x[i]][fireballs_y[i]] = '.';
				fireballs_x[i] = fireball_x;
				fireballs_y[i] = fireball_y;
			}
			if (map[fireball_x][fireball_y] == '#' || map[fireball_x][fireball_y] == '<') {
				map[fireballs_x[i]][fireballs_y[i]] = '.';
				fireballs_x.erase(fireballs_x.begin() + i);
				fireballs_y.erase(fireballs_y.begin() + i);
				fireballs_direction.erase(fireballs_direction.begin() + i);
				fireballs_size--;
				i--;
			}
			if (map[fireball_x][fireball_y] == 'S') {
				map[fireball_x][fireball_y] = '.';
				map[fireballs_x[i]][fireballs_y[i]] = '.';
				fireballs_x.erase(fireballs_x.begin() + i);
				fireballs_y.erase(fireballs_y.begin() + i);
				fireballs_direction.erase(fireballs_direction.begin() + i);
				for (int j = 0; j < slimes_size; j++) {
					if (slimes_x[j] == fireball_x && slimes_y[j] == fireball_y) {
						slimes_x.erase(slimes_x.begin() + j);
						slimes_y.erase(slimes_y.begin() + j);
						break;
					}
				}
				slimes_size--;
				fireballs_size--;
				i--;
			}
		}

		if (button == 's') {
			new_x = player_x + 1;
			new_direction = look_down;
		}
		if (button == 'w') {
			new_x = player_x - 1;
			new_direction = look_up;
		}
		if (button == 'd') {
			new_y = player_y + 1;
			new_direction = look_right;
		}
		if (button == 'a') {
			new_y = player_y - 1;
			new_direction = look_left;
		}
		if (new_x != player_x || new_y != player_y) {
			if (map[new_x][new_y] == '#') {
				player_direction = new_direction;
				previous_move = "pass";
				cout << player_direction << endl << wall_hit_message << endl;
			}
			if (map[new_x][new_y] == '.') {
				map[player_x][player_y] = '.';
				map[new_x][new_y] = '@';
				player_x = new_x;
				player_y = new_y;
				player_direction = new_direction;
				previous_move = "movement";
				cout << player_direction << endl << move_message << endl;
			}
			if (map[new_x][new_y] == '<') {
				goto exit;
			}
			if (map[new_x][new_y] == 'S') {
				button = 'q';
			}
		}

		if (button == 'z') {
			if (previous_move != "shoot") {
				int fireball_x = player_x;
				int fireball_y = player_y;

				if (player_direction == look_up) {
					fireball_x--;
				}
				if (player_direction == look_down) {
					fireball_x++;
				}
				if (player_direction == look_right) {
					fireball_y++;
				}
				if (player_direction == look_left) {
					fireball_y--;
				}

				if (map[fireball_x][fireball_y] == '#') {
					cout << player_direction << endl << wall_shoot_message << endl;
				}
				if (map[fireball_x][fireball_y] == '.') {
					map[fireball_x][fireball_y] = '*';
					fireballs_x.push_back(fireball_x);
					fireballs_y.push_back(fireball_y);
					fireballs_direction.push_back(player_direction);
					fireballs_size++;
					previous_move = "shoot";
					cout << player_direction << endl << shoot_message << endl;
				}
				if (map[fireball_x][fireball_y] == 'S') {
					map[fireball_x][fireball_y] = '.';
					for (int j = 0; j < slimes_size; j++) {
						if (slimes_x[j] == fireball_x && slimes_y[j] == fireball_y) {
							slimes_x.erase(slimes_x.begin() + j);
							slimes_y.erase(slimes_y.begin() + j);
							break;
						}
					}
					slimes_size--;
					previous_move = "shoot";
					cout << player_direction << endl << shoot_message << endl;
				}
			}
			else {
				previous_move = "pass";
				cout << player_direction << endl << reload_message << endl;
			}
		}

		for (int i = 0; i < slimes_size; i++) {
			int slime_move = 1 + rand() % 4;
			int slime_x = slimes_x[i];
			int slime_y = slimes_y[i];
			if (slime_move == 1) {
				slime_x++;
			}
			if (slime_move == 2) {
				slime_x--;
			}
			if (slime_move == 3) {
				slime_y++;
			}
			if (slime_move == 4) {
				slime_y--;
			}
			if (map[slime_x][slime_y] == '#' || map[slime_x][slime_y] == '<' || map[slime_x][slime_y] == 'S') {
				i--;
			}
			if (map[slime_x][slime_y] == '@') {
				button = 'q';
			}
			
			if (map[slime_x][slime_y] == '.') {
				map[slime_x][slime_y] = 'S';
				map[slimes_x[i]][slimes_y[i]] = '.';
				slimes_x[i] = slime_x;
				slimes_y[i] = slime_y;
			}
			if (map[slime_x][slime_y] == '*') {
				map[slime_x][slime_y] = '.';
				map[slimes_x[i]][slimes_y[i]] = '.';
				slimes_x.erase(slimes_x.begin() + i);
				slimes_y.erase(slimes_y.begin() + i);
				for (int j = 0; j < fireballs_size; j++) {
					if (fireballs_x[j] == slime_x && fireballs_y[j] == slime_y) {
						fireballs_x.erase(fireballs_x.begin() + j);
						fireballs_y.erase(fireballs_y.begin() + j);
						fireballs_direction.erase(fireballs_direction.begin() + j);
						break;
					}
				}
				fireballs_size--;
				i--;
				slimes_size--;
			}
		}

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
		cout << "w - up" << endl << "s - down" << endl << "a - left" << endl << "d - right" << endl << endl << "z - shoot" << endl << "q - quit" << endl;
	} while (button != 'q');

	system("cls");
	cout << endl << endl << game_over_message << endl << endl;

	return 0;
}
