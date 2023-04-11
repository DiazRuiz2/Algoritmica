#!/bin/bash 
#echo "" >> salida.dat

echo Introduce el intervalo de valores 
echo Valor mínimo:

read minimum_interval

echo Valor máximo: 
read maximum_interval

echo Numero de datos: 
read num_data

./generador_datos_archivos.exe $minimum_interval $maximum_interval $num_data

sleep 2
echo QUé caso quieres ver:
echo 1: Fuerza bruta
echo 2: DyV


read option
path="  datos.dat"

if [ $option -eq 1 ]; then 
     ./../Específico/especifico.exe $path

elif [ $option -eq 2 ]; then
    ./../DyV/dyv.exe $path
fi