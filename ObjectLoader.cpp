#include "ObjectLoader.h"
#include "Object.h"
#include "ObjectData.h"

ObjectLoader::ObjectLoader()
{
	mFile = "empty.txt";
}
	
ObjectLoader::~ObjectLoader()
{

}

void ObjectLoader::setFile(string fileName)
{
	// Set XML file and create the Tiny XML document object
	mFile = fileName;
	mXmlFile = TiXmlDocument(fileName.c_str());

	// Important to load the file!
	mXmlFile.LoadFile();
}

ObjectData* ObjectLoader::getData(string objectClass, string type)
{
	// Get the data for the object with the name "objectName"
	TiXmlElement* root = mXmlFile.FirstChildElement();
	TiXmlElement* dataElement = root->FirstChildElement(objectClass.c_str());

	while(dataElement)
	{
		if(strcmp(dataElement->FirstAttribute()->Value(), type.c_str()) == 0)
			break;

		dataElement = dataElement->NextSiblingElement(objectClass.c_str());
	}

	// :NOTE: Possibly memory leak
	ObjectData* data = new ObjectData(dataElement);
	return data;
}