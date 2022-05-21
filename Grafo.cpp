
#include "Grafo.h"

void Grafo::Inicializa() {
	h = NULL;
}

bool Grafo::Vacio() {
	if (h == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int Grafo::Tamano() {
	int cont = 0;
	Vertice *aux;
	aux = h;
	while (aux != NULL) {
		cont++;
		aux = aux->sig;
	}
	return cont;
}

Vertice *Grafo::GetVertice(string nombre) {
	Vertice *aux;
	aux = h;
	while (aux != NULL) {
		if (aux->nombre == nombre) {
			return aux;
		}
		aux = aux->sig;
	}
	return NULL;
}

void Grafo::InsertaVertice(string nombre) {
	Vertice *nuevo = new Vertice;
	nuevo->nombre = nombre;
	nuevo->sig = NULL;
	nuevo->ady = NULL;

	if (Vacio()) {
		h = nuevo;
	}
	else {
		Vertice* aux;
		aux = h;
		while (aux->sig!=NULL) {
			aux=aux->sig;
		}
		aux->sig = nuevo;
	}
}

void Grafo::InsertaArista(Vertice *origen, Vertice *destino, int peso) {
	Arista *nueva = new Arista;
	nueva->peso = peso;
	nueva->sig = NULL;
	nueva->ady = NULL;

	Arista *aux;
	aux = origen->ady;
	if (aux == NULL) {
		origen->ady = nueva;
		nueva->ady = destino;
		//cout<<"El origen no tiene aristas"<<endl
	}
	else{
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nueva;
		nueva->ady = destino;
	}
}

void Grafo::ListaAdyacencia() {
	Vertice *VerAux;
	Arista *ArisAux;

	VerAux = h;

	while (VerAux!=NULL) {
		cout << VerAux->nombre << "->";
		ArisAux = VerAux->ady;
		while (ArisAux!=NULL) {
			cout << ArisAux->ady->nombre << "->";
			ArisAux = ArisAux->sig;
		}
		VerAux = VerAux->sig;
		cout << endl;
	}
}

void Grafo::Anular() {
	Vertice *aux;
	while (h!=NULL) {
		aux = h;
		h = h->sig;
		delete(aux);
	}
}

void Grafo::EliminarArista(Vertice *origen, Vertice *destino) {
	int band = 0;
	Arista *actual, *anterior;
	actual = origen->ady;

	if (actual==NULL) {
		cout << "El vertice origen no tiene aristas" << endl;
	}
	else if(actual->ady==destino){
		origen->ady = actual->sig;
		delete(actual);
	}
	else {
		while (actual != NULL) {
			if (actual->ady==destino) {
				band = 1;
				anterior->sig = actual->sig;
				delete(actual);
				break;
			}
			anterior = actual;
			actual = actual->sig;
		}
		if(band==0){
			cout << "Esos dos vertices no estan conectados" << endl;
		}
	}
}

void Grafo::EliminarVertice(Vertice *vert) {
	Vertice *actual, *anterior;
	Arista *aux;

	actual = h;
	while (actual!=NULL) {
		aux = actual->ady;
		while (aux!=NULL) {
			if (aux->ady==vert) {
				EliminarArista(actual,aux->ady);
				break;
			}
			aux=aux->sig;
		}
		actual = actual->sig;

	}
	actual = h;
	if (h==vert) {
		h = h->sig;
		delete(actual);
	}
	else {
		while (actual!=vert) {
			anterior = actual;
			actual = actual->sig;
		}
		anterior->sig = actual->sig;
		delete(actual);
	}
}

void Grafo::RecorridoAnchura(Vertice *origen){
    int band,band2;
    Vertice *actual;
    queue<Vertice*> cola;
    list<Vertice*> lista;
    list<Vertice*>::iterator i;

    cola.push(origen);

    while(!cola.empty()){
        band=0;
        actual=cola.front();
        cola.pop();

        for(i=lista.begin();i!=lista.end();i++){
                if(*i== actual){
                    band=1;
                }
        }
        if(band==0){
            cout<<actual->nombre<<",";
            lista.push_back(actual);

            Arista *aux;
            aux= actual->ady;
            while(aux!=NULL){
                band2=0;

               for(i=lista.begin();i!=lista.end();i++){
                    if(aux->ady==*i){
                        band2=1;
                    }
               }

                if(band2==0){
                    cola.push(aux->ady);
                }
                aux=aux->sig;
            }
        }
    }
}

void Grafo::RecorridoProfundidad(Vertice *origen){
    int band,band2;
    Vertice *actual;
    stack<Vertice*> pila;
    list<Vertice*> lista;
    list<Vertice*>::iterator i;


    pila.push(origen);
    while(!pila.empty()){
        band=0;
        actual=pila.top();
        pila.pop();

        for(i=lista.begin();i!=lista.end();i++){
            if(*i==actual){
                band=1;
            }
        }
        if(band==0){
            cout<<actual->nombre<<",";
            lista.push_back(actual);

            Arista *aux;
            aux=actual->ady;

            while(aux!=NULL){
                    band2=0;
                for(i=lista.begin();i!=lista.end();i++){
                      if(*i==aux->ady){
                        band2=1;
                      }
                }
                if(band2==0){
                    pila.push(aux->ady);
                }
                aux=aux->sig;
            }
        }
    }
}

void Grafo::PrimeroAnchura(Vertice *origen, Vertice *destino){

    int band,band2,band3=0;
    Vertice *VerticeActual, *DestinoActual;
    Arista *aux;
    typedef pair<Vertice*, Vertice*> VerticeVertice;
    queue<Vertice*> cola;
    stack<VerticeVertice> pila;
    list<Vertice*> lista;
    list<Vertice*>::iterator i;

    cola.push(origen);
    while(!cola.empty()){
        band=0;
        VerticeActual = cola.front();
        cola.pop();
        for(i=lista.begin();i!=lista.end();i++){
            if(VerticeActual == *i){
                band=1;
            }
        }
        if(band==0){
            if(VerticeActual == destino){
                band3=1;
                DestinoActual = destino;

                while(!pila.empty()){
                    cout<<DestinoActual->nombre<<"<-";

                    while(!pila.empty() && pila.top().second != DestinoActual){
                        pila.pop();
                    }
                    if(!pila.empty()){
                        DestinoActual = pila.top().first;
                    }
                }
                break;
            }
            lista.push_back(VerticeActual);

            aux = VerticeActual->ady;
            while(aux!=NULL){
                band2=0;
                for(i=lista.begin();i!=lista.end();i++){
                        if(aux->ady == *i){
                            band2=1;
                        }
                }
                if(band2==0){
                    cola.push(aux->ady);
                    pila.push(VerticeVertice(VerticeActual,aux->ady));
                }
                aux=aux->sig;
            }
        }
    }
    if(band3==0){
        cout<<"No hay una ruta entre esos dos vertices"<<endl;
    }
}

void Grafo::PrimeroProfundidad(Vertice *origen, Vertice *destino){

    int band,band2,band3=0;
    Vertice *VerticeActual, *DestinoActual;
    Arista *aux;
    typedef pair<Vertice*, Vertice*> ParVertice; //declarar para almacenar pareja de evrtices
    stack<Vertice*> pila;//pila de vertices
    list<Vertice*> lista;//lista de vertices
    stack<ParVertice> PilaPar; //pila para pares de vertices
    list<Vertice*>::iterator i;

    //colocar el vertice en la pila
    pila.push(origen);
    //mientras la pila no este vacia
    while(!pila.empty()){
        band=0;
        //desapilar un vertice, sera el vertice actual
        VerticeActual= pila.top();
        pila.pop();
        //si el vertice actual no ha sido visitado
        for(i=lista.begin();i!=lista.end();i++){
            if(VerticeActual==*i){//si es igual al elemento recorrido al de la otra lista
               band=1;
            }
        }
        if(band==0){//no ha encontrado ese vertice en visitados
            if(VerticeActual==destino){
                band3=1; //hay camino
               //mostramos ruta encontrada
               DestinoActual= destino;
               while(!PilaPar.empty()){
                    cout<<DestinoActual->nombre<<"<-";
                    while(!PilaPar.empty()&& PilaPar.top().second !=DestinoActual){
                       PilaPar.pop();
                    }
                    if(!PilaPar.empty()){
                        DestinoActual= PilaPar.top().first;
                    }
               }
               break;
            }
            lista.push_back(VerticeActual);
            aux=VerticeActual->ady;
            while(aux!=NULL){
                band2=0;
                for(i=lista.begin();i!=lista.end();i++){
                    if(aux->ady == *i){
                      band2=1;//existe
                    }
                }
                if(band2==0){
                    pila.push(aux->ady);
                    PilaPar.push(ParVertice(VerticeActual,aux->ady));
                }
                aux=aux->sig;
            }
        }
    }
    if(band3==0){
        cout<<"No hay una ruta entre esos dos vertices"<<endl;
    }
}

//Comparar peso
bool Comparacion(pair<Vertice*, int> a, pair<Vertice*, int> b){
    return a.second < b.second;
}

void Grafo::PrimeroMejor(Vertice *origen, Vertice *destino){

    int CostoActual=0,band,band2=0;
    Vertice *VerticeActual, *DestinoActual;
    Arista *aux;
    //Declaramos lista de par lista y costo , enteros
    typedef pair<Vertice*, int> VerticeCosto;
    typedef pair<Vertice*, Vertice*> VerticeVertice;//para la pila
    list<VerticeCosto> ListaCostos;// lista costos
    list<VerticeCosto> ListaOrdenada;//lista costos ordenada
    stack<VerticeVertice> pila; // pila que almacena datos origen/destino
    list<VerticeCosto>::iterator i,j;

    // colocar el vertice origen en una lista costos y asociar a este un costo cero
    ListaCostos.push_back(VerticeCosto(origen,0));
    ListaOrdenada.push_back(VerticeCosto(origen,0));//lo mismo para ordenada

    //Mientras Lista ordenada no este vacia
    while(!ListaOrdenada.empty()){
        //obtenemos el primer vertice de lista ordenada
        //lo hacemos el actual y el costo asociado a este
        //tambien lo hacemos costo actual-> declaramos otro vertice y entero
        VerticeActual = ListaOrdenada.front().first;
        CostoActual = ListaOrdenada.front().second;
        //eliminamos el vertice de la lista
        ListaOrdenada.pop_front();

        //si el vertice actual es igual al vertice destino
        if(VerticeActual == destino){
            cout<<"Costo: "<<CostoActual<<endl;
            band2=1; //hay ruta
            //mostramos ruta encontrada

            // el vertice destino se convierte en destino actual
            //declaramos destino actual
            DestinoActual = destino;
            //mientras la pila  no este vacia
            while(!pila.empty()){
                //imprimir el destino actual
                cout<<DestinoActual->nombre<<"<-";

                //mientras la pila no este vacia y el vertice en el tope de la pila
                //sea distinto del destino actual
                while(!pila.empty() && pila.top().second !=DestinoActual){
                    //desapilamos
                    pila.pop();
                }
                // si la pila no esta vacia
                if(!pila.empty()){
                    // el vertice origen en el tope de la pila se convierte
                    //en el destino actual
                    DestinoActual = pila.top().first;
                }
            }
            break;
        }
        //para cada vertice que el vertice actual tiene como destino
        //declaramos arista auxiliar
        aux = VerticeActual->ady;
        while(aux!=NULL){
            band=0;//no se encuentra en la lista de costos
            //calcular el costo del vertce destino , sumando su costo al costo actual
            CostoActual= CostoActual+aux->peso;
            //declaramos iterador
            for(i=ListaCostos.begin();i!=ListaCostos.end();i++){
                //si el vertice no se encuentra en la lista de costos
                if(aux->ady == i->first){ // si en el adyacente es igual al elemento que estamos recorriendo en la lista
                  //declaramos bandera band
                  band=1;//se encuentra en la lista de costos

                  //de lo contrario: si el nuevo costo es menor al costo que tiene asociado
                  //el vertice en la lista de costos
                  if(CostoActual < i->second){
                    //actualizar el costo del vertice en la lista de costos con el nuevo costo
                        (*i).second = CostoActual;
                        //Tambien en la lista Ordenada
                        //declaramos otro iterador
                        for(j=ListaOrdenada.begin();j!=ListaOrdenada.end();j++){
                            if(j->first == aux->ady){
                                //si son iguales , actualizamos lista ordenada
                                (*j).second = CostoActual;
                            }
                        }
                    //**CADA QUE INGRESEMOS UN NUEVO COSTO LO TENEMOS QUE ORDENAR PARA ESO ES LA FUNCION CAMPARACION**
                    ListaOrdenada.sort(Comparacion);
                    //apilamos pareja vertice actual y vertice destino
                    pila.push(VerticeVertice(VerticeActual,aux->ady));
                    //**AQUI DEBEMOS CALCULAR DE NUEVO EL COSTO ACTUAL**
                    //por que va a estar sumando todas las opciones de camino,
                    //cuando unicamente debe de ir sumando los pesos mas chicos
                    CostoActual= CostoActual- aux->peso;
                  }

                }
            }
            if(band==0){//si sigue siendo 0 al terminar de recorrer la lista
                //no esta en la lista de costos
                //insertar el vertice en la lista de costos, asociando el nuevo costo
                ListaCostos.push_back(VerticeCosto(aux->ady,CostoActual));
                //lo mismo para lista ordenada
                ListaOrdenada.push_back(VerticeCosto(aux->ady,CostoActual));
                //**CADA QUE INGRESEMOS UN NUEVO COSTO LO TENEMOS QUE ORDENAR PARA ESO ES LA FUNCION CAMPARACION**
                ListaOrdenada.sort(Comparacion);
                //se apila la pareja; vertice actual y vertice destino
                pila.push(VerticeVertice(VerticeActual,aux->ady));

                //**AQUI DEBEMOS CALCULAR DE NUEVO EL COSTO ACTUAL**
                //por que va a estar sumando todas las opciones de camino,
                //cuando unicamente debe de ir sumando los pesos mas chicos
                CostoActual= CostoActual- aux->peso;
            }
            aux = aux->sig;
        }
    }
    //si la lista ordenada se vacio sin encontrar el destino , no existe una ruta entre esos vertices
    if(band2==0){
       cout<<"No hay una ruta entre esos dos vertices"<<endl;
    }
}
