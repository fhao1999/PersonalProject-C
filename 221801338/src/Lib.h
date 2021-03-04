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

static map<string, int> mapword1;

void loadword(char w[]);

struct sWord
{
	string w;
	int count;

};//定义一个用于存放单词及频次的结构体 

void merge(sWord* , sWord* , int , int , int );
void sort(sWord* , sWord* , int , int);
#endif //LIB_H
