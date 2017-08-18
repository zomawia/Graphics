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

	verts[0] = { { 0,0,0,1 },{ 1,0,0,1 } };
	
	for (int i = 0; i < sides; ++i) {

		float x = cos(i*a) * r;
		float y = sin(i*a) * r;

		verts[i].position = { x, y, 0, 1 };
		verts[i].color = { 0, 1, 1, 1 };

	

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
	unsigned vdim = dim + 1;
	unsigned vsize = vdim * vdim;
	unsigned isize = 3 * 2 * dim * dim;

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = size/dim;
	float offset = size / 2;
	int l = 0;

	for (int i = 0; i < vsize; ++i) {
		float x = (i % vdim) * step - offset;
		float y = (i / vdim) * step - offset;

		verts[i].position = {x,y,0,1};
		if (i % 2 == 0)
			verts[i].color = { 1, 0, 0, 1 };
		else
			verts[i].color = { 0, 0, 1, 1 };

		if (i == 1 && dim > 1 || 
			i % vdim != vdim - 1 && 
			i / vdim != vdim - 1 &&
			l < isize) {

			idxs[l++] = i;
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;

			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
			idxs[l++] = i + vdim + 1;

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
