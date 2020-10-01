struct range_minimum_query{
  vector<int> a;
  vector<vector<int>> p;
  int n, max_lv;
  void init(int n_, auto &a_){ // 1 indexed
    n = n_;
    max_lv = log2(n);
    a.resize(n + 1);
    for(int i = 1; i <= n; i ++) a[i] = a_[i];
    p.assign(n + 1, vector<int>(max_lv + 1, 0));
    for(int i = 1; i <= n; i ++) p[i][0] = i;
    for(int lv = 1; lv <= max_lv; lv ++)
      for(int i = 1; i + (1 << lv) - 1 <= n; i ++)
        p[i][lv] = (a[p[i][lv - 1]] <= a[p[i + (1 << (lv - 1))][lv - 1]]) ? p[i][lv - 1]: p[i + (1 << (lv - 1))][lv - 1];
  }
  int get(int l, int r, int get_value = false){ // supports lowest id
    int k = log2(r - l + 1), id;
    if(a[p[l][k]] <= a[p[r - (1 << k) + 1][k]]) id = p[l][k];
    else id = p[r - (1 << k) + 1][k];
    return get_value ? a[id]: id;
  }
};
