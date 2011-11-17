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
	mFile = fileName;
	mXmlFile = TiXmlDocument(fileName.c_str());
	mXmlFile.LoadFile();
}

ObjectData* ObjectLoader::getData(string objectName)
{
	TiXmlElement* root = mXmlFile.FirstChildElement();

	string s = root->Value();

	TiXmlElement* dataElement = root->FirstChildElement(objectName.c_str());

	ObjectData* data = new ObjectData(dataElement);
	return data;
}