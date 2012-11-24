/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_TEMPLATE_PAGE_HTTP_NODE_H
#define HTOPML_TEMPLATE_PAGE_HTTP_NODE_H

/********************  HEADERS  *********************/
#include "../server/HttpNode.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*********************  CLASS  **********************/
class TemplatePageHttpNode : public HttpNode
{
	public:
		TemplatePageHttpNode(const std::string& mount,const std::string & contentFile,bool cache = false,const std::string & templateFile="../src/www/theme/layout.htm");
		virtual void onHttpRequest(HttpResponse & response,const HttpRequest & request);
	protected:
		void load(std::ostream & stream);
	private:
		std::string templateFile;
		std::string contentFile;
		std::string cacheContent;
		bool cache;
};

};

#endif // HTOPML_TEMPLATE_PAGE_HTTP_NODE_H
