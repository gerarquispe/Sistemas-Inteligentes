#include <bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define ii pair<int,int>
#define vii vector<ii>
#define REPN(i,x,y) for(int i=x;i<y;i++)
#define REP(i,y) REPN(i,0,y)
#define REPR(i,y,x) for(int i=y;i>=x;i--)
#define CLR(A,x) memset(A,x,sizeof(A))
#define INF (1<<30)
#define EPS (1e-9)
#define ones(x) __builtin_popcount(x)
#define ALL(v) (v).begin(),(v).end()
#define RALL(v) (v).rbegin(),(v).rend()
#define pb push_back
#define mp make_pair
#define sqr(x) (x)*(x)
#define dbg(x) cout << #x << " = " << x << endl
#define dbg2(x,y)cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define dbg3(x,y,z)cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define S(x)scanf("%d\n",&x)
#define SS(str) scanf("%[^\n]\n",str)
#define S2(x,y)scanf("%d %d\n",&x,&y)
#define SC(x)scanf("%d",&x)
#define SC2(x,y)scanf("%d %d",&x,&y)
#define P(x)printf("%d\n",x)
#define SZ(v) v.size()
#define f first
#define s second
#define MOD 100007
#define MAXN 100005

using namespace std;

string i2s(int x) { stringstream ss; ss << x; return ss.str();}
int s2i(string str) { istringstream ss(str);int nro; ss >> nro; return nro;}


string A,B,C,D,Tipe;
map<string,int> Table[2][4]; // Mapa bidimensional para yes & no.
int f[2]; // frecuencia de No & Yes

set<string> opc[4];

int main(){


  while(cin >> A >> B >> C >> D >> Tipe){
    
    opc[0].insert(A);
    opc[1].insert(B);
    opc[2].insert(C);
    opc[3].insert(D);
    
    if(Tipe=="No"){
      f[0]++;
      
      Table[0][0][A]++;
      Table[0][1][B]++;
      Table[0][2][C]++;
      Table[0][3][D]++;
      
    } else {
      f[1]++;
      
      Table[1][0][A]++;
      Table[1][1][B]++;
      Table[1][2][C]++;
      Table[1][3][D]++;
    }
  }

  // Escribiendo resultados

  set<string>::iterator it;


  REP(cases,4){
    
    printf("Caso %d\n",cases);
    printf("=============================\n");
    printf("Nombre  YES   NO       Total \n");
    printf("=============================\n");
    int sz1 = Table[1][cases].size();
    int sz2 = Table[0][cases].size();
    for(it=opc[cases].begin();it!=opc[cases].end();it++){
      printf("%s    %d/%d -- %d/%d  == %d/%d \n",(*it).c_str(),Table[1][cases][*it],f[1],Table[0][cases][*it],f[0],Table[1][cases][*it]+Table[0][cases][*it],f[0]+f[1]);
    }
    	
    putchar ('\n');
    putchar ('\n');
    
  }

  printf("P(Yes)=%d/%d\n",f[1],f[0]+f[1]);
  printf("P(No)=%d/%d\n",f[0],f[0]+f[1]);


  //Ahora la parte del testing.

  // Dado un caso de prueba tenemos.
  
  A ="Sunny";B="Cool"; C="High";D="Strong";
  
  //Hallamos probabilidad para ambos casos yes & no

  double Prob_yes = double(Table[1][0][A]*Table[1][1][B]*Table[1][2][C]*Table[1][3][D]) / (f[1]*f[1]*f[1]*f[1]) * f[1] / double(f[0]+f[1]);
  double Prob_no = double(Table[0][0][A]*Table[0][1][B]*Table[0][2][C]*Table[0][3][D]) / (f[0]*f[0]*f[0]*f[0]) * f[0] / double(f[0]+f[1]);

  dbg2(Prob_yes,Prob_no);
  
  double denominador = double(f[0]+f[1]);
  denominador = denominador*denominador*denominador*denominador;
  double Prob_x = double(Table[1][0][A]+Table[0][0][A])*(Table[1][1][B]+Table[0][1][B])*(Table[1][2][C]+Table[0][2][C])*(Table[1][3][D]+Table[0][3][D])/(denominador);
  dbg(Prob_x);

  double rpta = max(Prob_yes/Prob_x,Prob_no/Prob_x);

  dbg(rpta);

  if(Prob_yes/Prob_x > Prob_no/Prob_x)
    printf("Respuesta: Yes\n");
  else
    printf("Respuesta: No\n");
  
  return 0;
} 

