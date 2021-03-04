#pragma once
#ifndef LIB_H
#define LIB_H

#include <iostream>
#include<string>
#include<fstream>
#include<cassert>
#include<map> 
#include<cstdlib>
#include<time.h> 
#define MAXN 10000000
using namespace std;
class testfile
{
public:
	testfile countcha(char*, testfile);//计算字符数
	testfile countword(char*, testfile);//计算单词数
	testfile countline(char*, testfile);//计算行数
	int getcharacters();
	int getlines();
	int getwords();
	char* content;//存放文本文件数据 
	void init();
private:
	int characters;
	int words;
	int lines;

};


#endif //LIB_H
