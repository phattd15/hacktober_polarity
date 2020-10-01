template<int mod=MOD> struct int_mod{
  int x;
  int_mod():x(0){} int_mod(int64_t y):x(y>=0?y%mod:(mod-(-y)%mod)%mod){}
  int_mod &operator+=(const int_mod &p){if((x+=p.x)>=mod)x-=mod;return *this;}
  int_mod &operator-=(const int_mod &p){if((x+=mod-p.x)>=mod)x-=mod;return *this;}
  int_mod &operator*=(const int_mod &p){x=(int)(1LL*x*p.x%mod);return *this;}
  int_mod &operator/=(const int_mod &p){*this *=p.inv();return *this;}
  int_mod operator-()const{return int_mod(-x);}
  int_mod operator+(const int_mod &p)const{return int_mod(*this)+=p;}
  int_mod operator-(const int_mod &p)const{return int_mod(*this)-=p;}
  int_mod operator*(const int_mod &p)const{return int_mod(*this)*=p;}
  int_mod operator/(const int_mod &p)const{return int_mod(*this)/=p;}
  bool operator==(const int_mod &p)const{return x==p.x;}
  bool operator!=(const int_mod &p)const{return x!=p.x;}
  int_mod inv()const{int a=x,b=mod,u=1,v=0,t;while(b>0){t=a/b;swap(a-=t*b,b);swap(u-=t*v,v);}return int_mod(u);}
  int_mod pow(int64_t n)const{int_mod ret(1),mul(x);while(n){if(n&1)ret*=mul;mul*=mul;n>>=1;}return ret;}
  friend ostream &operator<<(ostream &os,const int_mod &p){return os<<p.x;}
  friend istream &operator>>(istream &is,int_mod &a){int64_t t;is>>t;a=int_mod<mod>(t);return(is);}
};
namespace double_bases_hash{
  pair<int, int> base = {311, 313};
  using hash_int = int_mod<>;
  vector<pair<hash_int, hash_int>> d, invd;
  void hash_setup(int MAX_HASH = MAXN){
    d.resize(MAX_HASH);
    invd.resize(MAX_HASH);
    d[0] = {1, 1}; 
    for(int i = 1; i < MAX_HASH; i ++)
      d[i] = {
        d[i - 1].fi*base.fi,
        d[i - 1].se*base.se
      };
    invd[MAX_HASH - 1] = {
      d[MAX_HASH - 1].fi.inv(),
      d[MAX_HASH - 1].se.inv()
    };
    for(int i = MAX_HASH - 2; i >= 0; i --)
      invd[i] = {
        invd[i + 1].fi*base.fi,
        invd[i + 1].se*base.se
      };
  }
  vector<pair<hash_int, hash_int>> build_hash(string &str){ // 0 indexed
    vector<pair<hash_int, hash_int>> res(str.size()); 
    res[0] = {(int) str[0], (int) str[0]};
    for(int i = 1; i < str.size(); i ++)
      res[i] = {
        res[i - 1].fi + ((hash_int)str[i])*d[i].fi,
        res[i - 1].se + ((hash_int)str[i])*d[i].se
      };
    return res;
  }
  pair<hash_int, hash_int> get_hash(vector<pair<hash_int, hash_int>>& hash_data, int l, int r){
    if(l) return make_pair(
      (hash_data[r].fi - hash_data[l - 1].fi)*invd[l].fi,
      (hash_data[r].se - hash_data[l - 1].se)*invd[l].se
    );
    else return hash_data[r];
  }
}
#define hs double_bases_hash
