#include "own_library.h"

void add_value_to_weight_ratio(vector<vector<double>> &, const int &);
void knapsack(vector<vector<double>> &, vector<int> &, vector<int> &, int, int, int, const int &, int &, const int &, ofstream &);
void fill_solutions_vector(vector<vector<double>> &, vector<int> &, vector<int> &);
bool promising(vector<vector<double>> &, const int &, const int &, const int &, const int &, const int &, const int &, ofstream &);

int main()
{
	string data_input, data_output;
	valid_filename("data_input", ".txt", data_input);
	valid_filename("data_output", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	int capacity;
	get_variable_from_file(capacity, fin);

	vector<vector<double>> items;

	int sentinel = 0;

	while (fin)
	{
		if (!fin.eof())
		{
			vector<double> added_row_for_items_vector;
			items.push_back(added_row_for_items_vector);

			for (int secondSentinel = 0, auxiliaryValue = 0; !fin.eof() && secondSentinel < 3; ++secondSentinel)
			{
				if (fin >> auxiliaryValue)
				{
					items[sentinel].push_back(auxiliaryValue);
				}
			}

			add_value_to_weight_ratio(items, sentinel);
			++sentinel;
		}

		else
		{
			break;
		}
	}

	sort_two_dimensional_vector_of_double(items, 3);

	vector<int> included(sentinel, 0);
	vector<int> solutions;

	int maxProfit = 0;

	knapsack(items, solutions, included, 0, 0, 0, capacity, maxProfit, sentinel, fout);

	fout << endl << "greatest profit obtained: " << maxProfit << endl << "indexes of items in the knapsack: ";
	vector_to_file_row_in_single_line(solutions, fout);

	fin.close();
	fout.close();

	return 0;
}

/**
* Adding value to weight ratio to a vector of vector of double
*
* @param	vector_of_vector_of_double	vector of vector of double
* @param	sentinel					index of a current element (row) in the vector of vector of double
*/
void add_value_to_weight_ratio(vector<vector<double>> & vector_of_vector_of_double, const int & sentinel)
{
	double value_to_weight_ratio = 0;

	vector<vector<double>>::iterator row;
	vector<double>::iterator column;
	vector<double>::iterator secondColumn;

	row = vector_of_vector_of_double.begin() + sentinel;
	column = row->begin() + 1;
	secondColumn = row->begin() + 2;
	value_to_weight_ratio = *column / *secondColumn;

	vector_of_vector_of_double[sentinel].push_back(value_to_weight_ratio);
}

/**
* Creating a tree corresponding to an optimal combination of items put in the knapsack which will give the greatest profit
*
* @param	items					data of every item to be considered with its properties
* @param	solutions				vector which contains the numbers of items which constitutes the optimal
									combination of items put in the knapsack
* @param	included				vector which consists of only "ones" and "zeros" which are set corresponding
									to the examining combination of items
* @param	level					level represents current item in regard of the combination whether it can be added or omitted
* @param	profit					current profit of the examined combination of items
* @param	weight					current weight of the examined combination of items
* @param	possibleWeight			value which represents the capacity of the considered knapsack
* @param	maxProfit				value which represents the greatest possible profit obtained so far
* @param	numOfElementsConsidered	number of all elements which are to be considered
* @param	fout					object of ofstream class which writes a data to the file
*/
void knapsack(vector<vector<double>> & items, vector<int> & solutions, vector<int> & included, int level, int profit, int weight, const int & possibleWeight, int & maxProfit, const int & numOfElementsConsidered, ofstream & fout)
{
	if (level != 0)
	{
		fout << endl;
	}

	fout << "level: " << level << endl << "combination: ";
	vector_to_file_row_in_single_line(included, fout);

	if (weight <= possibleWeight && profit > maxProfit)
	{
		maxProfit = profit;
		fill_solutions_vector(items, included, solutions);
	}

	if (promising(items, level, profit, weight, possibleWeight, maxProfit, numOfElementsConsidered, fout) == true)
	{
		included[level] = 1;
		knapsack(items, solutions, included, ++level, profit + items[level - 1][1], weight + items[level - 1][2], possibleWeight, maxProfit, numOfElementsConsidered, fout);

		included[level - 1] = 0;
		knapsack(items, solutions, included, level, profit, weight, possibleWeight, maxProfit, numOfElementsConsidered, fout);
	}

	else
	{
		fout << "This node is unpromising" << endl;
	}
}

/**
* Filling solutions vector which contains the numbers of items which constitutes the optimal combination of items put in the knapsack
*
* @param	items					data of every item to be considered with its properties
* @param	solutions				vector which contains the numbers of items which constitutes the optimal
									combination of items put in the knapsack
* @param	included				vector which consists of only "ones" and "zeros" which are set corresponding
									to the examining combination of items
*/
void fill_solutions_vector(vector<vector<double>> & items, vector<int> & included, vector<int> & solutions)
{
	solutions.clear();

	vector<int>::iterator includedRow;

	int sentinel = 0;
	for (includedRow = included.begin(); includedRow != included.end(); ++sentinel, ++includedRow)
	{
		if (*includedRow == true)
		{
			solutions.push_back(items[sentinel][0]);
		}
	}
}

/**
* Evaluating whether an examined combination is prosperous
*
* @param	items					data of every item to be considered with its properties
* @param	level					level at which current item is added or omitted to the combination
* @param	profit					current profit of the examined combination of items
* @param	weight					current weight of the examined combination of items
* @param	possibleWeight			value which represents the capacity of the considered knapsack
* @param	maxProfit				value which represents the greatest possible profit obtained so far
* @param	numOfElementsConsidered	number of all elements which are to be considered
* @param	fout					object of ofstream class which writes a data to the file
*/
bool promising(vector<vector<double>> & items, const int & level, const int & profit, const int & weight, const int & possibleWeight, const int & maxProfit, const int & numOfElementsConsidered, ofstream & fout)
{
	int firstIndex, secondIndex, totalWeight;
	double bound;

	if (weight >= possibleWeight)
	{
		return false;
	}

	else
	{
		firstIndex = level;
		bound = profit;
		totalWeight = weight;

		while (firstIndex < numOfElementsConsidered && totalWeight + items[firstIndex][2] <= possibleWeight)
		{
			totalWeight = totalWeight + items[firstIndex][2];
			bound = bound + items[firstIndex][1];
			++firstIndex;
		}

		secondIndex = firstIndex;

		if (secondIndex < numOfElementsConsidered)
		{
			bound = bound + (possibleWeight - totalWeight) * items[secondIndex][3];
		}

		fout << "profit:\t" << profit << endl;
		fout << "weight:\t" << weight << endl;
		fout << "bound:\t" << bound << endl;

		return bound > maxProfit;
	}
}