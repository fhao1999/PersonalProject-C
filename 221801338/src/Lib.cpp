#include "Lib.h"

int testfile::getcharacters()
{
	return characters;
}

int testfile::getlines()
{
	return lines;
}

int testfile::getwords()
{
	return words;
}

void testfile::init()
{
	characters = 0;
	words = 0;
	lines = 0;
	content = (char*)malloc(sizeof(char*) * MAXN);
}

testfile testfile::countcha(char* t, testfile f1)
{
	int i = 0;
	ifstream myfile;
	myfile.open(t);
	if (!myfile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	char c;
	myfile >> noskipws;//强制读入空格和换行符
	while (!myfile.eof())
	{
		myfile >> c;
		if (myfile.eof())
			break;//防止最后一个字符输出两次
		i++;
	}
	f1.characters = i;
	myfile.close();
	return f1;
}

testfile testfile::countline(char* t, testfile f1)
{
	ifstream myfile;
	myfile.open(t, ios::in);
	int i = 0;
	string temp;//作为getline参数使用
	if (!myfile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	while (getline(myfile, temp))
	{
		if (temp.empty())
			continue;
		i++;
	}
	f1.lines = i;
	myfile.close();
	return f1;
}



