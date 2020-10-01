struct lazy_segment_tree{
  using it_type = int;
  const it_type it_null = INF;
  const int lz_null = 0;
  it_type it_merge(it_type a, it_type b){return min(a, b);}
  void lz_stack(int &lz_cur, int val){lz_cur += val;}
  void it_modify(int &it_cur, int val){it_cur += val;}
  /*-----------------------*/
  int32_t n;
  vector<it_type> it;
  vector<int> lz;
  void init(int _, vector<it_type> init_val = vector<it_type>()){
    n = _;
    it.resize((n << 2)|1, it_null);
    lz.resize((n << 2)|1, lz_null);
    if(init_val.size()) build(1, 1, n, init_val);
  }
  it_type build(int32_t u, int32_t l, int32_t r, auto &a){
    if(l == r) return it[u] = a[l];
    return it[u] = it_merge(build(u << 1, l, ((l + r)>>1), a), build((u << 1)|1, ((l + r)>>1) + 1, r, a));
  }
  void lazy(int32_t u, int32_t l, int32_t r){
    if(lz[u] == lz_null) return;
    it_modify(it[u], lz[u]);
    if(l != r){
      lz_stack(lz[u << 1], lz[u]);
      lz_stack(lz[u << 1|1], lz[u]);
    }
    lz[u] = lz_null;
  }
  void _update(int32_t u, int32_t l, int32_t r, int32_t L, int32_t R, int val){
    if(R < L) return;
    lazy(u, l, r);
    if(l > R || r < L) return;
    if(L <= l && r <= R){
      lz_stack(lz[u], val);
      lazy(u, l, r);
      return;
    }
    _update(u << 1, l, ((l + r)>>1), L, R, val);
    _update((u << 1)|1, ((l + r)>>1) + 1, r, L, R, val);
    it[u] = it_merge(it[u << 1], it[(u << 1)|1]);
  }
  it_type _get(int32_t u, int32_t l, int32_t r, int32_t L, int32_t R){
    if(l > R || r < L) return it_null;
    lazy(u, l, r);
    if(L <= l && r <= R) return it[u];
    return it_merge(_get(u << 1, l, ((l + r)>>1), L, R), _get((u << 1)|1, ((l + r)>>1) + 1, r, L, R));
  }
  void update(int32_t L, int32_t R, int val){_update(1, 1, n, L, R, val);}
  it_type get(int32_t L, int32_t R){return _get(1, 1, n, L, R);}
};
