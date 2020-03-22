// house_in_the_woods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

fstream& go_to_line(fstream& file_address, unsigned int index);
void read_passage(fstream& file, unsigned int start, unsigned int end);

struct passage {
	int start;
	int end;
	bool death;
	passage* one;
	passage* two;
};

int main()
{
	string myline;
	fstream myfile("house_in_the_woods.txt");

	passage house, stay_inside, lock_door, cellar, coffin,
		icebox, outside_norun, outside_run, firewood,
		opendoor_firewood, opendoor_nofirewood, follow_smoke, join_them,
		lake_nocult, lake_cult, old_man, swim;

	passage *p_stay_inside, *p_lock_door, *p_cellar, *p_coffin,
		*p_icebox, *p_outside_norun, *p_outsiderun, *p_firewood,
		*p_opendoor_firewood, *p_opendoor_nofirewood, *p_follow_smoke, *p_join_them,
		*p_lake_nocult, *p_lake_cult, *p_old_man, *p_swim;

	p_stay_inside = &stay_inside;
	p_lock_door = &lock_door;
	p_cellar = &cellar;
	p_coffin = &coffin;
	p_icebox = &icebox;
	p_outside_norun = &outside_norun;
	p_outsiderun = &outside_run;
	p_firewood = &firewood;
	p_opendoor_firewood = &opendoor_firewood;
	p_opendoor_nofirewood = &opendoor_nofirewood;
	p_follow_smoke = &follow_smoke;
	p_join_them = &join_them;
	p_lake_nocult = &lake_nocult;
	p_lake_cult = &lake_cult;
	p_old_man = &old_man;
	p_swim = &swim;

	house = { 1, 10, false, p_stay_inside, p_outside_norun};
	stay_inside = { 13, 22, false, p_lock_door, p_opendoor_nofirewood};
	lock_door = { 25, 33, false, p_cellar, p_outsiderun};
	cellar = { 36, 44, false, p_coffin, p_icebox};
	coffin = { 46, 54, true };
	icebox = { 56, 59, true };
	outside_norun = { 60, 69, false, p_firewood, p_follow_smoke };
	outside_run = { 70, 78, false, p_follow_smoke, p_lake_nocult };
	firewood = { 80, 89, false, p_lock_door, p_opendoor_firewood };
	opendoor_firewood = { 90, 101, true };
	opendoor_nofirewood = { 102, 113, true };
	follow_smoke = { 114, 129, false, p_join_them, p_lake_cult };
	join_them = { 130, 141, true };
	lake_nocult = { 143, 157, false, p_old_man, p_swim };
	lake_cult = { 142, 157, false, p_old_man, p_swim };
	old_man = { 158, 169, true };
	swim = { 170, 173, true };
	
	bool finished = false;
	passage current = house;
	int next = 0;

	if (myfile.is_open()) {

		while (!finished)
		{
			read_passage(myfile, current.start, current.end);
			finished = current.death;

			if (finished) {
				break;
			}

			cout << "Enter [1] or [2]: ";
			cin >> next;
			cout << endl;

			if (next == 1) {
				current = *current.one;
			}
			else if(next == 2) {
				current = *current.two;
			}
			else {
				cout << "Invalid." << endl;
			}
		}
		cin.get();
	}
}

fstream& go_to_line(fstream& file, unsigned int index) {
	// go to beginning of file.
	file.seekg(ios::beg);

	for (int i = 0; i < index - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return file;
}

void read_passage(fstream& file, unsigned int start, unsigned int end) {
	string line;
	go_to_line(file, start);

	for (int i = start; i < end; ++i) {
		getline(file, line);
		cout << line << endl;
	}
}
