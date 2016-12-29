#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

namespace
{
	const unsigned short MIN_PORT = 1;
	const unsigned short MAX_PORT = 65535;
	const unsigned short DEFAULT_HTTP_PORT = 80;
	const unsigned short DEFAULT_HTTPS_PORT = 443;
}

class CHttpUrl
{
public:
	CHttpUrl(std::string const & url);

	CHttpUrl(
		const std::string &domain,
		const std::string &document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocumentPath()const;
	Protocol GetProtocol()const;
	unsigned GetPort()const;

private:
	std::string m_domain;
	std::string m_document = "\\";
	Protocol m_protocol = Protocol::HTTP;
	unsigned m_port = 80;
};

namespace parsing
{
	Protocol StrToProtocol(std::string const & protocolStr);
	std::string ProtocolToStr(Protocol protocol);

	std::string ParseProtocol(std::string const & url);
	std::string ParseDomain(std::string const & url);
	unsigned ParsePort(std::string const & url);
	std::string ParseDocumentPath(std::string const & url);	
}
