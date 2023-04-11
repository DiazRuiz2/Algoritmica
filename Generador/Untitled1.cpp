#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<map>

static const int NUMS = 10;
using namespace std;
bool Sort_Second_Coordinate(const pair<pair<pair<int,int>,int>,int> &x, const pair<pair<pair<int,int>,int>,int> &y){
	
	return(x.first.first.second<y.first.first.second);
}

void muestra(vector<pair<pair<pair<int,int>,int>,int>>lista){
	
	for(int x=0; x<lista.size();x++){
		cout << lista[x].first.first.first << " " << lista[x].first.first.second << " " << lista[x].first.second << " " << lista[x].second << endl;
	}
	cout << endl << endl;
	
}
void DivideYVenceras(vector<pair<pair<int,int>,int>> &valores){
	
	
	if(valores.size()==1) return;
	
	auto mitad = valores.begin()+(valores.size()/2);
	vector<pair<pair<int,int>,int>> A(valores.begin(),(valores.begin()+valores.size()/2));
	vector<pair<pair<int,int>,int>> B((valores.begin()+valores.size()/2),valores.end());
	
	DivideYVenceras(A);
	DivideYVenceras(B);
	
	vector<pair<pair<pair<int,int>,int>,int>> lista;
	for(int x=0; x<A.size();x++){
		lista.push_back(pair<pair<pair<int,int>,int>,int>(A[x],-1));
	}

	for(int x=0; x<B.size();x++){
		lista.push_back(pair<pair<pair<int,int>,int>,int>(B[x],x));
	}
	
	sort(lista.begin(),lista.end(),Sort_Second_Coordinate);
	muestra(lista);
	
	int valores_iguales[NUMS] = {0};	
	int contador = 0;
	for(int x=0;x<lista.size();x++){
		if(lista[x].second ==-1){
			contador++;
			valores_iguales[lista[x].first.first.first]+=1;
		} 
		else if(x!=0){
			int contador_aux = contador;
			int pos = 0;
			while(lista[x-pos].first.first.second==lista[x].first.first.second){
				pos++;
				contador_aux--;
			}
			valores[(valores.size()/2)+lista[x].second].second += contador_aux-valores_iguales[lista[x].first.first.first];
		}
	}
	return;
	
	
}

int main(int argc,char ** argv){
	
	
	vector<pair<pair<int,int>,int>> valores(NUMS);
	
	srand(time(0));
	for (int x=0; x<NUMS;x++){
		int y = rand() %NUMS;
		int z = rand() %NUMS;
		pair<int,int> val(y,z);
		valores[x] = {val,0};
		
	}
	
	sort(valores.begin(),valores.end()); //Ordenamos primera coordenada.
	
	
	DivideYVenceras(valores);	
	
	for(int x=0; x<NUMS; x++){
		
		cout << valores[x].first.first << "  " << valores[x].first.second << " " << valores[x].second << endl;
	}
	
}
