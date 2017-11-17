#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct turtle_state {
    float heading;
    float x, y;
};

static struct turtle_state turtle;

static void draw_line(int x1, int y1, int x2, int y2)
{
    printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(255, 0, 0);stroke-width:2\" />\n", x1, y1, x2, y2);
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

static void bd(float dist)
{
    lt(180);
    fd(dist);
    rt(180);
}

static void ud(float dist)
{
    lt(90);
    fd(dist);
    rt(90);
}

static void dd(float dist)
{
    rt(90);
    fd(dist);
    lt(90);
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

static void snowflake_fractal(int width)
{
    draw_bump_fractal(width/2);
    rt(120);
    draw_bump_fractal(width/2);
    rt(120);
    draw_bump_fractal(width/2);
}

static void triangle(float dist)
{
    fd(dist);
    lt(120);
    fd(dist);
    lt(120);
    fd(dist);
    lt(120);
}

static void sierpinski_triangle(float dist)
{
    if (dist < 10) {
        triangle(dist);
        return;
    }

    sierpinski_triangle(dist/2);
    fd(dist/2);
    sierpinski_triangle(dist/2);
    lt(120);
    fd(dist/2);
    rt(120);
    sierpinski_triangle(dist/2);
    rt(120);
    fd(dist/2);
    lt(120);
}

static void square(float dist)
{
    fd(dist);
    lt(90);
    fd(dist);
    lt(90);
    fd(dist);
    lt(90);
    fd(dist);
    lt(90);
}

static void sierpinski_carpet(float dist)
{
    if (dist < 5) {
        square(dist);
        return;
    }

    sierpinski_carpet(dist / 3);
    fd(dist/3);
    sierpinski_carpet(dist / 3);
    fd(dist/3);
    sierpinski_carpet(dist / 3);
    ud(dist/3);
    sierpinski_carpet(dist / 3);
    ud(dist/3);
    sierpinski_carpet(dist / 3);
    bd(dist/3);
    sierpinski_carpet(dist / 3);
    bd(dist/3);
    sierpinski_carpet(dist / 3);
    dd(dist/3);
    sierpinski_carpet(dist / 3);
    dd(dist/3);
}

int main(int argc, char **argv)
{
    int width = 800;
    int height = 800;

    turtle.heading = 0;
    turtle.x = width / 3;
    turtle.y = (3 * height) / 4;

    printf("<svg width=\"%d\" height=\"%d\">\n", width, height);

    // fractal calls go here
    sierpinski_carpet(width/2);

    printf("</svg>\n");
}
