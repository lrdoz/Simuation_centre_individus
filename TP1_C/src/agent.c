#include <agent.h>
#include <environment.h>
#include <stdlib.h>
#include <stdio.h>

static int nb_agent = 1;

/**
 * {@inheritdoc}
 */
void init_agent(struct agent_s *agent, struct environment_s *environment){
	//Init
	agent->num = nb_agent++/2;
	agent->position = NULL;
	agent->vector = NULL;
	agent->environment = environment;
	
	// Add agent in list of environment
	add(environment->agents, agent);
}

/**
 * {@inheritdoc}
 */
void set_vector(struct agent_s *agent, int vx, int vy){
	if(agent->vector == NULL)
		agent->vector = malloc(sizeof(struct vector_s));

	agent->vector->v_x = vx;
	agent->vector->v_y = vy;
}

/**
 * {@inheritdoc}
 */
void set_position(struct agent_s *agent, int x, int y){

	//Check if node is in board
	if(agent->position == NULL)
		agent->position = malloc(sizeof(struct position_s));
	else
		remove_environment(agent);
	agent->position->x = x;
	agent->position->y = y;

	update_position(agent);
}

/**
 * {@inheritdoc}
 */
void update_position(struct agent_s *agent){
	struct agent_s **agent_board;
	
	if(agent->position == NULL)
		return;
	
	agent_board = get_position(agent->environment, agent->position);
	*agent_board = agent;
}

/**
 * {@inheritdoc}
 */
void remove_environment(struct agent_s *agent){
	struct agent_s **agent_board;

	agent_board = get_position(agent->environment, agent->position);
	*agent_board = NULL;
}

/**
 * {@inheritdoc}
 */
void move_agent(struct agent_s *agent){
	struct vector_s *vector;
	struct agent_s **box;
	struct position_s old_p, *position;

	vector = agent->vector;
	position = agent->position;
	old_p.x = position->x;
	old_p.y = position->y;

	//Check inercial of agent
	if(vector->v_x == 0 && vector->v_y == 0)
		return;
	
	//Get New position of agent
	remove_environment(agent);
	
	//Update position of agent
	move_position(agent);
	box = get_position(agent->environment, agent->position);
	
	if(*box == NULL || (*box)->num == agent->num){
		*box = agent;
	}
	else{
		//Marche pas
		position->x = old_p.x;
		position->y = old_p.y;
		inverse_vector(agent, *box);
		
		box = get_position(agent->environment, agent->position);
		*box = agent;
		(*box)->colision = 1;
		agent->colision = 1;
	}
}

/**
 * {@inheritdoc}
 */
static void inverse_vector(struct agent_s *v1, struct agent_s *v2){
	struct vector_s *tmp;

	tmp = v1->vector;
	v1->vector = v2->vector;
	v2->vector = tmp;
}

/**
 * {@inheritdoc}
 */
static void move_position(struct agent_s *agent){
	struct vector_s *vector;
	struct position_s *position;
	
	// Get variable
	vector = agent->vector;
	position = agent->position;

	//Moove node
	position->x += vector->v_x;
	position->y += vector->v_y;

	//Check if new position have problem in environment
	correct_position(agent);

	return;
}

/**
 * {@inheritdoc}
 */
static void correct_position(struct agent_s *agent){
	struct vector_s *vector;
	struct environment_s *env;
	struct position_s *position;
	
	// Get variable
	vector = agent->vector;
	env = agent->environment;
	position = agent->position;
	
	if(position->x < 0 || position->x >= env->width || position->y < 0 || position->y >=env->height){
		if(torus){
			if(position->x < 0 || position->x >= env->width){
				vector->v_x *= -1;
				position->x += vector->v_x*2;
			}
			if(position->y < 0 || position->y >= env->height){
				vector->v_y *= -1;
				position->y += vector->v_y*2;
			}
		}
		else{
			position->x = position->x + env->width;
			position->y = position->y + env->height;
			position->x %= env->width;
			position->y %= env->height;
		}
	}
}

/**
 * {@inheritdoc}
 */
void display_agent(void *arg, char *buffer){
	struct agent_s *agent;
	struct position_s *position;
	
	agent = arg;
	position = agent->position;
	sprintf(buffer, "(%d,%d;%d)",agent->num, position->x, position->y);

	return;
}
