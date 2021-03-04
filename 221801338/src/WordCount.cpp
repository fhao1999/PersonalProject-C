#include "Lib.h"
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

map<string, int> mapword1;

void loadword(char w[])
{
	string wr;
	wr = w;
	map<string, int>::iterator it1 = mapword1.find(wr);//在map红黑树中查找单词 
	if (it1 == mapword1.end())
		mapword1.insert(pair<string, int>(wr, 1));//未找到单词，插入单词并设定频次为1 
	else
		++it1->second;//找到单词，单词出现频次增加 
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

struct sWord
{
	string w;
	int count;

};//定义一个用于存放单词及频次的结构体 

void merge(sWord* a, sWord* c, int l, int mid, int r) {
	int i = l, j = mid + 1, m = 1;
	while (i <= mid && j <= r) {
		if (a[i].count < a[j].count) c[m++] = a[j++];
		else c[m++] = a[i++];
	}
	while (i <= mid) c[m++] = a[i++];
	while (j <= r) c[m++] = a[j++];
	for (int k = 1; k <= r - l + 1; k++)
		a[l + k - 1] = c[k];
}

void sort(sWord* a, sWord* c, int l, int r) {
	if (l < r) {
		int mid = (l + r) / 2;
		sort(a, c, l, mid);
		sort(a, c, mid + 1, r);
		merge(a, c, l, mid, r);
	}
}


int main(int argc, char* argv[])
{
	clock_t start = clock();
	string f = argv[2];
	int i, num = 0, j;
	testfile f1;
	f1.init();
	if (!argv[1])
	{
		cout << "您未输入文件名或文件不存在，导致exe无法运行" << endl;
		return 0;
	}
	f1 = f1.countcha(argv[1], f1);
	f1 = f1.countline(argv[1], f1);
	f1 = f1.countword(argv[1], f1);
	sWord* ww = new sWord[f1.getwords()];//给结构体分配一个大小为单词数目的动态空间 
	sWord* temp = new sWord[f1.getwords()];
	map<string, int>::iterator it;
	it = mapword1.begin();
	for (it; it != mapword1.end(); it++)
	{
		ww[num].w = it->first;
		ww[num].count = it->second;
		num++;
	}
	sort(ww, temp, 0, num - 1);//把已经按字典序排号按出现频率进行从大到小的归并排序
	//输出 
	ofstream fout;
	fout.open(f);
	if (!fout)
		cout << "文件打开失败" << endl;
	cout << "characters: " << f1.getcharacters() << endl;
	fout << "characters: " << f1.getcharacters() << endl;
	cout << "words: " << f1.getwords() << endl;
	fout << "words: " << f1.getwords() << endl;
	cout << "lines: " << f1.getlines() << endl;
	fout << "lines: " << f1.getlines() << endl;
	if (num < 10)
	{
		for (i = 0; i < num; i++)
		{
			cout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
			fout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
		}
	}
	else
	{
		for (i = 0; i < 10; i++)

		{
			cout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
			fout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
		}
	}
	delete[]temp;
	delete[]ww;
	free(f1.content);//动态空间释放 
	clock_t ends = clock();
	cout << "运行时间 : " << (double)(ends - start) / CLOCKS_PER_SEC << "秒" << endl;
	return 0;
}
