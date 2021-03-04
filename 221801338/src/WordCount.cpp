#include "Lib.h"

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
