#include <iostream>
#include <string>
#include <fstream>
#include "MyVector.h"
#include "Stack.h"

class Table;

class Cell
{
	Table* table;
	std::string data;
	int x, y;

public:

	Cell(const std::string& data, int x, int y, Table* table) : data(data), x(x), y(y), table(table) {}

	virtual std::string stringify();
	virtual int to_numeric();

};

class Table
{
protected:
	int max_row_size, max_col_size;

	Cell*** data_table;

public:

	Table(int max_row_size, int max_col_size) : max_row_size(max_row_size), max_col_size(max_col_size) 
	{
		data_table = new Cell * *[max_row_size];

		for (int i = 0; i < max_row_size; i++)
		{
			data_table[i] = new Cell * [max_row_size];

			for (int j = 0; j < max_col_size; j++)
			{
				data_table[i][j] = nullptr; 
			}
		}

	}


	void reg_cell(Cell* c, int row, int col);

	int to_numeric(const std::string& s);
	int to_numeric(int x, int y);

	std::string stringify(const std::string s);
	std::string stringify(int x,int y);

	std::string get_cell_string(int row, int col);

	virtual std::string print_table() = 0;

	virtual ~Table() 
	{
		for (int i = 0; i < max_row_size; i++)
		{
			for (int j = 0; j < max_col_size; j++)
			{
				if(data_table[i][j])
					delete data_table[i][j];
			}
	
		}

		for (int i = 0; i < max_row_size; i++)
		{
			
			delete[] data_table[i];
		}

		delete[] data_table;
	}

};


std::string Cell::stringify()
{
	return data;
}

int Cell::to_numeric()
{
	return 0;
}

class TxtTable : public Table
{
	std::string repeat_char(int n, char c);

	std::string col_num_to_str(int n);

public:

	TxtTable(int row, int col);
	std::string print_table();

};


class CSVTable : public Table
{
public:
	CSVTable(int row, int col);
	std::string print_table();

};


class HTMLTable : public Table
{
public:
	HTMLTable(int row, int col);
	std::string print_table();

};

void Table::reg_cell(Cell* c, int row, int col)
{
	if (!(row < max_row_size && row >= 0 && col < max_col_size && col >= 0)) return;


	if (data_table[row][col])
	{
		delete data_table[row][col];
	}

	data_table[row][col] = c;
}

std::string Table::get_cell_string(int row, int col)
{
	return data_table[row][col]->stringify();
}

int Table::to_numeric(const std::string& s)
{
	int row = s[0] - 'A';
	int col = atoi(s.c_str() + 1) - 1;

	if ((row < max_row_size && row >= 0 && col < max_col_size && col >= 0))
	{
		if (data_table[row][col])
			return data_table[row][col]->to_numeric();
	}

	return 0;
}

int Table::to_numeric(int x, int y)
{
	if ((x < max_row_size && x >= 0 && y < max_col_size && y >= 0))
	{
		if (data_table[x][y])
			return data_table[x][y]->to_numeric();
	}

	return 0;
}

std::string Table::stringify(const std::string s)
{
	int row = s[0] - 'A';
	int col = atoi(s.c_str() + 1) - 1;

	if ((row < max_row_size && row >= 0 && col < max_col_size && col >= 0))
	{
		if (data_table[row][col])
			return data_table[row][col]->stringify();
	}

	return "";
}
std::string Table::stringify(int x, int y)
{
	if ((x < max_row_size && x >= 0 && y < max_col_size && y >= 0))
	{
		if (data_table[x][y])
			return data_table[x][y]->stringify();
	}

	return "";

}

std::ostream& operator <<(std::ostream& o, Table& t)
{
	o << t.print_table();
	return o;
}



