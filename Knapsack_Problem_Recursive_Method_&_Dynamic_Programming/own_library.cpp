void valid_filename(string valid_filename, string extension, string & name)
{
	string valid_filename_with_extension = valid_filename;
	valid_filename_with_extension.append(extension);

	do
	{
		cin >> name;

		if (name == valid_filename)
		{
			name.append(extension);
			break;
		}

		if (name == valid_filename_with_extension)
		{
			break;
		}

	} while (cout << "Enter the proper name of the file!" << endl);
}

void valid_filename_two_possibilities(string first_valid_filename, string second_valid_filename, string extension, string & name)
{
	string first_valid_filename_with_extension = first_valid_filename;
	first_valid_filename_with_extension.append(extension);

	string second_valid_filename_with_extension = second_valid_filename;
	second_valid_filename_with_extension.append(extension);

	do
	{
		cin >> name;

		if (name == first_valid_filename || name == second_valid_filename)
		{
			name.append(extension);
			break;
		}

		if (name == first_valid_filename_with_extension || name == second_valid_filename_with_extension)
		{
			break;
		}

	} while (cout << "Enter the proper name of the file!" << endl);
}

ofstream & openFile(string name, ofstream & fout)
{
	fout.open(name, ios_base::app);							//	appending new data to the file

	if (!fout.is_open())									//	error opening the file
	{
		cout << "Error! (couldn't open the file: " << name << ")" << endl;
		exit(EXIT_FAILURE);
	}

	return fout;
}

ifstream & openFile(string name, ifstream & fin)
{
	fin.open(name);

	if (!fin.is_open())										//	error opening the file
	{
		cout << "Error! (couldn't open the file: " << name << ")" << endl;
		exit(EXIT_FAILURE);
	}

	return fin;
}

void get_variable(int & variable)							//	assuming valid value is greater than 1
{
	do
	{
		cin >> variable;
	} while (variable < 1 && cout << "Enter valid value of the variable: ");
}

void get_variable_from_file(int & variable, ifstream & fin)	//	assuming valid value is greater than 1
{
	fin >> variable;

	if (variable < 1)
	{
		cout << "Invalid value of variable!" << endl;
	}
}

void get_variable_from_file_up_to_million(int & variable, ifstream & fin)	//	assuming valid value is greater than 1
{																			//	and lesser than 1000000
	fin >> variable;

	if (variable < 1 || variable > 1000000)
	{
		cout << "Invalid value of variable!" << endl;
	}
}

int return_bigger_value(int first_value, int second_value)
{
	return (first_value > second_value) ? first_value : second_value;
}

bool is_prime(int variable)
{
	int variable_sqrt = sqrt(variable);
	int instances = 0;

	for (int sentinel = 2; sentinel <= variable_sqrt; sentinel++)
	{
		if (variable % sentinel == 0)
		{
			++instances;
		}
	}

	if (instances > 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool GCD(int first_value, int second_value)
{
	int auxiliary_value;

	while (second_value != 0)
	{
		auxiliary_value = first_value % second_value;
		first_value = second_value;
		second_value = auxiliary_value;
	}

	if (first_value == 1)
	{
		return true;
	}

	else
	{
		return false;
	}
}

unsigned long long int factorial(int value)
{
	long long int sum = 1;

	for (int sentinel = 2; sentinel < value + 1; sentinel++)
	{
		sum *= sentinel;
	}

	return sum;
}

int * create_array(int length)
{
	int * array = nullptr;

	try
	{
		array = new int[length];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		cout << ba.what() << endl;							//	displays the exact cause
	}

	return array;
}

unsigned long * create_unsigned_long_array(int length)
{
	unsigned long * array = nullptr;

	try
	{
		array = new unsigned long[length];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		cout << ba.what() << endl;							//	displays the exact cause
	}

	return array;
}

int ** create_two_dimensional_array(int rows, int columns)
{
	int ** array = nullptr;

	try
	{
		array = new int *[rows];
	}

	catch (bad_alloc & ba)
	{
		cout << "Error! (couldn't allocate the dynamic array)" << endl;
		cout << ba.what() << endl;							//	displays the exact cause
	}

	for (int sentinel = 0; sentinel < rows; sentinel++)
	{
		try
		{
			*(array + sentinel) = new int[columns];
		}

		catch (bad_alloc & ba)
		{
			cout << "Error! (couldn't allocate the dynamic array)" << endl;
			cout << ba.what() << endl;						//	displays the exact cause
		}

	}

	return array;
}

void delete_two_dimensional_array(int ** array, int columns)
{
	for (int sentinel = 0; sentinel < columns; sentinel++)
	{
		delete[] array[sentinel];
	}

	delete[] array;
}

void load_unsigned_long_array_from_file(unsigned long * array, int length, ifstream & fin)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		fin >> *(array + sentinel);
	}
}

