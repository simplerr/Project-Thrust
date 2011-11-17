#include "ObjectData.h"
#include <Windows.h>

ObjectData::ObjectData(TiXmlElement* element)
{
	// Set the element
	mElement = element;
}
	
ObjectData::~ObjectData()
{
	// Gives weird Assembler error, but it might need to be deleted :NOTE:
	// delete mElement;
}

double ObjectData::getValueDouble(string name)
{
	// Gets the value of the element "name" in double type
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
	// Gets the value of the element "name" in string type
	TiXmlElement* attribute = mElement->FirstChildElement(name.c_str());
	if(attribute)
		return string(attribute->GetText());
	else
		MessageBox(0, "ObjectData::getValueString() failed", 0, 0);
}

string ObjectData::getType()
{
	// Returns the type, ie : <Object type="this>....</Object>
	return string(mElement->FirstAttribute()->Value());
}