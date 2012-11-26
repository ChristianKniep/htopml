/*****************************************************
             PROJECT  : htopml
             VERSION  : 0.1.0-dev
             DATE     : 11/2012
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <hwloc.h>
// #include <hwloc/linux.h>
#include <dirent.h>
#include "HwlocThreadBindingHttpNode.h"

/**********************  USING  *********************/
using namespace std;

/********************  NAMESPACE  *******************/
namespace htopml
{

/*******************  FUNCTION  *********************/
HwlocThreadBindingHttpNode::HwlocThreadBindingHttpNode(const string& path)
	:JsonHttpNode<HwlocBinding>(path,&data)
{
	hwlocWasInit = false;
}

/*******************  FUNCTION  *********************/
HwlocThreadBindingHttpNode::~HwlocThreadBindingHttpNode(void )
{
	if (hwlocWasInit)
	{
		hwloc_topology_destroy(topology);
		hwloc_bitmap_free(cpuset);
	}
}

/*******************  FUNCTION  *********************/
void HwlocThreadBindingHttpNode::onRequest(const HttpRequest& request)
{
	if (!hwlocWasInit)
		initHwloc();
    syncListOfThreads();
	syncHwlocInfos();
}

/*******************  FUNCTION  *********************/
void HwlocThreadBindingHttpNode::initHwloc(void )
{
	data.processId = getpid();
	int res = hwloc_topology_init(&topology);
	assert(res == 0);
	res = hwloc_topology_load(topology);
	assert(res == 0);
	assert(hwloc_topology_get_support(topology)->cpubind->get_proc_cpubind);
	topocpuset = hwloc_topology_get_topology_cpuset(topology);
	assert(topocpuset != NULL);
	cpuset = hwloc_bitmap_alloc();
}

/*******************  FUNCTION  *********************/
void HwlocThreadBindingHttpNode::syncHwlocInfos(void )
{
	//vars
	int res;

	//read info for process
	res = hwloc_get_proc_cpubind(topology,data.processId,cpuset,0);
	hwloc_bitmap_and(cpuset, cpuset, topocpuset);
	data.binding = getBindingFromCpuset(cpuset,false,true);

	//read info for tid
	for (HwlocThreadBindingVector::iterator it = data.threads.begin() ; it != data.threads.end() ; ++it)
	{
		res = hwloc_get_proc_cpubind(topology, it->threadId, cpuset,0);
		hwloc_bitmap_and(cpuset, cpuset, topocpuset);
		it->binding = getBindingFromCpuset(cpuset,false,true);
	}
}

/*******************  FUNCTION  *********************/
//The code of this function is inspired from hwloc-ps
void HwlocThreadBindingHttpNode::syncListOfThreads(void )
{
	//vars
	DIR * dir;
	dirent * dirent;
	int cnt = 0;

	//open proc dir
	dir = opendir("/proc/self/task");
	assert(dir != NULL);//TODO : transform to assume

	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] != '.' && dirent->d_name[1] != '\0')
		{
			if (cnt >= data.threads.size())
				data.threads.resize(cnt+1);
			data.threads[cnt].threadId = atoi(dirent->d_name);
			assert(data.threads[cnt].threadId > 0);
			cnt++;
		}
	}

	//check size
	if (cnt < data.threads.size())
		data.threads.resize(cnt);

	//finish
	closedir(dir);
}

/*******************  FUNCTION  *********************/
//this is a copy past from hwloc-ps
std::string HwlocThreadBindingHttpNode::getBindingFromCpuset(hwloc_bitmap_t cpuset,bool show_cpuset,bool logical)
{
	//vars
	std::string res;
	char buffer[1024];

	if (show_cpuset) {
		char *cpuset_str = NULL;
		hwloc_bitmap_asprintf(&cpuset_str, cpuset);
		res = cpuset_str;
		free(cpuset_str);
	} else {
		hwloc_bitmap_t remaining = hwloc_bitmap_dup(cpuset);
		int first = 1;
		while (!hwloc_bitmap_iszero(remaining))
		{
			char type[64];
			unsigned idx;
			hwloc_obj_t obj = hwloc_get_first_largest_obj_inside_cpuset(topology, remaining);
			hwloc_obj_type_snprintf(type, sizeof(type), obj, 1);
			idx = logical ? obj->logical_index : obj->os_index;
			if (idx == (unsigned) -1)
				sprintf(buffer,"%s\"%s\"", first ? "" : ", ", type);
			else
				sprintf(buffer,"%s\"%s:%u\"", first ? "" : ", ", type, idx);
			hwloc_bitmap_andnot(remaining, remaining, obj->cpuset);
			first = 0;
			res+=buffer;
		}
		res = string("[") + res + "]";
		hwloc_bitmap_free(remaining);
	}

	return res;
}

/*******************  FUNCTION  *********************/
void typeToJson(JsonState& state, ostream& stream, const HwlocThreadBinding& value)
{
	state.openStruct();
	state.printField("threadId",value.threadId);
	state.printFormattedField("binding","%s",value.binding.c_str());
	state.closeStruct();
}

/*******************  FUNCTION  *********************/
void typeToJson(JsonState& state, ostream& stream, const HwlocBinding& value)
{
	state.openStruct();
	state.printField("processId",value.processId);
	state.printFormattedField("binding","%s",value.binding.c_str());
	state.printField("threads",value.threads);
	state.closeStruct();
}

};
