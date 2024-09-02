
/* Wasmer graphics for logo. */

#include <memory.h>
#include <stdio.h>

#include "logo.h"

#define GR_SIZE 60000
#define NUMCOLORS 512
#define NUMINITCOLORS 16

void webgraphics_init();

#define prepare_to_draw fprintf(stderr, "\n<<LOGOGRAPHICS\n")

#define done_drawing fprintf(stderr, "\nLOGOGRAPHICS\n")

#define prepare_to_draw_turtle nop()
#define done_drawing_turtle nop()

#define screen_left -100
#define screen_right 100
#define screen_top -100
#define screen_bottom 100

#define screen_height (screen_bottom - screen_top)
#define screen_width (screen_right - screen_left)

#define screen_x_center (screen_left + (screen_width) / 2)
#define screen_y_center (screen_top + (screen_height) / 2)

#define turtle_left_max ((screen_left) - (screen_x_center))
#define turtle_right_max ((screen_right) - (screen_x_center))
#define turtle_top_max ((screen_y_center) - (screen_top))
#define turtle_bottom_max ((screen_y_center) - (screen_bottom))

#define screen_x_coord ((screen_x_center) + turtle_x)
#define screen_y_coord ((screen_y_center) - turtle_y)

#define turtle_height 18
#define turtle_half_bottom 6.0
#define turtle_side 19.0

#define clear_screen erase_screen()
void erase_screen();

#define line_to(a, b)                                      \
  if (xgr_pen.vis == 0)                                    \
    fprintf(stderr, "lineTo, %ld, %ld\n", (long)a, (long)b); \
  move_to(a, b)

#define move_to(a, b)                                    \
  fprintf(stderr, "moveTo, %ld, %ld\n", (long)a, (long)b); \
  xgr_pen.xpos = (a);                                    \
  xgr_pen.ypos = (b)
#define draw_string(s) fprintf(stderr, "strokeText, %s, %ld, %ld\n", \
                               s, (long)xgr_pen.xpos, (long)xgr_pen.ypos)
#define set_pen_vis(v) xgr_pen.vis = (v)
#define set_pen_mode(m) xgr_pen.pm = (m)
#define set_pen_color(c)         \
  xgr_pen.color = c % NUMCOLORS; \
  fprintf(stderr, "set, strokeStyle, %s\n", colors[c + SPECIAL_COLORS])
#define set_pen_width(w) \
  xgr_pen.pw = w;        \
  fprintf(stderr, "set, lineWidth, %ld\n", (long)w)
#define set_pen_height(h) nop()
#define set_pen_x(x) nop()
#define set_pen_y(y) nop()
#define set_back_ground(c) nop()

/* pen_info is a stucture type with fields for the various
   pen characteristics including the location, size, color,
   mode (e.g. XOR or COPY), pattern, visibility (0 = visible) */

typedef struct
{
  int color;
  int xpos;
  int ypos;
  int vis;
  int pw;
  int ph;
  int pm;
} pen_info;

void save_pen(pen_info *p);
void restore_pen(pen_info *p);

extern pen_info xgr_pen;
extern char *colors[NUMCOLORS + SPECIAL_COLORS];
extern int back_ground;

#define p_info_x(p) (p.xpos)
#define p_info_y(p) (p.ypos)

/* All these should take an argument, like the two just above.
   Then we could support multiple turtles.
 */

#define pen_width xgr_pen.pw
#define pen_height xgr_pen.ph
#define pen_color xgr_pen.color
#define pen_mode xgr_pen.pm
#define pen_vis xgr_pen.vis
#define pen_x (xgr_pen.xpos)
#define pen_y (xgr_pen.ypos)

#define get_node_pen_pattern make_intnode(0)

#define PEN_REVERSE 0
#define PEN_ERASE 1
#define PEN_DOWN 2

#define pen_reverse pen_mode = PEN_REVERSE
#define pen_erase pen_mode = PEN_ERASE
#define pen_down pen_mode = PEN_DOWN

#define button FALSE
#define mouse_x 0
#define mouse_y 0

#define full_screen nop()
#define split_screen nop()
#define text_screen nop()

#define plain_xor_pen() pen_reverse
#define label(s) draw_string(s)

#define tone(p, d) nop()
#define get_pen_pattern(p) nop()
#define set_pen_pattern(p) nop()
#define set_list_pen_pattern(p) nop()

extern void set_palette(int, unsigned int, unsigned int, unsigned int);
extern void get_palette(int, unsigned int *, unsigned int *, unsigned int *);
extern void nop();

void logofill(void);
