#define NODE_LIMIT 300000
#define DEPTH_LIMIT 20
#include "splender.h"
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define IFOR(i,a,b) for(int i=a-1;i>=b;--i)
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define F first
#define S second
#define pb emplace_back 
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvll vector<vll>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define BE(a) a.begin(),a.end()
#define DIM(S) template<typename T> struct Dim<S<T>>{ enum {val = 1 + Dim<T>::val}; };
#define UGLIFY(U,B,S,E) template<typename ...T> ostream& operator<<(ostream&O,U<T...> a){ O<<B; int c=0; for(auto i:a)O<<(c++?S:"")<<i; return O<<E; } template<typename ...T> void _print(const char *s,U<T...> a,bool nxt_line = false,int idt = 0,int dim = Dim<U<T...>>::val,typename enable_if< (Dim<U<T...>>::val>1) >::type* = 0){ bool b = strlen(s); if(b) cerr<<s<<" =\n";if(nxt_line) cerr<<"\n"; cerr<<B; int c=0; string sep = S; for(int i=0;i<dim-1;++i)sep += "\n"; for(int i=0;i<idt+1;++i)sep += " "; for(auto i:a){ cerr<<(c++?sep:""); _print("",i,0,idt+1,dim-1); } cerr<<E; cerr<<(b?"\n":""); return; }
#ifdef ONLINE_JUDGE
#define print(arg...) 0
#else
#define print(arg...) _print_all(#arg,arg);
#endif
#define endl '\n'
using namespace std;
template<typename T> struct Dim{ enum {val = 0}; }; DIM(vector); DIM(deque); DIM(set); DIM(multiset); DIM(unordered_set); template<typename S,typename T> struct Dim<map<S,T>>{ enum {val = 1 + Dim<T>::val}; }; template<typename S,typename T> struct Dim<unordered_map<S,T>>{ enum {val = 1 + Dim<T>::val}; }; template<typename S,typename T> ostream& operator<<(ostream&O,pair<S,T> a){ return O<<"("<<a.first<<", "<<a.second<<")"; } template<typename T> void _print(const char *s,T a,bool nxt_line = false,int idt = 0,int dim = Dim<T>::val,typename enable_if< (Dim<T>::val<=1) >::type* = 0){ bool b = strlen(s); if(b) cerr<<s<<" = "; cerr<<a<<(b?"\n":""); return; }
UGLIFY(vector,"[",", ","]"); UGLIFY(deque,"[",", ","]"); UGLIFY(set,"{",", ","}"); UGLIFY(multiset,"{",", ","}"); UGLIFY(unordered_set,"{",", ","}"); UGLIFY(map,"{",", ","}"); UGLIFY(unordered_map,"{",", ","}"); 
template<typename ...T> void _print_all(const char*s,T... a){ cerr<<s<<" = "; int c=0; ((cerr<<(c++?", ":""),_print("",a,true)),...); cerr<<"\n"; }
ostream& operator <<(ostream&O, card c){
	return O<<"id: "<<c.id<<
		" cost[5]: "<<c.cost[0]<<c.cost[1]<<c.cost[2]<<c.cost[3]<<c.cost[4]<<
		" gem: "<<c.gem<<
		" score: "<<c.score;
}
template<>
struct Dim<card> {enum{val=1};};
const string mt[4] = {"null","take","buy","res"};
const int take3[10][5] = { {1,1,1,0,0},{1,1,0,1,0},{1,1,0,0,1},{1,0,1,1,0},{1,0,1,0,1},{1,0,0,1,1},{0,1,1,1,0},{0,1,1,0,1},{0,1,0,1,1},{0,0,1,1,1} };
const int take2[5][5] = { {2,0,0,0,0},{0,2,0,0,0},{0,0,2,0,0},{0,0,0,2,0},{0,0,0,0,2} };
ostream& operator <<(ostream&O, struct move m){
	O<<mt[m.type];
	if(m.type==2 || m.type==3){
		return O<<" "<<m.card_id;
	}
	if(m.type==1){
		return O<<" "<<m.gem[0]<<m.gem[1]<<m.gem[2]<<m.gem[3]<<m.gem[4];
	}
	return O;
}
struct Player{
	int id = 0;
	int gem[7] = {0,0,0,0,0,0,0};
	int score = 0;
	int bonus[5] = {0,0,0,0,0};
	int res[3] = {-1,-1,-1};
	Player(int i){id = i;}
};
ostream& operator <<(ostream& O,struct Player p){
	return O<<"id: "<<p.id<<
		" gem[6]: "<<p.gem[0]<<p.gem[1]<<p.gem[2]<<p.gem[3]<<p.gem[4]<<p.gem[5]<<
		" bonus[5]: "<<p.bonus[0]<<p.bonus[1]<<p.bonus[2]<<p.bonus[3]<<p.bonus[4]<<
		" score: "<<p.score<<
		" res: "<<p.res[0]<<' '<<p.res[1]<<' '<<p.res[2];
}
struct Node{
	int eval,alpha = INT_MIN,beta = INT_MAX;
	bool mx = false;
	struct move best_move;
	Player plyr[2] = {Player(0),Player(1)};
	vi g,vci;
	vvi b;
	vector<int> chs;
	vector<struct move> legal_moves;
	Node(){
		g = vi(6,4);
		vci = vi(3,4);
		b = vvi(3,vi(4,-1));
	}
};