void fill_array_with_value(int * array, int length, int value)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		*(array + sentinel) = value;
	}
}

void fill_two_dimensional_array_with_value(int ** array, int rows, int columns, int value)
{
	for (int sentinel = 0; sentinel < rows; sentinel++)
	{
		for (int secondSentinel = 0; secondSentinel < columns; secondSentinel++)
		{
			array[sentinel][secondSentinel] = value;
		}
	}
}

void fill_array_increasingly_with_initial_value(int * array, int final_element, int initial_value)
{
	for (int sentinel = 0; sentinel < final_element; sentinel++)
	{
		*(array + sentinel) = sentinel + initial_value;
	}
}

void copy_array(int * array, int * arrayCopied, int length)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		*(array + sentinel) = *(arrayCopied + sentinel);
	}
}

void copy_two_dimensional_array(int ** array, int ** arrayCopied, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; sentinel++)
	{
		for (int secondSentinel = 0; secondSentinel < columns; secondSentinel++)
		{
			array[sentinel][secondSentinel] = arrayCopied[sentinel][secondSentinel];
		}
	}
}

void reverse_array(int * array, int length)
{
	int first = 0;
	int last = length - 1;

	while (first < last)
	{
		swap(*(array + first), *(array + last));
		++first;
		--last;
	}
}

void display_array_in_single_line(int * array, int length)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		cout << *(array + sentinel);

		if (sentinel != length - 1)
		{
			cout << " ";
		}
	}

	cout << endl;
}

void display_two_dimensional_array_rows_in_single_line(int ** array, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			cout << array[sentinel][secondSentinel];

			if (sentinel != columns - 1)
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}

void display_two_dimensional_array_rows_in_single_line_negative_numbers(int ** array, int rows, int columns)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < columns; ++secondSentinel)
		{
			cout.width(3);
			cout.fill(' ');
			cout << array[sentinel][secondSentinel];
		}

		cout << endl;
	}
}

void display_irregular_two_dimensional_array_rows_in_single_line(int ** array, int * arrayOfColumns, int rows)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < *(arrayOfColumns + sentinel); ++secondSentinel)
		{
			cout << array[sentinel][secondSentinel];

			if (secondSentinel != *(arrayOfColumns + rows) - 1)
			{
				cout << " ";
			}
		}

		cout << endl;
	}
}

void display_one_column_array_multiple_lines_numeration(int * array, int length)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		cout << "#" << sentinel + 1 << ": " << *(array + sentinel);
		cout << endl;
	}
}

