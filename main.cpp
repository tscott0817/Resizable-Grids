#define GLEW_STATIC // Macro must be defined before glew.h; needed for static linking
#include "Gl/glew.h" // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720


struct key {
    bool cur, prev;
};

GLFWwindow* window;
GLFWmonitor* monitor;
bool running = 1, fullscreen;
std::map<int, key> keyMap;

void display();
void input();
void update();

int main(void)
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Grid System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* GLEW init */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


    monitor = glfwGetPrimaryMonitor();
    running = true;
    fullscreen = false;

    double lastTime = 0.0;

    while (running) {

        double time = glfwGetTime();
        double deltaTime = time - lastTime; // Time since last frame

        // Locks framerate at 60fps
        if (deltaTime >= 1/60) {
            lastTime = time;
            display();
        }
        update();
        input();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void display() {

    // Set background color
    glClearColor( 0.2f, 0.4f, 0.5f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw stuff here

    glfwSwapBuffers(window); // Switch old buffer with new; update screen
}

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

void update() {

}
