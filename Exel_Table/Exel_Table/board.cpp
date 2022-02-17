#include "Board.h"

vector<vector<Cell*>>Board::cell{};

Board::Board()
{
    Board::cell;
    bool file_opened = false;
    string file_name = "";
}

void Board::make_Board(const string& file_name)
{
    if (file_opened == true)
    {
        cout << "You have open file" << endl;
    }
    else
    {
        vector<vector<string>> cell_helper;
        vector<string> row;
        string line = "";
        string value = "";

        int br_commas = 0;

        ifstream my_file(file_name);
        this->file_name = file_name;
        if (my_file.is_open())
        {
            while (getline(my_file, line))
            {
                br_commas = 0;
                int index = 0;
                while (index <= line.size())
                {
                    if (line[index] == ',')
                    {
                        br_commas++;
                    }
                    index++;
                }
                int i = 0;
                for (int j = 0; j < br_commas; j++)
                {
                    value = "";
                    while (line[i] != ',')
                    {
                        value = value + line[i];
                        i++;
                    }
                    i++;
                    row.push_back(value);
                }
                cell_helper.push_back(row);
                row.clear();
            }
            my_file.close();
            cout << "Successfully opened : " << file_name << endl;
            file_opened = true;
            int max_row = 0;
            int max_column = cell_helper.size();

            for (int i = 0; i < cell_helper.size(); i++)
            {
                if (cell_helper[i].size() > max_row)
                {
                    max_row = cell_helper[i].size();
                }
            }
            vector<Cell*> row_str;

            for (int i = 0; i < max_column; i++)
            {
                for (int j = 0; j < max_row; j++)
                {
                    row_str.push_back(new String_cell(" "));
                }
                Board::cell.push_back(row_str);
                row_str.clear();
            }


            for (int i = 0; i < cell_helper.size(); i++)
            {
                for (int j = 0; j < cell_helper[i].size(); j++)
                {
                    delete Board::cell[i][j];

                    int is_formula = 0;
                    int br_dot = 0;
                    int br_num = 0;
                    int br_sym = 0;

                    char type = cell_helper[i][j].at(0);

                    if (type == '=')
                    {
                        is_formula = 1;
                    }

                    else if (type != '=')
                    {
                        char ch;
                        for (int m = 0; m < cell_helper[i][j].length(); m++)
                        {
                            ch = cell_helper[i][j].at(m);
                            if ('0' <= ch <= '9')
                                br_num++;
                            if (ch == '.')
                                br_dot++;
                            if ((ch < '0' || '9' < ch) && ch != '.')
                                br_sym++;
                        }
                    }

                    if (is_formula == 1)
                    {
                        Board::cell[i][j] = new Formula_cell(cell_helper[i][j]);
                    }

                    else if (br_sym > 0)
                    {
                        Board::cell[i][j] = new String_cell(cell_helper[i][j]);
                    }

                    else if (br_sym == 0 && br_dot <= 1 && br_num >= 1)
                    {
                        Board::cell[i][j] = new Double_cell(cell_helper[i][j]);
                    }

                    else if (br_sym == 0 && br_dot == 0 && br_num >= 1)
                    {
                        Board::cell[i][j] = new Int_cell(cell_helper[i][j]);
                    }

                    else
                    {
                        cout << "Error: row " << i + 1 << ", col" << " " << j + 1 << ", " << cell_helper[i][j] << "is unknown data type.";
                        Board::cell[i][j] = new String_cell(" ");
                    }
                }
            }
            cell_helper.clear();
        }

        else
        {
            ofstream outfile(file_name);
            cout << "You create new file " << file_name << endl;
            my_file.close();
            file_opened = true;
        }
    }
}

Board::~Board()
{
    Board::cell.clear();
}

double Board::get_board_value(int row, int column)
{

    if (Board::cell.size() > row)
    {

        if (Board::cell[row - 1].size() > column)
        {

            return Board::cell[row - 1][column - 1]->get_value();

        }
        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }

}

void Board::print_board() const
{
    int maxl = 0;
    for (int i = 0; i < Board::cell.size(); i++)
    {
        for (int j = 0; j < Board::cell[i].size(); j++)
        {
            if (this->Board::cell[i][j]->get_string_value().length() > maxl)
            {
                maxl = this->Board::cell[i][j]->get_string_value().length();
            }
        }
    }

    for (int i = 0; i < Board::cell.size(); i++)
    {
        cout << "|";
        for (int j = 0; j < Board::cell[i].size(); j++)
        {
            if (this->Board::cell[i][j]->type_value() == "string")
            {
                cout << setw(maxl);
                cout << this->Board::cell[i][j]->get_string_value();
                cout << setw(2);
                cout << "|";
            }
            else
            {
                cout << setw(maxl);
                cout << Board::cell[i][j]->get_value();
                cout << setw(2);
                cout << "|";
            }
        }
        cout << endl;
    }
}

void Board::save_command()
{
    if (file_opened == true)
    {
        ofstream my_file(file_name);
        if (my_file.good())
        {
            for (int i = 0; i < Board::cell.size(); i++)
            {

                for (int j = 0; j < Board::cell[i].size(); j++)
                {
                    my_file << Board::cell[i][j]->get_string_value();
                    my_file << ",";
                }
                my_file << "\n";
            }
            cout << "File \"" << this->file_name << "\" successfully saved." << endl;
        }
        my_file.close();
    }
    else
    {
        cout << "Error : no file opened." << endl;
    }
}

