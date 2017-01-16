#include "stdafx.h"
#include "CHttpUrl.h"
#include <cctype>

using namespace parsing;

CHttpUrl::CHttpUrl(std::string const & url)
{
	std::string urlStr(url);

	auto protocolStr = ParseProtocol(urlStr);
	m_protocol = StrToProtocol(protocolStr);
	urlStr = urlStr.substr(protocolStr.size() + 3);

	m_domain = ParseDomain(urlStr);
	urlStr = urlStr.substr(m_domain.size());

	// если явно указан порт
	if (urlStr[0] == ':')
	{
		m_port = ParsePort(urlStr);
		urlStr = urlStr.substr(std::to_string(m_port).size() + 1);
	}
	else
	{
		m_port = (m_protocol == Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
	}

	m_document = ParseDocumentPath(urlStr);
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_protocol(protocol)
{
	m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol, unsigned short port)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_protocol(protocol)
	, m_port(port)
{
	if (port == 0 )
	{
		throw std::invalid_argument("Port must not be equal to zero");
	}
}

std::string CHttpUrl::GetURL() const
{
	auto url = ProtocolToStr(m_protocol) + "://" + m_domain;

	if (!(m_port == DEFAULT_HTTP_PORT && m_protocol == Protocol::HTTP) && 
		!(m_port == DEFAULT_HTTPS_PORT && m_protocol == Protocol::HTTPS))
	{
		url += ":" + std::to_string(m_port);
	}
	return  url + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocumentPath() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned CHttpUrl::GetPort() const
{
	return m_port;
}

std::string parsing::ParseProtocol(std::string const & url)
{
	auto end = url.find("://");

	if (end == std::string::npos)
	{
		throw CUrlParsingError("Invalid URL protocol.");
	}

	return url.substr(0, end);
}

std::string parsing::ParseDomain(std::string const & url)
{
	auto end = url.find(':');
	if (end == std::string::npos)
	{
		end = url.find("/");
	}
	auto domain = url.substr(0, end);
	return (domain == "" || (domain.find(' ') != std::string::npos)) ?	
		throw std::invalid_argument("Invalid URL domain.") : domain;
}

unsigned parsing::ParsePort(std::string const & url)
{
	auto end = url.find("/");
	auto port = url.substr(1, end);

	if (port.empty() || (port.find(' ') != std::string::npos))
	{
		throw CUrlParsingError("Invalid URL port.");
	}

	signed portNumber = 0;
	try
	{
		portNumber = std::stoi(port);
	}
	catch (...)
	{
		throw CUrlParsingError("Invalid URL port.");
	}	

	return (portNumber < MIN_PORT || portNumber > MAX_PORT) ?
		throw CUrlParsingError("Invalid URL port.") : portNumber;
}

std::string parsing::ParseDocumentPath(std::string const & url)
{
	auto document = (url[0] != '/') ? '/' + url : url;
	return ((document.find(' ') != std::string::npos)) ?
		throw std::invalid_argument("Invalid URL document path.") : document;
}

Protocol parsing::StrToProtocol(std::string const & protocolStr)
{
	std::string protocol = protocolStr;
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);

	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid protocol type");
}

std::string parsing::ProtocolToStr(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}