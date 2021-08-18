#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Word.h"

//Mark Joyce 2019; Student ID: 10421019

//The Dictionary Class
class Dictionary
{
private:
	vector<Word* > words; //Create a Vector  Words connects to Word.h class Word. A vector full of Word pointers.

	enum command { isBlank, isNumber, isInRange, isWord, isLength }; //enum for function checkIt() - verification type.

	/*
	loadDictionary - Loads Dictionary file, Places memory location of strings into a vector using a Word class for structure.*/
	void loadDictionary(string fileName)
	{
		ifstream dictFile(fileName);
		//Opening the file
		if (dictFile.is_open())
		{
			string buffer;
			string currentWord = "none";
			string currentDefinition = "none";
			string currentType = "none";

			while (!dictFile.eof())
			{
				getline(dictFile, buffer); //Fill first
				if (buffer != "")          //Test
				{
					//First Line = Word
					currentWord = buffer;

					//Second Line = Definition
					getline(dictFile, buffer);
					currentDefinition = buffer;

					//Third Line = Type
					getline(dictFile, buffer);
					currentType = buffer;

					//Create a Word record - Can do without pointer.
					//Word *f;
					//f =  new Word(currentWord, currentDefinition, currentType); //Using the class

					//Create a Word recorod
					words.push_back(new Word(currentWord, currentDefinition, currentType));
				}
			}
			dictFile.close();
		}
		else
		{   //No file found.
			cout << "File Load Error!" << endl;
			system("pause");
			exit(0); //Exit program
		}
	}

	/*
	toLowercase - converts string to lowercase and returns it.
	*/
	string toLowercase(string term)
	{
		for (unsigned int i = 0; i < term.length(); i++) // Convert to lowercase
		{
			term[i] = tolower(term[i]);
		}
		return term;
	}

	/*
	findTerm - Called by searchWord(), Searches vector
	Calls Word class function getWord() to get a word,
	If target found, Prints term, then calls Word Class function printDefinition & printLexical; that prints definition and type of term.*/
	void findTerm(string term)
	{
		bool success = false;

		term = toLowercase(term);

		for (unsigned int i = 0; i < words.size(); i++)
		{
			string buffer;
			buffer = words[i]->getWord();
			if (term == buffer)
			{
				success = true;
				system("cls");
				cout << "\033[4mWord:\033[0m" << " " << "\u001b[1m\u001b[32m\u001b[7m" << words[i]->getWord() << "\u001b[0m" << endl; //word
				cout << endl;
				cout << "\033[4mDefinition\033[0m" << "\n" << endl; // Definition
				words[i]->printDefinition();
				cout << "\n" << endl;
				cout << "\033[4mWord Type:\033[0m " << endl; // Lexi
				//cout << "\n" << endl;
				words[i]->printLexical();

				system("pause");
			}
		}
		if (!success) //Search Failed
		{
			cout << "word not found" << endl;
			system("pause");
		}
	}

	/*
	getInput - Gets user input and returns it in a string variable.*/
	string getInput()
	{
		string dummy;
		//getline(cin, dummy, ' ');
		cin >> dummy;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore all other data (rest of the line) in the buffer: https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
		return dummy;
	}

	/*
	searchWord - Searches for an exact match to an entered word.
	Verifies user input*/
	void searchWord()
	{
		string choice;
		bool error = true;

		while (error) // While input is incorrect, loop.
		{
			wSTitle(); //Display Title
			choice = getInput();
			if (checkIt(choice, isWord, "Not a Word, Please enter a word to search"))
			{
				error = true;
			}
			else
			{
				error = false;
			}
		}

		findTerm(choice); //Find the string.
	}

