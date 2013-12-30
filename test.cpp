/*
 * test.cpp
 *
 *  Created on: 2013-12-27
 *      Author: HZY
 */
#include "xmlconfig.h"
#include <iostream>
using namespace std;

int main() {
	XMLConfig* config = new XMLConfig("newfile.xml");
	config->putInt("myint", 56)
			->putFloat("myfloat", .14f)
			->putDouble("mydouble",569.4415)
			->putUnsigned("myunsigned", 3998572554U)
			->putString("mystring", "this is hello World!我是中文，XMl编码与源文件编码有关")
			->putBool("mybool", true)
			->commit();

	cout<<"myint:\t"<<config->getInt("myint", 0)<<endl;
	cout<<"mydouble:\t"<<config->getDouble("mydouble", 0.0)<<endl;
	cout<<"myfloat:\t"<<config->getFloat("myfloat", 0.0f)<<endl;
	cout<<"mystring:\t"<<config->getString("mystring", "")<<endl;
	cout<<"myunsigned:\t"<<config->getUnsigned("myunsigned", 0U)<<endl;
	cout<<"mybool:\t"<<config->getBool("mybool", false)<<endl;

//	config->removeBool("mybool");
//	config->commit();
	delete config;
	return 0;
}
