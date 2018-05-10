/*******************************************/
/*Esta funcion hara el direccionamiento y  */
/*encontrara la ruta mas corta para llegar */
/*al destino                               */
/*******************************************/

/*#include<stdio.h>

void main(){
printf("Esta funcion realizara el direccionamiento");
}*/
#include<stdio.h>
#include<stdlib.h>

struct valoresNodo{
  int nodo;
  int anterior;
  int costo;
  int paso;
};
typedef struct valoresNodo valoresNodo_t;

struct avanzarNodo{
  int dato;
  struct avanzarNodo * siguienteNodo;
};
typedef struct avanzarNodo avanzarNodo_t;

int vacio (avanzarNodo_t *);
int siguiente (avanzarNodo_t **, int, valoresNodo_t *);
void quitaNodo(avanzarNodo_t **, int);
int primero (avanzarNodo_t **);
void imprimeNodos (avanzarNodo_t *);
void direccionamiento (int , int **, int , int );

int main (){
  int i, j, n, **matriz; //**matriz refrencia a puntero bidimensional, servira para construir matriz de adyacencia
  int numeroNodos, partida, llegada;
  printf("Numero de nodos:  \n");
  scanf("%d",&n);
  if ((matriz= (int **) malloc (n * sizeof(int *))) ==NULL){
    return 1;
  }
  for(i=0;i<n;i++){
    if((matriz[i] = (int *)malloc(n * sizeof(int)))==NULL){
      return 1;
    }
  }
  for(j=0;j<=n;j++){
    if((matriz[j] = (int *)malloc(n * sizeof(int)))==NULL){
      return 1;
    }
  }

  for(i=0; i<n; i++){ //pide costo de nodo por nodo
    printf("Costo nodo directo:\n");
      for(j=0;j<n;j++){
        scanf("%d",&matriz[i][j]);
      }
  }


  printf( "Matriz de adyacencia:\n\n" );
	for (i=0;i<n;i++) {
    for (j=0;j<n;j++){
      printf("%2d",matriz[i][j]);
    }
		printf("\n");
	}
	printf("\n");

  printf("De que nodo partes:\n");
  scanf("%d", &partida);
  printf("A que nodo quieres llegar:\n");
  scanf("%d", &llegada );
  direccionamiento(n, matriz, partida, llegada);
}

void direccionamiento (int nodos, int **matriz, int origen, int destino){
  valoresNodo_t *ValorNodo;
  int i, j, k, costo;
  int *ruta; //arreglo de nodos

  avanzarNodo_t *Ultimo = NULL;

  if((ValorNodo=malloc(nodos * sizeof(valoresNodo_t)))==NULL){//arreglo dinamico de los valores del nodo
    return;
  }
  //
  if(origen<0||origen>nodos-1){
    return;
  }
  if(destino<0||destino>nodos-1){
    return;
  }
  for (i=0;i<nodos;i++){
    ValorNodo[i].nodo=i;
    if (i != origen){
      ValorNodo[i].anterior=-1;
      ValorNodo[i].costo=-1;
      ValorNodo[i].paso=0;
    }
    else{
      ValorNodo[i].anterior=-1;
      ValorNodo[i].costo=0;
      ValorNodo[i].paso=0;
    }
  }
  siguiente(&Ultimo,origen,ValorNodo);
  while(!vacio(Ultimo)){
    k=primero(&Ultimo);
    for(i=0;i<nodos;i++){
      if(matriz[k][i]>0 && ValorNodo[i].paso==0){
        if(ValorNodo[i].costo==-1){
          ValorNodo[i].costo=ValorNodo[k].costo + matriz[k][i];
          siguiente(&Ultimo, i, ValorNodo);
        }
        else if(ValorNodo[k].costo + matriz[k][i]<ValorNodo[i].costo){
          ValorNodo[i].costo=ValorNodo[k].costo + matriz[k][i];
          quitaNodo(&Ultimo,i);
          siguiente(&Ultimo,i,ValorNodo);
        }
        ValorNodo[i].anterior=k;
      }
    }
    ValorNodo[k].paso=1;
    imprimeNodos(Ultimo);
  }

  int longitud = 2;
	i = destino;
	while ((i = ValorNodo[i].anterior)!=origen){
    longitud++;
  }
	if ((ruta=malloc(longitud * sizeof(int)))==NULL){
    return;
  }

	ruta[longitud-1]=destino;		/* luego rellenamos */
	i = destino;
	j = 0;
	for(j=1;j<longitud;j++) {
		i=ValorNodo[i].anterior;
		ruta[longitud-j-1] = i;
	}

	printf("================================================================\n");
	printf("\nRuta mas corta entre nodo %d y nodo %d:\n\n", origen, destino);
	for (i=0;i<longitud;i++) {
		printf("%d",ruta[i]);
		if(i<longitud-1){
      printf("-");
    }
	}
	printf("\n\nCosto total: %d\n\n", ValorNodo[destino].costo);

	free(ruta);
	free(ValorNodo);
}

