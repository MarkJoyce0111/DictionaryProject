#pragma once
#include <iostream>
#include <string>
#include <vector>

//Mark Joyce 2019 SID: 10421019

using namespace std;

class Word
{
	//Declaration Section
private:

	string word;
	string definition;
	string type; // in documentation ?????

public:

	Word(string, string, string);
	~Word();
	string getWord();
	string getDefinition();
	string getType();
	void printDefinition();
	void printLexical();

};

/*Implementation*/

//Constructor
Word::Word(string word, string definition, string type)
{
	Word::word = word;
	Word::definition = definition;
	Word::type = type;
}

//Destructor
Word::~Word()
{
	
}

//Returns word definition
string Word::getDefinition()
{
	return definition;
}

//Returns the word Type
string Word::getType()
{
	return type;
}

//Returns the word
string Word::getWord()
{
	return word;
}

//Print Definition.
void Word::printDefinition()
{
	char t;
	const char bullet = 254;
	cout << bullet << " ";
	for (unsigned int i = 0; i < definition.length(); i++)
	{
		cout << definition[i];
		if (definition[i] == 0x3b || definition[i] > 0x7E) // Equal to ';' OR > than '~'
		{
			i++; //Remove space.
			cout << endl;
			i++;
			if (definition[i] == 0x20) // Equal to ' ';
			{
				i++;
			}
			t = toupper(definition[i]); //To uppercase
			cout << bullet << " " << t;
		}
	}
}

//Print Lexical
void Word::printLexical()
{
	string returnlexical;
	string lexi[2][8] = {
		{"adj", "adv","n","v", "prep", "pn", "n_and_v", "misc"},
		{"Adjective", "Adverb", "Noun", "Verb" , "Preposition", "Proper Noun,", "Noun and a Verb", "Miscellaneous"}
	};

	for (unsigned int i = 0; i < 8; i++)
	{
		if (lexi[0][i] == type)
		{
			returnlexical = lexi[1][i]; // Return Translation.
			break;
		}
	}
	cout << returnlexical << endl;
}


