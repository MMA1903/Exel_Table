#include "Formula_cell.h"

Formula_cell::Formula_cell()
{
    value = "";
}

Formula_cell::Formula_cell(string value)
{
    this->value = value;
}

double Formula_cell::get_value() const
{
    return calculate();
}

void Formula_cell::print() const
{
    cout << this->value;
}

const string Formula_cell::get_string_value()
{
    return this->value;
}

const string Formula_cell::type_value()
{
    return "formula";
}

double Formula_cell::calculate_value_of_cell(double a, char c, double b) const
{

    switch (c)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    }

}

double Formula_cell::calculate() const
{
    int length = this->value.length();
    int row = 0;
    int column = 0;
    int number_of_rows = 0;

    string first_str = "";
    string second_str = "";
    string row_str = "";
    string column_str = "";
    string helper = "";

    double first = 0;
    double second = 0;

    char symbol;

    bool have_first = false;

    for (int i = 1; i < length; i++)
    {
        if (this->value.at(i) == 'R')
        {
            number_of_rows++;
        }
    }
    if (number_of_rows == 0)
    {
        for (int i = 1; i < length; i++)
        {
            if ((('0' <= this->value.at(i) && this->value.at(i) <= '9') || this->value.at(i) == '.') && have_first == false)
            {
                first_str = first_str + this->value.at(i);
                first = string_to_double(first_str);
            }
            else if (this->value.at(i) == '+' || this->value.at(i) == '-' || this->value.at(i) == '*' || this->value.at(i) == '/' || this->value.at(i) == '^')
            {
                symbol = this->value.at(i);
                have_first = true;
            }
            else if ((('0' <= this->value.at(i) && this->value.at(i) <= '9') || this->value.at(i) == '.') && have_first == true)
            {
                second_str = second_str + this->value.at(i);
                second = string_to_double(second_str);
            }
        }
        return calculate_value_of_cell(first, symbol, second);
    }
    else if (number_of_rows == 1)
    {
        if (this->value.at(1) == 'R')
        {
            for (int i = 1; i < length; i++)
            {
                if (this->value.at(i) == 'R')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        row_str = row_str + this->value.at(j);
                    }
                    row = string_to_double(row_str);
                }
                else if (this->value.at(i) == 'C')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        column_str = column_str + this->value.at(j);
                    }
                    column = string_to_double(column_str);
                }
                else if (this->value.at(i) == '+' || this->value.at(i) == '-' || this->value.at(i) == '*' || this->value.at(i) == '/' || this->value.at(i) == '^')
                {
                    symbol = this->value.at(i);
                    have_first = true;
                }
                else if ((('0' <= this->value.at(i) && this->value.at(i) <= '9') || this->value.at(i) == '.') && have_first == true)
                {
                    second_str = second_str + this->value.at(i);
                    second = string_to_double(second_str);
                }
                if (row != 0 && column != 0 && have_first == false)
                {
                    first = Board::get_board_value(row, column);;
                }

            }
            return calculate_value_of_cell(first, symbol, second);
        }
        else
        {
            for (int i = 1; i < length; i++)
            {
                if ((('0' <= this->value.at(i) && this->value.at(i) <= '9') || this->value.at(i) == '.') && have_first == false)
                {
                    first_str = first_str + this->value.at(i);
                    first = string_to_double(first_str);
                }
                else if (this->value.at(i) == '+' || this->value.at(i) == '-' || this->value.at(i) == '*' || this->value.at(i) == '/' || this->value.at(i) == '^')
                {
                    symbol = this->value.at(i);
                    have_first = true;
                }
                else if (this->value.at(i) == 'R')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        row_str = row_str + this->value.at(j);
                    }
                    row = string_to_double(row_str);
                }
                else if (this->value.at(i) == 'C')
                {
                    for (int j = i + 1; j < length; j++)
                    {
                        column_str = column_str + this->value.at(j);
                    }
                    column = string_to_double(column_str);
                }

                if (row != 0 && column != 0 && have_first == true)
                {
                    second = Board::get_board_value(row, column);;
                }
            }
            return calculate_value_of_cell(first, symbol, second);
        }
    }
    else if (number_of_rows == 2)
    {
        for (int i = 1; i < length; i++)
        {
            if (this->value.at(i) == '+' || this->value.at(i) == '-' || this->value.at(i) == '*' || this->value.at(i) == '/' || this->value.at(i) == '^')
            {
                symbol = this->value.at(i);
                have_first = true;
                row = 0;
                column = 0;
            }
            else if (have_first == false)
            {
                if (this->value.at(i) == 'R')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        row_str = row_str + this->value.at(j);
                    }
                    row = string_to_double(row_str);
                }
                else if (this->value.at(i) == 'C')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        column_str = column_str + this->value.at(j);
                    }
                    column = string_to_double(column_str);
                }
                else if (row != 0 && column != 0)
                {
                    first = Board::get_board_value(row, column);
                    row_str = "";
                    column_str = "";
                }
            }
            else if (have_first == true)
            {
                if (this->value.at(i) == 'R')
                {
                    for (int j = i + 1; '0' <= this->value.at(j) && this->value.at(j) <= '9'; j++)
                    {
                        row_str = row_str + this->value.at(j);
                    }
                    row = string_to_double(row_str);
                }
                else if (this->value.at(i) == 'C')
                {
                    for (int j = i + 1; j < length; j++)
                    {
                        column_str = column_str + this->value.at(j);
                    }
                    column = string_to_double(column_str);
                }
                else if (row != 0 && column != 0)
                {
                    second = Board::get_board_value(row, column);
                }
            }
        }
        return calculate_value_of_cell(first, symbol, second);
    }
    else
    {
        cout << "Error";
    }
}
