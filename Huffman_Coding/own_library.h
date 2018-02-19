#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void valid_filename(string, string, string &);
void valid_filename_two_possibilities(string, string, string, string &);

ofstream & openFile(string, ofstream &);

ifstream & openFile(string, ifstream &);

void get_variable(int &);
void get_variable_from_file(int &, ifstream &);
void get_variable_from_file_up_to_million(int &, ifstream &);

template <typename T>
T return_bigger_value(const T & firstValue, const T & secondValue)
{
	return (firstValue > secondValue) ? firstValue : secondValue;
}

bool is_prime(int);

bool GCD(int, int);

unsigned long long int factorial(int);

#pragma region createArray
template <typename T>
T * create_array(int length)
{
	T * arrayOfValues = nullptr;

	try
	{
		arrayOfValues = new T[length];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		// displays the exact cause
		cout << ba.what() << endl;
	}

	return arrayOfValues;
}

template <typename T>
T ** create_two_dimensional_array(int rows, int columns)
{
	T ** arrayOfValues = nullptr;

	try
	{
		arrayOfValues = new T *[rows];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		// displays the exact cause
		cout << ba.what() << endl;
	}

	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		try
		{
			*(arrayOfValues + sentinel) = new T[columns];
		}

		catch (bad_alloc & ba)
		{
			cout << "Error! (couldn't allocate the dynamic array)" << endl;
			// displays the exact cause
			cout << ba.what() << endl;
		}

	}

	return arrayOfValues;
}
#pragma endregion

#pragma region deleteArray
template <typename T>
void delete_two_dimensional_array(T ** arrayOfValues, int columns)
{
	for (int sentinel = 0; sentinel < columns; ++sentinel)
	{
		delete[] arrayOfValues[sentinel];
	}

	delete[] arrayOfValues;
}
#pragma endregion

template <typename T>
void load_array_from_file(T * arrayOfValues, int length, ifstream & fin)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		fin >> *(arrayOfValues + sentinel);
	}
}

#pragma region fillArray
template <typename T>
void fill_array_with_value(T * arrayOfValues, int length, T value)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		*(arrayOfValues + sentinel) = value;
	}
}
template <typename T>
void fill_two_dimensional_array_with_value(T ** arrayOfValues, int rows, int columns, T value)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			arrayOfValues[sentinel][secondSentinel] = value;
		}
	}
}

template <typename T>
void fill_array_increasingly_with_initial_value(T * arrayOfValues, int final_element, T initial_value)
{
	for (int sentinel = 0; sentinel < final_element; ++sentinel)
	{
		*(arrayOfValues + sentinel) = sentinel + initial_value;
	}
}
#pragma endregion

#pragma region manipulateArray
template <typename T>
void copy_array(T * arrayOfValues, T * arrayCopied, int length)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		*(arrayOfValues + sentinel) = *(arrayCopied + sentinel);
	}
}

template <typename T>
void copy_two_dimensional_array(T ** arrayOfValues, T ** arrayCopied, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			arrayOfValues[sentinel][secondSentinel] = arrayCopied[sentinel][secondSentinel];
		}
	}
}

template <typename T>
void reverse_array(T * arrayOfValues, int length)
{
	int first = 0;
	int last = length - 1;

	while (first < last)
	{
		swap(*(arrayOfValues + first), *(arrayOfValues + last));
		++first;
		--last;
	}
}
#pragma endregion

#pragma region displayArray
template <typename T>
void display_array_in_single_line(T * arrayOfValues, int length)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		cout << *(arrayOfValues + sentinel);

		if (sentinel != length - 1)
		{
			cout << " ";
		}
	}

	cout << endl;
}
template <typename T>
void display_two_dimensional_array_rows_in_single_line(T ** arrayOfValues, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			cout << arrayOfValues[sentinel][secondSentinel];

			if (sentinel != columns - 1)
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}
template <typename T>
void display_two_dimensional_array_rows_in_single_line_negative_numbers(T ** arrayOfValues, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			cout.width(3);
			cout.fill(' ');
			cout << arrayOfValues[sentinel][secondSentinel];
		}

		cout << endl;
	}
}
template <typename T>
void display_irregular_two_dimensional_array_rows_in_single_line(T ** arrayOfValues, int * arrayOfColumns, int rows)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < *(arrayOfColumns + sentinel); ++secondSentinel)
		{
			cout << arrayOfValues[sentinel][secondSentinel];

			if (secondSentinel != *(arrayOfColumns + rows) - 1)
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}

template <typename T>
void display_array_multiple_lines_numeration(T * arrayOfValues, int length)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		cout << "#" << sentinel + 1 << ": " << *(arrayOfValues + sentinel);
		cout << endl;
	}
}

