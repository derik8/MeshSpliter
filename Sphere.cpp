
#define _USE_MATH_DEFINES
#include "Sphere.h"
#define Deb 0;

const std::string & Sphere::getName() const
{	
	
	return nameSph;
}

int Sphere::execute(const std::map<std::string, std::string>& args)
{
	//std::vector<char> alf_vec;
	//std::string alf = "ABCDEF";

	int d = 1;
	bool lo;

	const int sectorCount = 10, stackCount = 10;
	double radius=7, PI=180;
	double mass[3][3];

	std::vector<double> vertices;
	

	Vec xyz;
	Vertex PosNormal[2+sectorCount*(stackCount-1)];
	PosNormal->normal = { 1,0,0 };
	TriangleSoup tringlsoup;

	double x, y, z, xy;                              // vertex position
	double nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	double s, t;                                     // vertex texCoord

	double sectorStep = 2 * PI / sectorCount;
	double stackStep = PI / stackCount;
	double sectorAngle, stackAngle;



	for (int i = 0,k=0; i <= stackCount; i++,k++)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2

		xy =  cosf(stackAngle* M_PI / 180);             // r * cos(u)
		
		xy = radius * xy;
		z = radius * sin(stackAngle* M_PI / 180);              // r * sin(u)
		
		if(i==0||i==stackCount){
			
			vertices.push_back(0);
			vertices.push_back(0);
			vertices.push_back(z);
			xyz = { 0,0,z };
			PosNormal[k].pos = xyz;
		}
		else
		{


			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j < sectorCount; j++, k++)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cos(sectorAngle* M_PI / 180);             // r * cos(u) * cos(v)
				y = xy * sin(sectorAngle* M_PI / 180);             // r * cos(u) * sin(v)
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				xyz = { x,y,z };
				PosNormal[k].pos = xyz;
				

			}
			k--;
		}
	}


// triangle soup
	

	for (int i = 1; i <=sectorCount; i++)
	{
		
		tringlsoup.push_back(PosNormal[0]);
		tringlsoup.push_back(PosNormal[i]);
		if (i+1==sectorCount+1)
			tringlsoup.push_back(PosNormal[1]);
		else
			tringlsoup.push_back(PosNormal[i+1]);
			

		/*alf_vec.push_back(alf[0]);
		alf_vec.push_back(alf[i]);
		if (i + 1 == sectorCount + 1)
			alf_vec.push_back(alf[1]);
		else
			alf_vec.push_back(alf[i + 1]);*/


			
				
	}
	
	for (int i = 0; i < stackCount-2; i++)
	{
		for (int j = 0, k=d,lo = true; j < sectorCount*2 - 2; j++,k++)
		{
			if (lo) {

				/*alf_vec.push_back(alf[k]);
				alf_vec.push_back(alf[k + sectorCount]);
				alf_vec.push_back(alf[k + 1]);*/
				tringlsoup.push_back(PosNormal[k]);
				tringlsoup.push_back(PosNormal[k + sectorCount]);
				tringlsoup.push_back(PosNormal[k + 1]);

				lo = false;
			}
			else
			{
				/*alf_vec.push_back(alf[k]);
				alf_vec.push_back(alf[k + sectorCount-1]);
				alf_vec.push_back(alf[k + sectorCount]);*/
				tringlsoup.push_back(PosNormal[k]);
				tringlsoup.push_back(PosNormal[k + sectorCount - 1]);
				tringlsoup.push_back(PosNormal[k + sectorCount]);
				lo = true;
				k--;
			}

			if (j + 1 == sectorCount * 2 - 2)
			{
				k++;
				/*alf_vec.push_back(alf[k]);
				alf_vec.push_back(alf[k + sectorCount ]);
				alf_vec.push_back(alf[k-sectorCount+1]);

				alf_vec.push_back(alf[k - sectorCount + 1]);
				alf_vec.push_back(alf[k + sectorCount]);
				alf_vec.push_back(alf[k+1]);*/

				tringlsoup.push_back(PosNormal[k]);
				tringlsoup.push_back(PosNormal[k + sectorCount]);
				tringlsoup.push_back(PosNormal[k - sectorCount + 1]);
									 
				tringlsoup.push_back(PosNormal[k - sectorCount + 1]);
				tringlsoup.push_back(PosNormal[k + sectorCount]);
				tringlsoup.push_back(PosNormal[k + 1]);

			}
		}
		d += sectorCount;
	}

	
	for (int i = 0,k=d++; i <sectorCount; i++,k++)
	{
		tringlsoup.push_back(PosNormal[k]);
		tringlsoup.push_back(PosNormal[2+sectorCount*(stackCount -1)-1]);
		if (i + 1 == sectorCount)
			tringlsoup.push_back(PosNormal[k - sectorCount + 1]);
		else
			tringlsoup.push_back(PosNormal[k + 1]);
		
			/*alf_vec.push_back(alf[k]);
			alf_vec.push_back(alf[alf.length()-1]);
			if (i+1==sectorCount)
				alf_vec.push_back(alf[k-sectorCount+1]);
			else
				alf_vec.push_back(alf[k+1]);*/
				
	}

//calc normal
	for (int i = 0; i < tringlsoup.size(); i += 3)
	{
	
			mass[0][0] = -1*tringlsoup[i].pos.x;
			mass[0][1] = -1*tringlsoup[i].pos.y;
			mass[0][2] = -1*tringlsoup[i].pos.z;

			mass[1][0] = tringlsoup[i + 1].pos.x - tringlsoup[i].pos.x;
			mass[1][1] = tringlsoup[i + 1].pos.y - tringlsoup[i].pos.y;
			mass[1][2] = tringlsoup[i + 1].pos.z - tringlsoup[i].pos.z;
						 
			mass[2][0] = tringlsoup[i+2].pos.x- tringlsoup[i].pos.x;
			mass[2][1] = tringlsoup[i+2].pos.y- tringlsoup[i].pos.y;
			mass[2][2] = tringlsoup[i+2].pos.z- tringlsoup[i].pos.z;

		
		tringlsoup[i].normal = {
			 mass[1][1] * mass[2][2] -  mass[1][2] * mass[2][1],
			  mass[1][2] * mass[2][0] -  mass[1][0] * mass[2][2],
			 mass[1][0] * mass[2][1] - mass[1][1] * mass[2][0] };
	}

	STLParser pars;
	pars.write(tringlsoup, "sphere.stl");
	return 0;
}


