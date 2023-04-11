#include<iostream>
#include<set>
#include<fstream>
#include<ctime>
using namespace std;

int main(int argc, char ** argv){
	
	if(argc!=4){
		cout << "Introduce rango de valores correcto. " << endl;
		exit(1);
	}
	
	int min_val = atoi(argv[1]);
	int max_val = atoi(argv[2]);
	int num_data = atoi(argv[3]);
	
	
	if(min_val>max_val){
		int aux = min_val;
		min_val = max_val;
		max_val = aux;
		
	}
	srand(time(0));
	ofstream write("datos.dat");
	
	if(write.is_open()){
		
		for(int x=0; x<num_data;x++){
			
			int eje_x = min_val + (rand() % (max_val-min_val+1));
			int eje_y = min_val + (rand() % (max_val-min_val+1));
			
			write << eje_x;
			write << endl;
			write << eje_y;
			write << endl;
		}
		
		write << -1;
		write.close();
	}
	
	else cout << "No ha abierto nada" << endl;
	
	
	
	
}