template <typename T>
void display_vector_in_single_line(const vector<T> & vectorOfValues)
{
	auto indexOfLastElement = end(vectorOfValues);

	for (auto sentinel = vectorOfValues.begin(); sentinel != vectorOfValues.end(); ++sentinel)
	{
		auto & element = *sentinel;

		cout << element;

		if (sentinel != indexOfLastElement - 1)
		{
			cout << " ";
		}
	}

	cout << endl;
}
#pragma endregion

template <typename T>
void sort_two_dimensional_vector(vector<vector<T>> & vectorOfVectorOfValues, int sentinel)
{
	sort(vectorOfVectorOfValues.begin(), vectorOfVectorOfValues.end(),
		[&](const vector<T> & firstToCompare, const vector<T> & secondToCompare)
	{
		return firstToCompare[sentinel] > secondToCompare[sentinel];
	});
}

#pragma region arrayToFile
template <typename T>
void array_to_file_single_line(T * arrayOfValues, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		fout << *(arrayOfValues + sentinel);

		if (sentinel != length - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}
template <typename T>
void two_dimensional_array_to_file_rows_in_single_line_negative_numbers(T ** arrayOfValues, int rows, int columns, ofstream & fout)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		fout.width(2);
		fout.fill(' ');
		fout << arrayOfValues[sentinel][0];

		for (int secondSentinel = 1; secondSentinel < columns; ++secondSentinel)
		{
			fout.width(3);
			fout.fill(' ');
			fout << arrayOfValues[sentinel][secondSentinel];
		}

		fout << endl;
	}
}
template <typename T>
void irregular_two_dimensional_array_to_file_rows_in_single_line(T ** arrayOfValues, T * arrayOfColumns, int rows, ofstream & fout)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < *(arrayOfColumns + sentinel); ++secondSentinel)
		{
			fout << arrayOfValues[sentinel][secondSentinel];

			if (secondSentinel != *(arrayOfColumns + rows) - 1)
			{
				fout << " ";
			}
		}

		fout << endl;
	}
}

template <typename T>
void array_to_file_multiple_lines(T * arrayOfValues, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		fout << *(arrayOfValues + sentinel) << endl;
	}
}
template <typename T>
void array_to_file_multiple_lines_numeration(T * arrayOfValues, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		fout << "#" << sentinel + 1 << ": " << *(arrayOfValues + sentinel);
		fout << endl;
	}
}
#pragma endregion

#pragma region vectorToFile
template <typename T>
void vector_to_file_rows_in_single_line(vector<T> & vectorOfValues, ofstream & fout)
{
	typename vector<T>::iterator column;

	for (column = vectorOfValues.begin(); column != vectorOfValues.end(); ++column)
	{
		fout.width(3);
		fout.fill(' ');
		fout << *column;

		if (column != vectorOfValues.end() - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}
template <typename T>
void vector_to_file_rows_in_single_line_fixed_width(vector<T> & vectorOfValues, int coutWidth, ofstream & fout)
{
	typename vector<T>::iterator column;

	for (column = vectorOfValues.begin(); column != vectorOfValues.end(); ++column)
	{
		fout.width(coutWidth);
		fout.fill(' ');
		fout << *column;

		if (column != vectorOfValues.end() - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

template <typename T>
void two_dimensional_vector_to_file_rows_in_single_line_negative_numbers(vector<vector<T>> & vectorOfVectorOfValues, ofstream & fout)
{
	typename vector<vector<T>>::iterator row;
	typename vector<T>::iterator column;

	for (row = vectorOfVectorOfValues.begin(); row != vectorOfVectorOfValues.end(); ++row)
	{
		for (column = row->begin(); column != row->end(); ++column)
		{
			if (column == row->begin())
			{
				fout.width(2);
				fout.fill(' ');
				fout << *column;
			}

			else
			{
				fout.width(3);
				fout.fill(' ');
				fout << *column;
			}
		}

		fout << endl;
	}
}
template <typename T>
void two_dimensional_vector_to_file_rows_in_single_line(vector<vector<T>> & vectorOfVectorOfValues, ofstream & fout)
{
	typename vector<vector<T>>::iterator row;
	typename vector<T>::iterator column;

	for (row = vectorOfVectorOfValues.begin(); row != vectorOfVectorOfValues.end(); ++row)
	{
		for (column = row->begin(); column != row->end(); ++column)
		{
			fout.width(3);
			fout.fill(' ');
			fout << *column;

			if (column != row->end() - 1)
			{
				fout << " ";
			}
		}

		fout << endl;
	}
}
#pragma endregion