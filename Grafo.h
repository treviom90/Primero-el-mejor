
#ifndef GRAFO_H
#define GRAFO_H
#include<iostream>
#include<queue>
#include<list>
#include<stack>


using namespace std;
class Arista;

class Vertice {
	Vertice* sig;
	Arista* ady;
	string nombre;
	friend class Grafo;
};

class Arista {
	Arista* sig;
	Vertice* ady;
	int peso;
	friend class Grafo;
};

class Grafo {
	Vertice* h;
	public:
		void Inicializa();
		bool Vacio();
		int Tamano();
		Vertice *GetVertice(string nombre);
		void InsertaArista(Vertice *origen, Vertice *destino, int peso);
		void InsertaVertice(string nombre);
		void ListaAdyacencia();
		void EliminarArista(Vertice *origen, Vertice *destino);
		void Anular();
		void EliminarVertice(Vertice *vert);
		void RecorridoAnchura(Vertice *origen);
		void RecorridoProfundidad(Vertice *origen);
		void PrimeroAnchura(Vertice *origen, Vertice *destino);
		void PrimeroProfundidad(Vertice *origen, Vertice *destino);
		void PrimeroMejor(Vertice *origen, Vertice *destino);

};
#endif
