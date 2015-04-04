/***********************************************************
 
                 penguin.cpp
                 author: Mike Pratscher
                 based on code by: Eron Steger, J. Radulovich

                Main source file for assignment 2
                Uses OpenGL, GLUT and GLUI libraries
  
    Instructions:
        Please read the assignment page to determine 
        exactly what needs to be implemented.  Then read 
        over this file and become acquainted with its 
        design. In particular, see lines marked 'README'.
		
                Be sure to also look over keyframe.h and vector.h.
                While no changes are necessary to these files, looking
                them over will allow you to better understand their
                functionality and capabilites.

        Add source code where it appears appropriate. In
        particular, see lines marked 'TODO'.

        You should not need to change the overall structure
        of the program. However it should be clear what
        your changes do, and you should use sufficient comments
        to explain your code.  While the point of the assignment
        is to draw and animate the character, you will
        also be marked based on your design.

 ***********************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "keyframe.h"
#include "timer.h"
#include "vector.h"
#include "utils.h"
#include "world.h"

// *************** GLOBAL VARIABLES *************************


const float PI = 3.14159;

const float SPINNER_SPEED = 0.1;


// --------------- USER INTERFACE VARIABLES -----------------

// Window settings
int windowID; // Glut window ID (for display)
int Win[2]; // window (x,y) size

World world;

const GLdouble CAMERA_FOVY = 60.0;
const GLdouble NEAR_CLIP = 0.1;
const GLdouble FAR_CLIP = 1000.0;


// ***********  FUNCTION HEADER DECLARATIONS ****************

// Initialization functions
void initDS();
void initGlut(int argc, char** argv);
void initGlui();
void initGl();

// Callbacks for handling events in glut
void reshape(int w, int h);
void display(void);
void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);

void gameLoop();

// ******************** FUNCTIONS ************************



// main() function
// Initializes the user interface (and any user variables)
// then hands over control to the event handler, which calls 
// display() whenever the GL window needs to be redrawn.

int main(int argc, char** argv) {

    // Process program arguments
    if (argc != 3) {
        printf("Usage: demo [width] [height]\n");
        printf("Using 640x480 window by default...\n");
        Win[0] = 640;
        Win[1] = 480;
    } else {
        Win[0] = atoi(argv[1]);
        Win[1] = atoi(argv[2]);
    }

    // Initialize data structs, glut, glui, and opengl
    initDS();
    initGlut(argc, argv);
    initGlui();
    initGl();

    // Invoke the standard GLUT main event loop
    glutMainLoop();

    return 0; // never reached
}


// Create / initialize global data structures

void initDS() {
}


// Initialize glut and create a window with the specified caption 

void initGlut(int argc, char** argv) {
    // Init GLUT
    glutInit(&argc, argv);

    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Win[0], Win[1]);
    windowID = glutCreateWindow(argv[0]);

    // Setup callback functions to handle events
    glutReshapeFunc(reshape); // Call reshape whenever window resized
    glutDisplayFunc(display); // Call display whenever new frame needed
    glutKeyboardFunc(keydown);
    glutKeyboardUpFunc(keyup);
    glutIdleFunc(gameLoop);
}

// Initialize GLUI and the user interface

void initGlui() {
}


// Performs most of the OpenGL intialization

void initGl(void) {
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f, 0.7f, 0.9f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

// Callback idle function for animating the scene

// Handles the window being resized by updating the viewport
// and projection matrices

void reshape(int w, int h) {
    // Update internal variables and OpenGL viewport
    Win[0] = w;
    Win[1] = h;
    glViewport(0, 0, (GLsizei) Win[0], (GLsizei) Win[1]);

    // Setup projection matrix for new window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CAMERA_FOVY, (GLdouble) Win[0] / (GLdouble) Win[1], NEAR_CLIP, FAR_CLIP);
}

// Keyboard event callback

void keydown(unsigned char key, int x, int y) {
    world.keydown(key);
}

void keyup(unsigned char key, int x, int y) {
    world.keyup(key);
}

// display callback
//
// README: This gets called by the event handler
// to draw the scene, so this is where you need
// to build your scene -- make your changes and
// additions here. All rendering happens in this
// function. For Assignment 2, updates to the
// joint DOFs (joint_ui_data) happen in the
// animate() function.

void display(void) {
    
    // Clear the screen with the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the model-view transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    world.update();
    world.render();

    // Execute any GL functions that are in the queue just to be safe
    glFlush();


    // Now, show the frame buffer that we just drew into.
    // (this prevents flickering).
    glutSwapBuffers();
}

// Game loop for the program
// Nothing too complicated/awesome, just checks the time between updates and
// tries to update+redraw a certain number of times per second.

int desiredFps = 60;
double timeBetweenUpdates = 1000 / desiredFps;
long previousUpdateTime = 0;

void gameLoop() {
    long currentTime = getTotalMillisecondsElapsed();
    long timeElapsedSincePreviousUpdate = currentTime - previousUpdateTime;
    
    if (timeElapsedSincePreviousUpdate >= timeBetweenUpdates) {
        previousUpdateTime = currentTime;
        
        display();
        
        glutPostRedisplay();
    }
}