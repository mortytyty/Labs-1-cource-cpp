#include <iostream>
#include <queue> 
using namespace std;

const int n = 6;
int i, j;
bool* NUM = new bool[n];
int G[n][n];//граф
/* = {
	{0,1,1,0,0,1},
	{1,0,0,1,0,0},
	{1,0,0,0,1,0},
	{0,1,0,0,0,0},
	{0,0,1,0,0,0},
	{1,0,0,0,0,0}
};*/

//поиск в ширину
void BFS(int v)
{
	queue <int> Q;
	Q.push(v);
	NUM[v] = true;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		cout << v + 1<< " ";
		for (i = 0; i < n; i++)
			if (G[v][i] && !NUM[i])
			{
				Q.push(i);
				NUM[i] = true;
			}
	}
}

//главная функция
void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int start;
	cout << "Стартовая вершина >> "; cin >> start;
	for (i = 0; i < n; i++)
	{
		NUM[i] = false;
		G[i][i] = 0;
		for (j = 0; j < i; j++)
		{
			G[j][i] = G[i][j] = rand() % 2; //заполнение графа случайными числами
		}
	}
	cout << "Матрица смежности графа: " << endl;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			cout << " " << G[i][j];
		cout << endl;
	}

	cout << "Порядок обхода: ";
	BFS(start - 1);
	delete[]NUM;
	system("pause>>void");
}