#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

int main(int argc, char *argv[])
{
	std::string input;
	while (std::getline(std::cin, input))
	{
		try
		{
			CHttpUrl url(input);

			std::cout << "URL: " << url.GetURL() << std::endl;
			std::cout << "Protocol: ";
			
			if (url.GetProtocol() == Protocol::HTTP)
			{
				std::cout << "HTTP";
			}
			else
			{
				std::cout << "HTTPS";
			}

			std::cout << std::endl
				<< "Domain: " << url.GetDomain() << std::endl
				<< "Port: " << url.GetPort() << std::endl
				<< "Document path: " << url.GetDocumentPath() << std::endl << std::endl;
		}
		catch (std::invalid_argument const & error)
		{
			std::cout << error.what() << std::endl;
		}
	}
	return 0;
}

