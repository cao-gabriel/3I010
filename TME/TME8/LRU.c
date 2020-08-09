#include "LRU.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	initLRU(Swapper*);
void	referenceLRU(Swapper*,unsigned int frame);
unsigned int chooseLRU(Swapper*);
void	finalizeLRU(Swapper*);

typedef struct {
	unsigned int clock;
	unsigned int * age;
} InfoLRU;

int initLRUSwapper(Swapper*swap,unsigned int frames){
 return	initSwapper(swap,frames,initLRU,referenceLRU,chooseLRU,finalizeLRU);
}

int	initLRU(Swapper*swap){
	void * lru = malloc(sizeof( InfoLRU));
	swap -> private_data = lru;
	InfoLRU * plru = (InfoLRU *) swap -> private_data;
	plru -> age = malloc(sizeof(int) * swap -> frame_nb);
	plru -> clock = 0;
	for(int i = 0; i < swap -> frame_nb; i++){
		plru -> age[i] = 0;
	}
	return 0;
}

void	referenceLRU(Swapper*swap,unsigned int frame){
	unsigned int clock = ++((InfoLRU *)(swap -> private_data)) -> clock;
	printf("Clock changed for frame %d, now : %d\n", frame , clock);
	((InfoLRU *)(swap -> private_data)) -> age[frame] = clock;
}

unsigned int chooseLRU(Swapper*swap){
int chosen_frame = 0;
int i;
// Cast
InfoLRU * plru = (InfoLRU *) swap -> private_data;

int age_i;

// Take the oldest
for(i = 0; i < swap -> frame_nb; i++){
	age_i = plru -> age[i];
	printf("Age of frame %d : %d \n",i, age_i );
	if(age_i < plru -> age[chosen_frame]){
		chosen_frame = i;
	}
}

return chosen_frame;

}

void	finalizeLRU(Swapper*swap){
	/* A ecrire en TME */
InfoLRU * plru = (InfoLRU *) swap -> private_data;
free(plru -> age);
free(swap -> private_data);
}
