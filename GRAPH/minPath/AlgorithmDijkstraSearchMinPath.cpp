#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#define N 10005
using namespace std;
/*
Thuật toán dijkstra( chỉ sử dụng khi các trọng số đều >=0 ):
- Khởi tạo các giá trị ban đầu
- đánh dấu các đỉnh thêm vào đương đi T bằng mảng visited
- mảng d[] chưa khoảng cách ngắn nhất từ đỉnh t đến các đỉnh còn lại đã được thêm vào cây T
- mảng pa[] chưa điểm gần nhất với các điểm đã thăm 
*/
int n, m; // số đỉnh và số cạnh của đồ thị
int s, t; // đỉnh đầu và đỉnh cuối ta cần tìm
vector<int> pa, d,T,visited;
// chứa đường đi giữa các đỉnh
vector<list<pair<int,int>>> a;
// nhập dữ liệu vào
void READ() {
	cin >> n >> m;
	a.resize(n + 1);
	for (int i = 1; i <= m; i++) {
		int u, v, c; // c là trọng số, chi phí đường đi từ u tới v
		cin >> u >> v >> c;
		a[u].push_back(pair<int, int>(v, c));
	}
	cin >> s >> t;
}
// hàm khởi tạo dữ liệu ban đầu
void init() {
	visited.resize(n + 1,0);
	d.resize(n + 1, 0);
	pa.resize(n + 1);
	T.push_back(s);
	visited[s] = 1;
	for (int i = 1; i <= n; i++)
	{
		if (visited[i] == 0)
		{
			pa[i] = s;
			d[i] = 99999;
		}
	}
	for (auto i : a[s])
		d[i.first] = i.second;
}
// hàm tìm ra đỉnh gần nhất tiếp theo có thể duyệt
int nearIndex() {
	int mx = 1e5;
	int luu = 0;
	for(int i=1;i<=n;i++)
		if (visited[i] == 0)
		{
			if (d[i] < mx)
			{
				mx = d[i];
				luu = i;
			}
		}
	return luu;
}
// cập nhật lại các giá trị 
void updatealg(int u) {
	for (auto i : a[u])
		if (visited[i.first] == 0)
			if (d[i.first] > d[u] + i.second)
			{
				d[i.first] = d[u] + i.second;
				pa[i.first] = u;
			}
}
void print() {
	for (int i = 1; i <= n; i++)
		cout << d[i] << " "<<pa[i]<<endl;
	cout << endl;
}
// thuật toán tìm đường đi ngắn nhất giữa s và t
void dijkstra() {
	while (T.size() !=n) {
		int index = nearIndex();
		T.push_back(index);
		visited[index] = 1;
		updatealg(index);
		if (index == t)
			break;
	}
}
int main() {
	string res;//luu ket qua
	READ();
	init();
	dijkstra();
	cout << d[t] << endl;
	while (t != s)
	{
		res = to_string(t)+res;
		t = pa[t];
	}
	res = to_string(s)+res;
	for (auto i : res)
		cout << i << " ";
	return 0;
}