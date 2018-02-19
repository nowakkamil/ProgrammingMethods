#include "own_library.h"

void quicksort(unsigned long *, int, int, int);
int partition(unsigned long *, int, int);

int main()
{
	string data_input, data_output;
	valid_filename("data_input", ".txt", data_input);
	valid_filename("data_output", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int sets, length;
	get_variable_from_file(sets, fin);

	while (sets > 0)
	{
		get_variable_from_file(length, fin);
		unsigned long * arrayOfValues = create_array<unsigned long>(length);
		load_array_from_file(arrayOfValues, length, fin);

		quicksort(arrayOfValues, length, 0, length - 1);
		array_to_file_single_line(arrayOfValues, length, fout);

		delete[] arrayOfValues;
		--sets;
	}

	fin.close();
	fout.close();

	return 0;
}

void quicksort(unsigned long * arrayOfValues, int length, int left_index, int right_index)
{
	int auxiliary_index = 0;

	while (left_index < right_index || auxiliary_index > 0)
	{
		if (left_index < right_index)
		{
			right_index = partition(arrayOfValues, left_index, right_index);
			++auxiliary_index;
		}

		else
		{
			right_index += 2;
			left_index = right_index;

			while (right_index < length)
			{
				++right_index;
			}

			--auxiliary_index;
		}
	}
}

int partition(unsigned long * arrayOfValues, int first_index, int last_index)
{
	unsigned long auxiliary_value = *(arrayOfValues + last_index);
	int left_index = first_index - 1;

	for (int right_index = first_index; right_index < last_index; right_index++)
	{
		if (*(arrayOfValues + right_index) <= auxiliary_value)
		{
			++left_index;
			swap(*(arrayOfValues + left_index), *(arrayOfValues + right_index));
		}
	}

	swap(*(arrayOfValues + left_index + 1), *(arrayOfValues + last_index));
	return left_index;
}