int main()
{
	TxtTable table(5, 5);
	std::ofstream out("test.txt");

	table.reg_cell(new Cell("Hello~", 0, 0, &table), 0, 0);
	table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);
	table.reg_cell(new Cell("Programming", 1,1 , &table), 1,1);

	std::cout << std::endl << table;
	out << table;

	HTMLTable table2(5, 5);
	std::ofstream out2("test.html");

	table2.reg_cell(new Cell("Hello~", 0, 0, &table2), 0, 0);
	table2.reg_cell(new Cell("C++", 0, 1, &table2), 0, 1);
	table2.reg_cell(new Cell("Programming", 1, 1, &table2), 1, 1);

	std::cout << std::endl << table2;
	out2 << table2;

	

	return 0;
}

std::string TxtTable::repeat_char(int n, char c)
{
	std::string s = "";

	for (int i = 0; i < n; i++)
	{
		s.push_back(c);
	}

	return s;
}

std::string TxtTable::col_num_to_str(int n)
{
	std::string s = "";
	if (n < 26)
	{
		s.push_back('A' +  n);
	}
	else
	{
		char first = 'A' + n / 26 - 1;
		char second = 'A' + n % 26;
		s.push_back(first);
		s.push_back(second);
	}

	return s;
}

TxtTable::TxtTable(int row, int col) : Table(row, col) 
{
	
}

HTMLTable::HTMLTable(int row, int col) : Table(row, col)
{
}

CSVTable::CSVTable(int row, int col) : Table(row, col)
{
}

std::string TxtTable::print_table()
{
	std:: string total_table;

	int* col_max_wide = new int[max_col_size];
	
	for (int i = 0; i < max_col_size; i++)
	{
		unsigned int max_wide = 2;

		for (int j = 0; j < max_row_size; j++)
		{
			if (data_table[j][i] && data_table[j][i]->stringify().length() > max_wide)
			{
				max_wide = data_table[j][i]->stringify().length();
			}
		}

		col_max_wide[i] = max_wide;
	}

	total_table += "    ";
	int total_wide = 4;

	for (int i = 0; i < max_col_size; i++)
	{
		if (col_max_wide[i])
		{
			int max_len = std::max(2, col_max_wide[i]);
			total_table += " | " + col_num_to_str(i);
			total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');
		
			total_wide += (max_len + 3);
		}
	}


	total_table += '\n';

	for (int i = 0; i < max_row_size; i++)
	{
		total_table += repeat_char(total_wide, '-');
		total_table += '\n' + std::to_string(i + 1);
		total_table += repeat_char(4 - std::to_string(i + 1).length(), ' ');

		for (int j = 0; j < max_col_size; j++)
		{
			if (col_max_wide[j])
			{
				int max_len = std::max(2, col_max_wide[j]);

				std::string s = "";
				if (data_table[i][j])
				{
					s = data_table[i][j]->stringify();
				}

				total_table += " | " + s;
				total_table += repeat_char(max_len - s.length(), ' ');

			}
		}

		total_table += '\n';
	}

	return total_table;
}

std::string HTMLTable::print_table()
{
	std::string s = "<table border='1' cellpadding = '10'>";

	for (int i = 0; i < max_row_size; i++)
	{
		s += "<tr>";

		for (int j = 0; j < max_col_size; j++)
		{
			s += "<td>";
			if (data_table[i][j]) s += data_table[i][j]->stringify();
			s += "</td>";
		}
		s += "</tr>";
	}

	s += "</table>";
	return s;
}

std::string CSVTable::print_table()
{
	std::string s = "";

	for (int i = 0; i < max_row_size; i++)
	{
		for (int j = 0; j < max_col_size; j++)
		{
			if (j >= 1) s += ",";
			
			std::string temp;
			if (data_table[i][j]) temp = data_table[i][j]->stringify();

			for (int k = 0; k < temp.length(); k++)
			{
				if (temp[k] == '"') 
				{
					temp.insert(k, 1, '"');
				
					k++;
				}
			}

			temp = '"' + temp + '"';
			s += temp;
		}

		s += '\n';
	}

	return s;
}