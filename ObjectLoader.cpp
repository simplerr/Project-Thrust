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

ObjectData* ObjectLoader::getData(string name)
{
	// Get the data for the object with the name "objectName"
	TiXmlElement* root = mXmlFile.FirstChildElement();
	TiXmlElement* dataElement = root->FirstChildElement(name.c_str());

	// :NOTE: Possibly memory leak
	ObjectData* data = new ObjectData(dataElement);
	return data;
}