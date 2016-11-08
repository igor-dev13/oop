#pragma once
#include "stdafx.h"

using namespace std;
#define Dictionary map<string, string>

void SerializeDictionary(Dictionary &dictionary, istream &dictionaryInput);
void ProcessDictionary(Dictionary &dictionary, istream &input, const string &inputFileOfDictionary);
string GetTranslation(Dictionary &dictionary, const string &searchingWord);
void SaveTranslation(Dictionary &dictionary, istream &input, string const &seachingWord, bool &setNewTranslations);
void AddNewTranslation(Dictionary &dictionary, string const &seachingWord, string const &translation);
void UpdateDictionary(Dictionary &dictionary, istream &input, const string &inputFileOfDictionary);