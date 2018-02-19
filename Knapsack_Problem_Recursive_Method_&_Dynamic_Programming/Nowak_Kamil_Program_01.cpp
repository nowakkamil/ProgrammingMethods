#include "own_library.h"

// variables wchich are used continually in the functions
int sentinel = 0, secondSentinel = 0, thirdSentinel = 0, starter = 0, auxiliaryValue = 0;

void assign_elements(vector<int> &, int * &, int &, int &, const int &, ofstream &);
bool change_sentinels(vector<int> &, int &, int &, const int &, ofstream &);

int main()
{
	string data_input, data_output;
	valid_filename("data_input_p1", ".txt", data_input);
	valid_filename("data_output_p1", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int sets;
	get_variable_from_file_up_to_million(sets, fin);

	for (int sentry = 0, capacity, constCapacity, numOfElements; sentry < sets; ++sentry,
		sentinel = 0, secondSentinel = 0, thirdSentinel = 0)
	{
		get_variable_from_file_up_to_million(capacity, fin);
		constCapacity = capacity;
		get_variable_from_file_up_to_million(numOfElements, fin);

		int * items = create_array<int>(numOfElements);

		for (int secondSentry = 0, auxiliaryValue; secondSentry < numOfElements; ++secondSentry)
		{
			get_variable_from_file_up_to_million(auxiliaryValue, fin);
			*(items + secondSentry) = auxiliaryValue;
		}

		vector<int> solutions_vector;

		assign_elements(solutions_vector, items, numOfElements, capacity, constCapacity, fout);
	}

	fin.close();
	fout.close();

	return 0;
}

void assign_elements(vector<int> & solutions_vector, int * & items, int & numOfElements,
int & targetCapacity, const int & constCapacity, ofstream & fout)
{
	if (starter == sentinel)
	{
		auxiliaryValue = sentinel;
	}

	else
	{
		auxiliaryValue = thirdSentinel;
	}

	if (*(items + auxiliaryValue) == targetCapacity)
	{
		solutions_vector.push_back(*(items + auxiliaryValue));

		fout << constCapacity << " = ";
		vector_to_file_rows_in_single_line(solutions_vector, fout);

		return;
	}

	else if (*(items + auxiliaryValue) < targetCapacity)
	{
		solutions_vector.push_back(*(items + auxiliaryValue));
		targetCapacity = targetCapacity - *(items + auxiliaryValue);

		if (change_sentinels(solutions_vector, numOfElements, targetCapacity, constCapacity, fout) == true)
		{
			return;
		}

		assign_elements(solutions_vector, items, numOfElements, targetCapacity, constCapacity, fout);

		return;
	}

	else
	{
		if (change_sentinels(solutions_vector, numOfElements, targetCapacity, constCapacity, fout) == true)
		{
			return;
		}

		assign_elements(solutions_vector, items, numOfElements, targetCapacity, constCapacity, fout);

		return;
	}
}

bool change_sentinels(vector<int> & solutions_vector, int & numOfElements,
	int & targetCapacity, const int & constCapacity, ofstream & fout)
{
	++starter;

	if (secondSentinel + 1 == thirdSentinel && thirdSentinel == numOfElements - 1)
	{
		solutions_vector.erase(solutions_vector.begin(), solutions_vector.end());
		targetCapacity = constCapacity;

		++sentinel;
		thirdSentinel = sentinel;
		secondSentinel = sentinel;
	}

	else
	{
		if (thirdSentinel == numOfElements - 1)
		{
			solutions_vector.erase(solutions_vector.begin(), solutions_vector.end());
			targetCapacity = constCapacity;

			starter = sentinel;

			if (secondSentinel == numOfElements - 1)
			{
				if (sentinel == numOfElements - 1)
				{
					fout << "LACK" << endl;

					return true;
				}

				++sentinel;
				starter = sentinel;
				thirdSentinel = sentinel;
				secondSentinel = sentinel;
			}

			else
			{
				++secondSentinel;
				thirdSentinel = secondSentinel;
			}
		}

		else
		{
			++thirdSentinel;
		}
	}

	return false;
}