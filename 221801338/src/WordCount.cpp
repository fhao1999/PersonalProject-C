/**
作者：221801338_冯浩
最后修改时间：2021/03/04
**/
#include "Lib.h"


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
		cout << "未输入文件名或文件不存在" << endl;
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
