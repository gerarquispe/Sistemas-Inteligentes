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

  // Inicializando valores de las clases
  map<string,int> ID;
  vector<string> UnID;
  string ss1 = "No";
  ID[ss1] = 0;
  UnID.pb(ss1);
  ss1 = "Yes";
  ID[ss1] = 1;
  UnID.pb(ss1);

  ifstream myfile;
  myfile.open("training.in");
  string line;
  while(!myfile.eof()){
    
    getline(myfile,line);
    istringstream ss(line);
    ss >> A >> B >> C >> D >> Tipe;
    
    opc[0].insert(A);
    opc[1].insert(B);
    opc[2].insert(C);
    opc[3].insert(D);
    

    f[ID[Tipe]]++;
    
    Table[ID[Tipe]][0][A]++;
    Table[ID[Tipe]][1][B]++;
    Table[ID[Tipe]][2][C]++;
    Table[ID[Tipe]][3][D]++;
  
  }

  myfile.close();
  
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

  // Dado un conjunto de casos de prueba

  int nroImput=0;
  ifstream ftest;
  ftest.open("test.in");
  while(!ftest.eof()){
    
    getline(ftest,line);
    istringstream ss(line);
    ss >> A >> B >> C >> D ;  // No se tiene el atributo Tipe
    

    vector<string> v ;
    v.push_back(A);
    v.push_back(B);
    v.push_back(C);
    v.push_back(D);
    //Hallamos probabilidad para ambos casos yes & no
    int sumClases=0;
    REP(i,2){
      sumClases+=f[i];
    }
    // Hallando Prob_x general
    
    double rpta=0;
    int Tclase=0;
    
    REP(i,2){
      double Prob_n = double(Table[i][0][A]*Table[i][1][B]*Table[i][2][C]*Table[i][3][D]) / (f[i]*f[i]*f[i]*f[i]) * f[i] / double(sumClases);
      // Hallando los totales y sumandolos
      double Prob_x=1;
      REP(j,4){
	int sumaClases=0;
	REP(k,2){
	  sumaClases+=Table[k][j][v[j]];
	}
	Prob_x *= double(sumaClases);
      }
      
      Prob_x /= double(pow(sumClases,4));
      // dbg(Prob_x);
      // dbg(Prob_n);
      if(rpta<Prob_n/Prob_x){
	rpta=Prob_n/Prob_x;
	Tclase=i;
      }
      
    }
    
    printf("Respuesta para la entrar %d: es la clase %d=%s\n",++nroImput,Tclase,UnID[Tclase].c_str());
  }

  return 0;
} 

