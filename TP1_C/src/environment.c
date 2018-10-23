#include <environment.h>
#include <agent.h>
#include <stdio.h>
#include <stdlib.h>

int ticks = 0;

/**
 * {@inheritdoc}
 */
void init_environment(struct environment_s *environment, int width, int height, int wide){
	int i, j;
	struct agent_s ***board;
	struct agent_s **row;

	environment->width = width;
	environment->height = height;
	environment->wide = wide;
	environment->agents = malloc(sizeof(struct list_s));

	board = environment->board = malloc(sizeof(struct agent_s **) * width);
	init_list(environment->agents, sizeof(struct agent_s));

	// On rajoute des cases pour créer le board
	for(i = 0; i < width; i++, board++){
		row = malloc(sizeof(struct agent_s *) * height);
		*board = row;
		for(j = 0; j < height; j++, row++)
			*row = NULL;
	}
}

/**
 * {@inheritdoc}
 */
void generate_board(struct environment_s *env, int nbAgent){
	int i;

	for(i = 0; i < nbAgent; i++)
		generate_agent(env);
}

/**
 * {@inheritdoc}
 */
static void generate_agent(struct environment_s *env){
	struct agent_s *agent, **box, *copy;
	struct position_s position;
	
	//Generate random position of agent
	agent = malloc(sizeof(struct agent_s));
	copy = malloc(sizeof(struct agent_s));

	init_agent(agent, env);


	do{
		position.x = rand() % env->width;
	    position.y = rand() % env->height;
		box = get_position(env, &position);
	}while(*box != NULL);
	
	set_position(agent, position.x, position.y);
	
	set_vector(agent, rand_vector(), rand_vector());

}

/**
 * {@inheritdoc}
 */
static int rand_vector(){
	int res;
	
	res = rand()%3;

	if(res == 2)
		return -1;
	return res;
}

/**
 * {@inheritdoc}
 */
static void copy_old(struct environment_s *env){
	struct iterator_s it, ito;
	struct agent_s *agent, *old_a;

	init_Iterator(env->agents, &ito);

	while(hasNext(&it)){
		agent = next(&it);
		old_a = next(&ito);
		agent->position->x = old_a->position->x;
		agent->position->y = old_a->position->y;
	}
}

/**
 * {@inheritdoc}
 */
void move(struct environment_s *env){
	struct iterator_s it;
	struct agent_s *agent;
	
	if(sheduling)
		shuffle(env->agents);
	
	init_Iterator(env->agents, &it);
	while(hasNext(&it)){
		agent = next(&it);
		agent->colision = 0;
		move_agent(agent);
	}
	csv(env->agents);

	ticks++;
	if(ticks == nbTicks)
		exit(EXIT_SUCCESS);
}

/**
 * {@inheritdoc}
 */
struct agent_s **get_position(struct environment_s *env, struct position_s *position){
	struct agent_s **row;

	row = *(env->board + position->x);
	row += position->y;
	
	return row;
}

/**
 * {@inheritdoc}
 */
void csv(struct list_s *agents){
	struct iterator_s it;
	struct agent_s *agent;

	init_Iterator(agents, &it);
	
	while(hasNext(&it)){
		agent = next(&it);
		if(trace)
			printf("(%d,%d,%d,%d),",agent->num, agent->position->x, agent->position->y, agent->colision);
	}
	if(trace)
		printf("\n");
}