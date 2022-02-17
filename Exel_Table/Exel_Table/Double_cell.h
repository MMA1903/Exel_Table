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

using namespace std;

class Double_cell : public Cell {
	string value;
public:
	Double_cell();

	Double_cell(string value);

	double get_value() const;

	void print() const;

	const string get_string_value();

	const string type_value();

};

