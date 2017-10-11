#include <iostream>
#include "own_library.h"

int valid_num_of_rows(int, ifstream &);
void fill_incidence_matrix(vector<vector<int>> &, int, ifstream &);
void fill_adjacent_vertices(vector<vector<int>> &, vector<vector<int>> &, int, int);

int main()
{
	string data_input, data_output;
	valid_filename("data_input_p1b", ".txt", data_input);
	valid_filename("data_output_p1b", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int rows, columns;
	get_variable_from_file(columns, fin);
	rows = valid_num_of_rows(columns, fin);

	vector<vector<int>> incidence_matrix(rows, vector<int>(columns, 0));
	
	fin.ignore(1);
	fill_incidence_matrix(incidence_matrix, columns, fin);

	vector<vector<int>> adjacent_vertices(rows, vector<int>(0));

	fill_adjacent_vertices(incidence_matrix, adjacent_vertices, rows, columns);

	two_dimensional_vector_to_file_rows_in_single_line_negative_numbers(incidence_matrix, fout);
	irregular_two_dimensional_vector_to_file_rows_in_single_line(adjacent_vertices, fout);

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

void fill_incidence_matrix(vector<vector<int>> & incidence_matrix, int columns, ifstream & fin)
{
	for (int sentinel = 0, auxiliary_value; sentinel < columns; ++sentinel)
	{
		fin >> auxiliary_value;
		incidence_matrix[auxiliary_value - 1][sentinel] = 1;

		fin >> auxiliary_value;
		incidence_matrix[auxiliary_value - 1][sentinel] = -1;
	}
}

void fill_adjacent_vertices(vector<vector<int>> & incidence_matrix, vector<vector<int>> & adjacent_vertices, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			if (incidence_matrix[sentinel][secondSentinel] == 1 || incidence_matrix[sentinel][secondSentinel] == -1)
			{
				for (int thirdSentinel = 0; thirdSentinel < rows; ++thirdSentinel)
				{
					if (thirdSentinel != sentinel && (incidence_matrix[thirdSentinel][secondSentinel] == 1
						|| incidence_matrix[thirdSentinel][secondSentinel] == -1))
					{
						adjacent_vertices[sentinel].push_back(thirdSentinel + 1);
					}
				}
			}
		}
	}
}