#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Player.h"
#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "Cube.h"


using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

vector<shared_ptr<GameAsset> > assets;

bool horrible_global_go = false;

SDL_Window * window = nullptr;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display() {
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // This O(n + n^2 + n) sequence of loops is written for clarity,
  // not efficiency
  for(auto it : assets) {
    if(horrible_global_go) {it->update();}
  }

  for(auto i : assets) {
    for(auto j : assets) {
      if((i != j) && i->collidesWith(*j)) {
	cout << "We have a collision"  << endl;
      }
    }
  }

  for(auto it : assets) {
    it->draw();
  }
  
  // Don't forget to swap the buffers
  SDL_GL_SwapWindow(window);
}

int main(int argc, char ** argv) {
	Uint32 width = 800;
	Uint32 height = 600;
	Uint32 delay = 1000/60; // in milliseconds

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	window = SDL_CreateWindow("CI224 - Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (nullptr == window) {
			cout << "Failed to create SDL window: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (nullptr == glContext) {
			cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
			SDL_Quit();

	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}

	
	shared_ptr<PlayerAsset> p = shared_ptr<PlayerAsset> (new PlayerAsset(0, 0, 0));
	shared_ptr<IInterpolator> i = shared_ptr<IInterpolator>(new BallisticInterpolator(Vector3(7.0, 7.0, 0), 60));
	p->setInterpolator(i);
	assets.push_back(p);

	assets.push_back(shared_ptr<Cube>(new Cube(5, 5, 0,0)));
	assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(10, 0, 0)));
	assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(12, 0, 0)));
	assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(14, 0, 0)));

	// Set the camera
	//Camera::getInstance().lookAt(Point3(0.0, 0.0, -10.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0));
	//  Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(-10.0, 0.0, 20.0)));
	//	display();
	//	Camera::getInstance().setCamera(Matrix4::identity());

	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);

	// Add the main event loop
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			  SDL_Quit();
			  break;
			case SDL_USEREVENT:
			  display();
			  break;
			case SDL_KEYUP:


				break;
			case SDL_KEYDOWN:

			  Matrix4 Camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  case SDLK_LEFT:
			    Camera::getInstance().setCamera((Camera * Matrix4::rotationY(10.0/360.0)));

			    break;
			  case SDLK_RIGHT:
			    Camera::getInstance().setCamera(Camera * Matrix4::rotationY(-15.0/360.0) );

			    break;
			  case SDLK_UP:
				  Camera::getInstance().setCamera((Camera * Matrix4::rotationX(10.0 / 360.0)));

			    Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(0.0, 0.0, -1.0)) );
			    break;
			  case SDLK_DOWN:
			    Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(0.0, 0.0, 1.0)) );

			    break;
			  case SDLK_g:
			    horrible_global_go = true;
			  
			    break;
			  }
			  break;
			}
	}
}
