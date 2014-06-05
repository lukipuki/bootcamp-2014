//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

#include <cstdio>
#include <cmath>
#include <complex>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define repd(i,a,b) for(__typeof(b) i=a; i>=(b); --i)

typedef long long ll;
typedef complex<ll> vekt;
ll vs(const vekt &a, const vekt &b) {//vektorovy sucin
    return imag(conj(a)*b);
}
ll ss(const vekt &a, const vekt &b) {//skalarny sucin
    return real(conj(a)*b);
}
double ang(const vekt &x, const vekt &y) {
    double r=acos( ss(x, y)/sqrt(ss(x, x))/sqrt(ss(y, y)) );
    return r;
}
bool priam(vekt a, vekt b, vekt c) {//je bod c na usecke ab?
    return vs(c-a, b-a)==0 && ss(a-c, b-c)<0;
}
bool inside(vekt a, vekt &x, vekt &y, vekt &z)// is a inside xyz?
{
    ll area = abs(vs(x - a, y - a)) +
              abs(vs(y - a, z - a)) +
              abs(vs(x - a, z - a));
    return (area == abs(vs(y - x, z - x)));
}
void imprMax(int &a, int b)
{
    a = max(a, b);
}
typedef vector<int> vi;
int n;
int in[10][10][10][10];
int on[10][10][10][10];
int p[10][10][10][10];
int gx, gy;
int go(int i, int j, int u, int v, double angle)
{
    int &res = p[i][j][u][v];
    if (res != -123456) return res;

    if (u == gx && v == gy)
    {
        return res = -on[u][v][i][j];
    }

    vekt x(i, j), y(u, v);
    rep(s,0,n) rep(t,0,n) if (in[u][v][s][t] > -123456)
    {
        vekt z(s, t);
        if (vs(y - x, z - y) > 0)
        {
            double al = ang(y - x, z - y);
            if (angle + al <= 2 * M_PI - 1e-9)
                imprMax(res, go(u, v, s, t, angle + al) + in[u][v][s][t] + on[u][v][s][t] +
                        on[gx][gy][u][v] + 1);
        }
    }
    return res;
}
int main()
{
    int t; scanf("%d", &t);
    rep(cas,0,t)
    {
        scanf("%d", &n);

        bool a[n][n];
        rep(i,0,n)
        {
            int x;
            rep(j,0,n)
            {
                scanf("%d", &x);
                a[i][j] = x;
            }
        }

        rep(i,0,n) rep(j,0,n) rep(k,0,n) rep(l,0,n)
            on[i][j][k][l] = 0;

        int res = 0;
        rep(i,0,n) rep(j,0,n) if (a[i][j])
            rep(k,0,n) rep(l,0,n) if (a[k][l] && (k != i || l != j))
            {
                on[i][j][k][l] = 0;
                vekt x(i, j), y(k, l);
                rep(u,0,n) rep(v,0,n)
                {
                    int coeff = a[u][v] * 2 - 1;
                    if (priam(x, y, vekt(u, v)))
                        on[i][j][k][l] += coeff;
                }
                imprMax(res,  on[i][j][k][l] + 2);
            }

        rep(k,0,n) rep(l,0,n) if (a[k][l])
        {
            imprMax(res, 1);
            rep(i,0,n) rep(j,0,n) rep(u,0,n) rep(v,0,n)
            {
                p[i][j][u][v] = -123456;
                in[i][j][u][v] = -123456;
            }

            rep(i,k,n) rep(j,0,n) if (a[i][j] && (i != k || j != l))
                rep(u,k,n) rep(v,0,n) if (a[u][v] && (u != i || v != j) && (u != k || v != l))
            {
                vekt x(k, l), y(i, j), z(u, v);
                in[i][j][u][v] = 0;
                rep(s,0,n) rep(t,0,n)
                {
                    int coeff = a[s][t] * 2 - 1;
                    if (inside(vekt(s, t), x, y, z))
                        in[i][j][u][v] += coeff;
                }

                in[i][j][u][v] -= on[k][l][i][j] + on[k][l][u][v] + on[i][j][u][v] + 3;
                //subtract 3 for corners
            }

            rep(i,k,n) rep(j,0,n)
                in[i][j][k][l] = in[k][l][i][j] = 0;

            gx = k; gy = l;
            vekt x(k, n+1), y(k, l);
            rep(i,k,n) rep(j,0,n) if (a[i][j] && (i != k || j != l))
            {
                vekt z(i, j);
                imprMax(res, go(k, l, i, j, ang(y - x, z - y)) + 1); //+1 for (k, l), +1 for other two vertices
            }
        }
        printf("%d\n", res);
    }
}
