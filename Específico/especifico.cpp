#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<chrono>
using namespace std;

void Fuerzabruta(const vector<pair<int,int>> &valores, vector<pair<pair<int,int>,vector<pair<int,int>>>> &resultado ){
		
				
		for(int i=0; i < valores.size(); i++){ //O(n)
			//Creamos vector con las superaciones.
			vector<pair<int,int>> superaciones;	
			for(int j=0; j < valores.size(); j++){//O(n)
				if(i==j) continue; 
				if(valores.at(i).first > valores.at(j).first && valores.at(i).second > valores.at(j).second){
					
					superaciones.push_back(valores.at(j));
				}
			}

			pair<pair<int,int>,vector<pair<int,int>>> val(valores[i],superaciones);
			resultado.push_back(val);
		

		}
}



int main(int argc, char ** argv){
	
	int contador = 0;
		set<pair<int,int>> valores_set;
	
	if(argc!=2) exit (1);
	ifstream leer;
	leer.open(argv[1]);
	
	if(leer.is_open()){
		
		int z;
		do{
			
			leer >> z;
			if(z!=-1){
				int y; 
				leer >> y;
				
				pair<int,int> valor = {z,y};
				valores_set.insert(valor);
				contador ++;
			}
		
		}while(z!=-1);
	}
	
	
	

	//Pasamos los valores del set donde están ordenados, directamente a un vector
	// que será la estructura que usemos para el algoritmo.
	
	vector<pair<int,int>> valores;
	
	auto pos = valores_set.begin();
	
	while(pos!=valores_set.end()){
		
		valores.push_back((*pos));
		++pos;
		
		
	}
	
	/*Como prerequisito para usar este algoritmo de ordenación, pediremos que
	  el conjunto de datos dado, este ordenado en su primera coordenada, y para
	  ello usaremos la estrcutura set de la STL que tiene justo el funcionamiento
	  que buscamos */
	 
	 
	vector<pair<pair<int,int>,vector<pair<int,int>>>>  res;
	
	
	 
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	t_antes = std::chrono::high_resolution_clock::now();
	Fuerzabruta(valores,res);
	t_despues = std::chrono::high_resolution_clock::now();
	auto transcurrido = std::chrono::duration_cast<std::
						chrono::duration<double>>(t_despues - t_antes);
	cout << "Número de datos: " << contador << "  Tiempo transcurrido: "
		 << transcurrido.count() << endl;
		 
		 int opcion;
	do{
		cout << "¿Quieres ver resultados específicos?" << endl << "0:NO" << endl	
		 << "1:SI" << endl;
		 cin >> opcion;
	
	}while(opcion!=0 && opcion!=1);
	
	//Caso que queramos saber si funcionamiento de DyV es correcto.
	if(opcion==1){
		cout << "Resultados:  " << endl;
		for(int x = 0; x < res.size(); x++){
			
			cout << res[x].first.first << " " << res[x].first.second  << " "
				 << res[x].second.size() << endl;
		}
		
		
		
	}
	
}
