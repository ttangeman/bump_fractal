#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum pen_state {
    PEN_DOWN,
    PEN_UP
};

struct turtle_state {
    float heading;
    float x, y;
};

FILE *outf;
static struct turtle_state turtle;

static void draw_line(int x1, int y1, int x2, int y2)
{
    fprintf(outf, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(255, 0, 0);stroke-width:2\" />\n", x1, y1, x2, y2);
}

// PI / 180
#define RAD_CONST 0.0174533

static void fd(float dist)
{
    float dx = turtle.x + dist * cos(turtle.heading * RAD_CONST);
    float dy = turtle.y + dist * sin(turtle.heading * RAD_CONST);

    draw_line(turtle.x, turtle.y, dx, dy);

    turtle.x = dx;
    turtle.y = dy;
}

static void rt(float angle)
{
    turtle.heading += angle;
    turtle.heading = fmodf(turtle.heading, 360);
}

static void lt(float angle)
{
    rt(-angle);
}

static void draw_bump_fractal(float dist)
{
    float dt = dist / 3;

    if (dt < 2) {
        fd(dist);
        return;
    }

    draw_bump_fractal(dt);
    lt(60);
    draw_bump_fractal(dt);
    rt(120);
    draw_bump_fractal(dt);
    lt(60);
    draw_bump_fractal(dt);
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s [width] [height] [output]\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    outf = fopen(argv[3], "w");

    turtle.heading = 0;
    turtle.x = 0;
    turtle.y = height / 2;

    fprintf(outf, "<svg width=\"%d\" height=\"%d\">\n", width, height);

    draw_bump_fractal(width);

    fprintf(outf, "</svg>\n");
    fclose(outf);
}
