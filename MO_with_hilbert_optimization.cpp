#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define fi first
#define se second
#define endl '\n'
#define int int64_t
#define double long double
template<int D, typename T>struct dense:public vector<dense<D-1,T>>{static_assert(D>=1,"dim err");template<typename... Args>dense(int n=0,Args... args):vector<dense<D-1,T>>(n,dense<D-1,T>(args...)){}};
template<typename T>struct dense<1,T>:public vector<T>{dense(int n=0,const T& val=T()):vector<T>(n,val){}};
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using reverse_queue = priority_queue<T, vector<T>, greater<T>>;
mt19937_64 rnd(time(0));
const int64_t FIXED_RANDOM = rnd();
template<typename T> struct custom_hash{T operator()(T x)const{return (T) x^FIXED_RANDOM;}}; // check hash in whether int64 or int32
template<typename T1, typename T2> using hash_map = gp_hash_table<T1, T2, custom_hash<T1>>;
const int MAXN = (int) 1e5 + 2;
const int INF = numeric_limits<int>::max() >> 1;
const int MOD = (int) 998244353;
// Tao luyện kỹ thuật trong 8 năm mày luyện kỹ thuật trong buồng tắm nam
struct query{
  int l, r, id;
  long long ord;
  long long build_order(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotate_delta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotate_delta[seg]) & 3;
    int64_t ssq = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * ssq;
    int64_t add = build_order(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (ssq - add - 1);
    return ans;
  }
  void get_order() {ord = build_order(l, r, 18, 0);}
  bool operator < (const query &rhs) const {return ord < rhs.ord;}
} q[MAXN];
int T, c[MAXN], euler[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p){
  q[u - 1].l = ++ T;
  euler[T] = u;
  for(int v: g[u]) if(v != p) dfs(v, u);
  q[u - 1].r = T;
  q[u - 1].id = u;
  q[u - 1].get_order();
}
signed main(){
  ios_base::sync_with_stdio(0); 
  cin.tie(0);
  // freopen("FDT.txt", "r", stdin);
  int n;
  cin >> n;
  for(int i = 1; i <= n; i ++) cin >> c[i];
  for(int i = 1; i < n; i ++){
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> ans(n + 1);
  dfs(1, 0);
  int L = 1, R = 0;
  vector<int> cnt(n + 1);
  map<int, int> sum;
  auto modify = [&](int color, int add){
    sum[cnt[color]] -= color;
    if(sum[cnt[color]] == 0) sum.erase(cnt[color]);
    cnt[color] += add;
    sum[cnt[color]] += color;
  };
  sort(q, q + n);
  for(int i = 0; i < n; i ++){
    auto qr = q[i];
    while(L < qr.l) modify(c[euler[L]], -1), L ++;
    while(L > qr.l) modify(c[euler[L - 1]], 1), L --;
    while(R < qr.r) modify(c[euler[R + 1]], 1), R ++;
    while(R > qr.r) modify(c[euler[R]], -1), R --;
    ans[qr.id] = (sum.rbegin()->se);
  }
  for(int i = 1; i <= n; i ++) cout << ans[i] << " ";
}
