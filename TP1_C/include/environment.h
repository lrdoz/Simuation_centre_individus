#ifndef STRUCT_H
	#include <struct.h>
#endif

/**
 * Initialise environment
 *
 * @param environment Environment we are looking for
 * @param width Width of board
 * @param height Height of board
 */
void init_environment(struct environment_s *environment, int width, int height, int wide);

/**
 *  Generate agents
 *
 * @param env Environment used
 * @param nbAgent Number of agent
 */
void generate_board(struct environment_s *env, int nbAgent);

/**
 * Generate agent in board
 *
 * @param env Environment we are looking for
 */
static void generate_agent(struct environment_s *env);

/**
 * Create generator vector
 *
 * @return Random vector generator
 */
static int rand_vector();

/**
 * Moove agent in environment
 * 
 * @param env Environmnet 
 */
void move(struct environment_s *env);

/**
 * Retrieve agent in position, into environement
 *
 * @param env Environment we are looking for
 * @param position Position we are find agent
 * @return Agent found in position
 */
struct agent_s **get_position(struct environment_s *env, struct position_s *position);

/**
 * Display information about environment
 *
 * @param agents List of agent in environment
 */
void csv(struct list_s *agents);
