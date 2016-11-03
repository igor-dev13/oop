#pragma once
#include "stdafx.h"

using namespace std;

#define Dictionary map<string, string>

void SerializeDictionary(Dictionary &dictionary, istream &dictionaryFile);
void AddNewTranslation(Dictionary &dictionary, string const &inputTranslation, string const &translation);
void UpdateDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName);
void SaveNewTranslation(Dictionary &dictionary, istream &input, string const &inputTranslation, bool &setNewWords);
void MakeDictionary(Dictionary &dictionary, istream &input, string const &dictionaryName);