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


string A,B,C,D,E,F,Tipe;
map<string,int> Table[4][6]; // Mapa bidimensional para yes & no.
int f[2]; // frecuencia de No & Yes

set<string> opc[6];

int main(){

  // Inicializando valores de las clases
  map<string,int> ID;
  string Array[4] = {"unacc","acc","good","vgood"};
  string Attrib[6] = {"buying","maint","doors","persons","lug_boot","safety"};
  vector<string> UnID(Array,Array+4);
  REP(i,4){ID[UnID[i]]=i;}

  ifstream myfile;
  myfile.open("car.data");
  string line;
  while(!myfile.eof()){
    
    getline(myfile,line);
    REP(i,line.size()){
      if(line[i]==','){
	line[i]=' ';
      }
    }
    istringstream ss(line);
    ss >> A >> B >> C >> D >> E >> F >> Tipe;
    
    opc[0].insert(A);
    opc[1].insert(B);
    opc[2].insert(C);
    opc[3].insert(D);
    opc[4].insert(E);
    opc[5].insert(F);
    

    f[ID[Tipe]]++;
    
    Table[ID[Tipe]][0][A]++;
    Table[ID[Tipe]][1][B]++;
    Table[ID[Tipe]][2][C]++;
    Table[ID[Tipe]][3][D]++;
    Table[ID[Tipe]][4][E]++;
    Table[ID[Tipe]][5][F]++;
  
  }

  myfile.close();
  
  // Escribiendo resultados
  set<string>::iterator it;
  
  int CopySumTotales=0;
  
  REP(cases,6){
    
    printf("Attributo: %s\n",Attrib[cases].c_str());
    printf("=============================\n");
    printf("Nombre     unacc  -  acc  -   good  -  vgood   =    Total \n");
    printf("=============================\n");
    
    
    // escribir frecuencias
    int sumaTotales=0;  
    int sumaCasos=0;
    
    for(it=opc[cases].begin();it!=opc[cases].end();it++){
      printf("%s   ",(*it).c_str());
      REP(j,4){
	sumaCasos+=Table[j][cases][*it];
	sumaTotales+=f[j];
	printf(" -- %d/%d ",Table[j][cases][*it],f[j]);
      }
      
      printf(" == %d/%d\n",sumaCasos,sumaTotales);
      
      CopySumTotales=sumaTotales;
      sumaTotales=0;
      sumaCasos=0;
    }
    
    // Escribir totales

    putchar ('\n');
    putchar ('\n');
    
    // int sz1 = Table[1][cases].size();
    // int sz2 = Table[0][cases].size();
    // for(it=opc[cases].begin();it!=opc[cases].end();it++){
    //   printf("%s    %d/%d -- %d/%d  == %d/%d \n",(*it).c_str(),Table[1][cases][*it],f[1],Table[0][cases][*it],f[0],Table[1][cases][*it]+Table[0][cases][*it],f[0]+f[1]);
    
  }

  REP(i,4){
    printf("P(%s)=%d/%d\n",Array[i].c_str(),f[i],CopySumTotales);
  }
  
  
  
  //Ahora la parte del testing.
  // Dado un conjunto de casos de prueba

  int nroImput=0;
  ifstream ftest;
  ftest.open("car-prueba2.data");
  while(!ftest.eof()){
    
    getline(ftest,line);
    REP(i,line.size()){ if(line[i]==',') line[i]=' ';}
    istringstream ss(line);
    
    ss >> A >> B >> C >> D >> E >> F;  // No se tiene el atributo Tipe
    

    vector<string> v ;
    v.push_back(A);
    v.push_back(B);
    v.push_back(C);
    v.push_back(D);
    v.push_back(E);
    v.push_back(F);
    //Hallamos probabilidad para ambos casos yes & no
    int sumClases=0;
    REP(i,4){
      sumClases+=f[i];
    }
    
    // Hallando Prob_x general
    double rpta=0;
    int Tclase=0;
    
    REP(i,4){
      double Prob_n = (double)Table[i][0][A]*Table[i][1][B]*Table[i][2][C]*Table[i][3][D]*Table[i][4][E]*Table[i][5][F]*f[i];
      if(Prob_n != 0.0)
	Prob_n /= (double)f[i]*f[i]*f[i]*f[i]*f[i]*f[i]*sumClases;
      
       // dbg(Prob_n);
      // Hallando los totales y sumandolos
      double Prob_x=1;
      REP(j,6){
	int sumaClases=0;
	REP(k,4){
	  sumaClases+=Table[k][j][v[j]];
	}
	Prob_x *= double(sumaClases);
      }
      
      Prob_x /= double(pow(sumClases,6));

       // dbg(Prob_x);

      if(rpta<Prob_n/Prob_x){
	rpta=Prob_n/Prob_x;
	Tclase=i;
      }
      
    }
    
    printf("Respuesta para la entrar %d: es la clase %s cont Prob=%lf\n",++nroImput,UnID[Tclase].c_str(),rpta);
  }
  
 
  return 0;
} 

