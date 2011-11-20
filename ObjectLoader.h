#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include "tinymxl\tinystr.h";
#include "tinymxl\tinyxml.h"
using namespace std;

class Object;
class ObjectData;

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	ObjectData* getData(string objectClass, string type);
	void setFile(string fileName);
private:
	TiXmlDocument mXmlFile;
	string mFile;
};

#endif