void display_vector_in_single_line(const vector<int> & vector_of_int)
{
	auto indexOfLastElement = end(vector_of_int);

	for (auto sentinel = vector_of_int.begin(); sentinel != vector_of_int.end(); ++sentinel)
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

void sort_two_dimensional_vector_of_double(vector<vector<double>> & vector_of_vector_of_double, int sentinel)
{
	sort(vector_of_vector_of_double.begin(), vector_of_vector_of_double.end(),
		[&](const vector<double> & first_to_compare, const vector<double> & second_to_compare)
	{
		return first_to_compare[sentinel] > second_to_compare[sentinel];
	});
}


void array_to_file_single_line(int * array, int	length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		fout << *(array + sentinel);

		if (sentinel != length - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

void unsigned_long_array_to_file_single_line(unsigned long * array, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		fout << *(array + sentinel);

		if (sentinel != length - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

void two_dimensional_array_to_file_rows_in_single_line_negative_numbers(int ** array, int rows, int columns, ofstream & fout)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		fout.width(2);
		fout.fill(' ');
		fout << array[sentinel][0];

		for (int secondSentinel = 1; secondSentinel < columns; ++secondSentinel)
		{
			fout.width(3);
			fout.fill(' ');
			fout << array[sentinel][secondSentinel];
		}

		fout << endl;
	}
}

void irregular_two_dimensional_array_to_file_rows_in_single_line(int ** array, int * arrayOfColumns, int rows, ofstream & fout)
{
	for (int sentinel = 0; sentinel < rows; ++sentinel)
	{
		for (int secondSentinel = 0; secondSentinel < *(arrayOfColumns + sentinel); ++secondSentinel)
		{
			fout << array[sentinel][secondSentinel];

			if (secondSentinel != *(arrayOfColumns + rows) - 1)
			{
				fout << " ";
			}
		}

		fout << endl;
	}
}

void array_to_file_multiple_lines(int * array, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		fout << *(array + sentinel) << endl;
	}
}

void one_column_array_to_file_multiple_lines_numeration(int * array, int length, ofstream & fout)
{
	for (int sentinel = 0; sentinel < length; sentinel++)
	{
		fout << "#" << sentinel + 1 << ": " << *(array + sentinel);
		fout << endl;
	}
}

void vector_to_file_row_in_single_line(vector<int> & vector_of_int, ofstream & fout)
{
	vector<int>::iterator column;

	for (column = vector_of_int.begin(); column != vector_of_int.end(); ++column)
	{
		fout.width(3);
		fout.fill(' ');
		fout << *column;

		if (column != vector_of_int.end() - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

void vector_to_file_row_in_single_line_width_of_three(vector<int> & vector_of_int, ofstream & fout)
{
	vector<int>::iterator column;

	for (column = vector_of_int.begin(); column != vector_of_int.end(); ++column)
	{
		fout.width(3);
		fout.fill(' ');
		fout << *column;

		if (column != vector_of_int.end() - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

void vector_of_string_to_file_row_in_single_line(vector<string> & vector_of_string, ofstream & fout)
{
	vector<string>::iterator column;

	for (column = vector_of_string.begin(); column != vector_of_string.end(); ++column)
	{
		fout << *column;

		if (column != vector_of_string.end() - 1)
		{
			fout << " ";
		}
	}

	fout << endl;
}

void two_dimensional_vector_to_file_rows_in_single_line_negative_numbers(vector<vector<int>> & vector_of_vector_of_int, ofstream & fout)
{
	vector<vector<int>>::iterator row;
	vector<int>::iterator column;

	for (row = vector_of_vector_of_int.begin(); row != vector_of_vector_of_int.end(); ++row)
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

void irregular_two_dimensional_vector_to_file_rows_in_single_line(vector<vector<int>> & vector_of_vector_of_int, ofstream & fout)
{
	vector<vector<int>>::iterator row;
	vector<int>::iterator column;

	for (row = vector_of_vector_of_int.begin(); row != vector_of_vector_of_int.end(); ++row)
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

void irregular_two_dimensional_vector_of_double_to_file_rows_in_single_line(vector<vector<double>> & vector_of_vector_of_double, ofstream & fout)
{
	vector<vector<double>>::iterator row;
	vector<double>::iterator column;

	for (row = vector_of_vector_of_double.begin(); row != vector_of_vector_of_double.end(); ++row)
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