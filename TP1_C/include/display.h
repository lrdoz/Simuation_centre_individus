#include <gtk/gtk.h>

#ifndef STRUCT_H
	#include <struct.h>
#endif

#define DISPLAY_H

/**
 * Struct be used for current data in windows traitement
 */
typedef struct Info {
	/**
	 * Current windows display
	 */
	GtkWidget * win;
	/**
	 * 
	 */
	cairo_t * cairo;
	/**
	 *
	 */
	struct list_s *old;

} Info;

/**
 * Struct of current windows
 */
struct display_s{
	/**
	 * Data 
	 */
    Info *info;
	/**
	 * Current environment display
	 */
    struct environment_s *env;
};

/**
 * Initialize windows
 *
 * @param argc 
 * @param argv
 * @param display Current windows display
 * @return 
 */
void init_windows(int argc, char **argv, struct display_s *display);

/**
 * Initialise display
 *
 * @param display Struct of display want to be start
 * @param win Windows init
 */
void info_init (struct display_s *display, GtkWidget * win);

/**
 * 
 *
 * @param widget
 * @param e
 * @param data
 * @return 
 */
gboolean on_expose (GtkWidget * widget, GdkEvent *e, gpointer data);

/**
 * 
 * @param data
 * @return
 */
gboolean on_timer(gpointer data);

/**
 * Draw one environment
 * 
 * @param display
 */
void draw_environment(struct display_s *display);

/**
 * Draw one agent 
 * 
 * @param info
 * @param pos
 * @param wide
 * @param color
 */
void draw_agent(Info *info, struct position_s *pos, int wide, cairo_pattern_t *color);

/**
 * Parse all agent and display in windows
 * 
 * 
 * @param display
 * @param color
 */
void parse_agents(struct display_s *display, cairo_pattern_t *color);

/**
 *  Set back ground color
 *
 * @param display
 */
void set_back_ground(struct display_s *display);

/**
 * 
 * @param display
 */
void draw_grid(struct display_s *display);

/**
 * 
 * 
 * @param cr
 * @param x
 * @param y
 * @param x2
 * @param y2
 */
static void draw_line(cairo_t *cr, int x, int y, int x2, int y2);