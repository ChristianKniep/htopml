/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <cstdio>
#include <cstring>
#include "ValidationWebNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
ValidationWebNode::ValidationWebNode(const std::string& path, bool strictPath)
	: WebNode(path, strictPath)
{

}

/*******************  FUNCTION  *********************/
WebNodeData ValidationWebNode::getContent(const Request & request)
{
	char buffer[2048];
	sprintf(buffer,"Ok, get the page at URI : %s\n",request.getUri().c_str());
	return WebNodeData(strdup(buffer),strlen(buffer),"text/plain",true);
}

}
