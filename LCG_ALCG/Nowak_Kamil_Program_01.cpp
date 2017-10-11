#include "own_library.h"
#include <ctime>

struct values
{
	int first = 0, last = 0;
};

void get_c(int &, int);
int * LCG_array(int, int, int, int, int, int);
void find_al(int * &, int, int, int);
int valid_a(int *, int *, int, int, int &);
bool assumptions(int *, int, int, int &);
bool find_pfactor(int, int &);
int * fill_pfactor(int, int);
int * generate_array(int, int, int, int, int);
void proper_indexes(struct values &, int);
int * calculate_candidate_value(int **, int, int);
void ALCG(int *, int, int, int, int);

int main()
{
	char choice;

	do
	{
		cin.get(choice);
		cin.ignore(256, '\n');
	} while (choice != '1' && choice != '2' && cout << "Enter \"1\" or \"2\"!" << endl);

	switch (choice)
	{
	//	Linear Congruential Generator
	case '1':
	{
		string name = "results_p1.txt";
		ofstream fout;
		openFile(name, fout);

		int maxValue, numOfPseudorandoms;

		get_variable(maxValue);
		get_variable(numOfPseudorandoms);

		int m = maxValue + 1;
		int c, a = 2, lmax = 1;
		srand(time(NULL));
		int x0 = rand() % m;

		get_c(c, m);

		int * array = LCG_array(m, a, c, lmax, x0, numOfPseudorandoms);
		array_to_file_multiple_lines(array, numOfPseudorandoms, fout);

		delete[] array;
		fout.close();

		break;
	}

	//	Additive Linear Congruential Generator
	case '2':
	{
		string name = "results_p2.txt";
		ofstream fout;
		openFile(name, fout);

		int maxValue, numOfPseudorandoms;

		get_variable(maxValue);
		get_variable(numOfPseudorandoms);

		values indexes;
		proper_indexes(indexes, numOfPseudorandoms);

		int m = maxValue + 1;
		int c, a = 2, lmax = 1;
		srand(time(NULL));
		int x0 = rand() % m;

		get_c(c, m);

		int * first_array = create_array(numOfPseudorandoms);
		first_array = LCG_array(m, a, c, lmax, x0, numOfPseudorandoms);
		int * second_array = create_array(numOfPseudorandoms);

		copy_array(second_array, first_array, numOfPseudorandoms);
		reverse_array(second_array, numOfPseudorandoms);
		ALCG(second_array, m, indexes.first - 1, indexes.last - 1, numOfPseudorandoms);
		array_to_file_multiple_lines(second_array, numOfPseudorandoms, fout);

		delete[] first_array;
		delete[] second_array;
		fout.close();

		break;
	}
	default:
		break;
	}

	return 0;
}

void get_c(int & c, int m)
{
	do
	{
		c = rand() % m;
	} while (GCD(c, m) == false);
}

int * LCG_array(int m, int a, int c, int lmax, int x0, int numOfPseudorandoms)
{
	//	(m - 2) - number of possibilites in choosing a
	int * lambda = create_array(m - 2);

	for (int i = a; i < m; ++i)
	{
		find_al(lambda, i, lmax, m);
	}

	int lmax_index = 0;

	//	(m - 4) - number of comparing operations
	for (; lmax_index < m - 4; ++lmax_index)
	{
		//	searching for lmax
		if (*(lambda + lmax_index + 1) > *(lambda + lmax_index))
		{
			lmax = *(lambda + lmax_index + 1);
		}
	}

	int lmax_instances = 1;

	//	last comparison is executed for l = 1
	for (int i = lmax_index; i > 0; --i)
	{
		if (*(lambda + i) == lmax)
		{
			++lmax_instances;
			lmax_index = i;
		}
	}

	if (lmax_instances > 1)
	{
		//	array storing maximum a values for the greatest and at the same time equal l values
		int * amax = create_array(lmax_instances);

		//	last comparison is executed for lmax_index = 1
		for (int sentinel = 0; lmax_index >= 0; --lmax_index)
		{
			if (*(lambda + lmax_index) == lmax)
			{
				//	(lmax_index + 2) - lmax array's index increased by 2 is equal to a
				*(amax + sentinel) = lmax_index + 2;
				++sentinel;
			}
		}

		int num_p_factors = 0;

		if (find_pfactor(m, num_p_factors) == true)
		{
			//	error handling
			int is_valid;
			int * pfactor = fill_pfactor(m, num_p_factors);
			is_valid = valid_a(amax, pfactor, lmax_instances, m, num_p_factors);

			if (is_valid != 0)
			{
				a = is_valid;
			}

			else
			{
				a = *(amax);
			}
		}

		//	when any of the assumptions aren't met the greatest a is chosen
		else
		{
			a = *(amax);
		}

		return generate_array(m, a, c, x0, numOfPseudorandoms);
	}

	//	lmax occurs only once in an array
	else
	{
		a = lmax_index + 2;
		return generate_array(m, a, c, x0, numOfPseudorandoms);
	}
}

void find_al(int * & lambda, int a, int l, int m)
{
	while (static_cast<unsigned long long int>(pow(a, l)) % m != 1)
	{
		++l;
	}

	lambda[a - 2] = l;
}

int valid_a(int * amax_array, int * pfactor, int length, int m, int & num_p_factors)
{
	//	loop is being executed unless it finds the greatest a which meets all the assumptions
	for (int i = 0; i < length; ++i)
	{
		if (assumptions(pfactor, *(amax_array + i) - 1, m, num_p_factors) == true)
		{
			return *(amax_array + i);
		}
	}

	//	when none of the a values meets the assumptions
	return 0;
}

