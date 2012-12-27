/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_HTTP_REQUEST_H
#define HTOPML_HTTP_REQUEST_H

/********************  HEADERS  *********************/
#include <string>

/*********************  STRUCT  *********************/
struct mg_request_info;
struct mg_connection;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class HttpRequest
{
	public:
		HttpRequest(const mg_request_info * mongooseRequest,std::string auth = "");
		std::string getUri(void) const;
		std::string getAuth(void) const;
	private:
		const mg_request_info * mongooseRequest;
		std::string auth;
};

}

#endif // REQUEST_H