	/*
	searchMultiLetter - Searches for a single letter greater than a selected multible in all words*/
	void searchMultiLetter()
	{
		string choice;
		string letter;
		int multiples;
		int match = 0;
		bool success = false;
		bool error = true;

		//Get single letter to search from user, and verify correct input.
		while (error)
		{
			mLTitle(); //Clear Screen, Display Multi Letter Title.
			letter = getInput(); //Get user Input
			if (checkIt(letter, isWord, "Not a letter, Please enter a single letter to search"))
			{
				error = true;  //For reference
			}
			else// Is a word, Check the length, should be One.
			{
				if (checkIt(letter, isLength, "Please enter a single character, for example 'A' Hyphen (-) is allowed ", 1))
				{
					error = true;
				}
				else
				{
					error = false;
				}
			}
		}
		//Get Mulitples from user, and verify correct input.
		error = true;
		while (error)
		{
			mLTitle();
			cout << "How many multiples of '" << letter << "' do you wish to search for?" << endl;
			cout << "Greater than '" << letter << "' times ";
			choice = getInput();
			if (checkIt(choice, isNumber, "Please enter a number from 1 to 99, for example '1' "))
			{
				error = true;
			}
			else // Is a Number
			{
				if (checkIt(choice, isLength, "Please enter a number less than 100, for example '11' ", 2))
				{
					error = true;
				}
				else // Correct Length
				{
					error = false; //break loop.
				}
			}
		}

		letter = toLowercase(letter);// Convert to Lowercase

		multiples = stoi(choice);  //Covert to int.
		// Search each string for target and check mulitble count.
		for (unsigned int i = 0; i < words.size(); i++)
		{
			int count = 0;
			string buffer;
			buffer = words[i]->getWord();
			for (unsigned int i = 0; i < buffer.length(); i++)
			{
				if (buffer[i] == letter[0]) // Do any letters in the string match?
				{
					count += 1;
				}
			}

			if (count > multiples) //A match in the search criteria is found. Greater than.
			{
				success = true;
				cout << "Match = " << buffer << endl; //Display Match
				match += 1;
			}
		}
		if (!success)// No match
		{
			cout << "Combination not found" << endl;
		}
		else
		{
			cout << "'" << match << "' Records found matching letter '" << letter << "' greater than '" << multiples << "' times in a word" << endl;
		}
		system("pause");
	}

	/*
	notQU - Returns all words that don't match a user entered two letter pattern
	ie qu (Search for all words that have a q but no u to the right of q)
	Locates a supplied letter in a word and checks the next variable
	to the right to ensure it is not the target */
	void notQU()
	{
		int match = 0;
		string letterLead;
		string letterAvoid;
		bool success = false;
		bool error = true;

		// Get first letter to search for.
		while (error)
		{
			system("cls");
			cout << "----------Find letter combinations avoiding a selected letter----------" << endl;
			cout << "Enter a letter to search for " << endl;
			letterLead = getInput(); //Get user Input
			if (checkIt(letterLead, isWord, "Not a letter, Please enter a single letter to search"))
			{
				error = true;   //Not A word. No effect (error = true), but included for reference.
			}
			else// Is a word, Check the length, should be One.
			{
				if (checkIt(letterLead, isLength, "Please enter a single character, for example 'A' ", 1))
				{
					error = true;
				}
				else
				{
					error = false;
				}
			}
		}

		//cout << "What letter do you want to avoid directly after '" << letterLead << "' ?" << endl;
		//cin >> letterAvoid;

		// Get second letter to search for, check for input error.
		error = true;
		while (error)
		{
			system("cls");
			cout << "What letter do you want to avoid directly after '" << letterLead << "' ?" << endl;

			letterAvoid = getInput(); //Get user Input
			if (checkIt(letterAvoid, isWord, "Not a letter, Please enter a single letter to search"))
			{
				error = true;   //Not A word. No effect (error = true), but included for reference.
			}
			else// Is a word, Check the length, should be One.
			{
				if (checkIt(letterAvoid, isLength, "Please enter a single character, for example 'A' ", 1))
				{
					error = true;
				}
				else
				{
					error = false;
				}
			}
		}

		//Convert to lowercase.
		letterLead = toLowercase(letterLead);
		letterAvoid = toLowercase(letterAvoid);
		for (unsigned int i = 0; i < words.size(); i++)
		{
			int count = 0;
			string buffer;
			buffer = words[i]->getWord();
			for (unsigned int i = 0; i < buffer.length(); i++)
			{
				if (buffer[i] == letterLead[0] && buffer[i + 1] != letterAvoid[0])
				{
					success = true;
					match += 1;
					cout << "Match = " << buffer << endl;
				}
			}
		}
		if (!success)
		{
			cout << "Combination not found" << endl;
		}
		else
		{
			cout << "'" << match << "' Records found matching '" << letterLead << "' and avoiding '" << letterAvoid << "' directly after" << endl;
		}
		system("pause");
	}

	/*
	Display Main Title*/
	void title()
	{
		system("cls");
		cout << "\u001b[1m\u001b[32m _____ _            ____  _      _ " << endl;
		cout << "|_   _| |__   ___  |  _ \\(_) ___| |_" << endl;
		cout << "  | | | '_ \\ / _ \\ | | | | |/ __| __| " << endl;
		cout << "  | | | | | |  __/ | |_| | | (__| |  " << endl;
		cout << "  |_| |_| |_|\\___| |____/|_|\\___|_| \u001b[0m" << endl;
		cout << "\n";
		cout << "\u001b[1m\u001b[32m\u001b[7m---------Welcome to My Dictionary---------\u001b[0m \n" << "" << endl;
		cout << "\u001b[4mMain Menu\033[0m" << "\n" << endl; //https://www.experts-exchange.com/questions/22059388/how-to-write-underlined-text-in-c.html
		cout << "\u001b[34;1m1) Search Word" << endl;
		cout << "2) Search for multiple letters in words" << endl;
		cout << "3) Search for letter and avoid a selected trailing letter\n" << endl;
		cout << "\u001b[7m4) Exit\u001b[0m \n" << endl;
		cout << "\033[4mEnter a choice & press enter\033[0m" << endl;
	}

