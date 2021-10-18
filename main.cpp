#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

std::string readfile(const char* path)
{
    ifstream ifs(path);
    if (ifs.is_open()){
        return std::string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    }
    return nullptr;
}

int main(){
    auto vertexShaderSource = readfile("vert.glsl");
    auto fragmentShaderSource = readfile("frag.glsl");

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Tell GLFW we are using the CORE Profile
    //So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f
    };



    //Create GLFWwindow object of 800 by 800 pixels, naming it YoutubeOpenGL
    GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
    //Error check if the window fails to create
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    
    // Load GLAD so it configures OpenGL
    gladLoadGL();

    //Specify the viewport of OpenGL in the window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);
    

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource.c_str(), NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource.c_str(), NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // do not confuse front and back buffers....!!



    GLuint VBO;
    glGenBuffers(1, &VBO);
    

    //specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    
    // Main While loop (rendering loop)
    while (!glfwWindowShouldClose(window)){
        // Take care of all GLFW events
        glfwPollEvents();
    }
    //Destroy window
    glfwDestroyWindow(window);
    //Terminate GLFW
    glfwTerminate();
    return 0;
}