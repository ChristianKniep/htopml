/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef RESPONSE_H
#define RESPONSE_H

/********************  HEADERS  *********************/
#include <string>
#include <sstream>
#include <ostream>

/*********************  STRUCT  *********************/
struct mg_connection;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class Response
{
	public:
		Response(void);
		virtual ~Response(void);
		void setMimeType(const char * mimeType);
		void setMimeType(std::string & mimeType);
		void setRawData(void * data,size_t size,bool autodelete,std::string mimeType = "{KEEP_PREVIOUS}",int status = 200);
		void setHttpStatus(int status);
		std::ostream & getStream(void);
		bool isRawData(void) const;
		bool isStringData(void) const;
		void flushInConnection(mg_connection* conn);
		void printf(const char * format,...);
		void print(const char * format);
		void error(int status,const char * format,...);
		void errorHtml(int status,const char *test,...);
		void setInfo(int status,const std::string & mimeType);
	private:
		/** Copy is not supported. **/
		Response(const Response & response);
	private:
		std::string mimeType;
		void * rawData;
		size_t rawDataSize;
		std::stringstream * stringData;
		bool freeRawData;
		int status;
};

};

#endif // RESPONSE_H
