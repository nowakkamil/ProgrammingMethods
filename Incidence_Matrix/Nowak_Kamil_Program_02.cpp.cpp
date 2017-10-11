#include <iostream>
#include <vector>
#include "own_library.h"

struct incidenceList
{
	int value;
	incidenceList * next;
};

int valid_num_of_rows(int, ifstream &);
void fill_incidence_matrix(vector<vector<incidenceList *>> &, int, ifstream &);
void irregular_two_dimensional_vector_to_file_rows_in_single_line(vector<vector<incidenceList *>> &, ofstream &);
int * calculate_degree_of_vertex(vector<vector<incidenceList *>> &, int);

int main()
{
	string data_input, data_output;
	valid_filename("data_input_p2a", ".txt", data_input);
	valid_filename("data_output_p2a", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int rows, edges;
	get_variable_from_file(edges, fin);
	rows = valid_num_of_rows(edges, fin);

	vector<vector<incidenceList *>> incidence_matrix(rows);

	fin.ignore(1);
	fill_incidence_matrix(incidence_matrix, edges, fin);

	irregular_two_dimensional_vector_to_file_rows_in_single_line(incidence_matrix, fout);
	fout << endl;

	int * degree_of_vertex = calculate_degree_of_vertex(incidence_matrix, rows);
	one_column_array_to_file_multiple_lines_numeration(degree_of_vertex, rows, fout);

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

void fill_incidence_matrix(vector<vector<incidenceList *>> & incidence_matrix, int edges, ifstream & fin)
{
	for (int sentinel = 0, first_auxiliary_value, second_auxiliary_value; sentinel < edges; ++sentinel)
	{
		fin >> first_auxiliary_value;
		fin >> second_auxiliary_value;

		incidenceList * first_element = nullptr;
		first_element = new incidenceList;

		first_element->value = second_auxiliary_value;
		first_element->next = nullptr;

		if (!incidence_matrix[first_auxiliary_value - 1].empty())
		{
			incidence_matrix[first_auxiliary_value - 1].back()->next = first_element;
		}

		incidence_matrix[first_auxiliary_value - 1].push_back(first_element);

		//	adding the element of the list for the second time
		incidenceList * second_element = nullptr;
		second_element = new incidenceList;

		second_element->value = first_auxiliary_value;
		second_element->next = nullptr;

		if (!incidence_matrix[second_auxiliary_value - 1].empty())
		{
			incidence_matrix[second_auxiliary_value - 1].back()->next = second_element;
		}

		incidence_matrix[second_auxiliary_value - 1].push_back(second_element);
	}
}

void irregular_two_dimensional_vector_to_file_rows_in_single_line(vector<vector<incidenceList *>> & vector_of_vector_of_list, ofstream & fout)
{
	vector<vector<incidenceList *>>::iterator row;
	vector<incidenceList *>::iterator column;

	for (row = vector_of_vector_of_list.begin(); row != vector_of_vector_of_list.end(); ++row)
	{
		for (column = row->begin(); column != row->end(); ++column)
		{
			fout.width(2);
			fout.fill(' ');
			fout << (*column)->value;

			if (column != row->end() - 1)
			{
				fout << " ";
			}
		}

		fout << endl;
	}
}

int * calculate_degree_of_vertex(vector<vector<incidenceList *>> & vector_of_vector_of_list, int rows)
{
	int * degree_of_vertex = create_array(rows);

	vector<vector<incidenceList *>>::iterator row;
	vector<incidenceList *>::iterator column;
	row = vector_of_vector_of_list.begin();

	for (int sentinel = 0, elements = 0; sentinel < rows; elements = 0, sentinel++)
	{
		for (column = row->begin(); column != row->end(); ++column)
		{
			++elements;
		}

		*(degree_of_vertex + sentinel) = elements;
		++row;
	}

	return degree_of_vertex;
}
