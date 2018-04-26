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

struct valoresNodo{//esta estructura servira para recorrer la lista de los nodos y poder moverse entre ellos
  int nodo;
  int anterior;
  int costo;
  int paso;
};

typedef struct valoresNodo nodoTopologia;

struct avanzarNodo{//permitira avanzar en la lista de nodos seleccionados como posible ruta
  int dato;
  struct avanzarNodo * siguienteNodo;
};
typedef struct avanzarNodo proximoNodo;
 //funciones a implementar
int vacio (proximoNodo *);
int siguiente (proximoNodo **, int, nodoTopologia *);
void quitaNodo(proximoNodo **, int);
int primero (proximoNodo **);
void imprimeNodos (proximoNodo *);

void direccionamiento (int nodos, int **matriz, int origen, int destino);

int main (){
  int i, j, n, **matriz; //**matriz refrencia a puntero bidimensional, servira para construir matriz de adyacencia
  int numeroNodos, partida, llegada;
  printf("Numero de nodos:  \n"); //simulara entrada de topologia
  scanf("%d",&n);
  if ((matriz= (int **) malloc (n * sizeof(int *))) ==NULL){
    return 1;
  }
  for(i=0;i<n;i++){
    if((matriz[i] = (int *)malloc(n * sizeof(int)))==NULL){
      return 1;
    }
  }

  for(i=0; i<n; i++){ //pide costo de nodo por nodo
    printf("Costo nodo directo:\n");
      for(j=1;j<=n;j++){
        scanf("%d",&matriz[i][j]);//almacena valores para construir la matriz de adyacencia (simula tabla de ruteo)
      }
  }

  printf( "Matriz de adyacencia:\n\n" );//verifica que la matriz se imprima como se introdujo
	for (i=0;i<n;i++) {
    for (j=1;j<=n;j++){
      printf("%2d",matriz[i][j]);
    }
		printf("\n");
	}
	printf("\n");

  printf("De que nodo partes:\n"); //pedira por consola el nodo por el que quiere partir
  scanf("%d", &partida);
  printf("A que nodo quieres llegar:\n");//pedira el nodo al que quiera llegar
  scanf("%d", &llegada );
  direccionamiento(n, matriz, partida, llegada);
}

void direccionamiento (int nodos, int **matriz, int origen, int destino){ //esta funcion realizara el direccionamiento ubicando cual es la ruta mas corta para llegar al destino segun los nodos entrados en el main
  nodoTopologia *ValorNodo;
  int i, j, k, costo;
  int *ruta; //arreglo de nodos

  proximoNodo *Ultimo = NULL;

  if((ValorNodo=malloc(nodos * sizeof(ValorNodo)))==NULL){//arreglo dinamico de los valores del nodo
    return;
  }
  //
  if(origen<0||origen>nodos-1){
    return;
  }
  if(destino<0||destino>nodos-1){
    return;
  }
  for(i=0;i<nodos;i++){//reccorre cantidad de nodos
    ValorNodo[i].nodo=i;
    if(i!=origen){//si la variable es el nodo de partida marcando que no hay nodo anterior y que el peso es -1 ya que para llegar de un nodo a si mismo es 0, marca se refiere a que no ha pasado sobre el
      ValorNodo[i].anterior=-1;
      ValorNodo[i].costo=-1;
      ValorNodo[i].paso=0;
    }
    else{//si el nodo ya no es el previo solo considerara los valores hacia enfrente, descartando el enlace al nodo previo, su costo en 0 ya que comenzara la suma de valores de costos
      ValorNodo[i].anterior=-1;
      ValorNodo[i].costo=0;
      ValorNodo[i].paso=0;
    }
  }
  inserta(&Ultimo,origen,ValorNodo);




}
