#include <iostream>
#include <vector>
#include <algorithm>
#include<map>
#define N 10005
using namespace std;
/*
mảng d[] dùng lưu khoảng cách ngắn nhất giữa điểm ngoài cây T và cây T
mảng pa[] dùng lưu điểm nối điểm trong cây với ngoài cây
mảng visited[] đánh dấu các điểm đã được thêm vào cây
mảng T[] lưu cây khung
*/
vector<int> d, pa, visited,T;
vector<pair<int, int>> arr;
int n, m,val=0;
int a[N][N];
void READ() {
	cin >> n >> m;
	d.resize(n + 1, 0);
	pa.resize(n + 1, 0);
	visited.resize(n + 1, 0);
	for (int i = 0; i < m; i++)
	{
		int u, v,c;
		cin >> u >> v >> c;
		a[u][v] = c;
		a[v][u] = c;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j && a[i][j] == 0)
				a[i][j] = 99999;
}
// khoi tao cac dinh va cay khung
void init() {
	T.push_back(1);
	visited[1] = 1;
	for(int i=1;i<=n;i++)
		if (visited[i] == 0)
		{
			pa[i] = 1;
			d[i] = a[1][i];
		}
}
// tim canh an toan de them vao cay khung
int findSave() {
	int mx = 99999;
	int luu = 0;
	for(int i=1;i<=n;i++)
		if (visited[i] == 0)
		{
			if (mx > d[i])
			{
				luu = i;
				mx = d[i];
			}
		}
	return luu;
}
// cap nhat lai cay khung
void updateTree(int u) {
	for (int i = 1; i <= n; i++)
	{
		if (visited[i] == 0) {
			if (a[i][u] < d[i])
			{
				pa[i] = u;
				d[i] = a[i][u];
			}
		}
	}
}
void prim() {
	init();
	while (T.size() != n) {
		int u = findSave();
		T.push_back(u);
		visited[u] = 1;
		arr.push_back(pair<int,int>(pa[u], u));
		val += d[u];
		updateTree(u);
	}
}
int main() {
	READ();
	prim();
	cout << val<<endl;
	sort(arr.begin(), arr.end());
	for (auto i : arr)
		cout << i.first << " " << i.second << " ";
	return 0;
}