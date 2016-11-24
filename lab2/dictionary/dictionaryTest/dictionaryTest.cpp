#include "stdafx.h"
#include "../dictionary/dictionaryProcessor.h"
#include <sstream>
#include <boost/test/output_test_stream.hpp>

using namespace std;
BOOST_AUTO_TEST_SUITE(serialize_dictionary_function)

	BOOST_AUTO_TEST_CASE(should_serialize_dictionary_from_existing_file)
	{
		ifstream dictionaryFile("testTextFile.txt");
		map<string, string> dictionary;
		map<string, string> tempDictionary = { { "man", "человек" },{ "girl", "девушка" },{ "phone", "телефон" } };
		SerializeDictionary(dictionary, dictionaryFile);
		BOOST_CHECK((dictionary == tempDictionary));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(get_translation_function)

	BOOST_AUTO_TEST_CASE(should_get_word_translation)
	{
		map<string, string> tempDictionary = { { "man", "человек" },{ "girl", "девушка" },{ "phone", "телефон" } };
		string translation = GetTranslation(tempDictionary, "man");
		BOOST_CHECK((translation == "человек"));		
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(add_new_translation_function)

	BOOST_AUTO_TEST_CASE(should_add_new_translation_for_dictionary)
	{
		map<string, string> tempDictionary = { { "man", "человек" },{ "girl", "девушка" },{ "phone", "телефон" } };
		map<string, string> tempDictionaryAdditional = { { "man", "человек" },{ "girl", "девушка" },{ "phone", "телефон" },{"car", "машина"} };
		AddNewTranslation(tempDictionary, "car", "машина");
		BOOST_CHECK((tempDictionary == tempDictionaryAdditional));
	}

BOOST_AUTO_TEST_SUITE_END()