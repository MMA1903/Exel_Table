#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

#include "Cell.h"
#include "Int_cell.h"
#include "Double_cell.h"
#include "String_cell.h"
#include "Formula_cell.h"


using namespace std;


class Board {
	static vector<vector<Cell*>> cell;
	bool file_opened;
	string file_name;

public:
	Board();

	void make_Board(const string& file_name);

	~Board();

	static double get_board_value(int row, int column);

	void print_board() const;

	///////////////////////////////

	void save_command();

	void save_as_command(const string& file_name);

	void close_command();

	void edit_comand();

	void activate();

};
