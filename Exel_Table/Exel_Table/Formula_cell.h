#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

#include "Cell.h"
#include "String_cell.h"
#include "Board.h"


using namespace std;

class Formula_cell : public Cell {
	string value;
public:
	Formula_cell();

	Formula_cell(string value);

	double get_value() const;

	void print() const;

	const string get_string_value();

	const string type_value();

	///////////////////////////////

	double calculate() const;

	double calculate_value_of_cell(double a, char c, double b) const;

};

