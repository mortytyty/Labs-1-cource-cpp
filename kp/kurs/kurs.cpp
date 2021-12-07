//Реализация алгоритма выделен ия компонент связности орграфа, используя поиск в ширину

#include <iostream>
#include <queue> 
#include <vector>
using namespace std;

const int n = 10;
int i, j;
vector<bool> used(n);
vector<int>KS[n];
int G[n][n];//граф

void BFS(int v)//поиск в ширину
{

	queue <int> Q;
	Q.push(v);
	used[v] = true;
	int k = v;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		KS[k].push_back(v+1);
		for (i = 0; i < n; i++)
			if ((G[v][i] || G[i][v]) && !used[i])
			{
				Q.push(i);
				used[i] = true;
			}
			
	}
}

void main() //главная функция
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	for (i = 0; i < n; i++)
	{
		used[i] = false;
		G[i][i] = 0;
		for (j = 0; j < i; j++)
		{
			if (rand() % 100 <= 5) //заполнение графа случайными числами
				G[i][j] = 1; 
			if (rand() % 100 <= 5)
				G[j][i] = 1; 
		}
	}

	cout << "Матрица смежности графа: " << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			cout << " " << G[i][j];
		cout << endl;
	}

	cout << "Компоненты связности: " <<endl;
	for (j = 0; j < n; j++) {
		if (!used[j])
		{
			BFS(j);
			for(int p = 0; p < KS[j].size(); p++)
			{
				cout << KS[j].at(p) << " ";
			}
			cout << endl;
		}
	}

	system("pause>>void");
}




