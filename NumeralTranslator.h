#ifndef NUMERAL_TRANSLATOR_H
#define NUMERAL_TRANSLATOR_H
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>


class NumeralTranslator
{
private:
    std::map<std::string, int> acceptableDifferences = { {"CM", 900}, {"CD", 400}, {"XC", 90}, {"XL", 40}, {"IX", 9}, {"IV", 4} };
    std::map<std::string, int> romanValues = { {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100}, {"XC", 90}, {"L", 50}, {"XL", 40}, {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1} };
    //Map containing illegal combos not already restricted by allowableNumerals
    std::map<std::string, std::set<std::string>> impossibleCombos{
    {"D", {"CM"}}, {"CD", {"CM", "D"}}, {"C", {"CM", "CD"}},
    {"L", {"XC"}}, {"XL", {"XC", "L"}}, {"X", {"XC", "XL"}},
    {"V", {"IX"}}, {"IV", {"IX", "V"}}, {"I", {"IX", "IV"}} };
    std::set<std::string> allowableNumerals = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    std::vector<std::string> translated;
    std::vector<std::string> inputs;

public:
    NumeralTranslator(std::vector<std::string> i) : inputs(i) {};

    std::vector<std::string> Translate()
    {
        //Looks at first symbol of each input to determine which translation method is needed and sends the input to the proper function
        for (unsigned int i = 0; i < inputs.size(); i++)
        {
            if (isdigit(inputs.at(i).at(0)))
            {
                translated.push_back(NumberToRoman(inputs.at(i)));
            }

            else
            {
                translated.push_back(newFunction(inputs.at(i)));
            }
        }
        return translated;
    }

    //Starts from the end and works backwards based on allowable preceding numerals
    std::string newFunction(std::string numeral)
    {
        int theNumber = 0;
        int index = numeral.size();
        std::set<std::string> currentImpossible = {};

        std::string currentNumeral;

        while (index > 0)
        {
            index--;
            currentNumeral = pairChecker(index, numeral);
            if (currentNumeral.size() == 2)
            {
                index -= 1;
            }
            if (romanValues.find(currentNumeral) == romanValues.end())
            {
                return "**Invalid Input: " + numeral;
            }
            if (!isAllowable(currentNumeral, currentImpossible))
            {
                return "**Invalid Input: " + numeral;
            }


            int value = romanValues.find(currentNumeral)->second;
            theNumber += value;

            purgeNumerals(value);
            if (impossibleCombos.find(currentNumeral) != impossibleCombos.end())
            {
                currentImpossible = impossibleCombos.find(currentNumeral)->second;
            }
            else
            {
                currentImpossible = {};
            }

        }


        return FinalErrorCheck(std::to_string(theNumber), numeral);
    }

    //Checks restriction data structures
    bool isAllowable(std::string numeral, std::set<std::string> impossible)
    {
        if (allowableNumerals.find(numeral) == allowableNumerals.end())
        {
            return false;
        }
        if (impossible.find(numeral) != impossible.end())
        {
            return false;
        }

        return true;
    }

    //Determines if the numeral is one character or two (ex I vs. IV)
    std::string pairChecker(int index, std::string numeral)
    {
        std::stringstream baseNumeral;
        baseNumeral << numeral.at(index);
        if (index == 0)
        {
            return baseNumeral.str();
        }

        std::stringstream testNumeral;
        testNumeral << numeral.at(index - 1) << numeral.at(index);

        if (acceptableDifferences.find(testNumeral.str()) != acceptableDifferences.end())
        {
            return testNumeral.str();
        }

        return baseNumeral.str();
    }

    //Eliminates numerals will values less than the current numeral
    void purgeNumerals(int value)
    {
        std::set<std::string> allowableNumeralsReplacement = allowableNumerals;
        for (auto num : allowableNumerals)
        {
            if (romanValues.find(num)->second < value)
            {
                allowableNumeralsReplacement.erase(num);
            }
        }

        allowableNumerals = allowableNumeralsReplacement;
    }

    //Handles multiples of numerals (Turns stuff like IIIII into V, and asks the user if that's what they meant
    std::string FinalErrorCheck(std::string numberString, std::string numeral)
        {
            std::string correctNumeral = NumberToRoman(numberString);
             
            if(numeral == correctNumeral)
            {
                return numberString;
            }
             
            return "Invalid input: " + numeral + ".\nDid you mean: " + correctNumeral + "?";
             
        }


    std::string NumberToRoman(std::string numberString)
    {
        std::ostringstream out;
        int number = std::stoi(numberString);

        //Uses the LetterAdder function generate Roman Numerals for each order of magnitude 
        out << LetterAdder(number, 100, 'M', 'D', 'C');
        out << LetterAdder(number, 10, 'C', 'L', 'X');
        out << LetterAdder(number, 1, 'X', 'V', 'I');
        while (number >= 1)
        {
            number -= 1;
            out << 'I';
        }

        return out.str();
    }

    std::string LetterAdder(int& number, int magnitude, char big, char middle, char small)
    {
        std::ostringstream out;
        int tenBound = 10 * magnitude;
        int nineBound = 9 * magnitude;
        int fiveBound = 5 * magnitude;
        int fourBound = 4 * magnitude;

        while (number >= tenBound)
        {
            number -= tenBound;
            out << big;
        }
        if (number >= nineBound)
        {
            number -= nineBound;
            out << small << big;
        }
        if (number >= fiveBound)
        {
            number -= fiveBound;
            out << middle;
        }
        if (number >= fourBound)
        {
            number -= fourBound;
            out << small << middle;
        }
        return out.str();
    }
};
















#endif