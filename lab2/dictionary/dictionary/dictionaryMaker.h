#pragma once
#include "stdafx.h"

using namespace std;

#define Dictionary map<string, string>

void SerializeDictionary(Dictionary &dictionary, istream &dictionaryFile);
void MakeDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName);
void AddNewTranslation(Dictionary &dictionary, string const &inputWord, string const &translation);
void UpdateDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName);
void SaveNewTranslation(Dictionary &dictionary, istream &input, string const &inputWord, bool &haveNewWords);