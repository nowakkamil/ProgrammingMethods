#include "own_library.h"

void compute_solutions(vector<vector<int>> &, vector<vector<int>> &, vector<vector<int>> &, const int &, const int &);

int main()
{
	string data_input, data_output;
	valid_filename("data_input_p2", ".txt", data_input);
	valid_filename("data_output_p2", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int capacity;
	get_variable_from_file(capacity, fin);

	vector<vector<int>> items, greatestValue, chosenItem;
	vector<int> added_row_for_solutions_vector(capacity + 1, 0);
	greatestValue.push_back(added_row_for_solutions_vector);
	chosenItem.push_back(added_row_for_solutions_vector);

	int sentinel = 0;

	while (fin)
	{
		if (!fin.eof())
		{
			vector<int> added_row_for_items_vector;
			items.push_back(added_row_for_items_vector);

			vector<int> added_row_for_solutions_vector(capacity + 1, 0);
			greatestValue.push_back(added_row_for_solutions_vector);
			chosenItem.push_back(added_row_for_solutions_vector);

			for (int secondSentinel = 0, auxiliaryValue = 0; !fin.eof() && secondSentinel < 3; ++secondSentinel)
			{
				if (fin >> auxiliaryValue)
				{
					items[sentinel].push_back(auxiliaryValue);
				}
			}

			++sentinel;
		}

		else
		{
			break;
		}
	}

	compute_solutions(greatestValue, chosenItem, items, capacity, sentinel);

	irregular_two_dimensional_vector_to_file_rows_in_single_line(greatestValue, fout);
	fout << endl;

	irregular_two_dimensional_vector_to_file_rows_in_single_line(chosenItem, fout);
	fout << endl;

	fin.close();
	fout.close();

	return 0;
}

void compute_solutions(vector<vector<int>> & greatestValue, vector<vector<int>> & chosenItem,
	vector<vector<int>> & items, const int & capacity, const int & lastElement)
{
	for (int sentinel = 0; sentinel <= lastElement; ++sentinel)
	{
		for (int remainingCapacity = 0; remainingCapacity <= capacity; ++remainingCapacity)
		{
			if (sentinel == 0 || remainingCapacity == 0)
			{
				greatestValue[sentinel][remainingCapacity] = 0;
				chosenItem[sentinel][remainingCapacity] = 0;
			}

			else if (items[sentinel - 1][1] <= remainingCapacity)
			{
				int first_value = items[sentinel - 1][2] + greatestValue[sentinel - 1][remainingCapacity - items
					[sentinel - 1][1]];
				int second_value = greatestValue[sentinel - 1][remainingCapacity];
				int bigger_value = return_bigger_value(first_value, second_value);
				greatestValue[sentinel][remainingCapacity] = bigger_value;

				if (bigger_value == first_value)
				{
					chosenItem[sentinel][remainingCapacity] = items[sentinel - 1][0];
				}

				else
				{
					chosenItem[sentinel][remainingCapacity] = chosenItem[sentinel - 1][remainingCapacity];
				}
			}

			else
			{
				greatestValue[sentinel][remainingCapacity] = greatestValue[sentinel - 1][remainingCapacity];
				chosenItem[sentinel][remainingCapacity] = chosenItem[sentinel - 1][remainingCapacity];
			}
		}
	}
}