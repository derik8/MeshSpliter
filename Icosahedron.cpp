
#define _USE_MATH_DEFINES
#include "Icosahedron.h"


const std::string & Icosahedron::getName() const
{

	return nameIcos;
}

int Icosahedron::execute(const std::map<std::string, std::string>& args)
{
	// constants
	
	const double H_ANGLE = M_PI / 180 * 72;    // 72 degree = 360 / 5
	const double V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

	std::vector<double> vertices(12 * 3);    // array of 12 vertices (x,y,z)
	int i1, i2;                             // indices
	double z, xy;                            // coords
	double hAngle1 = -M_PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
	double hAngle2 = -M_PI / 2;                // start from -90 deg at 2nd row
	double radius = 1;

	// the first top vertex at (0, 0, r)
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = radius;

	// compute 10 vertices at 1st and 2nd rows
	for (int i = 1; i <= 5; ++i)
	{
		i1 = i * 3;         // index for 1st row
		i2 = (i + 5) * 3;   // index for 2nd row

		z = radius * sinf(V_ANGLE);            // elevaton
		xy = radius * cosf(V_ANGLE);            // length on XY plane

		vertices[i1] = xy * cosf(hAngle1);      // x
		vertices[i2] = xy * cosf(hAngle2);
		vertices[i1 + 1] = xy * sinf(hAngle1);  // y
		vertices[i2 + 1] = xy * sinf(hAngle2);
		vertices[i1 + 2] = z;                   // z
		vertices[i2 + 2] = -z;

		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	// the last bottom vertex at (0, 0, -r)
	i1 = 11 * 3;
	vertices[i1] = 0;
	vertices[i1 + 1] = 0;
	vertices[i1 + 2] = -radius;


	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
	// find middle point of 2 vertices
	// NOTE: new vertex must be resized, so the length is equal to the radius
	///////////////////////////////////////////////////////////////////////////////
/*void computeHalfVertex(const float v1[3], const float v2[3], float newV[3])
{
	newV[0] = v1[0] + v2[0];    // x
	newV[1] = v1[1] + v2[1];    // y
	newV[2] = v1[2] + v2[2];    // z
	float scale = radius / sqrtf(newV[0] * newV[0] + newV[1] * newV[1] + newV[2] * newV[2]);
	newV[0] *= scale;
	newV[1] *= scale;
	newV[2] *= scale;
}*/