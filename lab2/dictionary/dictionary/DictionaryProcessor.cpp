#include "stdafx.h"
#include "dictionaryProcessor.h"

void SerializeDictionary(Dictionary &dictionary, istream &dictionaryInput)
{
	string word, translation;

	while (getline(dictionaryInput, word))
	{
		getline(dictionaryInput, translation);
		dictionary.insert(make_pair(word, translation));
	}
}

void ProcessDictionary(Dictionary &dictionary, istream &input, const string &inputFileOfDictionary)
{
	const string exitCommand = "...";
	bool setNewTranslation = false;
	string searchingWord, translation;
	cout << ">";

	while (getline(input, searchingWord) && (searchingWord != exitCommand))
	{
		if (!searchingWord.empty())
		{
			translation = GetTranslation(dictionary, searchingWord);

			if (translation != "")
			{
				cout << translation << "\n";
			}
			else
			{
				SaveTranslation(dictionary, input, searchingWord, setNewTranslation);
			}
		}

		cout << ">";
	}

	if (setNewTranslation)
	{
		UpdateDictionary(dictionary, input, inputFileOfDictionary);
	}
}

string GetTranslation(Dictionary &dictionary, const string &searchingWord)
{
	map<string, string>::iterator iterator;
	iterator = dictionary.find(searchingWord);

	if (iterator != dictionary.end())
	{
		return dictionary.find(searchingWord)->second;
	}
	else 
	{
		return "";
	}
}

void SaveTranslation(Dictionary &dictionary, istream &input, string const &seachingWord, bool &setNewTranslations)
{
	string translation;
	cout << "Неизвестное слово '" << seachingWord << "' Введите перевод или пустую строку для отказа.\n>";
	getline(input, translation);

	if (translation != "")
	{
		AddNewTranslation(dictionary, seachingWord, translation);
		setNewTranslations = true;
	}
	else
	{
		cout << "Слово '" << seachingWord << "' проигнорировано\n";
	}

}

void AddNewTranslation(Dictionary &dictionary, string const &seachingWord, string const &translation)
{
	dictionary.insert(make_pair(seachingWord, translation));
}

void UpdateDictionary(Dictionary &dictionary, istream &input, const string &inputFileOfDictionary)
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом.\n>";
	ofstream dictionaryFileOutput(inputFileOfDictionary);
	string saveFile;
	input >> saveFile;

	if (saveFile == "Y" || saveFile == "y")
	{
		for (auto i = dictionary.begin(); i != dictionary.end(); ++i)
		{
			dictionaryFileOutput << i->first << "\n" << i->second << "\n";
		}

		dictionaryFileOutput.close();
		cout << "Изменения сохранены. До свидания.";
	}
}