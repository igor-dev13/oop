#include "stdafx.h"
#include "../CHttpUrl.h"
#include "../CUrlParsingError.h"

BOOST_AUTO_TEST_SUITE(CHttpUrl_)
	BOOST_AUTO_TEST_CASE(can_parse_protocol)
	{
		{
			CHttpUrl urlHttp("http://www.yandex.ru/");
			BOOST_CHECK_EQUAL(parsing::ProtocolToStr(urlHttp.GetProtocol()), "http");

			CHttpUrl urlHttps("https://www.ya.com/");
			BOOST_CHECK_EQUAL(parsing::ProtocolToStr(urlHttps.GetProtocol()), "https");
		}
		{
			CHttpUrl urlHttp("http://www.yandex.com/");
			BOOST_CHECK(urlHttp.GetProtocol() == Protocol::HTTP);

			CHttpUrl urlHttps("https://www.yandex.com/");
			BOOST_CHECK(urlHttps.GetProtocol() == Protocol::HTTPS);
		}
	}

	BOOST_AUTO_TEST_CASE(protocol_can_be_in_different_registers)
	{
		{
			CHttpUrl urlHttp("hTTp://www.yandex.com/");
			BOOST_CHECK(urlHttp.GetProtocol() == Protocol::HTTP);
		}
		{
			CHttpUrl urlHttp("HTTP://www.yandex.com/");
			BOOST_CHECK(urlHttp.GetProtocol() == Protocol::HTTP);
		}
		{
			CHttpUrl urlHttp("https://www.yandex.com/");
			BOOST_CHECK(urlHttp.GetProtocol() == Protocol::HTTPS);
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_wrong_protocol)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("a."), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("ht://www.yandex.com/"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("qq/ya.ru/"), CUrlParsingError);		
	}

	BOOST_AUTO_TEST_CASE(can_parse_domain_address)
	{
		{
			CHttpUrl url("http://www.yandex.ru/");
			BOOST_CHECK_EQUAL(url.GetDomain(), "www.yandex.ru");
		}
		{
			CHttpUrl url("https://yandex.ru/index.php");
			BOOST_CHECK_EQUAL(url.GetDomain(), "yandex.ru");
		}
		{
			CHttpUrl url("https://localhost");
			BOOST_CHECK_EQUAL(url.GetDomain(), "localhost");
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_wrong_url_address)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://www.ya ndex.com/"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl url(""), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_parse_port_number)
	{
		{
			CHttpUrl url("http://yandex.ru");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
		}
		{
			CHttpUrl url("http://yandex.ru:79");
			BOOST_CHECK_EQUAL(url.GetPort(), 79);
		}
		{
			CHttpUrl url("http://yandex.ru:430");
			BOOST_CHECK_EQUAL(url.GetPort(), 430);
		}
		{
			CHttpUrl url("http://yandex.ru:1");
			BOOST_CHECK_EQUAL(url.GetPort(), 1);
		}
		{
			CHttpUrl url("http://yandex.ru:65535");
			BOOST_CHECK_EQUAL(url.GetPort(), 65535);
		}
		{
			CHttpUrl url("http://yandex.ru:1140");
			BOOST_CHECK_EQUAL(url.GetPort(), 1140);
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_wrong_port_number)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:  "), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:-1/"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:0"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:65536"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://localhost:73124"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_parse_document_path)
	{
		{
			CHttpUrl url("http://www.yandex.ru/index.php");
			BOOST_CHECK_EQUAL(url.GetDocumentPath(), "/index.php");
		}
		{
			CHttpUrl url("https://yandex.ru/img/bg.png");
			BOOST_CHECK_EQUAL(url.GetDocumentPath(), "/img/bg.png");
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_wrong_document_path)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://www.yandex.ru/i mage"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://www.yandex.ru/doc /7"), std::invalid_argument);
	}
	
	BOOST_AUTO_TEST_CASE(can_return_url_by_string)
	{
		{
			CHttpUrl url("http://www.yandex.ru/index.php");
			BOOST_CHECK_EQUAL(url.GetURL(), "http://www.yandex.ru/index.php");
		}
		{
			CHttpUrl url("https://yandex.ru:62/src/images/image.png");
			BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru:62/src/images/image.png");
		}
		{
			CHttpUrl url("https://www.yandex.ru/index.php");
			BOOST_CHECK_EQUAL(url.GetURL(), "https://www.yandex.ru/index.php");
		}
	}
	
	BOOST_AUTO_TEST_CASE(can_create_objects_without_errors_by_constructor)
	{
		{
			CHttpUrl url("yandex.ru", "src/img/image.png", Protocol::HTTPS, 443);
			BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru/src/img/image.png");
		}
		{
			CHttpUrl url("yandex.ru", "src/img/image.png", Protocol::HTTP, 443);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru:443/src/img/image.png");
		}
		{
			CHttpUrl url("yandex.ru", "src/img/image.png", Protocol::HTTP, 80);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru/src/img/image.png");
		}
		{
			CHttpUrl url("yandex.ru", "src/img/image.png", Protocol::HTTPS, 80);
			//BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru:80/src/img/image.png"); ////////////////////////////////////
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_objects_with_errors)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("www.yandex. m", "docs/word.doc", Protocol::HTTP, 15), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl url("www.yandex.ru", "docs/wo rd.doc", Protocol::HTTPS, 42), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl url("www.yandex.ru", "docs/word.doc", Protocol::HTTPS, 0), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(port_can_be_initialized_by_default_values)
	{
		{
			CHttpUrl url("yandex.ru", "doc/00/word.doc", Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru/doc/00/word.doc");
			BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
		}

		{
			CHttpUrl url("yandex.ru", "", Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru/");
			BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
		}
	}

	BOOST_AUTO_TEST_CASE(port_can_be_initialized_by_default_value_for_default_protocol)
	{
		{
			CHttpUrl url("yandex.ru", "doc/00/word.doc", Protocol::HTTPS);
			BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru/doc/00/word.doc");
			BOOST_CHECK_EQUAL(url.GetPort(), 443);
		}
		{
			CHttpUrl url("yandex.ru", "doc/00/word.doc", Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru/doc/00/word.doc");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_invalid_url_port)
	{
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.yandex.ru:88 08/image"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url2("http://www.yandex.ru:8 000/doc/7"), std::invalid_argument);

			BOOST_REQUIRE_THROW(CHttpUrl url3("http://www.yandex.ru:номер_порта/doc/7"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url4("http://www.yandex.ru:восемьдесяттри/doc/7"), std::invalid_argument);
		}
		{
			CHttpUrl url("http://www.yandex.ru:8808/image");
			BOOST_CHECK_EQUAL(url.GetPort(), 8808);
		}
	}

BOOST_AUTO_TEST_SUITE_END()