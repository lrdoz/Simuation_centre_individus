#ifndef STRUCT_H
	#include <struct.h>
#endif

/**
 * Initialize agent
 *
 * @param agent Agent we are looking for
 * @param environment Environment of agent
 */
void init_agent(struct agent_s *agent, struct environment_s *environment);

/**
 * Defined vector of agent
 *
 * @param agent Agent we are looking for
 * @param vx New vertical vector
 * @param vy New horizontal vector
 */
void set_vector(struct agent_s *agent, int vx, int vy);

/**
 * Defined position of agent in environment
 *
 * @param agent Agent we are looking for
 * @param x New x position
 * @param y New y position
 */
void set_position(struct agent_s *agent, int x, int y);

/**
 * Update position in environment of agent
 *
 * @param agent Agent we are looking for
 */
void update_position(struct agent_s *agent);

/**
 * Remove position in environement of agent
 *
 * @param agent Agent we are looking for
 */
void remove_environment(struct agent_s *agent);

/**
 * Defined moove of agent
 *
 * @param agent Agent
 */
void move_agent(struct agent_s *agent);

/**
 * 
 * 
 * 
 */
static void inverse_vector(struct agent_s *v1, struct agent_s *v2);

/**
 * Update position with vector of agent
 *
 * @param agent Agent we are looking for
 */
static void move_position(struct agent_s *agent);

/**
 *
 *
 *
 */
static void correct_position(struct agent_s *agent);

/**
 *
 *
 * @param arg 
 * @param buffer String buffer
 */
void display_agent(void *arg, char *buffer);
