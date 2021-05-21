#include "Cube.h"

const std::string & Cube::getName() const
{
	
	return nameC;
}

int Cube::execute(const std::map<std::string, std::string>& args)
{

	Vec xyz;
	Vertex PosNormal[36];
	TriangleSoup tringlsoup;
	std::map<std::string, std::string>::const_iterator  it;

	it = args.find("L");
	int L = std::stoi(it->second), p_one, p_two;

	it = args.find("origin");
	std::string var4 = it->second;
	double i1, j1, k1;
	p_one = var4.find(' ');
	p_two = var4.find(' ', p_one + 1);


	i1 = std::stod(var4.substr(p_one));
	j1 = std::stod(var4.substr(p_two - p_one));
	k1 = std::stod(var4.substr(var4.length() - 1 - p_two));





	xyz = { +0.0, +0.0, +1.0 };
	PosNormal[0].normal = xyz;
	xyz = { +0.0, +0.0, +1.0 };
	PosNormal[3].normal = xyz;
	xyz = { -1.0, +0.0, +0.0 };
	PosNormal[6].normal = xyz;
	xyz = { -1.0, +0.0, +0.0 };
	PosNormal[9].normal = xyz;
	xyz = { +1.0, +0.0, +0.0 };
	PosNormal[12].normal = xyz;
	xyz = { +1.0, +0.0, +0.0 };
	PosNormal[15].normal = xyz;
	xyz = { +0.0, +1.0, +0.0 };
	PosNormal[18].normal = xyz;
	xyz = { +0.0, +1.0, +0.0 };
	PosNormal[21].normal = xyz;
	xyz = { +0.0, -1.0, +0.0 };
	PosNormal[24].normal = xyz;
	xyz = { +0.0, -1.0, +0.0 };
	PosNormal[27].normal = xyz;
	xyz = { +0.0, +0.0, -1.0 };
	PosNormal[30].normal = xyz;
	xyz = { +0.0, +0.0, -1.0 };
	PosNormal[33].normal = xyz;

	// points
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[0].pos = xyz;
	xyz = { +1.0, -1.0, +1.0 };
	PosNormal[1].pos = xyz;
	xyz = { +1.0, +1.0, +1.0 };
	PosNormal[2].pos = xyz;
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[3].pos = xyz;
	xyz = { +1.0, +1.0, +1.0 };
	PosNormal[4].pos = xyz;
	xyz = { -1.0, +1.0, +1.0 };
	PosNormal[5].pos = xyz;
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[6].pos = xyz;
	xyz = { -1.0, +1.0, +1.0 };
	PosNormal[7].pos = xyz;
	xyz = { -1.0, +1.0, -1.0 };
	PosNormal[8].pos = xyz;
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[9].pos = xyz;
	xyz = { -1.0, +1.0, -1.0 };
	PosNormal[10].pos = xyz;
	xyz = { -1.0, -1.0, -1.0 };
	PosNormal[11].pos = xyz;
	xyz = { +1.0, -1.0, -1.0 };
	PosNormal[12].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[13].pos = xyz;
	xyz = { +1.0, -1.0, +1.0 };
	PosNormal[14].pos = xyz;
	xyz = { +1.0, -1.0, +1.0 };
	PosNormal[15].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[16].pos = xyz;
	xyz = { +1.0, +1.0, +1.0 };
	PosNormal[17].pos = xyz;
	xyz = { +1.0, +1.0, +1.0 };
	PosNormal[18].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[19].pos = xyz;
	xyz = { -1.0, +1.0, +1.0 };
	PosNormal[20].pos = xyz;
	xyz = { -1.0, +1.0, +1.0 };
	PosNormal[21].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[22].pos = xyz;
	xyz = { -1.0, +1.0, -1.0 };
	PosNormal[23].pos = xyz;
	xyz = { +1.0, -1.0, -1.0 };
	PosNormal[24].pos = xyz;
	xyz = { +1.0, -1.0, +1.0 };
	PosNormal[25].pos = xyz;
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[26].pos = xyz;
	xyz = { -1.0, -1.0, -1.0 };
	PosNormal[27].pos = xyz;
	xyz = { +1.0, -1.0, -1.0 };
	PosNormal[28].pos = xyz;
	xyz = { -1.0, -1.0, +1.0 };
	PosNormal[29].pos = xyz;
	xyz = { +1.0, -1.0, -1.0 };
	PosNormal[30].pos = xyz;
	xyz = { -1.0, -1.0, -1.0 };
	PosNormal[31].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[32].pos = xyz;
	xyz = { -1.0, -1.0, -1.0 };
	PosNormal[33].pos = xyz;
	xyz = { -1.0, +1.0, -1.0 };
	PosNormal[34].pos = xyz;
	xyz = { +1.0, +1.0, -1.0 };
	PosNormal[35].pos = xyz;


	for (int i = 0; i < 36; i++)
		PosNormal[i].pos = { i1+PosNormal[i].pos.x*L / 2,j1+PosNormal[i].pos.y*L / 2,k1+PosNormal[i].pos.z*L / 2 };

	
	


	for(int i=0;i<36;i++)
	tringlsoup.push_back(PosNormal[i]);

	STLParser pars;
	pars.write(tringlsoup,"cube.stl");

	return 0;
}
