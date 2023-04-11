#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<map>
#include<chrono>


using namespace std;


struct Point2D{
	int eje_x;
	int eje_y;
};

struct Point_Value{
	Point2D point;
	int value;
};


bool Sort_Second_Coordinate(const pair<Point_Value,int> &x, const pair<Point_Value,int> &y){
	
	if(x.first.point.eje_y==y.first.point.eje_y){
		return (x.first.point.eje_x<y.first.point.eje_x);
	}
	return(x.first.point.eje_y<y.first.point.eje_y);
	
}

bool Sort_Struct(const Point_Value &x, const Point_Value &y){
	if(x.point.eje_x==y.point.eje_x) return (x.point.eje_y<x.point.eje_x);
	else return x.point.eje_x<y.point.eje_x;
}


void DivideYVenceras(vector<Point_Value> &valores, vector<vector<Point2D>> &dominados){
	
	//Caso base que devolvemos.
	if(valores.size()==1) return;
	//cout << dominados.size() << endl;
	//Dividimos el vector en dos partes.
	vector<Point_Value> A(valores.begin(),(valores.begin()+valores.size()/2));
	vector<Point_Value> B((valores.begin()+valores.size()/2),valores.end());
	
	vector<vector<Point2D>> dom_A(dominados.begin(),(dominados.begin()+dominados.size()/2));
	vector<vector<Point2D>> dom_B((dominados.begin()+dominados.size()/2),dominados.end());

	DivideYVenceras(A,dom_A);
	DivideYVenceras(B,dom_B);
	//cout << dominados.size() << endl;
	for(int x=0;x<A.size();x++){
		valores[x]=A[x];
	}
	for(int x=0;x<B.size();x++){
		valores[A.size()+x]=B[x];
	}
	
	for(int x=0; x<dom_A.size();x++){
		dominados[x]=(dom_A[x]);
	}
	
	for(int x=0; x<dom_B.size();x++){
		dominados[x]=(dom_B[x]);
	}
	
	/*Vector que almacena:
		first--> Punto y valor dominado en struct Point_Value
		second--> Posición original en el vector para los B, para los A, un 
				  indicador de que pertenece a este.
	*/
	vector<pair<Point_Value,int>> lista;
	
	//Introducimos valores de A y B en una lista para ordenarlos.
	for(int x=0; x<A.size();x++){//O(n)
		lista.push_back(pair<Point_Value,int>(A[x],-1));
	}

	for(int x=0; x<B.size();x++){//O(n)
		lista.push_back(pair<Point_Value,int>(B[x],x));
	}
	
	//Ordenamos la lista por la segunda coordenada.
	sort(lista.begin(),lista.end(),Sort_Second_Coordinate);//O(logn)
	
	
	/*
		Mapa donde guardamos número veces que aparece cada primera coordenada,
		para tenerlo en cuenta a la hora de sumar el número de puntos dominados
		ya que si tiene mismo valor eje_x--> NO DOMINA.
	*/
	
	map<int,int> valores_iguales;	
	int contador = 0;
	vector<Point2D> val_dominados;
	
	for(int x=0;x<lista.size();x++){//O(n)
		
		//si es un punto del vector A.
		if(lista[x].second ==-1){
			//Aumentamos contador números dominados.
			contador++;
			//Aumentamos número valores que son dominados y que tienen 
			//primera variable del valor del punto, algo que tendremos que 
			//tener en cuenta a la hora de sumar el número de puntos dominados.
			valores_iguales[lista[x].first.point.eje_x]+=1;
			val_dominados.push_back(lista[x].first.point);
			
		} 
		//Si es un punto del vector B y no es el primero.
		else if(x!=0){
			
			int contador_aux = contador;
			int pos = 1;
			while(lista[x-pos].first.point.eje_y==lista[x].first.point.eje_y){
				//Si nos vamos a meter en posiciones que no son del vector,
				// salimos.
				if(pos>x) break;
				//Si el punto previo tiene misma coordenada y y es de A, le 
				//restamos 1 al contador ya que no domina en este caso.
				if(lista[x-pos].second==-1)contador_aux--;
				pos++;
				
			}
			/*
				Aquí finalmente guardamos el número de puntos dominados, 
				teniendo en cuenta puntos con mismo eje_y(contador-contador_aux)
				y número de eje_x(valores_iguales...).
			*/	 
			valores[(valores.size()/2)+lista[x].second].value += contador_aux-valores_iguales[lista[x].first.point.eje_x];
			for(int y=0;y<val_dominados.size();y++){
				if(lista[x].first.point.eje_x!=val_dominados[y].eje_x && (lista[x].first.point.eje_y!=val_dominados[y].eje_y)){
					//cout << val_dominados[y].eje_x << " " << val_dominados[y].eje_y << " " << lista[x].first.point.eje_x << " " <<lista[x].first.point.eje_y <<  endl;
					dominados[dominados.size()/2+lista[x].second].push_back(val_dominados[y]);
				}
			}
		}
	}
	
	
	return;
	
	
}

int main(int argc,char ** argv){
	
	
	
	
	int n = 100000;
	vector<vector<Point2D>> dominados(n);
	vector<Point_Value> valores(n);
	srand(time(0));
	for (int x=0; x<n;x++){
		int y = rand() %n;
		int z = rand() %n;
		Point2D val = {y,z};
		valores[x] = {val,0};
		
	}

	
	sort(valores.begin(),valores.end(),Sort_Struct); //Ordenamos primera coordenada.
	
	std::chrono::high_resolution_clock::time_point t_antes2, t_despues2;
	t_antes2 = std::chrono::high_resolution_clock::now();
  	DivideYVenceras(valores,dominados);
	t_despues2 = std::chrono::high_resolution_clock::now();
  	
	auto transcurrido2 = std::chrono::duration_cast<std::
						chrono::duration<double>>(t_despues2 - t_antes2);
  	cout << "Número de datos: " << n << "  Tiempo transcurrido: "
	  	 << transcurrido2.count() << endl;
	
	
/*	for(int x=0; x<n; x++){
		
		cout << valores[x].point.eje_x << "  " << valores[x].point.eje_y << " " << valores[x].value << endl;
		cout << "Dominados: " << endl;
		for(int y=0; y<dominados[x].size();y++){
			cout << dominados[x][y].eje_x << " " << dominados[x][y].eje_y << endl;
		}
		cout << endl << endl;
	}*/
	
}
