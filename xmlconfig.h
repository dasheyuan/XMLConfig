/*
 * xmlconfig.h
 *
 *  Created on: 2013-12-27
 *      Author: HZY
 */

#ifndef XMLCONFIG_H_
#define XMLCONFIG_H_

#include "tinyxml2.h"

using namespace tinyxml2;

#define XML_CONFIG_DECLARATION			"xml version='1.0' encoding='utf-8' standalone='yes'"
#define XML_CONFIG_DEFAULT_FILE_NAME	"./config.xml"
#define XML_CONFIG_ROOT				"map"
#define XML_CONFIG_NAME				"name"
#define XML_CONFIG_VALUE				"value"
#define XML_CONFIG_INT					"int"
#define XML_CONFIG_BOOL				"bool"
#define XML_CONFIG_FLOAT				"float"
#define XML_CONFIG_DOUBLE				"double"
#define XML_CONFIG_UNSIGNED			"unsigned"
#define XML_CONFIG_XML_CONFIGING				"string"

class XMLConfig{
public:
	XMLConfig(const char* fileName = XML_CONFIG_DEFAULT_FILE_NAME);
	~XMLConfig();
	XMLConfig* putInt(const char* key, int value);
	XMLConfig* putFloat(const char* key, float value);
	XMLConfig* putDouble(const char* key, double value);
	XMLConfig* putUnsigned(const char* key, unsigned int value);
	XMLConfig* putBool(const char* key, bool value);
	XMLConfig* putString(const char* key, const char* value);

	XMLConfig* removeValue(const char* type, const char* key);
	XMLConfig* removeInt(const char* key);
	XMLConfig* removeFloat(const char* key);
	XMLConfig* removeDouble(const char* key);
	XMLConfig* removeUndigned(const char* key);
	XMLConfig* removeBool(const char* key);
	XMLConfig* removeString(const char* key);

	XMLConfig* clear(void);
	void commit(bool compact = false);

	int getInt(const char* key, int defaultValue);
	unsigned int getUnsigned(const char* key, unsigned int defaultValue);
	bool getBool(const char* key, bool defaultValue);
	float getFloat(const char* key, float defaultValue);
	double getDouble(const char* key, double defaultValue);
	const char* getString(const char* key, const char* defaultValue);
private:
	XMLDocument* doc;
	XMLElement* root;
	const char* fileName;
	XMLElement* findElement(const char* type, const char* key);
	template<class T> void putValue(const char* type, const char* key, T value);
};


#endif /* XMLCONFIG_H_ */
