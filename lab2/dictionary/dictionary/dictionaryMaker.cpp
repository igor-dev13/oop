#include "stdafx.h"
#include "dictionaryMaker.h"

void SerializeDictionary(Dictionary &dictionary, istream &dictionaryFile)
{
	string word, translation;

	while (getline(dictionaryFile, word))
	{
		getline(dictionaryFile, translation);
		dictionary.insert(make_pair(word, translation));
	}
}

void SaveNewTranslation(Dictionary &dictionary, istream &input, string const &inputTranslation, bool &setNewWords)
{
	string translation;
	cout << "Неизвестное слово '" << inputTranslation << "' Введите перевод или пустую строку для отказа.\n>";	
	getline(input, translation);

	if (translation != "")
	{
		AddNewTranslation(dictionary, inputTranslation, translation);
		setNewWords = true;
	}
	else
	{
		cout << "Слово '" << inputTranslation << "' проигнорировано\n";
	}
}

void AddNewTranslation(Dictionary &dictionary, string const &inputTranslation, string const &translation)
{
	dictionary.insert(make_pair(inputTranslation, translation));
}

void UpdateDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName)
{
	string saveParametr;
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом.\n>";	
	input >> saveParametr;

	if (saveParametr == "Y" || saveParametr == "y")
	{
		ofstream dictionaryFileOut(dictionaryName);

		for (auto i = dictionary.begin(); i != dictionary.end(); ++i)
		{
			dictionaryFileOut << i->first << "\n" << i->second << "\n";
		}

		dictionaryFileOut.close();
		cout << "Изменения сохранены. До свидания.";
	}
}

void MakeDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName)
{
	const string PROGRAM_EXIT = "...";
	bool setNewWords = false;
	string inputTranslation;
	cout << ">";

	while (getline(input, inputTranslation) && (inputTranslation != PROGRAM_EXIT))
	{
		if (!inputTranslation.empty())
		{
			bool haveTranslation = (dictionary.find(inputTranslation) != dictionary.end());
			if (haveTranslation)
			{
				cout << dictionary.find(inputTranslation)->second << "\n";
			}
			else
			{
				SaveNewTranslation(dictionary, input, inputTranslation, setNewWords);
			}
		}

		cout << ">";
	}

	if (setNewWords)
	{
		UpdateDictionary(dictionary, input, dictionaryName);
	}
}