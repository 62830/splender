int card_info[90][8] = {{0,0,2,0,0,1,4,0}, {1,1,0,0,0,2,3,0}, {2,0,1,1,1,2,3,0}, {3,1,1,1,0,1,1,0}, {4,1,1,2,1,0,3,0}, {5,0,0,4,0,0,3,1}, {6,0,0,1,2,2,0,0}, {7,4,0,0,0,0,1,1}, {8,0,0,2,1,0,3,0}, {9,2,0,2,1,0,3,0}, {10,0,1,0,1,3,2,0}, {11,1,2,0,0,2,2,0}, {12,0,2,1,2,0,4,0}, {13,1,3,0,1,0,4,0}, {14,0,0,2,2,0,0,0}, {15,1,1,0,3,0,0,0}, {16,2,0,0,0,2,1,0}, {17,3,0,1,0,1,1,0}, {18,3,0,0,0,0,1,0}, {19,0,2,1,1,1,4,0}, {20,0,4,0,0,0,4,1}, {21,0,0,2,0,2,3,0}, {22,1,1,1,1,0,3,0}, {23,1,0,0,0,2,2,0}, {24,0,0,0,4,0,0,1}, {25,1,0,0,2,0,0,0}, {26,0,0,0,0,4,2,1}, {27,0,1,1,2,1,1,0}, {28,2,1,2,0,0,1,0}, {29,1,1,1,0,1,4,0}, {30,2,2,0,0,0,4,0}, {31,0,1,3,0,1,3,0}, {32,1,1,1,0,1,2,0}, {33,1,1,0,1,1,0,0}, {34,0,1,1,2,1,0,0}, {35,0,3,0,0,0,4,0}, {36,0,3,0,0,0,2,0}, {37,2,0,0,1,0,1,0}, {38,0,0,3,0,0,3,0}, {39,0,0,0,3,0,0,0}, {40,0,0,5,0,0,0,2}, {41,0,0,2,3,2,2,1}, {42,3,0,2,0,2,4,1}, {43,6,0,0,0,0,4,3}, {44,0,1,2,4,0,2,2}, {45,2,0,0,3,3,1,1}, {46,2,4,0,0,1,3,2}, {47,0,2,3,0,2,0,1}, {48,0,0,6,0,0,0,3}, {49,0,2,2,0,3,1,1}, {50,5,0,0,3,0,4,2}, {51,3,0,5,0,0,0,2}, {52,0,2,4,1,0,0,2}, {53,0,3,2,3,0,3,1}, {54,0,0,0,0,5,1,2}, {55,3,2,0,0,3,4,1}, {56,4,2,1,0,0,4,2}, {57,0,0,0,6,0,2,3}, {58,0,6,0,0,0,3,3}, {59,0,0,0,3,5,1,2}, {60,5,0,0,0,0,4,2}, {61,2,3,0,2,0,3,1}, {62,0,5,0,0,0,4,2}, {63,0,0,0,5,0,2,2}, {64,0,0,0,5,3,2,2}, {65,3,2,3,0,0,0,1}, {66,0,2,1,0,4,1,2}, {67,0,5,3,0,0,3,2}, {68,3,0,0,3,2,2,1}, {69,0,0,0,0,6,1,3}, {70,0,0,3,3,6,3,4}, {71,0,3,5,3,3,4,3}, {72,3,6,0,3,0,0,4}, {73,0,0,0,0,7,3,4}, {74,0,7,0,0,0,0,4}, {75,3,3,0,3,5,3,3}, {76,0,0,3,7,0,1,5}, {77,0,0,7,0,0,4,4}, {78,6,0,3,0,3,2,4}, {79,0,3,6,0,3,4,4}, {80,3,0,3,6,0,1,4}, {81,0,3,0,0,7,3,5}, {82,3,3,0,5,3,1,3}, {83,5,3,3,0,3,2,3}, {84,7,0,0,3,0,2,5}, {85,0,7,0,0,3,0,5}, {86,7,0,0,0,0,2,4}, {87,0,0,0,7,0,1,4}, {88,3,0,7,0,0,4,5}, {89,3,5,3,3,0,0,3}};

#define ARENA
#include "splender2.cpp"
namespace arena{

vector<vector<card>> vc(3);
vector<card> svc(90);
vector<Node> tmp_nodes(2500);
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
	arena::list_legal_moves(n.plyr[1-n.mx],n.legal_moves,n.g,n.b);
}


