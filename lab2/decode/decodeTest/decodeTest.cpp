#include "stdafx.h"
#include "../decode/decode.h"

using namespace std;

bool StringsAreEqual(string const& x, string const& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(ChangeEntity_function)
	
	BOOST_AUTO_TEST_CASE(emptyString)
	{		
		string input = "";
		const string searchStr = "hello";
		const string replaceStr = "world!";
		auto result = ChangeEntity(input, searchStr, replaceStr);
		BOOST_CHECK(StringsAreEqual(result, ""));
	}

	BOOST_AUTO_TEST_CASE(replace_string_bigger_than_searching)
	{
		const string expected = "Hellnew year is coming soon wnew year is coming soonrld!";
		string input = "Hello world!";
		const string searchStr = "o";
		const string replaceStr = "new year is coming soon";
		auto result = ChangeEntity(input, searchStr, replaceStr);

		BOOST_CHECK(StringsAreEqual(result, expected));
	}

	BOOST_AUTO_TEST_CASE(replace_string_smaller_than_searching)
	{
		const string expected = "He world!";
		string input = "Hello world!";
		const string searchStr = "ello";
		const string replaceStr = "e";
		auto result = ChangeEntity(input, searchStr, replaceStr);

		BOOST_CHECK(StringsAreEqual(result, expected));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)
	
	BOOST_AUTO_TEST_CASE(string_no_coding)
	{
		string noCoding = "computer";
		noCoding = HtmlDecode(noCoding);
		BOOST_CHECK(StringsAreEqual(noCoding, "computer"));
	}

	BOOST_AUTO_TEST_CASE(string_repeated_symbol)
	{
		string repeatedHtmlSymbol = "hello &quot;&quot; world man";
		repeatedHtmlSymbol = HtmlDecode(repeatedHtmlSymbol);
		BOOST_CHECK(StringsAreEqual(repeatedHtmlSymbol, "hello \"\" world man"));
	}
	
	BOOST_AUTO_TEST_CASE(string_with_all_html_symbols)
	{
		string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		html = HtmlDecode(html);
		BOOST_CHECK(StringsAreEqual(html, "Cat <says> \"Meow\". M&M's"));
	}

BOOST_AUTO_TEST_SUITE_END()
