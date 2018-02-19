#include <iostream>
#include "own_library.h"

int valid_num_of_rows(int, ifstream &);
void fill_incidence_matrix(int **, int, ifstream &);
void fill_array_of_columns(int **, int **, int *, int, int);
void fill_adjacent_vertices(int **, int **, int, int);

int main()
{
	string data_input, data_output;
	valid_filename("data_input_p1a", ".txt", data_input);
	valid_filename("data_output_p1a", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int rows, columns;
	get_variable_from_file(columns, fin);
	rows = valid_num_of_rows(columns, fin);
	int ** incidence_matrix = create_two_dimensional_array<int>(rows, columns);
	fill_two_dimensional_array_with_value(incidence_matrix, rows, columns, 0);

	fin.ignore(1);
	fill_incidence_matrix(incidence_matrix, columns, fin);

	int ** adjacent_vertices = nullptr;
	adjacent_vertices = new int *[rows];
	int * array_of_columns = create_array<int>(rows);
	fill_array_with_value(array_of_columns, rows, 0);

	fill_array_of_columns(incidence_matrix, adjacent_vertices, array_of_columns, rows, columns);
	fill_adjacent_vertices(incidence_matrix, adjacent_vertices, rows, columns);

	two_dimensional_array_to_file_rows_in_single_line_negative_numbers(incidence_matrix, rows, columns, fout);
	irregular_two_dimensional_array_to_file_rows_in_single_line(adjacent_vertices, array_of_columns, rows, fout);

	fin.close();
	fout.close();

	return 0;
}

int valid_num_of_rows(int columns, ifstream & fin)
{
	int lastVertix = 1;
	int auxiliaryValue = lastVertix;
	int numOfElements = 2 * columns;

	for (int sentinel = 0; sentinel < numOfElements; ++sentinel)
	{
		fin >> auxiliaryValue;

		if (auxiliaryValue > lastVertix)
		{
			lastVertix = auxiliaryValue;
		}
	}

	fin.clear();
	fin.seekg(0, ios::beg);
	
	return lastVertix;
}

void fill_incidence_matrix(int ** incidence_matrix, int columns, ifstream & fin)
{
	for (int sentinel = 0, auxiliary_value; sentinel < columns; ++sentinel)
	{
		fin >> auxiliary_value;
		incidence_matrix[auxiliary_value - 1][sentinel] = 1;

		fin >> auxiliary_value;
		incidence_matrix[auxiliary_value - 1][sentinel] = -1;
	}
}

void fill_array_of_columns(int ** incidence_matrix, int ** adjacent_vertices, int * array_of_columns, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			if (incidence_matrix[sentinel][secondSentinel] == 1 || incidence_matrix[sentinel][secondSentinel] == -1)
			{
				++array_of_columns[sentinel];
			}
		}

		adjacent_vertices[sentinel] = new int[array_of_columns[sentinel]];
	}
}

void fill_adjacent_vertices(int ** incidence_matrix, int ** adjacent_vertices, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0, auxiliaryIndex = 0; secondSentinel < columns; ++secondSentinel)
		{
			if (incidence_matrix[sentinel][secondSentinel] == 1 || incidence_matrix[sentinel][secondSentinel] == -1)
			{
				for (int thirdSentinel = 0; thirdSentinel < rows; ++thirdSentinel)
				{
					if (thirdSentinel != sentinel && (incidence_matrix[thirdSentinel][secondSentinel] == 1
						|| incidence_matrix[thirdSentinel][secondSentinel] == -1))
					{
						adjacent_vertices[sentinel][auxiliaryIndex] = thirdSentinel + 1;
						++auxiliaryIndex;
					}
				}
			}
		}
	}
}
