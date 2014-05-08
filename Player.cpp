#include "Player.h"
#include <SDL.h>
#include "Camera.h"

void specialKeys();



PlayerAsset::PlayerAsset() 
  : GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/hello-gl.f.glsl")
	      )
{
  PlayerAsset(0, 0, 0);
}




PlayerAsset::PlayerAsset(float x, float y, float z) {
  this->li = nullptr;

  // A default "unit" triangular pyramid
  num_vertices = 8;
  num_triangles = 6;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]; // three points per vertex
  g_element_buffer_data = new GLushort[num_triangles * 3]; // three vertices per triangle

  g_vertex_buffer_data[0] = -0.5;
  g_vertex_buffer_data[1] = -0.5;
  g_vertex_buffer_data[2] = 0.5;

  g_vertex_buffer_data[3] = 0.5;
  g_vertex_buffer_data[4] = -0.5;
  g_vertex_buffer_data[5] = 0.5;

  g_vertex_buffer_data[6] = 0.0;
  g_vertex_buffer_data[7] = -0.5;
  g_vertex_buffer_data[8] = -0.5;

  g_vertex_buffer_data[9] = 0.0;
  g_vertex_buffer_data[10] = 0.5;
  g_vertex_buffer_data[11] = 0.0;

  g_element_buffer_data[0] = 0;
  g_element_buffer_data[1] = 1;
  g_element_buffer_data[2] = 3;

  g_element_buffer_data[3] = 1;
  g_element_buffer_data[4] = 2;
  g_element_buffer_data[5] = 3;

  g_element_buffer_data[6] = 2;
  g_element_buffer_data[7] = 0;
  g_element_buffer_data[8] = 3;

  g_element_buffer_data[9] = 2;
  g_element_buffer_data[10] = 0;
  g_element_buffer_data[11] = 1;

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}


PlayerAsset::~PlayerAsset() {

	GLclampf green;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // TODO: do something nice here.
}

void PlayerAsset::update() {
  if (nullptr != li) {
      //Print coordinates// std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
    shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->li->update()));

    bbox.reset();
    bbox = shared_ptr<BoundingBox>(new BoundingBox(*p, 1.0, 1.0, 1.0));
  }
}

void PlayerAsset::setInterpolator(shared_ptr<IInterpolator> li) {
  this->li.swap(li);
}
			

void PlayerAsset::draw() {
  //std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
  GameAsset::draw();
}