	/*
	Display Multi Letter Title*/
	void mLTitle()
	{
		system("cls");
		cout << "----------multiple Letter Search----------" << endl;
		cout << "Enter a letter to search for" << endl;
	}

	/*
	Display Word Search title*/
	void wSTitle()
	{
		system("cls");
		cout << "\033[4m----------Word Search----------\033[0m" << endl;
		cout << "Please Enter a word to search" << endl;
		cout << " Note: Hyphen '-' is allowed." << endl;
	}

	/*
	checkIt() - Verifies user input.
	options isNumber (Is it a number?), IsInRange(Within a certain range 0 to n), isWord (Is Alpha or -), isLength (check string is a certain length)
	checkIt(<string to check> <What to check for> <string to reply if error thrown> <length of desired string size>)
	Returns True or False*/
	bool checkIt(string dataField, int checkFor, string errorStr, unsigned int sSize = 1)
	{
		bool error = false;
		int count = 0;
		switch (checkFor)
		{
		case isBlank:
			if (dataField == "")
			{
				cout << errorStr << endl;
				cout << (char)7 << endl; //Alert Bell.
				error = true;
				break;
			}
			else {
				error = false;
			}
			break;

		case isNumber: //Fix this use Built In Module like is isNumerical() - This may be better?
			try
			{
				int num = stoi(dataField);
				error = false;
				break;
			}
			catch (invalid_argument)
			{
				cout << errorStr << endl; //enter a number
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}
			catch (out_of_range)
			{
				cout << errorStr << endl; //enter a number
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}

		case isInRange:
			try
			{
				int num = stoi(dataField);
				if (num > 4 || num < 1)  //Check Menu Range
				{
					cout << errorStr << endl; //enter a number
					cout << (char)7 << endl;
					system("pause");
					error = true;
					break;
				}
				else
				{
					error = false;
					break;
				}
			}
			catch (invalid_argument)
			{

				cout << errorStr << endl; //enter a number
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}
			catch (out_of_range)
			{
				cout << errorStr << endl; //enter a number
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}

		case isWord:
			count = 0;
			for (unsigned int i = 0; i < size(dataField); i++)
			{
				if (isalpha(dataField[i]))
				{
					count += 1;
				}
				else
				{
					if (dataField[i] == '-')
					{
						count += 1;
					}
				}
			}
			if (count == size(dataField))
			{
				//cout << "is a word" << endl;
				error = false;
				break;
			}
			else
			{
				cout << errorStr << endl;
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}

		case isLength:
			if (sSize < dataField.length())
			{
				cout << errorStr << endl;
				cout << (char)7 << endl;
				system("pause");
				error = true;
				break;
			}
			else
			{
				//is corect length
				error = false;
				break;
			}
		}
		return error;
	}

	/*
	Run the dictionary menu*/
	void runDictionary()
	{
		bool exit = false;
		bool error;
		string choice;
		int numberChoice;

		while (!exit)
		{
			error = true;
			while (error)  //While error is true.
			{
				title(); //Print Title Menu
				choice = getInput(); //Get user Input.
				//Check if input is a number OR within a required range.
				if (!checkIt(choice, isNumber, "Please enter a number within the required range\n") == true) // checkIt returns true if error.
				{
					if (!checkIt(choice, isInRange, "Please enter a number within the required range \n") == true)
					{
						error = false;
					}
					else
					{
						error = true; //Clarity
					}
				}
				else
				{
					error = true; //Clarity - not needed
				}
			}

			numberChoice = stoi(choice); //Conversion String to int.
			switch (numberChoice) // Switch Menu Choice.
			{
			case 1:
				searchWord();
				break;

			case 2:
				searchMultiLetter();
				break;

			case 3:
				notQU();
				break;

			case 4:
				//TODO Clean up VARS!!! (new Word)
				exit = true;
				break;
			}
		}
		words.clear(); //Clear words vector.
	}

public:

	//Constructor
	Dictionary(string filename)
	{
		cout << "Loading Dictionary" << endl;
		loadDictionary(filename);
	}

	// run - run the application.
	void run()
	{
		runDictionary();
	}
};