vector<vector<card>> vc(3);
vector<card> svc(90);
vector<Node> tmp_nodes(NODE_LIMIT);
vector<float> gem_value(5,1);
Node cur;
int turn = 0,tni = 0;
void init (vector<card> stack_1, vector<card> stack_2, vector<card> stack_3) {
	vc[0] = stack_1;
	vc[1] = stack_2;
	vc[2] = stack_3;
	srand(time(NULL));
	FOR(i,0,3)
		for(auto u:vc[i])
			svc[u.id] = u;
	cur = Node();
	FOR(i,0,4)
		FOR(j,0,3)
			cur.b[j][i] = vc[j][i].id;
	turn = 0;
	tni = 0;

	vi gem_cnt(5,0);
	int gem_sum = 0;
	FOR(i,0,8){
		card c = vc[2][i];
		FOR(j,0,5)gem_cnt[j] += c.cost[j];
		++gem_cnt[c.gem];
	}
	FOR(i,0,14){
		card c = vc[1][i];
		FOR(j,0,5)gem_cnt[j] += c.cost[j];
		++gem_cnt[c.gem];
	}
	FOR(i,0,18){
		card c = vc[0][i];
		FOR(j,0,5)gem_cnt[j] += c.cost[j];
		++gem_cnt[c.gem];
	}
	FOR(i,0,5)gem_sum += gem_cnt[i];
	FOR(i,0,5)gem_value[i] = 5.0*gem_cnt[i] / gem_sum;
}

void update(Node &n,struct move &m,bool search){
	Player* p = &(n.plyr[1-n.mx]);
	if(m.type == 1){
		FOR(i,0,5){
			n.g[i] -= m.gem[i];
			p->gem[i] += m.gem[i];
			p->gem[6] += m.gem[i];
		}
	}
	else if(m.type == 2){
		int wild = 0;
		card c = svc[m.card_id];
		int dif;
		FOR(i,0,5){
			wild += max(0,c.cost[i] - p->bonus[i] - p->gem[i]);
			dif = min(p->gem[i],max(0,c.cost[i] - p->bonus[i]));
			p->gem[i] -= dif;
			p->gem[6] -= dif;
			n.g[i] += dif;
		}
		p->gem[5] -= wild;
		p->gem[6] -= wild;
		n.g[5] += wild;
		p->bonus[c.gem]++;
		p->score += c.score;
		int i,j;
		FOR(k,0,12){
			i = k/4;j=k%4;
			if(n.b[i][j] == m.card_id){
				n.b[i][j] = vc[i][n.vci[i]].id;
				++n.vci[i];
				break;
			}
		}
		FOR(i,0,3)
			if(p->res[i] == m.card_id){
				p->res[i] = -1;
				break;
			}
	}
	else if(m.type == 3){
		p->gem[5]++;
		p->gem[6]++;
		n.g[5]--;
		FOR(i,0,3)
			if(p->res[i]==-1){
				p->res[i] = m.card_id;
				break;
			}
		int i,j;
		FOR(k,0,12){
			i = k/4;j=k%4;
			if(n.b[i][j] == m.card_id){
				n.b[i][j] = vc[i][n.vci[i]].id;
				++n.vci[i];
				break;
			}
		}
	}
	
	n.legal_moves.clear();
	n.chs.clear();
	n.best_move.type = -1;
	n.mx = !n.mx;
	if(!search){
		tni = 0;
		n.alpha = INT_MIN;
		n.beta = INT_MAX;
	}
}

