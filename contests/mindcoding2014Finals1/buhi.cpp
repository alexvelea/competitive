#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream in("date.in");
ofstream out("date.out");

int N, M;
int ARB[4 * 100002], A1, A2, Ap, Ar, Ar1, Ar2;
int SUM[4 * 100002];

void update(int nod, int i1, int i2)
{
	if (A1 <= i1 && i2 <= A2)
	{
		ARB[nod] ^= 1;
		SUM[nod] = (i2 - i1 + 1) - SUM[nod];
		return;
	}
	
	int mid = (i1 + i2) / 2;
	if (ARB[nod])
	{
		ARB[nod] ^= 1;
		SUM[nod * 2] = (mid - i1 + 1) - SUM[nod * 2];
		ARB[nod * 2] ^= 1;
		SUM[nod * 2 + 1] = (i2 - mid) - SUM[nod * 2 + 1];
		ARB[nod * 2 + 1] ^= 1;
	}
	
	if (A1 <= mid) update(nod * 2, i1, mid);
	if (A2 > mid)  update(nod * 2 + 1, mid + 1, i2);
	
	SUM[nod] = SUM[nod * 2] + SUM[nod * 2 + 1];
}
void query(int nod, int i1, int i2)
{
	if (i1 == i2)
	{
		Ar = SUM[nod];
		return;
	}
	
	int mid = (i1 + i2) / 2;
	if (ARB[nod])
	{
		ARB[nod] ^= 1;
		SUM[nod * 2] = (mid - i1 + 1) - SUM[nod * 2];
		ARB[nod * 2] ^= 1;
		SUM[nod * 2 + 1] = (i2 - mid) - SUM[nod * 2 + 1];
		ARB[nod * 2 + 1] ^= 1;
	}
	
	if (Ap <= mid) query(nod * 2, i1, mid);
	else           query(nod * 2 + 1, mid + 1, i2);
	
	SUM[nod] = SUM[nod * 2] + SUM[nod * 2 + 1];
}
void querySUM(int nod, int i1, int i2)
{
	if (A1 <= i1 && i2 <= A2)
	{
		Ar += SUM[nod];
		return;
	}
	
	int mid = (i1 + i2) / 2;
	if (ARB[nod])
	{
		ARB[nod] ^= 1;
		SUM[nod * 2] = (mid - i1 + 1) - SUM[nod * 2];
		ARB[nod * 2] ^= 1;
		SUM[nod * 2 + 1] = (i2 - mid) - SUM[nod * 2 + 1];
		ARB[nod * 2 + 1] ^= 1;
	}
	
	if (A1 <= mid) querySUM(nod * 2, i1, mid);
	if (A2 > mid)  querySUM(nod * 2 + 1, mid + 1, i2);
	
	SUM[nod] = SUM[nod * 2] + SUM[nod * 2 + 1];
}
int getSUM(int i1, int i2)
{
	A1 = i1;
	A2 = i2;
	Ar = 0;
	querySUM(1, 1, N);
	return Ar;
}

int main()
{
//	cin.sync_with_stdio(false);
	
	in >> N >> M;
	for (int i = 1, type; i <= M; ++i)
	{
		in >> type;
		if (type == 1)
		{
			int p1, p2;
			in >> p1 >> p2;
			
			A1 = p1;
			A2 = p2;
			update(1, 1, N);
		}
		else
		{
			int pn;
			in >> pn;
			
			Ap = pn;
			query(1, 1, N);
			int val = Ar;
			
			int lf = pn, rg = pn;
			int step = (1 << 17);
			for (; step; step >>= 1)
				if (lf - step >= 1 && getSUM(lf - step, pn) == (pn - (lf - step) + 1) * val)
					lf -= step;
			step = (1 << 17);
			for (; step; step >>= 1)
				if (rg + step <= N && getSUM(pn, rg + step) == ((rg + step) - pn + 1) * val)
					rg += step;
			
			out << val << ' ' << lf << ' ' << rg << '\n';
		}
	}
	in.close();
	out.close();
}
