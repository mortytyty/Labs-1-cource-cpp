//Реализация алгоритма выделен ия компонент связности орграфа, используя поиск в ширину

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <conio.h> 
#include <cstdlib>
using namespace std;

int i, j;
ofstream fout;

void NKS(int** G,const int n);//нахождение компоненты смежности через обход в ширину
void RANDMATR(int** G, const int n);//генерация и вывод матрицы смежности графа
void OUTMATR(int** G, const int n);//вывод матрица в консоль и в файл
void INMATR(int** G, const int n);//загрузка матрицы из файла input.txt
void DELETEMASS(int** G, const int n);

void main()//главная функция
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << " Введите количество вершин графа: ";
	cin >> n;//размер графа
	int** G = new int* [n];//граф
	for (i = 0; i < n; i++)
		G[i] = new int[n];
	cout << "\n Выберите действие: \n 1) Сгенерировать граф размера: "<<n<<", случайным образом.\n 2) Загрузить граф из текстового файла «input.txt».\n Для выбора нажмите клавишу 1 или 2.\n ";
	int z = _getch()-48;
	switch (z)
	{
	case 1:
		cout << "1\n\n";
		RANDMATR(G,n);
		break;
	case 2:
		cout << "2\n\n";
		INMATR(G,n);
		break;
	default:
		cout << "\n Выбран несуществующий вариант, поэтому граф будет сгенерирован случайным образом. \n\n";
		RANDMATR(G,n);
		break;
	}
	fout.open("output.txt", ofstream::app);
	cout << " Матрица смежности графа: \n";
	fout << " Матрица смежности графа: \n";
	OUTMATR(G,n);
	cout << " Компоненты связности: \n";
	fout << " Компоненты связности: \n";
	NKS(G,n);
	fout << "\n=========================\n\n";
	fout.close();
	DELETEMASS(G,n);
	system("pause>>void");
}

void NKS(int** G, const int n)//нахождение компоненты смежности через обход в ширину
{
	vector<bool> used(n);//вектор использованных вершин
	vector<vector<int>>KS;//массив компонент связности
	KS.resize(n);
	for (j = 0; j < n; j++) {
		if (!used[j])
		{
			int v = j;
			queue <int> Q;
			Q.push(v);
			used[v] = true;
			while (!Q.empty())
			{
				v = Q.front();
				Q.pop();
				KS[j].push_back(v + 1);
				for (i = 0; i < n; i++)
					if ((G[v][i] || G[i][v]) && !used[i])
					{
						Q.push(i);
						used[i] = true;
					}
			}
			for (i = 0; i < KS[j].size(); i++)
			{
				cout << " " << KS[j].at(i); //вывод компоненты смежности
				fout << " " << KS[j].at(i);
			}
			cout << endl;
			fout << endl;
		}
	}
}
void RANDMATR(int** G, const int n)
{
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		G[i][i] = 0;
		for (j = 0; j < i; j++)
		{
			if (rand() % 100 <= 5) //заполнение графа случайными числами
				G[i][j] = 1;
			else
				G[i][j] = 0;
			if (rand() % 100 <= 5)
				G[j][i] = 1;
			else
				G[j][i] = 0;
		}
	}
}
void OUTMATR(int** G, const int n)
{
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << " " << G[i][j];
			fout << " " << G[i][j];
		}
		cout << endl;
		fout << endl;
	}
	cout << endl;
	fout << endl;
}
void INMATR(int** G, const int n)
{
	ifstream fin;
	fin.open("input.txt");
	if (!fin.is_open())
	{
		cout << "Ошибка при открытии файла.\n";
		system("pause>>void");
	}
	else
	{
		string str;
		int iin = 0;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				fin >> str;
				for (int m = 0; m < str.length(); m++)
				{
					if (str.at(m) == '1' || str.at(m) == '0')
					{
						iin = stoi(str);
						G[i][j] = iin;
					}
					else
					{
						cout << "В файл введены некорректные данные.\n";
						system("pause>>void");
					}
				}
			}
		}
		fin.close();
	}
}

void DELETEMASS(int** G, const int n)
{
	for (i = 0; i < n; i++)
		delete[] G[i];
	delete[] G;
}