void list_legal_moves(Player &p,vector<struct move> &v,vi &g,vvi &b){
	int gemsum = p.gem[6];
	struct move m;
	//list buy
	m.type = 2;
	FOR(i,0,3){
		FOR(j,0,4){
			int wild = 0;
			card c = svc[b[i][j]];
			FOR(k,0,5)
				wild += max(0,c.cost[k] - p.bonus[k] - p.gem[k]);
			if(wild <= p.gem[5]){
				m.card_id = b[i][j];
				v.pb(m);
			}
		}
	}
	FOR(i,0,3){
		if(p.res[i] == -1)continue;
		int wild = 0;
		card c = svc[p.res[i]];
		FOR(k,0,5)
			wild += max(0,c.cost[k] - p.bonus[k] - p.gem[k]);
		if(wild <= p.gem[5]){
			m.card_id = p.res[i];
			v.pb(m);
		}
	}
	//list take 
	if(gemsum <= 8){
		m.type = 1;
		m.card_id = -1;
		FOR(i,0,5){
			if(g[i] >= 2){
				FOR(j,0,5)
					m.gem[j] = take2[i][j];
				v.pb(m);
			}
		}
		if(gemsum <= 7){
			bool flag = true;
			FOR(i,0,10){
				flag = true;
				FOR(j,0,5){
					if(g[j] - take3[i][j] < 0) flag = false;
				}
				if(flag){
					FOR(j,0,5)
						m.gem[j] = take3[i][j];
					v.pb(m);
				}
			}
		}
	}
	//list reserve
	if(gemsum <= 9 && g[5] && (p.res[0] == -1 || p.res[1] == -1 || p.res[2] == -1)){
		m.type = 3;
		FOR(i,0,3){
			FOR(j,0,4){
				m.card_id = b[i][j];
				v.pb(m);
			}
		}
	}
	if(!v.size()){
		m.type = -1;
		v.pb(m);
	}
}
void list_legal_moves(Node &n){
	list_legal_moves(n.plyr[1-n.mx],n.legal_moves,n.g,n.b);
}

int eval(Node &n){
	if(n.plyr[0].score >= 15)return 1e9;
	if(n.plyr[1].score >= 15)return -1e9;
	const int T = 100;
	const int est_turn = 30;
	const int est_decay_to = 30;
	int ps = 0;
	ps += n.plyr[0].score * est_turn * T / 15;
	FOR(i,0,5)
		ps += n.plyr[0].gem[i]*gem_value[i]*T/3;
	ps += n.plyr[0].gem[5] * T / 2;
	int bns = 0;
	FOR(i,0,5)bns += n.plyr[0].bonus[i] * gem_value[i] * T;
	bns = max(bns / 3, 2*bns - (5*turn*bns/3/est_decay_to));
	ps += bns;

	int qs = 0;
	qs += n.plyr[1].score * est_turn * T / 15;
	FOR(i,0,5)
		qs += n.plyr[1].gem[i]*gem_value[i]*T/3;
	qs += n.plyr[1].gem[5] * T / 2;
	bns = 0;
	FOR(i,0,5)bns += n.plyr[1].bonus[i] * gem_value[i] * T;
	bns = max(bns / 3, 2*bns - (5*turn*bns/3/est_decay_to));
	qs += bns;
	return ps - qs;
}

