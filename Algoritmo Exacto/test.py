#encoding: utf-8
import numpy as np
from numpy import *
from time import time
from random import randint,shuffle
import random
import sys
import os

from distutils.core import setup, Extension

ejecutable3 = "./tiempo"
archivo_salida3 = "tiempo1.dat"
temp_file="temp"

intancias=1
max_nodos=25
parametro_2=6

def generar_grafos(nodos, densidad_normal, max_clique=15, max_frontera=15,numero=None):
	n = int (nodos)
	m = int(n*(n-1)/2*densidad_normal)
	mat = [[0 for x in xrange(n)] for y in xrange(n)]
	#creo las aristas normales
	adyacencias=[(i, j) for i in range(n) for j in xrange(i+1,n)]
	shuffle(adyacencias)
	res=[]
	if(numero!=None):
		nombre=temp_file+str(numero)
	with open(nombre,'w') as f:
		f.write(str(n)+" "+str(m)+"\n") #escribo las ciudades y rutas
		#escribo las aristas
		for i in range(m):
			f.write(str(adyacencias[i][0]+1)+" "+str(adyacencias[i][1]+1)+"\n")
		f.close()

usage1 = "\nerror, parametros incorrectos\n\
modo de ejecucion python correr_experimentos.py t|a archivo_casos archivo_salida\n\
t para correr casos de prueba \n\
a para correr instancias aleatorias\n"

if __name__ == '__main__':
	from sys import argv
	from subprocess import call
	if(len(argv)<2):
		print usage1
		sys.exit()
	if(argv[1]=='t'):
		archivo_salida=archivo_salida3
		ejecutable=ejecutable3
		if(len(argv)>=3):
			with open(argv[2],'r') as in_file:
				#terminar archivo_casos
				if(len(argv)>=4):
					archivo_salida=argv[3]
				with open(archivo_salida, 'a') as f:
					for line in in_file:
						path, file_name = os.path.split(argv[2])
						test_name=line.split(" ")[0]
						test=path+"/"+test_name
						sol=line.split(" ",1)[1]
						print "Test "+test_name 
						call(ejecutable+str(" a < ")+test,stdout=f,shell=True)	
				f.close()
			in_file.close()
			sys.exit()
		else:
			print "error,falta el archivo de entrada"
			sys.exit()
	elif(argv[1]=="a"):
		ejecutable=ejecutable3
		archivo_salida=archivo_salida3
		prueba_nro=0
		if(len(argv)>=3):
			archivo_salida=argv[2]
		if not os.path.exists(archivo_salida):
			with open(archivo_salida, 'w') as f:
				f.write("nodos;aristas;resultado;tiempo;\n")
				f.close()
		with open(archivo_salida, 'a') as f:
			for nodos in range(5,max_nodos):
				for k in range(5,parametro_2,5):
					for i in range(intancias): #cantidad de instancias distintas para cada configuracion
						densidad=random.random()
						densidad=1
						generar_grafos(nodos,densidad,numero=prueba_nro)
						print "prueba:"+str(prueba_nro)
				 		call(ejecutable+str(" a < ")+temp_file+str(prueba_nro),stdout=f,shell=True)	
				 		prueba_nro=prueba_nro+1
		 	f.close()
	else:
		print usage1
		sys.exit()