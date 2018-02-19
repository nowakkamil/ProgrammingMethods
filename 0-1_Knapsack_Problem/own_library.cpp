#include "own_library.h"

void valid_filename(string validFilename, string extension, string & name)
{
	string validFilename_with_extension = validFilename;
	validFilename_with_extension.append(extension);

	do
	{
		cin >> name;

		if (name == validFilename)
		{
			name.append(extension);
			break;
		}

		if (name == validFilename_with_extension)
		{
			break;
		}

	} while (cout << "Enter the proper name of the file!" << endl);
}

void valid_filename_two_possibilities(string firstValidFilename, string secondValidFilename, string extension, string & name)
{
	string firstValidFilename_with_extension = firstValidFilename;
	firstValidFilename_with_extension.append(extension);

	string secondValidFilename_with_extension = secondValidFilename;
	secondValidFilename_with_extension.append(extension);

	do
	{
		cin >> name;

		if (name == firstValidFilename || name == secondValidFilename)
		{
			name.append(extension);
			break;
		}

		if (name == firstValidFilename_with_extension || name == secondValidFilename_with_extension)
		{
			break;
		}

	} while (cout << "Enter the proper name of the file!" << endl);
}

ofstream & openFile(string name, ofstream & fout)
{
	// appending new data to the file
	fout.open(name, ios_base::app);

	// error opening the file
	if (!fout.is_open())
	{
		cout << "Error! (couldn't open the file: " << name << ")" << endl;
		exit(EXIT_FAILURE);
	}

	return fout;
}

ifstream & openFile(string name, ifstream & fin)
{
	fin.open(name);

	// error opening the file
	if (!fin.is_open())
	{
		cout << "Error! (couldn't open the file: " << name << ")" << endl;
		exit(EXIT_FAILURE);
	}

	return fin;
}

void get_variable(int & variable)
{
	// assuming valid value is greater than or equal to 1
	do
	{
		cin >> variable;
	} while (variable < 1 && cout << "Enter valid value of the variable: ");
}

void get_variable_from_file(int & variable, ifstream & fin)
{
	fin >> variable;

	// assuming valid value is greater than or equal to 1
	if (variable < 1)
	{
		cout << "Invalid value of variable!" << endl;
	}
}

void get_variable_from_file_up_to_million(int & variable, ifstream & fin)	
{
	// assuming valid value is greater than or equal to 1 and lesser than or equal to 1 000 000
	fin >> variable;

	if (variable < 1 || variable > 1000000)
	{
		cout << "Invalid value of variable!" << endl;
	}
}

bool is_prime(int variable)
{
	int variable_sqrt = sqrt(variable);
	int instances = 0;

	for (int sentinel = 2; sentinel <= variable_sqrt; ++sentinel)
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

bool GCD(int firstValue, int secondValue)
{
	int auxiliaryValue;

	while (secondValue != 0)
	{
		auxiliaryValue = firstValue % secondValue;
		firstValue = secondValue;
		secondValue = auxiliaryValue;
	}

	if (firstValue == 1)
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

	for (int sentinel = 2; sentinel < value + 1; ++sentinel)
	{
		sum *= sentinel;
	}

	return sum;
}