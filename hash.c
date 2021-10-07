namespace rolling_hash {
  using im1 = mint<1000000007>;
  using im2 = mint<1000000009>;
  using hp = pair<im1, im2>;
  hp operator+(const hp &p1, const hp &p2) {
    return hp { p1.first + p2.first, p1.second + p2.second };
  }
  hp operator-(const hp &p1, const hp &p2) {
    return hp { p1.first - p2.first, p1.second - p2.second };
  }
  hp operator*(const hp &p1, const hp &p2) {
    return hp { p1.first * p2.first, p1.second * p2.second };
  }
  hp operator*(const hp &p1, const int &val) {
    return { p1.first * val, p1.second * val };
  }
  hp base = hp {1427, 1429};
  hp *pw, *ipw;
  void init(int MAXN = 100000) {
    pw = new hp[MAXN];
    ipw = new hp[MAXN];
    pw[0] = {1, 1};
    for (int i = 1; i < MAXN; i ++)
      pw[i] = pw[i - 1] * base;
    ipw[MAXN - 1] = { pw[MAXN - 1].first.inv(), pw[MAXN - 1].second.inv() };
    for (int i = MAXN - 2; i >= 0; i --)
      ipw[i] = ipw[i + 1] * base;
  }
  vector<hp> build(string &s) {
    vector<hp> res(s.size() + 1);
    for (int i = 0; i < s.size(); i ++) 
      res[i + 1] = res[i] + pw[i + 1] * ((int) s[i]);
    return res;
  }
  hp get(vector<hp> &h, int l, int r) { // 1 indexed please
    return (h[r] - h[l - 1]) * ipw[l];
  }
};
#define rh rolling_hash
