#include <stdio.h>
#include <stdlib.h>
#include <struct.h>

int torus;
int gridSizeX;
int gridSizeY;
int boxSize;
int delay;
int sheduling;
int nbTicks;
int grid;
int trace;
int seed;
int refresh;
int nbParticles;


/**
 * {@inheritdoc}
 */
void parse(){
	char buffer[20];

	scanf("%s = %d", buffer, &torus);
	scanf("%s = %d", buffer, &gridSizeX);
	scanf("%s = %d", buffer, &gridSizeY);
	scanf("%s = %d", buffer, &boxSize);
	scanf("%s = %d", buffer, &delay);
	scanf("%s = %d", buffer, &sheduling);
	scanf("%s = %d", buffer, &nbTicks);
	scanf("%s = %d", buffer, &grid);
	scanf("%s = %d", buffer, &trace);
	scanf("%s = %d", buffer, &seed);
	scanf("%s = %d", buffer, &refresh);
	scanf("%s = %d", buffer, &nbParticles);

	srand(seed);
}
