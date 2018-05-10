//
//  mainProyecto2.c
//  
//
//  Created by Ernesto Mata on 01/05/18.
//
//

#include <stdio.h>
#include "matriz.h"
#include "ruteo.h"

int main()
{
    int eleccion,i,j,numNodos;
    int topologia[100][100]={0};
    char nodosCaC[10000];
    char *nombreNodos[100];

    numNodos= leeArchivo(topologia,nombreNodos,nodosCaC);
    
    for (i=0; i < numNodos; i++)
        printf("nombreNodos[%d]: %s\n",i,nombreNodos[i]);
    
    for (i=0; i < numNodos; i++)
    {
        for (j=0; j < numNodos; j++)
        {
            printf("MAIN topologia[%d][%d]: %d\n",i,j,topologia[i][j]);
        }
    }
    
    generaTablas(nombreNodos,topologia,numNodos);
    
    return 0;
}
