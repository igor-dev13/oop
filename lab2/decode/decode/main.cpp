#include "stdafx.h"
#include "decode.h"

using namespace std;

int main()
{
	string html;
	while (getline(cin, html))
	{
		html = HtmlDecode(html);
		cout << html << endl;
	}

	return 0;
}