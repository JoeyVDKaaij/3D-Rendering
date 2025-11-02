#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ShaderUtil.h"

/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */

int main () {
    //Open SFML Window == Valid OpenGL Context
    sf::Window window(
            sf::VideoMode (800, 600),       //800 x 600 x 32 bits pp
            "OpenGL Window",                //title
            sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
            sf::ContextSettings (
                    24,                         //24 bits depth buffer, important for 3D!
                    0,                          //no stencil buffer
                    0,                          //no anti aliasing
                    3,                          //requested major OpenGL version
                    3                           //requested minor OpenGL version
            )
    );

    window.setVerticalSyncEnabled(true);

    //initialize glew to load all available opengl functions/extensions
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
        return -1;
    }

    GLuint programID = ShaderUtil::createProgram("./../vertexshader.vs", "./../fragmentshader.fs");

    //declare the data to upload
    const GLfloat vertices[] = {
            //1 triangles, 3 vertices per triangle, 4 floats per vertex
            -0.5f, -0.5f, 0,
            0.5f, -0.5f, 0,
            -0.5f, 0.5f, 0,
            0.5,0.5f,0,
            -0.5f, 0.5f, 0,
            0.5f, -0.5f, 0
    };

    const GLfloat colors[] {
            //1 triangle, 3 vertices per triangle, 1 color per vertex, 4 "floats" per color RGBA
            0,0,0,
            1,0,0,
            0,1,0,
            1,1,0,
            0,1,0,
            1,0,0
    };

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //create a handle to the buffer
    GLuint vertexBufferId;
    glGenBuffers(1, &vertexBufferId);
    //bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
    //a new array buffer for vertex position data will be created
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    //stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
    //note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //disconnect the funnel
    //glBindBuffer(GL_ARRAY_BUFFER, 0);


    //create a handle to the buffer
    GLuint colorBufferId;
    glGenBuffers(1, &colorBufferId);
    //bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
    //a new array buffer for vertex color data will be created
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    //stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
    //note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    //disconnect the funnel
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint vertexIndex = glGetAttribLocation(programID, "vertex");
    GLint colorIndex = glGetAttribLocation(programID, "color");

    //make sure data is streamed to the shader for this index
    glEnableVertexAttribArray(vertexIndex);
    //bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    //tell OpenGL in which format to expect this data
    glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //make sure data is streamed to the shader for this index
    glEnableVertexAttribArray(colorIndex);
    //bind the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    //tell OpenGL in which format to expect this data
    glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //disconnect VAO
    glBindVertexArray(0);

    glClearColor(1, 0, 0, 1);

    float currentIncrement = 0;
    bool keyPressed = false;

    float scaleSpeed = 1;

    // UPDATE
    while (window.isOpen()) {
        float customClock = (float)clock();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            scaleSpeed += 0.2f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            scaleSpeed -= 0.2f;
        }

        sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
        float windowX = window.getSize().x;
        float windowY = window.getSize().y;
        mousePos = {mousePos.x / windowX, 1 - (mousePos.y / windowY)};

        glClear( GL_COLOR_BUFFER_BIT );

        //tell the GPU to use this program
        glUseProgram (programID);
        GLint columnsIndex = glGetUniformLocation(programID, "columns");
        glUniform1i (columnsIndex, 8);
        GLint rowsIndex = glGetUniformLocation(programID, "rows");
        glUniform1i (rowsIndex,  8);
        GLint clockIndex = glGetUniformLocation(programID, "clock");
        glUniform1f (clockIndex, customClock);
        GLint scaleSpeedIndex = glGetUniformLocation(programID, "scaleSpeed");
        glUniform1f (scaleSpeedIndex, scaleSpeed);
        GLint mousePositionIndex = glGetUniformLocation(programID, "mousePosition");
        glUniform2f (mousePositionIndex, (float)mousePos.x, (float)mousePos.y);
        GLint distanceIndex = glGetUniformLocation(programID, "distance");
        glUniform1f (distanceIndex, 0.2);

        GLint incrementIndex = glGetUniformLocation(programID, "increment");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !keyPressed)
        {
            currentIncrement += 0.1f;
            glUniform1f(incrementIndex, currentIncrement);
            keyPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) keyPressed = false;

        // Bind the VAO and draw the triangle
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glDisableVertexAttribArray(vertexIndex);
        glDisableVertexAttribArray(colorIndex);

        //display it
        window.display();

        //empty the event queue
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
        }

    }

    return 0;
}


