#include <environment.h>
#include <display.h>
#include <agent.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Main function
 */
int main(int argc, char **argv){
	struct display_s display;
	struct environment_s *environment;

	parse();
	environment = malloc(sizeof(struct environment_s));
	init_environment(environment, gridSizeX, gridSizeY, boxSize);
	generate_board(environment, nbParticles);

	
	display.env = environment;
	
	init_windows(argc, argv, &display);csv

	return 0;
}
