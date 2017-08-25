XMLConfig
=========
简介：
--------
* 该项目是通过对tinyxml2进行简单封装，是我们需要通过XML文档来存取一些键值对，如程序的系统配置等操作

更加方便，类似于安卓中使用的SharedPrefrences
* This project is mainly designed to use xml document to  save some key-value config for 

a program.
* We can use it just like SharedPrefrences in Android, just use put, get, remove, clear 

functions to operate the XML document and don't have to concern about the document 

structure.
* This project is all base on tinyxml2 .

使用方法：
--------
### 1. 插入或修改：

	XMLConfig* config = new XMLConfig("newfile.xml");
	config->putInt("myint", 56)
			->putFloat("myfloat", .14f)
			->putDouble("mydouble",569.4415)
			->putUnsigned("myunsigned", 3998572554U)
			->putString("mystring", "hello World!")
			->putBool("mybool", true)
			->commit();

### 2. 删除，清空：

	config->removeBool("mybool");
	config->clear();
	config->commit();

### 3. 读取：

	cout<<"myint:\t"<<config->getInt("myint", 0)<<endl;
	cout<<"mydouble:\t"<<config->getDouble("mydouble", 0.0)<<endl;
	cout<<"myfloat:\t"<<config->getFloat("myfloat", 0.0f)<<endl;
	cout<<"mystring:\t"<<config->getString("mystring", "")<<endl;
	cout<<"myunsigned:\t"<<config->getUnsigned("myunsigned", 0U)<<endl;
	cout<<"mybool:\t"<<config->getBool("mybool", false)<<endl;

