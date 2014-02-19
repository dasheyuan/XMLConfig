/*
 * xmlconfig.cpp
 *
 *  Created on: 2013-12-27
 *      Author: HZY
 */
#include "xmlconfig.h"

/**
 * Constructor
 * if XMl file exists, load the file
 * else create new XML structure
 */
XMLConfig::XMLConfig(const char* fileName) {
	this->doc = new XMLDocument();
	this->fileName = fileName;
	XMLError err = doc->LoadFile(fileName);
	if (err == XML_SUCCESS) {
		root = doc->RootElement();
		if (!root) {
			root = doc->NewElement(XML_CONFIG_ROOT);
			doc->InsertEndChild(root);
		}
		return;
	}
	if (err == XML_ERROR_FILE_NOT_FOUND) {
		XMLDeclaration* dec = doc->NewDeclaration(XML_CONFIG_DECLARATION);
		root = doc->NewElement(XML_CONFIG_ROOT);
		doc->InsertEndChild(dec);
		doc->InsertEndChild(root);
		return;
	}
	delete doc;
	doc = 0;
}

/**
 * delete the XMLDocument
 */
XMLConfig::~XMLConfig() {
	if (this->doc != 0)
		delete this->doc;
}

/**
 * find the first XMLElement by type and name attribute
 */
XMLElement* XMLConfig::findElement(const char* type, const char* key) {
	if (key == 0 || doc == 0 || root == 0)
		return 0;
	XMLElement *ele = root->FirstChildElement(type);
	while (ele != 0 && strcmp(key, ele->Attribute(XML_CONFIG_NAME)) != 0) {
		ele = ele->NextSiblingElement(type);
	}
	return ele;
}
/**
 * put a value in document
 */
template<class T> void XMLConfig::putValue(const char* type, const char* key,
		T value) {
	if (key == 0 || type == 0 || doc == 0 || root == 0)
		return;
	XMLElement* ele = findElement(type, key);
	if (ele != 0) {
		ele->SetAttribute(XML_CONFIG_VALUE, value);
		return;
	}
	ele = doc->NewElement(type);
	if (ele != 0) {
		ele->SetAttribute(XML_CONFIG_NAME, key);
		ele->SetAttribute(XML_CONFIG_VALUE, value);
		root->InsertEndChild(ele);
	}
}

/**
 * put a int value in document
 */
XMLConfig* XMLConfig::putInt(const char* key, int value) {
	putValue(XML_CONFIG_INT, key, value);
	return this;
}

/**
 * put a float value in document
 */
XMLConfig* XMLConfig::putFloat(const char* key, float value) {
	putValue(XML_CONFIG_FLOAT, key, value);
	return this;
}

/**
 * put a double value in document
 */
XMLConfig* XMLConfig::putDouble(const char* key, double value) {
	putValue(XML_CONFIG_DOUBLE, key, value);
	return this;
}

/**
 * put a unsigned int value in document
 */
XMLConfig* XMLConfig::putUnsigned(const char* key, unsigned int value) {
	putValue(XML_CONFIG_UNSIGNED, key, value);
	return this;
}

/**
 * put a boolean value in document
 */
XMLConfig* XMLConfig::putBool(const char* key, bool value) {
	putValue(XML_CONFIG_BOOL, key, value);
	return this;
}

/**
 * put a string value in document
 */
XMLConfig* XMLConfig::putString(const char* key, const char* value) {
	if (key == 0 || doc == 0 || root == 0)
		return this;
	XMLElement* ele = findElement(XML_CONFIG_STRING, key);
	if (ele == 0) {
		ele = doc->NewElement(XML_CONFIG_STRING);
		ele->SetAttribute(XML_CONFIG_NAME, key);
		root->InsertEndChild(ele);
	} else {
		ele->DeleteChildren();
	}
	XMLText* text = doc->NewText(value);
	ele->InsertEndChild(text);
	return this;
}

/**
 * remove a node by type and name
 */
XMLConfig* XMLConfig::removeValue(const char* type, const char* key) {
	if (key == 0 || root == 0)
		return this;
	XMLElement* ele = findElement(type, key);
	if (ele != 0)
		root->DeleteChild(ele);
	return this;
}

