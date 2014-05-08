#include "Md2Asset.h"

Md2Asset::Md2Asset(const string &filename) {
  
        import_md2_asset(filename);

	// set the bounding box
	// TODO: make this a non-arbitrary position.  Currently it makes no sense at all.
	bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f));

	// make the objects to display
	if(0 == make_resources()) {
	  cout << "Can't make the required OpenGL resources for Md2Asset." << endl;	  
	  // TODO: exit nicely here
	}

}

Md2Asset::~Md2Asset() {
  // TODO: clean up
}

void Md2Asset::update() {
}

void Md2Asset::import_md2_asset(const string &filename) {
	ifstream md2file;
	md2file.open(filename, ios::in|ios::binary);

	// C stuff
	//md2_header_t * md2header = (struct md2_header_t *)
	//	malloc(sizeof(struct md2_header_t));
	// Or we could use a stack allocated variable.
	md2_header_t md2header;

	// it involves evil casting.
	md2file.read((char *) &md2header, sizeof (struct md2_header_t));

	if ((md2header.ident != 844121161) ||
			(md2header.version != 8)) {
		/* Error! */
		cerr << "Error: bad version or identifier" << endl;
	}

	// Get the triangle data.
	// TODO: Better to store as a unique_ptr?
	this->triangles = (md2_triangle_t *)
			calloc(md2header.num_tris, sizeof (struct md2_triangle_t));
	this->num_triangles = md2header.num_tris;
	md2file.seekg(md2header.offset_tris, ios::beg);
	md2file.read((char *) triangles, sizeof (struct md2_triangle_t) * md2header.num_tris);

	// Turn the triangle information into an index buffer
	this->g_element_buffer_data = new GLushort[this->num_triangles * 3]; // 3 vertices per triangle
	for(int i=0; i<num_triangles;i++) {
	  this->g_element_buffer_data[(i*3)] = triangles[i].vertex[0];
	  this->g_element_buffer_data[(i*3) + 1] = triangles[i].vertex[1];
	  this->g_element_buffer_data[(i*3) + 2] = triangles[i].vertex[2];
	}

	// Get the vertices/indices of the first frame only.
	// Note: this is dangerous, we _really_
	// should populate the whole structure as documented in
	// http://tfc.duke.free.fr/coding/md2-specs-en.html
	this->g_vertex_buffer_data = new GLfloat[md2header.num_vertices * 3]; // 3 points per vertex

	md2file.seekg(md2header.offset_frames, ios::beg);

	/* Read first frame data */
	vec3_t * scale = (vec3_t *) malloc(sizeof(vec3_t));
	md2file.read((char *) scale, sizeof (vec3_t));
	cout << (*scale)[0] << " " << (*scale)[1] << " " << (*scale)[2] << endl;

	vec3_t * translate = (vec3_t *) malloc(sizeof(vec3_t));
	md2file.read((char *) translate, sizeof (vec3_t));
	cout << (*translate)[0] << " " << (*translate)[1] << " " << (*translate)[2] << endl;

	// beware the magic number
	char * name = (char *) calloc(16, sizeof(char));
	md2file.read((char *) name, 16);
	cout << name << endl;

	md2_vertex_t * c_vertices = (md2_vertex_t *) calloc(md2header.num_vertices, sizeof (struct md2_vertex_t));
	md2file.read((char *) c_vertices, (sizeof (struct md2_vertex_t)) *
			md2header.num_vertices);
	this->num_vertices = md2header.num_vertices;

	// Unpack vertices - put them in a 1d array.
	for(int i=0; i<this->num_vertices;i++) {
		this->g_vertex_buffer_data[i * 3] = (c_vertices[i].v[0] * (*scale)[0]) + (*translate)[0];
		this->g_vertex_buffer_data[(i*3)+1] = (c_vertices[i].v[1] * (*scale)[1]) + (*translate)[1];
		this->g_vertex_buffer_data[(i*3)+2] = (c_vertices[i].v[2] * (*scale)[2]) + (*translate)[2];
	}

	// Hopefully we now have vertices.  Note: No error checking.
	// cleanup
	md2file.close();
	free(c_vertices);
	free(scale);
	free(translate);
	free(name);
}
