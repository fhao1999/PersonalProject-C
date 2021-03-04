/**
作者：221801338_冯浩
最后修改时间：2021/03/04
**/
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




testfile testfile::countword(char* t, testfile f1)
{
	int n = 0;
	ifstream myfile;
	myfile.open(t);
	if (!myfile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	char c;
	myfile >> noskipws;
	while (!myfile.eof())
	{
		myfile >> c;
		if (myfile.eof())
			break;//防止最后一个字符输出两次
		if (c >= 65 && c <= 90)
			c += 32;//大写字母转小写 
		f1.content[n++] = c;//把文本文件内的数据存入类的content字符数组中	
	}
	myfile.close();
	char temp[4];
	int i = 0, j = 0, flag = 0, words = 0, m = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (!((f1.content[i] >= 48 && f1.content[i] <= 57) || (f1.content[i] >= 97 && f1.content[i] <= 122)))//跳过非字母和非数字字符 
			continue;
		else
		{
			for (j = 0; j < 4 && i < n; j++)
			{
				if (!((f1.content[i] >= 48 && f1.content[i] <= 57) || (f1.content[i] >= 97 && f1.content[i] <= 122)))
					break;
				temp[j] = f1.content[i++];//temp中存入四个非空格字符
			}
			if (j == 4)
			{
				for (m = 0; m < 4; m++)
				{
					if (temp[m] < 97 || temp[m]>122)
					{
						flag = 1;
						break;//判断这四个字符是否都是字母
					}
				}
				if (flag == 0)//四个字符都是字母的情况，判断为一个单词
				{
					char* w = new char[100];//存放单词 
					for (m = 0; m < 4; m++)
					{
						w[k++] = temp[m];//temp中字符存入w
					}
					while (((f1.content[i] >= 48 && f1.content[i] <= 57) || (f1.content[i] >= 97 && f1.content[i] <= 122)) && i < n)//继续存入单词剩余字符
					{
						w[k++] = f1.content[i++];
					}
					w[k] = '\0';
					loadword(w);//可以在此处插入一个外部函数返回一个单词存入map红黑树 
					delete[]w;
					words++;
					k = 0;
				}
				else
				{
					flag = 0;
					j = 0;
				}
			}
		}
	}
	f1.words = words;
	return f1;
}


