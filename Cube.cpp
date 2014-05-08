#include "Cube.h"



Cube::Cube()
: GameAsset(
string("shaders/hello-gl.v.glsl")
, string("shaders/hello-gl.f.glsl")
)
{
	Cube(0, 0, 0, 0);
}

Cube::Cube(float x, float y, float z, float e) {
	this->li = nullptr;

	num_vertices = 8;
	num_triangles = 12;
	g_vertex_buffer_data = new GLfloat[num_vertices * 3]; // three points per vertex
	g_element_buffer_data = new GLushort[num_triangles * 3]; // three vertices per triangle
	g_vertex_buffer_data[0] = 0;
	g_vertex_buffer_data[1] = 0;
	g_vertex_buffer_data[2] = 0;
	g_vertex_buffer_data[3] = 3;
	g_vertex_buffer_data[4] = 0;
	g_vertex_buffer_data[5] = 0;
	g_vertex_buffer_data[6] = 3;
	g_vertex_buffer_data[7] = 3;
	g_vertex_buffer_data[8] = 0;
	g_vertex_buffer_data[9] = 0;
	g_vertex_buffer_data[10] = 3;
	g_vertex_buffer_data[11] = 0;
	g_vertex_buffer_data[12] = 0;
	g_vertex_buffer_data[13] = 0;
	g_vertex_buffer_data[14] = 3;
	g_vertex_buffer_data[15] = 3;
	g_vertex_buffer_data[16] = 0;
	g_vertex_buffer_data[17] = 3;
	g_vertex_buffer_data[18] = 3;
	g_vertex_buffer_data[19] = 3;
	g_vertex_buffer_data[20] = 3;
	g_vertex_buffer_data[21] = 0;
	g_vertex_buffer_data[22] = 3;
	g_vertex_buffer_data[23] = 3;
	g_element_buffer_data[0] = 0;
	g_element_buffer_data[1] = 1;
	g_element_buffer_data[2] = 2;
	g_element_buffer_data[3] = 0;
	g_element_buffer_data[4] = 2;
	g_element_buffer_data[5] = 3;
	g_element_buffer_data[6] = 1;
	g_element_buffer_data[7] = 2;
	g_element_buffer_data[8] = 5;
	g_element_buffer_data[9] = 2;
	g_element_buffer_data[10] = 5;
	g_element_buffer_data[11] = 6;
	g_element_buffer_data[12] = 4;
	g_element_buffer_data[13] = 5;
	g_element_buffer_data[14] = 6;
	g_element_buffer_data[15] = 4;
	g_element_buffer_data[16] = 6;
	g_element_buffer_data[17] = 7;
	g_element_buffer_data[18] = 0;
	g_element_buffer_data[19] = 3;
	g_element_buffer_data[20] = 4;
	g_element_buffer_data[21] = 3;
	g_element_buffer_data[22] = 4;
	g_element_buffer_data[23] = 7;
	g_element_buffer_data[24] = 0;
	g_element_buffer_data[25] = 1;
	g_element_buffer_data[26] = 4;
	g_element_buffer_data[27] = 4;
	g_element_buffer_data[28] = 1;
	g_element_buffer_data[29] = 5;
	g_element_buffer_data[30] = 2;
	g_element_buffer_data[31] = 3;
	g_element_buffer_data[32] = 7;
	g_element_buffer_data[33] = 2;
	g_element_buffer_data[34] = 6;
	g_element_buffer_data[35] = 7;
	bbox.reset();
	bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

	make_resources();
}



Cube::~Cube() {
	// TODO: do something nice here.
}

void Cube::update() {
	if (nullptr != li) {
		shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->li->update()));
	}
}




void Cube::setInterpolator(shared_ptr<IInterpolator> li) {
	this->li.swap(li);
}

void Cube::draw() {
	//std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
	GameAsset::draw();
}