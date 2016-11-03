#include "stdafx.h"
#include "decode.h"

using namespace std;

string ChangeEntity(string const &text,  string const &searchStr,  string const &replaceStr)
{
	string resultStr;
	size_t startPosition = 0;
	size_t matchEndPosition = text.find(searchStr);

	while (matchEndPosition != string::npos)
	{
		resultStr += text.substr(startPosition, matchEndPosition - startPosition) + replaceStr;
		startPosition = matchEndPosition + searchStr.length();
		matchEndPosition = text.find(searchStr, startPosition);
	}

	return resultStr += text.substr(startPosition);
}

string HtmlDecode(string &html)
{
	map <string, string> decode;
	decode["&quot;"] = "\"";
	decode["&apos;"] = "'";
	decode["&lt;"] = "<";
	decode["&gt;"] = ">";
	decode["&amp;"] = "&";

	for (auto i = decode.begin(); i != decode.end(); ++i)
	{
		html = ChangeEntity(html, i->first, i->second);
	}

	return html;
}
