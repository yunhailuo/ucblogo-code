
/* A graphics implementation for WASM(wasmer-js) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#include "webgraphics.h"

char *LogoPlatformName = "Wasmer";

int initialized = 0;
int back_ground;
pen_info xgr_pen;

/* 16 named colors per spec.
   The ordering here corresponds to the zero-based argument
   to setpencolor that gives that color.
 */
char *colors[NUMCOLORS + SPECIAL_COLORS];

void webgraphics_init()
{
    if (initialized == 0)
    {
        initialized = 1;
        colors[SPECIAL_COLORS] = "#000000";      //"black"
        colors[SPECIAL_COLORS + 1] = "#0000ff";  //"blue"
        colors[SPECIAL_COLORS + 2] = "#008000";  //"green"
        colors[SPECIAL_COLORS + 3] = "#00ffff";  //"cyan"
        colors[SPECIAL_COLORS + 4] = "#ff0000";  //"red"
        colors[SPECIAL_COLORS + 5] = "#ff00ff";  //"magenta"
        colors[SPECIAL_COLORS + 6] = "#ffff00";  //"yellow"
        colors[SPECIAL_COLORS + 7] = "#ffffff";  //"white"
        colors[SPECIAL_COLORS + 8] = "#a52a2a";  //"brown"
        colors[SPECIAL_COLORS + 9] = "#d2b48c";  //"tan"
        colors[SPECIAL_COLORS + 10] = "#228b22"; //"forestgreen"
        colors[SPECIAL_COLORS + 11] = "#00ffff"; //"aqua"
        colors[SPECIAL_COLORS + 12] = "#fa8072"; //"salmon"
        colors[SPECIAL_COLORS + 13] = "#800080"; //"purple"
        colors[SPECIAL_COLORS + 14] = "#ffa500"; //"orange"
        colors[SPECIAL_COLORS + 15] = "#808080"; //"grey"

        // draw initial turtle with hardcoded location and heading
        prepare_to_draw;
        fprintf(stderr, "drawTurtle, %f, %f, %f\n", 0.0, 0.0, 0.0);
        done_drawing;
    }
}

void erase_screen()
{
    fprintf(stderr, "clear\n");
}

void save_pen(pen_info *p)
{
    memcpy(((char *)(p)), ((char *)(&xgr_pen)), sizeof(pen_info));
}

void restore_pen(pen_info *p)
{
    memcpy(((char *)(&xgr_pen)), ((char *)(p)), sizeof(pen_info));
    set_pen_width(p->pw);
    set_pen_height(p->ph);
}

void logofill() {
    fprintf(stderr, "floodFill, %d, %d\n", xgr_pen.xpos, xgr_pen.ypos);
}

void set_palette(int n, unsigned int r, unsigned int g, unsigned int b)
{
    if (!colors[n + SPECIAL_COLORS])
    {
        colors[n + SPECIAL_COLORS] = (char *)malloc(8);
    }
    snprintf(
        colors[n + SPECIAL_COLORS],
        8,
        "#%02x%02x%02x",
        r / 256 % 0x100,
        g / 256 % 0x100,
        b / 256 % 0x100);
}

void get_palette(int n, unsigned int *r, unsigned int *g, unsigned int *b)
{
    char rstr[3], gstr[3], bstr[3];
    strncpy(rstr, &colors[n + SPECIAL_COLORS][1], 2);
    rstr[2] = '\0';
    strncpy(gstr, &colors[n + SPECIAL_COLORS][3], 2);
    gstr[2] = '\0';
    strncpy(bstr, &colors[n + SPECIAL_COLORS][5], 2);
    bstr[2] = '\0';
    *r = strtol(rstr, NULL, 16) * 256;
    *g = strtol(gstr, NULL, 16) * 256;
    *b = strtol(bstr, NULL, 16) * 256;
}

void nop()
{
}
