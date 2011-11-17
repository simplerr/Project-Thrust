#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <string>
#include "tinymxl\tinyxml.h"

using namespace std;

class ObjectData
{
public:
	ObjectData(TiXmlElement* element);
	~ObjectData();

	string	getType();
	double	getValueDouble(string name);
	string	getValueString(string name);
private:
	TiXmlElement* mElement;
};

#endif