#define GLEW_STATIC // Macro must be defined before glew.h; needed for static linking
#include "Gl/glew.h" // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include "components/grid/grid.h"

#define WIDTH 1600
#define HEIGHT 900

// For keyboard keys
struct key {
    bool cur, prev;
};

// Init variables
GLFWwindow* window;
GLFWmonitor* monitor; // The literal PC monitor; used for fullscreen mode
bool running = 1, fullscreen;
std::map<int, key> keyMap; // Keyboard values

// Classes
Grid gridTest;

// Local functions
static void cursor(GLFWwindow* window, double x, double y);
void display();
void input();
void update();

int main(void)
{

    /* GLFW init */
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Grid System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* GLEW init */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    /*************
     * Main Loop *
     *************/
    double lastTime = 0.0; // Tracks previous frame for refresh rate
    monitor = glfwGetPrimaryMonitor();
    running = true;
    fullscreen = false;
    while (running) {

        double time = glfwGetTime(); // Gets current program time
        double deltaTime = time - lastTime; // Time since last frame

        // Locks framerate at 60fps (or keeps it above?)
        if (deltaTime >= 1/60) {
            lastTime = time; // Updates the time since previous frame
            display();
        }
        update();
        input();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

static void cursor(GLFWwindow* window, double x, double y) {

    if (gridTest.checkOverlap(x, y)) {
        gridTest.hoverColor();
        //gridTest.hoverCompress();
    }

    else {
        //gridTest.releaseAll();
        //gridTest.releaseCompress();
    }
}

void display() {


    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION); // Define GL_PROJECTION only once; use GL_MODELVIEW for objects
    glLoadIdentity();
    glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.f, 1.f);

    // Set background color
    glClearColor( 0.2f, 0.4f, 0.5f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Stuff to be drawn goes here */
    gridTest.setPadding(25); // Higher number = more space around edge of container
    gridTest.setCellSize(5); // Lower number = larger cells
    gridTest.grid(WIDTH/2, HEIGHT/2, 700, 450, 4, 5); // Centers grid
    gridTest.draw();

    glfwSwapBuffers(window); // Switch old buffer with new; update screen
    glFlush();

}


/* Event handling for user input */
void input() {

    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        running = false;
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && keyMap[GLFW_KEY_F].prev) {
        if (!fullscreen) {
            glfwSetWindowMonitor(window, monitor, 0, 0, WIDTH, HEIGHT, 0);
        }
        if (fullscreen) {
            glfwSetWindowMonitor(window, NULL, 0, 0, WIDTH, HEIGHT, 0);
        }
        fullscreen = !fullscreen;
    }
    keyMap[GLFW_KEY_F].prev = glfwGetKey(window, GLFW_KEY_F);
}

/* Things to happen on every frame refresh */
void update() {

    glfwSetCursorPosCallback(window, cursor); // Cursor callback
}
