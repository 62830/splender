#define NODE_LIMIT 100000
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
	bool id = 0;
	char gem[7] = {0,0,0,0,0,0,0};
	char score = 0;
	char bonus[5] = {0,0,0,0,0};
	char res[3] = {-1,-1,-1};
	Player(bool i){id = i;}
};
ostream& operator <<(ostream& O,struct Player p){
	return O<<"id: "<<p.id<<
		" gem[6]: "<<(int)p.gem[0]<<(int)p.gem[1]<<(int)p.gem[2]<<(int)p.gem[3]<<(int)p.gem[4]<<(int)p.gem[5]<<
		" bonus[5]: "<<(int)p.bonus[0]<<(int)p.bonus[1]<<(int)p.bonus[2]<<(int)p.bonus[3]<<(int)p.bonus[4]<<
		" score: "<<(int)p.score<<
		" res: "<<(int)p.res[0]<<' '<<(int)p.res[1]<<' '<<(int)p.res[2];
}
struct M{
	unsigned char c;
	M(){}
	M(struct move m){
		if(m.type == 2){
			c = 128 + m.card_id;
		}
		else if(m.type == 1){
			c = 0;
			FOR(i,0,5){
				c <<= 1;
				c += m.gem[i];
			}
			c += 90;
		}
		else if(m.type == 3){
			c = m.card_id;
		}
		else c = 255;
	}
};
struct move M2move(M m){
	struct move re;
	if(m.c==255){
		re.type = -1;
		return re;
	}
	else if(m.c >= 128){
		re.type = 2;
		re.card_id = m.c - 128;
	}
	else if(m.c >= 90){
		re.type = 1;
		bool flag = false;
		FOR(i,1,6)
			if(m.c == 90 + (1<<i)){
				re.gem[5-i] = 2;
				flag = true;
			}
			else re.gem[5-i] = 0;
		if(flag)return re;
		FOR(i,0,5)
			if((m.c-90) & (1<<i))
				re.gem[4-i] = 1;
			else re.gem[4-i] = 0;
	}
	else{
		re.type = 3;
		re.card_id = m.c;
	}
	
	return re;
}
ostream& operator<<(ostream& O,M m){
	return O<<M2move(m);
}

struct Node{
	int eval,alpha = INT_MIN,beta = INT_MAX;
	bool mx = false;
	M best_move;
	Player plyr[2] = {Player(0),Player(1)};
	vector<char>g,vci;
	vector<vector<char>>b;
	vector<int> chs;
	vector<M> legal_moves;
	Node(){
		g = vector<char>(6,4);
		vci = vector<char>(3,4);
		b = vector<vector<char>>(3,vector<char>(4,-1));
	}
};

namespace {

int search_depth = 0;
vector<vector<card>> vc(3);
vector<card> svc(90);
vector<Node> tmp_nodes(NODE_LIMIT);
vector<float> gem_value(5,1);
Node cur;
int turn = 0,tni = 0;
void update(Node &n,M cm,bool search){
	struct move m = M2move(cm);
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
			dif = min(p->gem[i],(char)max(0,c.cost[i] - p->bonus[i]));
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
	n.best_move.c = 255;
	n.mx = !n.mx;
	if(!search){
		tni = 0;
		n.alpha = INT_MIN;
		n.beta = INT_MAX;
	}
}

int wild_needed(int card_id,Player &p){
	card c = svc[card_id];
	int wild = 0;
	FOR(k,0,5)
		wild += max(0,c.cost[k] - p.bonus[k] - p.gem[k]);
	return wild;
}

void list_legal_moves(Player &p,vector<M> &v,vector<char> &g,vector<vector<char>> &b){
	int gemsum = p.gem[6];
	struct move m;
	//list buy
	m.type = 2;
	FOR(i,0,3){
		FOR(j,0,4){
			if(wild_needed(b[i][j],p) <= p.gem[5]){
				m.card_id = b[i][j];
				v.pb(M(m));
			}
		}
	}
	FOR(i,0,3){
		if(p.res[i] == -1)continue;
		if(wild_needed(p.res[i],p) <= p.gem[5]){
			m.card_id = p.res[i];
			v.pb(M(m));
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
				v.pb(M(m));
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
					v.pb(M(m));
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
				v.pb(M(m));
			}
		}
	}
	if(!v.size()){
		m.type = -1;
		v.pb(M(m));
	}
}
void list_legal_moves(Node &n){
	list_legal_moves(n.plyr[1-n.mx],n.legal_moves,n.g,n.b);
}

