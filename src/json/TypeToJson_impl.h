/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef HTOPML_TYPE_TO_JSON_IMPL_H
#define HTOPML_TYPE_TO_JSON_IMPL_H

/********************  HEADERS  *********************/
#include "TypeToJson.h"
#include "JsonState.h"

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
template <class T> void typeToJson(JsonState & json,std::ostream& stream, const std::vector<T> & iterable)
{
	json.openArray();

	for (typename std::vector<T>::const_iterator it = iterable.begin() ; it != iterable.end() ; ++it)
		json.printValue(*it);

	json.closeArray();
}

/*******************  FUNCTION  *********************/
template <class T> void typeToJson(JsonState & json,std::ostream& stream, const std::list<T> & iterable)
{
	json.openArray();

	for (typename std::vector<T>::const_iterator it = iterable.begin() ; it != iterable.end() ; ++it)
		json.printValue(*it);

	json.closeArray();
}

/*******************  FUNCTION  *********************/
template <class T> std::ostream& typeToJson(std::ostream& out,const T & value)
{
	JsonState state(&out);
	state.printValue(value);
	return out;
}

};

#endif //TYPE_TO_JSON_H
