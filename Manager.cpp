#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "Puente.h"
#include "Coche.h"

#define NUM_COCHES 10 /* Numero de coches para la simulación */

static void *coche_func (void *arg); /* Puntero a la función que ejecutará cada hilo/thread */

int main (int argc, char *argv[]){

    srand((int) getpid()); /* "Semilla plantada" para generar números aleatorios*/
    pthread_attr_t attr;
    /**** POR HACER ****/
     Puente *puente = new Puente((char *) S_N);/* Monitor que controla el puente, recibe la cadena de 						caracteres "N->S" o bien "S->N" como sentido del "turno 					inicial" que empezará atravesando el puente */
    					 
    pthread_t hilosCoches[NUM_COCHES];  /* Array para los NUM_COCHES hilos que se crearán después*/

    int r=rand() % 2; /* Genera tiempo aleatorio para ir creando hilos "coche" */ 
    int i;
    pthread_attr_init(&attr);
    /* Creacion de los hilos para los coches*/
    for (i=0; i<NUM_COCHES; i++){   
        sleep(r+1); /* Tiempo de espera hasta crear el próximo hilo */
        /**** POR HACER ****/
         pthread_create(&hilosCoches[i], &attr,coche_func,(void*)puente); /* Crear hilo que ejecute concurrentemente la función coche_func()*/
        			/* pthread_create debe recibir como parámetro el puntero de función 					void *coche_func() */
    } /* Fin for */
    /* Esperar terminación de los hilos "coche" */
    for (i=0; i<NUM_COCHES; i++) 
        pthread_join(hilosCoches[i], NULL);
    printf("Adios");
    delete puente; /* Destruye el monitor */

    return EXIT_SUCCESS;
}

/* Función que ejecuta cada hilo... */
static void *coche_func (void *arg){

    /**** POR HACER ****/	
     Puente *puente = (Puente*)arg; /* Obtener una referencia del puente a partir del puntero void *arg */
    
    /* Desde la función coche_func() que ejecuta cada hilo se declara e inicializa un objeto
       de clase coche (Coche *coche) que recibe tres atributos: i)un identificador entero (por ejemplo
       el propio id del thread); ii)una referencia/puntero al monitor (Puente *puente); y, por último,
       iii)se asigna un sentido al coche mediante la cadena de caracteres "N->S" ó "S->N" 
       dependiendo de si su identificador es par o impar */
    const char *sentido = (gettid()%2==0) ? N_S : S_N;
    //const char *sentido = (getpid()%2==0) ? N_S : S_N;
    Coche *coche = new Coche ((int)gettid(), puente, sentido);
    //Coche *coche = new Coche ((int)getpid(), puente, sentido);
    coche->circula(); /* Desde este hilo/thread se invoca el método circula() del objeto de clase Coche */
    
    /* Cuando ya el objeto coche (Coche *coche) termina de circular (y ha atravesado el puente) 
    es borrado de memoria con delete() */
    delete coche;
    return (void *) true;
}
