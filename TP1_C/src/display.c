#include <stdlib.h>
#include <stdio.h>
#include <cairo.h>
#include <unistd.h>
#include <display.h>
#include <math.h>
#include <unistd.h>
#include <environment.h>

#define UNUSED(x) (void)(x)

/**
 * {@inheritdoc}
 */
void init_windows(int argc, char **argv, struct display_s *display){
    /* Variables */
    GtkWidget * MainWindow = NULL;
    struct environment_s *env;

    env = display->env;
    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre */
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
	// Titre
    gtk_window_set_title(GTK_WINDOW(MainWindow), "SCI Interface");
	// Size
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), env->width * env->wide + env->width, env->height * env->wide + env->height);
    // Icône
    gtk_window_set_icon_from_file(GTK_WINDOW(MainWindow), "unique.jpg", NULL);
	// Boutton fermeture
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    //Définition des paramètre
    info_init(display, MainWindow);

    // Ajout de l'évenement de dessins
    g_signal_connect (MainWindow, "expose_event", G_CALLBACK (on_expose), display);
    g_timeout_add(delay, on_timer, display);
    
	//Ajout de la fentre de dessin
    gtk_widget_show(MainWindow);
    gtk_main();


    return;
}

/**
 * {@inheritdoc}
 */
void info_init (struct display_s *display, GtkWidget * win)  {
    Info * info;
	struct iterator_s it;
	struct agent_s *agent;
	struct position_s *pos;

    info = display->info = malloc(sizeof(Info));
	info->win  = win;
	info->cairo= NULL;

	info->old = malloc(sizeof(struct list_s));

	init_list(info->old, sizeof(struct position_s));
	init_Iterator(display->env->agents, &it);

	while(hasNext(&it)){
		agent = next(&it);
		pos = malloc(sizeof(struct position_s));
		pos->x = agent->position->x;
		pos->y = agent->position->y;
		add(info->old, pos);
	}
}

/**
 * {@inheritdoc}
 */
gboolean on_expose (GtkWidget * widget, GdkEvent *e, gpointer data) {
	struct display_s * display = data;
	UNUSED(e);
	display->info->cairo= gdk_cairo_create (widget->window);

	set_back_ground(display);
   	
    draw_environment(display);

	cairo_destroy (display->info->cairo); display->info->cairo= NULL;
	return TRUE;
}

void copy_old_position(struct display_s *display){
	struct agent_s *agent;
	struct position_s *pos;
	struct iterator_s ita, itp;

	init_Iterator(display->info->old, &itp);
	init_Iterator(display->env->agents, &ita);

	while(hasNext(&itp)){
		pos = next(&itp);
		agent = next(&ita);
		pos->x = agent->position->x;
		pos->y = agent->position->y;
	}
}

void remove_point(struct display_s *display){
	struct iterator_s it;
	struct position_s *pos;
    cairo_pattern_t *color;

	init_Iterator(display->info->old, &it);

	color = cairo_pattern_create_rgba (1.0, 1.0, 1.0, 1.0);
	while(hasNext(&it)){
		pos = next(&it);
		draw_agent(display->info, pos, display->env->wide, color);

	}
    cairo_pattern_destroy(color);
}

/**
 * {@inheritdoc}
 */
gboolean on_timer(gpointer data){
	int i;
    struct display_s * display = data;

	display->info->cairo= gdk_cairo_create (display->info->win->window);

	//copy_old_position(display);	
	for(i = 0; i < refresh; i++)
    	move(display->env);

	//remove_point(display);
	set_back_ground(display);
   	
    draw_environment(display);
	

	cairo_destroy (display->info->cairo); display->info->cairo= NULL;
	return TRUE;
}

/**
 * {@inheritdoc}
 */
void draw_environment(struct display_s *display){
    cairo_pattern_t *color;

    // RBG & Alpha
	color = cairo_pattern_create_rgba (1.0, 0.0, 0.0, 1.0);

    parse_agents(display, color);
    cairo_pattern_destroy(color);
}

/**
 * {@inheritdoc}
 */
void parse_agents(struct display_s *display, cairo_pattern_t *color){
    struct iterator_s it;
    struct agent_s *agent;
    struct environment_s *env;
    cairo_pattern_t *grey;

    env = display->env;
    init_Iterator(env->agents, &it);
	grey = cairo_pattern_create_rgba (0.0, 0.0, 0.0, 0.5);
    while(hasNext(&it)){
        agent = next(&it);
		if(agent->colision)
        	draw_agent(display->info, agent->position, env->wide, color);
		else
        	draw_agent(display->info, agent->position, env->wide, grey);

    }
    cairo_pattern_destroy(grey);
}

/**
 * {@inheritdoc}
 */
void draw_agent(Info *info, struct position_s *pos, int wide, cairo_pattern_t *color){
    
    cairo_arc(info->cairo,pos->x+ pos->x*wide + wide/2, pos->y+ pos->y*wide + wide/2,(wide- 0.5)/2,0, 2*M_PI);
    cairo_set_source (info->cairo, color);
    cairo_fill (info->cairo);
}

/**
 * {@inheritdoc}
 */
void set_back_ground(struct display_s *display){
	cairo_pattern_t *white;
    Info *info = display->info;
   	double red, green, blue, alpha;


	//Définition de la couleur de fond 
	red = green = blue = alpha = 1.0;

	white = cairo_pattern_create_rgba (red, green, blue, alpha);
	cairo_set_source(info->cairo, white);
	cairo_paint(info->cairo);
	
	if(grid)
   	draw_grid(display);

	cairo_pattern_destroy(white);
}

/**
 * {@inheritdoc}
 */
void draw_grid(struct display_s *display){
    int i, j;
    cairo_pattern_t *black;
    Info *info = display->info;
    struct environment_s * env = display->env;
    
    black = cairo_pattern_create_rgba (0.0, 0.0, 0.0, 1.0);
    cairo_set_source(info->cairo, black);

    //Vertical ligne
    for(i = 0; i <= env->width * env->wide + env->width; i+=env->wide +1)
        draw_line(info->cairo, i, 0, i, env->height * env->wide+ env->height);

    //Horizontal line
    for(j = 0; j <= env->height * env->wide + env->height; j+=env->wide+1)
        draw_line(info->cairo, 0, j, env->width * env->wide +env->width, j);
    

    cairo_set_line_width (info->cairo, 1.0);
    cairo_stroke (info->cairo);

    cairo_pattern_destroy(black);
}

/**
 * {@inheritdoc}
 */
static void draw_line(cairo_t *cr, int x, int y, int x2, int y2){
    cairo_move_to(cr,x,y);
    cairo_line_to(cr, x2, y2);
}
