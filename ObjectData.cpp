#include "ObjectData.h"
#include <Windows.h>

ObjectData::ObjectData(TiXmlElement* element)
{
	mElement = element;

	string s = element->Value();
	s = mElement->Value();
}
	
ObjectData::~ObjectData()
{
	// Gives weird Assembler error, but it might need to be deleted :NOTE:
	//delete mElement;
}

double ObjectData::getValueDouble(string name)
{
	TiXmlDocument doc("objects.xml");
	doc.LoadFile();

	TiXmlElement* root = doc.FirstChildElement();
	string s = root->FirstChildElement()->Value();

	TiXmlElement* attribute = mElement->FirstChildElement(name.c_str()); 
	if(attribute)
		return atof(attribute->GetText());
	else
		MessageBox(0, "ObjectData::getValueDouble failed", 0, 0);
}
	
string ObjectData::getValueString(string name)
{
	TiXmlElement* attribute = mElement->FirstChildElement(name.c_str());
	if(attribute)
		return string(attribute->GetText());
	else
		MessageBox(0, "ObjectData::getValueString() failed", 0, 0);
}

string ObjectData::getType()
{
	return string(mElement->FirstAttribute()->Value());
}