bool move_cmp(const struct move &a,const struct move &b){
	if(a.type == 2 && b.type == 2)
		return a.card_id > b.card_id;
	if(a.type == 2 || b.type == 2)
		return a.type ==2;
	if(a.type == 1 && b.type == 1){
		float av = 0,bv = 0;
		FOR(i,0,5)av += gem_value[i] * a.gem[i];
		FOR(i,0,5)bv += gem_value[i] * b.gem[i];
		return av > bv;
	}
	if(a.type == 1 || b.type == 1){
		return a.type == 1;
	}
	return a.card_id > b.card_id;
}

vi argsort_chs(Node &n){
	vi re(n.chs.size());
	iota(BE(re),0);
	if(n.mx)
		sort(BE(re),[&n](int a,int b){return tmp_nodes[n.chs[a]].eval > tmp_nodes[n.chs[b]].eval;});
	else
		sort(BE(re),[&n](int a,int b){return tmp_nodes[n.chs[a]].eval < tmp_nodes[n.chs[b]].eval;});
	return re;
}

void minimax(Node &n,int sd){
	if(sd <= 0 || n.plyr[0].score >= 15 || n.plyr[1].score >= 15){
		n.eval = eval(n);
		return;
	}
	if(!n.legal_moves.size()){
		list_legal_moves(n);
		sort(BE(n.legal_moves),move_cmp);
	}
	if(n.legal_moves[0].type == -1){
		n.eval = (n.mx?-1e9-3:1e9+3);
		if(n.mx) n.alpha = max(n.alpha,n.eval);
		else n.beta = min(n.beta,n.eval);
		return;
	}
	if(n.mx) n.eval = -1e9-5;
	else n.eval = 1e9+5;

	int idx;
	vi move_order = argsort_chs(n);
	for(auto i:move_order){
		idx = n.chs[i];
		tmp_nodes[idx].alpha = n.alpha;
		tmp_nodes[idx].beta = n.beta;
		if(tni == NODE_LIMIT)return;
		minimax(tmp_nodes[idx],sd-1);
		if(n.mx){
			if(tmp_nodes[idx].eval > n.eval){
				n.eval = tmp_nodes[idx].eval;
				n.best_move = n.legal_moves[i];
			}
			n.alpha = max(n.alpha,n.eval);
		}
		else{
			if(tmp_nodes[idx].eval < n.eval){
				n.eval = tmp_nodes[idx].eval;
				n.best_move = n.legal_moves[i];
			}
			n.beta = min(n.beta,n.eval);
		}
		if(n.alpha >= n.beta){
			return;
		}
	}

	int s = n.chs.size();
	FOR(i,s,n.legal_moves.size()){
		Node m = n;
		update(m,n.legal_moves[i],true);
		if(tni == NODE_LIMIT)return;
		tmp_nodes[tni] = m;
		n.chs.pb(tni);
		idx = tni;
		++tni;
		minimax(tmp_nodes[idx],sd-1);
		if(n.mx){
			if(tmp_nodes[idx].eval > n.eval){
				n.eval = tmp_nodes[idx].eval;
				n.best_move = n.legal_moves[i];
			}
			n.alpha = max(n.alpha,n.eval);
		}
		else{
			if(tmp_nodes[idx].eval < n.eval){
				n.eval = tmp_nodes[idx].eval;
				n.best_move = n.legal_moves[i];
			}
			n.beta = min(n.beta,n.eval);
		}
		if(n.alpha >= n.beta){
			return;
		}
	}
}

struct move player_move (struct move m) {
	update(cur,m,false);
	int search_depth = 0;
	struct move last_best_move;
	int last_eval;
	while(5*tni < NODE_LIMIT && search_depth < DEPTH_LIMIT){
		++search_depth;
		cur.alpha = INT_MIN;
		cur.beta = INT_MAX;
		minimax(cur,search_depth);
		if(tni == NODE_LIMIT){
			cur.best_move = last_best_move;
			cur.eval = last_eval;
			break;
		}
		last_best_move = cur.best_move;
		last_eval = cur.eval;
	}
	++turn;
	m = cur.best_move;
	update(cur,m,false);
    return m;
}