bool assumptions(int * pfactor, int b, int m, int & num_p_factors)		//	b = (a - 1)
{
	for (int i = 0; i < num_p_factors; ++i)
	{
		if (b % *(pfactor + i) != 0)
		{
			return false;
		}

		if (m % 4 == 0 && b % 4 != 0)
		{
			return false;
		}
	}

	return true;
}

bool find_pfactor(int m, int & num_p_factors)		//	searching for the m's factors which are prime numbers
{
	for (int i = 2; i < m; ++i)
	{
		if (m % i == 0 && is_prime(i) == true)
		{
			++num_p_factors;
		}
	}

	if (num_p_factors > 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

int * fill_pfactor(int m, int num_p_factors)
{
	int * pfactor = create_array(num_p_factors);

	for (int sentinel = 0, i = 2; i < m; ++i)
	{
		if (i % m == 0 && is_prime(i) == true)
		{
			//	filling an array with the factors which meet the assumptions
			*(pfactor + sentinel) = i;
			++sentinel;
		}
	}

	return pfactor;
}

int * generate_array(int m, int a, int c, int x0, int numOfPseudorandoms)
{
	int * array = create_array(numOfPseudorandoms);
	*(array) = x0;

	for (int i = 1; i < numOfPseudorandoms; ++i)
	{
		*(array + i) = (a * *(array + i - 1) + c) % m;
	}

	return array;
}

void proper_indexes(struct values & indexes, int numOfPseudorandoms)
{
	int pairs[90][2] =
	{
		{ 1,2 },{ 1,3 },{ 1,4 },{ 2,5 },{ 1,6 },{ 1,7 },{ 3,7 },{ 4,9 },{ 3,10 },{ 2,11 },
		{ 1,15 },{ 4,15 },{ 7,15 },{ 3,17 },{ 5,17 },{ 6,17 },{ 7,18 },{ 3,20 },{ 2,21 },{ 1,22 },
		{ 5,23 },{ 9,23 },{ 3,25 },{ 7,25 },{ 3,28 },{ 9,28 },{ 13,28 },{ 2,29 },{ 3,31 },{ 6,31 },
		{ 7,31 },{ 13,31 },{ 13,33 },{ 2,35 },{ 11,36 },{ 4,39 },{ 8,39 },{ 14,39 },{ 3,41 },{ 20,41 },
		{ 5,47 },{ 14,47 },{ 20,47 },{ 21,47 },{ 9,49 },{ 12,49 },{ 15,49 },{ 22,49 },{ 3,52 },{ 19,52 },
		{ 21,52 },{ 24,55 },{ 7,57 },{ 22,57 },{ 19,58 },{ 1,60 },{ 11,60 },{ 1,63 },{ 5,63 },{ 31,63 },
		{ 18,65 },{ 32,65 },{ 9,68 },{ 33,68 },{ 6,71 },{ 9,71 },{ 18,71 },{ 20,71 },{ 35,71 },{ 25,73 },
		{ 28,73 },{ 31,73 },{ 9,79 },{ 19,79 },{ 4,81 },{ 16,81 },{ 35,81 },{ 13,84 },{ 13,87 },{ 38,89 },
		{ 2,93 },{ 21,94 },{ 11,95 },{ 17,95 },{ 6,97 },{ 12,97 },{ 33,97 },{ 34,97 },{ 11,98 },{ 27,98 }
	};
	int sentinel = 0;
	int middle = numOfPseudorandoms / 2;

	while (pairs[sentinel][1] < numOfPseudorandoms + 1)
	{
		++sentinel;
	}

	int ** possible_pairs = create_two_dimensional_array(sentinel, 2);
	sentinel = 0;

	while (pairs[sentinel][1] < numOfPseudorandoms + 1)
	{
		for (int i = 0; i < 2; ++i)
		{
			possible_pairs[sentinel][i] = pairs[sentinel][i];
		}

		++sentinel;
	}

	int * candidates_values = calculate_candidate_value(possible_pairs, sentinel, middle);
	int best_candidate_index = 0;
	int lowest_value = numOfPseudorandoms;

	for (int i = 0; i < sentinel; ++i)
	{
		if (i + 1 != sentinel && *(candidates_values + i) <= lowest_value)
		{
			lowest_value = *(candidates_values + i);
			best_candidate_index = i;
		}
	}

	indexes.first = possible_pairs[best_candidate_index][0];
	indexes.last = possible_pairs[best_candidate_index][1];
}

int * calculate_candidate_value(int ** array, int length, int middle)
{
	int * candidates_values = create_array(length);
	fill_array_with_value(candidates_values, length, 0);
	int ** auxiliary_array = create_two_dimensional_array(length, 2);
	copy_two_dimensional_array(auxiliary_array, array, length, 2);

	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		while (auxiliary_array[sentinel][0] < middle + 1)
		{
			++*(candidates_values + sentinel);
			++auxiliary_array[sentinel][0];
		}

		while (auxiliary_array[sentinel][1] > middle - 1)
		{
			++*(candidates_values + sentinel);
			--auxiliary_array[sentinel][1];
		}
	}

	delete[] auxiliary_array;
	return candidates_values;
}

void ALCG(int * array, int m, int first_index, int second_index, int length)
{
	for (int sentinel = 0; sentinel < length; ++sentinel)
	{
		*(array + second_index) = (*(array + first_index) + *(array + second_index)) % m;
		--second_index;
		--first_index;

		if (second_index == 0)
		{
			second_index = length - 1;
		}

		else if (first_index == 0)
		{
			first_index = length - 1;
		}
	}
}