int eval_plyr(Node &n,int idx,int sd){
	if(n.plyr[idx].score >= 15)return 1e9 + DEPTH_LIMIT + sd - search_depth;
	const int T = 100;
	const int est_turn = 20;
	const int est_decay_to = 20;
	int ps = 0;
	ps += n.plyr[idx].score * est_turn * T / 15;
	FOR(i,0,5)
		ps += n.plyr[idx].gem[i]*gem_value[i]*T/3;
	ps += n.plyr[idx].gem[5] * T / 2;
	int bns = 0;
	FOR(i,0,5)bns += n.plyr[idx].bonus[i] * gem_value[i] * T;
	bns = max(bns / 3, 2*bns - (5*turn*bns/3/est_decay_to));
	ps += bns;
	return ps;
}

int eval(Node &n,int sd){
	int tmp = eval_plyr(n,0,sd);
	if(tmp >= 1e9)return tmp;
	int tmp2 = eval_plyr(n,1,sd);
	if(tmp2 >= 1e9)return -tmp2;
	return tmp - tmp2;
}

vi argsort_chs(Node &n){
	vi re(n.chs.size());
	iota(BE(re),0);
	if(n.mx)
		sort(BE(re),[&](int a,int b){return tmp_nodes[n.chs[a]].eval > tmp_nodes[n.chs[b]].eval;});
	else
		sort(BE(re),[&](int a,int b){return tmp_nodes[n.chs[a]].eval < tmp_nodes[n.chs[b]].eval;});
	return re;
}

void minimax(Node &n,int sd){
	if(sd <= 0 || n.plyr[0].score >= 15 || n.plyr[1].score >= 15){
		n.eval = eval(n,sd);
		return;
	}
	if(!n.legal_moves.size()){
		list_legal_moves(n);
		sort(BE(n.legal_moves),[&](M &a,M &b){return (svc[a.c-128].score > svc[b.c-128].score) || (svc[a.c-128].score == svc[b.c-128].score && a.c > b.c);});
	}
	if(n.legal_moves[0].c == 255){
		n.eval = 1e9 + DEPTH_LIMIT + sd - search_depth;
		if(n.mx)n.eval = - n.eval;
		if(n.mx)n.alpha = max(n.alpha,n.eval);
		else n.beta = min(n.beta,n.eval);
		return;
	}
	if(n.mx) n.eval = -2e9;
	else n.eval = 2e9;

	int idx;
	vi move_order = argsort_chs(n);
	for(auto i:move_order){
		if(tni == NODE_LIMIT)return;
		idx = n.chs[i];
		tmp_nodes[idx].alpha = n.alpha;
		tmp_nodes[idx].beta = n.beta;
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
		if(tni == NODE_LIMIT)return;
		update(m,n.legal_moves[i],true);
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

}//namespace 

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



struct move player_move (struct move mv) {
	M m(mv);
	update(cur,m,false);
	search_depth = 0;
	M last_best_move;
	int last_eval;
	int last_tni = 1;
	while((search_depth&1?2:10)*tni < NODE_LIMIT && search_depth < DEPTH_LIMIT){
		++search_depth;
		cur.alpha = INT_MIN;
		cur.beta = INT_MAX;
		minimax(cur,search_depth);
		if(tni == NODE_LIMIT){
			cur.best_move = last_best_move;
			cur.eval = last_eval;
			--search_depth;
			break;
		}
		last_best_move = cur.best_move;
		last_eval = cur.eval;
		last_tni = tni;
	}
	++turn;
	m = cur.best_move;
	mv = M2move(m);
	update(cur,m,false);
    return mv;
}
