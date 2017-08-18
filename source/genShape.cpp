#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"

#include <cmath>

#include "graphics\genShape.h"

const double PI = 3.14159265359;

Geometry makeNGon(size_t sides, float r)
{	
	
	
	unsigned vsize = sides + 1; //how big should this be?	
	unsigned isize = sides * 3; //how big?		

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float a = (2 * PI) / sides;

	verts[0] = { {0,0,0,1},{1,1,1,1} };	

	// the verts
	for (int i = 0; i < sides; ++i) {

		float x = cos(i*a) * r;
		float y = sin(i*a) * r;

		verts[i] = {{x, y, 0, 1},{ x, y, 0, 1 }};

		idxs[i * 3 + 0] = sides;
		idxs[i * 3 + 1] = i;
		idxs[i * 3 + 2] = (i + 1) % sides;
	}

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return ret;
	
}

Geometry makeCheckerboard(int dim, float size)
{	
	unsigned vsize = (dim + 1) * (dim + 1);;
	unsigned isize = 3 * 2 * dim * dim;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = dim/size;

	for (int i = 0; i < dim+1; ++i) {
		
		float y = i * step;
		
		for (int j = 0; j < dim; ++j) {
			float x = j * step;			
		}


	}



	Geometry ret = makeGeometry(verts, vsize, idxs,isize);

	delete[] verts;
	delete[] idxs;

	return ret;
}

Geometry makeCheckerboard(int rows, int cols, float width, float height)
{
	
	
	return Geometry();
}