void Board::save_as_command(const string& file_name)
{
    if (file_opened == true)
    {
        if (this->file_name == file_name)
        {
            ofstream my_file(file_name);
            if (my_file.good())
            {
                for (int i = 0; i < Board::cell.size(); i++)
                {
                    for (int j = 0; j < Board::cell[i].size(); j++)
                    {
                        my_file << Board::cell[i][j]->get_string_value();
                        my_file << ",";
                    }
                    my_file << "\n";
                }
                cout << "File \"" << file_name << "\" successfully overwritten." << endl;
            }
            my_file.close();
        }

        else if (this->file_name != file_name)
        {
            ofstream my_file(file_name);
            if (my_file.good())
            {
                for (int i = 0; i < Board::cell.size(); i++)
                {
                    for (int j = 0; j < Board::cell[i].size(); j++)
                    {
                        my_file << Board::cell[i][j]->get_string_value();
                        my_file << ",";
                    }
                    my_file << "\n";
                }
                this->file_name = file_name;
                cout << "New file \"" << file_name << "\" successfully saved." << endl;
            }
            my_file.close();
        }
    }
    else
    {
        cout << "Error : no file opened." << endl;
    }
}

void Board::close_command()
{
    if (file_opened == true)
    {
        this->file_opened = false;
        this->~Board();
        cout << "File \"" << this->file_name << "\" closed." << endl;
        this->file_name = "";
    }
    else
    {
        cout << "Error : no file opened." << endl;
    }
}

void Board::edit_comand()
{
    string row;
    string column;
    string value;

    bool have_cell = true;

    cout << ">Row : ";
    getline(cin, row);

    cout << ">Column : ";
    getline(cin, column);

    cout << ">Text : ";
    getline(cin, value);

    for (int i = 0; i < Board::cell.size(); i++)
    {
        if (Board::cell[i].size() <= string_to_double(column) - 1)
        {
            have_cell = false;
        }
    }

    if (Board::cell.size() <= string_to_double(row) - 1)
    {
        have_cell = false;
    }

    if (have_cell == false)
    {
        cout << "Cell Row:" << row << " " << "Column:" << column << " " << "is not in this file" << endl;
    }

    else
    {
        delete Board::cell[string_to_double(row) - 1][string_to_double(column) - 1];

        int is_formula = 0;
        int br_dot = 0;
        int br_num = 0;
        int br_sym = 0;

        char type = value.at(0);
        if (type == '=')
        {
            is_formula = 1;
        }

        else if (type != '=')
        {
            char ch;
            for (int m = 0; m < value.length(); m++)
            {
                ch = value.at(m);
                if ('0' <= ch <= '9')
                    br_num++;
                if (ch == '.')
                    br_dot++;
                if ((ch < '0' || '9' < ch) && ch != '.')
                    br_sym++;
            }
        }

        if (is_formula == 1)
        {
            Board::cell[string_to_double(row) - 1][string_to_double(column) - 1] = new Formula_cell(value);
        }

        else if (br_sym > 0)
        {
            Board::cell[string_to_double(row) - 1][string_to_double(column) - 1] = new String_cell(value);
        }

        else if (br_sym = 0 && br_dot <= 1 && br_num >= 1)
        {
            Board::cell[string_to_double(row) - 1][string_to_double(column) - 1] = new Double_cell(value);
        }

        else if (br_sym == 0 && br_dot == 0 && br_num >= 1)
        {
            Board::cell[string_to_double(row) - 1][string_to_double(column) - 1] = new Int_cell(value);
        }
        else
        {
            cout << "Error: " << value << "is unknown data type.";
        }
    }
}


void Board::activate()
{
    file_opened = false;

    const string exit = R"(^exit$)";
    const string open = R"(^open (([^\"\s]+)|(\"([^\"]+)\"))$)";
    const string save = R"(^save$)";
    const string saveas = R"(^saveas (([^\"\s]+)|(\"([^\"]+)\"))$)";
    const string close = R"(^close$)";
    const string edit = R"(^edit$)";
    const string print = R"(^print$)";

    const sregex_iterator end;

    const regex exit_pattern = regex(exit);
    const regex open_pattern = regex(open);
    const regex save_pattern = regex(save);
    const regex saveas_attern = regex(saveas);
    const regex close_pattern = regex(close);
    const regex edit_pattern = regex(edit);
    const regex print_pattern = regex(print);

    sregex_iterator iter;

    string text;
    while (true)
    {
        cout << ">";
        getline(cin, text);

        if ((iter = sregex_iterator(text.begin(), text.end(), exit_pattern)) != end)
        {
            cout << "exiting..." << endl;
            break;
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), open_pattern)) != end)
        {
            string file_name = string((*iter)[2]) + string((*iter)[4]);
            this->make_Board(file_name);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), save_pattern)) != end)
        {
            this->save_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), saveas_attern)) != end)
        {
            string file_name = string((*iter)[2]) + string((*iter)[4]);
            this->save_as_command(file_name);
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), close_pattern)) != end)
        {
            this->close_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), edit_pattern)) != end)
        {
            this->edit_comand();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), print_pattern)) != end)
        {
            this->print_board();
        }
        else
        {
            cout << "Error : invalid command syntax." << endl;
        }
        cout << endl;
    }
}