int vacio(avanzarNodo_t * inicio) {
	return inicio == NULL;
}

//recorrera la fila para encontrar aquellos nodos que tengan un valor
int siguiente(avanzarNodo_t ** siguienteNodo, int nodeNumber, valoresNodo_t * ValorNodo ) {
	avanzarNodo_t *nuevoNodo, *nodoActual, *nodoAnterior;
	if ((nuevoNodo=malloc(sizeof(avanzarNodo_t)))==NULL){
    return 1;
  }

	// busca el nodo menor para continuar con la ruta corta
	nodoActual= *siguienteNodo;
	nodoAnterior=NULL;
	while(nodoActual!=NULL && ValorNodo[nodoActual->dato].costo < ValorNodo[nodeNumber].costo ) {
		nodoAnterior = nodoActual;
		nodoActual = nodoActual->siguienteNodo;
	}

	//si encontro el nodo lo inserata al la cola y lo tomara como nodo inicial
	nuevoNodo->dato = nodeNumber;
	if (nodoActual!=NULL){
		nuevoNodo->siguienteNodo=nodoActual;
  }else{
		nuevoNodo->siguienteNodo=NULL;
  }
	if (nodoAnterior!=NULL){
		nodoAnterior->siguienteNodo=nuevoNodo;
	}else{
		*siguienteNodo = nuevoNodo;
  }
	return 0;
}

//si el nodo encontrado no es el menor lo quitara
void quitaNodo(avanzarNodo_t ** siguienteNodo,int dato) {

	avanzarNodo_t *nodoAnterior=NULL, *nodoActual = *siguienteNodo;

	while (nodoActual!=NULL && nodoActual->dato!=dato ) {
		nodoAnterior=nodoActual;
		nodoActual=nodoActual->siguienteNodo;
	}
	if (nodoActual==NULL){
    return;
  }

	if (nodoAnterior!=NULL){
		nodoAnterior->siguienteNodo = nodoActual->siguienteNodo;
	}else{
		*siguienteNodo=nodoActual->siguienteNodo;
  }
	free(nodoActual);
}

//revisara que el nodo de partida se encuente en la matriz si no lo tomara como 0
int primero( avanzarNodo_t **siguienteNodo ) {

	avanzarNodo_t *auxiliarNodo;
	int dato;

	if (*siguienteNodo!=NULL) {
		auxiliarNodo = *siguienteNodo;
		*siguienteNodo = (*siguienteNodo)->siguienteNodo;
		dato=auxiliarNodo->dato;
		free(auxiliarNodo);
		return dato;
	}
	else{
		return 0;
  }
}

//imprime los nodos que se si se guardaron en la cola
void imprimeNodos(avanzarNodo_t *guardados) {

	avanzarNodo_t *nodoActual=guardados;
	if (nodoActual==NULL){
		//printf( "(vacio)\n" );
		return;
	}

	while ( nodoActual != NULL ) {
		//printf( "%d", nodoActual->dato );
		if ( nodoActual->siguienteNodo != NULL ){
      //printf( " -> " );
    }
    nodoActual = nodoActual->siguienteNodo;
	}
	//printf( "\n" );
}
