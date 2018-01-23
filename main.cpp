#include <iostream>
#include <fcgio.h>

std::string get_uri(FCGX_Request const & request)
{
	int content_length = std::stoi(FCGX_GetParam("CONTENT_LENGTH", request.envp));
	std::string s(FCGX_GetParam("REQUEST_URI", request.envp));
//	std::ostream os;
	std::cout << "CONTENT_LENGTH = " << FCGX_GetParam("CONTENT_LENGTH", request.envp) << "\n"
	   << "CONTENT_TYPE   = " << FCGX_GetParam("CONTENT_TYPE", request.envp)   << "\n"
	   << "REQUEST_URI    = " << FCGX_GetParam("REQUEST_URI", request.envp)    << "\n"
	   << "REQUEST_METHOD = " << FCGX_GetParam("REQUEST_METHOD", request.envp) << "\n"
	   << "SCRIPT_NAME    = " << FCGX_GetParam("SCRIPT_NAME", request.envp)    << "\n"
	   << "SCRIPT_FILENAME= " << FCGX_GetParam("SCRIPT_FILENAME", request.envp)<< "\n"
	   << "PATH_INFO      = " << FCGX_GetParam("PATH_INFO", request.envp)      << "\n";
	// char buf[content_length];
	// std::cin.read(buf, content_length);
	// std::cin.ignore(1024);
	return s;
}

int main(int argc, char *argv[])
{
    std::streambuf * cin_streambuf  = std::cin.rdbuf();
    std::streambuf * cout_streambuf = std::cout.rdbuf();
    std::streambuf * cerr_streambuf = std::cerr.rdbuf();

    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0)
    {
        fcgi_streambuf cin_fcgi_streambuf (request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        std::cin.rdbuf (&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        std::cout << "Content-type: text/html\r\n"
                  << "\r\n"
                  << "<html>\n"
                  << "  <head>\n"
                  << "    <title>Hello, World!</title>\n"
                  << "  </head>\n"
                  << "  <body>\n"
                  << "<pre>" << get_uri(request)
                  << "</pre>\n"
                  << "  </body>\n"
                  << "</html>\n";
    }
    std::cin.rdbuf (cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

    return 0;
}
