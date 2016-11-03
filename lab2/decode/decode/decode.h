#pragma once
#include <iostream>
#include <fstream>

#include <string>
#include <map> 
#include <iterator> 
#include "stdafx.h"

using namespace std;

string ChangeEntity(string const &text, string const &searchStr, string const &replaceStr);
string HtmlDecode(string &html);