/**
 * remove a int node by  name
 */
XMLConfig* XMLConfig::removeInt(const char* key) {
	return removeValue(XML_CONFIG_INT, key);
}

/**
 * remove a float node by  name
 */
XMLConfig* XMLConfig::removeFloat(const char* key) {
	return removeValue(XML_CONFIG_FLOAT, key);
}

/**
 * remove a double node by  name
 */
XMLConfig* XMLConfig::removeDouble(const char* key) {
	return removeValue(XML_CONFIG_DOUBLE, key);
}

/**
 * remove a unsigned int node by  name
 */
XMLConfig* XMLConfig::removeUndigned(const char* key) {
	return removeValue(XML_CONFIG_UNSIGNED, key);
}

/**
 * remove a boolean node by  name
 */
XMLConfig* XMLConfig::removeBool(const char* key) {
	return removeValue(XML_CONFIG_BOOL, key);
}

/**
 * remove a string node by name
 */
XMLConfig* XMLConfig::removeString(const char* key) {
	return removeValue(XML_CONFIG_STRING, key);
}

/**
 * remove all nodes
 */
XMLConfig* XMLConfig::clear(void) {
	if (root != 0)
		root->DeleteChildren();
	return this;
}

/**
 * commit the change to the XML file
 */
void XMLConfig::commit(bool compact) {
	if (doc != 0 && fileName != 0)
		doc->SaveFile(fileName, compact);
}

/**
 * get value by key, if failed, return the default
 */
int XMLConfig::getInt(const char* key, int defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_INT, key);
	if (ele != 0)
		ele->QueryIntAttribute(XML_CONFIG_VALUE, &defaultValue);
	return defaultValue;
}

/**
 * get value by key, if failed, return the default
 */
unsigned int XMLConfig::getUnsigned(const char* key,
		unsigned int defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_UNSIGNED, key);
	if (ele != 0)
		ele->QueryUnsignedAttribute(XML_CONFIG_VALUE, &defaultValue);
	return defaultValue;
}

/**
 * get value by key, if failed, return the default
 */
bool XMLConfig::getBool(const char* key, bool defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_BOOL, key);
	if (ele != 0)
		ele->QueryBoolAttribute(XML_CONFIG_VALUE, &defaultValue);
	return defaultValue;
}

/**
 * get value by key, if failed, return the default
 */
float XMLConfig::getFloat(const char* key, float defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_FLOAT, key);
	if (ele != 0)
		ele->QueryFloatAttribute(XML_CONFIG_VALUE, &defaultValue);
	return defaultValue;
}

/**
 * get value by key, if failed, return the default
 */
double XMLConfig::getDouble(const char* key, double defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_DOUBLE, key);
	if (ele != 0)
		ele->QueryDoubleAttribute(XML_CONFIG_VALUE, &defaultValue);
	return defaultValue;
}

/**
 * get value by key, if failed, return the default
 */
const char* XMLConfig::getString(const char* key, const char* defaultValue) {
	XMLElement* ele = findElement(XML_CONFIG_STRING, key);
	if (ele != 0 && ele->GetText() != 0)
		return ele->GetText();
	return defaultValue;
}

bool XMLConfig::isExistInt(const char* key) {
	return (findElement(XML_CONFIG_INT, key) != 0);
}

bool XMLConfig::isExistFloat(const char* key) {
	return (findElement(XML_CONFIG_FLOAT, key) != 0);
}

bool XMLConfig::isExistDouble(const char* key) {
	return (findElement(XML_CONFIG_DOUBLE, key) != 0);
}

bool XMLConfig::isExistUnsigned(const char* key) {
	return (findElement(XML_CONFIG_UNSIGNED, key) != 0);
}

bool XMLConfig::isExistBool(const char* key) {
	return (findElement(XML_CONFIG_BOOL, key) != 0);
}

bool XMLConfig::isExistString(const char* key) {
	return (findElement(XML_CONFIG_STRING, key) != 0);
}