int eval(Node &n){
	if(n.plyr[0].score >= 15)return 1e9;
	if(n.plyr[1].score >= 15)return -1e9;
	const int T = 100;
	const int est_turn = 30;
	const int est_decay_to = 30;
	int ps = 0;
	ps += n.plyr[0].score * est_turn * T / 15;
	ps += (n.plyr[0].gem[6] - n.plyr[0].gem[5]) * T / 3;
	ps += n.plyr[0].gem[5] * T / 2;
	int bns = 0;
	FOR(i,0,5)bns += n.plyr[0].bonus[i];
	bns = max(bns * T / 3, 2*bns*T - (5*turn*bns*T/3/est_decay_to));
	ps += bns;

	int qs = 0;
	qs += n.plyr[1].score * est_turn * T / 15;
	qs += (n.plyr[1].gem[6] - n.plyr[1].gem[5]) * T / 3;
	qs += n.plyr[1].gem[5] * T / 2;
	bns = 0;
	FOR(i,0,5)bns += n.plyr[1].bonus[i];
	bns = max(bns * T / 3, 2*bns*T - (5*turn*bns*T/3/est_decay_to));
	qs += bns;
	return ps - qs;
}

void minimax(Node &n,int sd){
	if(sd <= 0){
		n.eval = arena::eval(n);
		return;
	}
	if(!n.legal_moves.size()){
		arena::list_legal_moves(n);
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
	FOR(i,0,n.chs.size()){
		arena::minimax(tmp_nodes[n.chs[i]],sd-1);
		idx = n.chs[i];
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
			n.beta = max(n.beta,n.eval);
		}
		if(n.alpha >= n.beta){
			return;
		}
	}

	int s = n.chs.size();
	FOR(i,s,n.legal_moves.size()){
		Node m = n;
		arena::update(m,n.legal_moves[i],true);
		tmp_nodes[tni] = m;
		n.chs.pb(tni);
		idx = tni;
		++tni;
		arena::minimax(tmp_nodes[idx],sd-1);
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
			n.beta = max(n.beta,n.eval);
		}
		if(n.alpha >= n.beta){
			return;
		}
	}
}

struct move player_move (struct move m) {
	arena::update(cur,m,false);
	arena::minimax(cur,2);
	++turn;
	m = cur.best_move;
	arena::update(cur,m,false);
    return m;
}

	

}//namespace arena

int main(){
	vector<card>s1,s2,s3;
	card c;
	int n;
	cin>>n;
	FOR(i,0,40){
		c.id = card_info[i][0];
		FOR(j,0,5)c.cost[j] = card_info[i][j+1];
		c.gem = card_info[i][6];
		c.score = card_info[i][7];
		s1.pb(c);
	}
	FOR(i,40,70){
		c.id = card_info[i][0];
		FOR(j,0,5)c.cost[j] = card_info[i][j+1];
		c.gem = card_info[i][6];
		c.score = card_info[i][7];
		s2.pb(c);
	}
	FOR(i,70,90){
		c.id = card_info[i][0];
		FOR(j,0,5)c.cost[j] = card_info[i][j+1];
		c.gem = card_info[i][6];
		c.score = card_info[i][7];
		s3.pb(c);
	}
	auto seed = time(NULL);
	int win=0,broken = 0,all_moves = 0,score_win = 0,score_game = 0,score_moves = 0;
	FOR(i,0,n){
		shuffle(BE(s1),default_random_engine(seed));
		shuffle(BE(s2),default_random_engine(seed));
		shuffle(BE(s3),default_random_engine(seed));

		int winner = -1;
		int moves = 0;
		init(s1,s2,s3);
		arena::init(s1,s2,s3);
		struct move m;
		m.type = 0;
		while(true){
			m = player_move(m);
			++moves;
			if(m.type == -1){
				print("no move 0");
				winner = 1;
				break;
			}
			m = arena::player_move(m);
			++moves;
			if(m.type == -1){
				print("no move 1");
				winner = 0;
				++win;
				break;
			}
			if(arena::cur.plyr[1].score >= 15){
				winner = 0;
				++score_game;
				score_moves += moves;
				++score_win;
				++win;
				break;
			}
			if(arena::cur.plyr[0].score >= 15){
				winner = 1;
				++score_game;
				score_moves += moves;
				break;
			}
			if(moves >= 300){
				++broken;
				print("brkoen");
				break;
			}
		}
		all_moves += moves;
		print(winner);
		print(tmp_nodes_sum / all_moves * 2);
	}
	cout<<win<<'/'<<n<<' '<<broken<<endl;
	cout<<score_win<<'/'<<score_game<<endl;
	float avg_turn = all_moves * 1.0 / n / 2;
	float avg_score_turn  = score_moves *1.0 / score_game / 2;
	print(avg_turn);
	print(avg_score_turn);
	return 0;
}
