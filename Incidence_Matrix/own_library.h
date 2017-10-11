using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "own_library.cpp"

void valid_filename(string, string, string &);
void valid_filename_two_possibilities(string, string, string, string &);

ofstream & openFile(string, ofstream &);

ifstream & openFile(string, ifstream &);

void get_variable(int &);
void get_variable_from_file(int &, ifstream &);
void get_variable_from_file_up_to_million(int &, ifstream &);

int return_bigger_value(int, int);

bool is_prime(int);

bool GCD(int, int);

unsigned long long int factorial(int);

int * create_array(int);
unsigned long * create_unsigned_long_array(int);

int ** create_two_dimensional_array(int, int);

void delete_two_dimensional_array(int **, int);

void load_unsigned_long_array_from_file(unsigned long *, int, ifstream &);

void fill_array_with_value(int *, int, int);
void fill_two_dimensional_array_with_value(int **, int, int, int);

void fill_array_increasingly_with_initial_value(int *, int, int);

void copy_array(int *, int *, int);

void copy_two_dimensional_array(int **, int **, int, int);

void reverse_array(int *, int);

void display_array_in_single_line(int *, int);
void display_two_dimensional_array_rows_in_single_line(int **, int, int);
void display_two_dimensional_array_rows_in_single_line_negative_numbers(int **, int, int);
void display_irregular_two_dimensional_array_rows_in_single_line(int **, int *, int);

void display_one_column_array_multiple_lines_numeration(int *, int);

void display_vector_in_single_line(const vector<int> &);

void sort_two_dimensional_vector_of_double(vector<vector<double>> &, int);

void array_to_file_single_line(int *, int, ofstream &);
void unsigned_long_array_to_file_single_line(unsigned long *, int, ofstream &);
void two_dimensional_array_to_file_rows_in_single_line_negative_numbers(int **, int, int, ofstream &);
void irregular_two_dimensional_array_to_file_rows_in_single_line(int **, int *, int, ofstream &);

void array_to_file_multiple_lines(int *, int, ofstream &);
void one_column_array_to_file_multiple_lines_numeration(int *, int, ofstream &);

void vector_to_file_row_in_single_line(vector<int> &, ofstream &);
void vector_to_file_row_in_single_line_width_of_three(vector<int> &, ofstream &);
void vector_of_string_to_file_row_in_single_line(vector<string> &, ofstream &);

void two_dimensional_vector_to_file_rows_in_single_line_negative_numbers(vector<vector<int>> &, ofstream &);
void irregular_two_dimensional_vector_to_file_rows_in_single_line(vector<vector<int>> &, ofstream &);
void irregular_two_dimensional_vector_of_double_to_file_rows_in_single_line(vector<vector<double>> &, ofstream &);