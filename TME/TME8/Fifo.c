#include "Fifo.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int initFifo(Swapper*);
unsigned int fifoChoose(Swapper*);
void fifoReference(Swapper*,unsigned int frame);
void finalizeFifo(Swapper*);

int initFifoSwapper(Swapper*swap,unsigned int frames){
	return	initSwapper(swap,frames,initFifo,NULL,fifoChoose,finalizeFifo);
}

int initFifo(Swapper*swap){
	swap -> private_data = calloc(1, sizeof(int));

	int * cases = (int *) swap -> private_data;
	cases[0] = 0;
	return 0;
}

unsigned int fifoChoose(Swapper*swap){
int * cases = (int *) swap -> private_data;
int cpt = cases[0];
cases[0] = (cases[0] + 1) % swap -> frame_nb;
return cpt;
}

void finalizeFifo(Swapper*swap){
	free(swap -> private_data);
}
