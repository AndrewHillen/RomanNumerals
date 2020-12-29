#include <iostream>
#include <fstream>
#include "NumeralTranslator.h"

using namespace std;

int main(int argC, char* argV[])
{
	//Opening file
	if (argC < 2)
	{
		cerr << "Missing input\n";
		return 1;
	}

	std::string input = argV[1];

	if (input == "0")
	{
		cout << "Romans did not have a number for 0";
	}
	if (input == "")
	{
		cout << "Please enter an input";
	}

	//This was originally built to handle vectors and inputfiles. I just left the vector stuff as is
	vector<string> inputs;
	inputs.push_back(input);


	NumeralTranslator translatedInputs(inputs);

	vector<string> translated = translatedInputs.Translate();

	cout << translated.at(0) << endl;



	return 0;
}