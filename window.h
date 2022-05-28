#ifndef GRID_WINDOW_H
#define GRID_WINDOW_H
#include "GL/glew.h" // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <map>

// For keyboard keys
struct key {
    bool cur, prev;
};

class Window  {

private:

public:

    static GLFWwindow* window;
    static GLFWmonitor* monitor;
    bool running = 1, fullscreen;
    std::map<int, key> keyMap; // Keyboard values

    int windowInit(int width, int height, char* title);
    void windowUpdate(void (*update)(float));
    void display();
    void input();
    void update();

};

#endif //GRID_WINDOW_H
