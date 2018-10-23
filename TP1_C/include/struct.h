#ifndef LIST_H
	#include <list.h>
#endif

#define STRUCT_H 1

/**
 * Struct of position
 */
struct position_s {
	/**
	 * X position
	 */
	int x;
	/**
	 * Y positiontt
	 */
	int y;
};

/**
 * Struct of vector
 */
struct vector_s {
	/**
	 * X vector
	 */
	int v_x;
	/**
	 * Y vector
	 */
	int v_y;
};

/**
 * Struct of agent
 */
struct agent_s {
	/**
	 * Number of agent
	 */
	int num;
	/**
	 *  Position of agent
	 */
	struct position_s *position;
	/**
	 * Vector of agent
	 */
	struct vector_s *vector;
	
	/**
	 * Environment struct
	 */
	struct environment_s *environment;

	int colision;
};

/**
 * Struct of environment
 */
struct environment_s {
    /**
     * Environment
     */
    struct agent_s ***board;
	/**
	 * List of agent in environment
	 */
	struct list_s *agents;
	/**
	 * Width of environment
	 */
	int width;
	/**
	 * Height of environment
	 */
	int height;
	/**
	 * Wide of ball
	 */
	int wide;
};

/**
 *
 */
extern int torus;
/**
 *
 */
extern int gridSizeX;
/**
 *
 */
extern int gridSizeY;
/**
 *
 */
extern int boxSize;
/**
 *
 */
extern int delay;
/**
 *
 */
extern int sheduling;
/**
 *
 */
extern int nbTicks;
/**
 *
 */
extern int grid;
/**
 *
 */
extern int trace;
/**
 *
 */
extern int seed;
/**
 *
 */
extern int refresh;
/**
 *
 */
extern int nbParticles;

/**
 * Parse input stream
 * 
 * @param data Data we are looking for
 */
void parse();
