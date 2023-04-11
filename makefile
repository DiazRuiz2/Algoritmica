

dyv: ./DyV/dyv.cpp
	g++ -o dyv.exe ./DyV/dyv.cpp

especifico : ./Específico/especifico.cpp
	g++ -o especifico.exe ./Especifico/especifico.cpp

generador_datos_archivo: ./Generador/generador_datos_archivo.cpp
	g++ -o generador_datos_archivo.exe ./Generador/generador_datos_archivo.cpp


