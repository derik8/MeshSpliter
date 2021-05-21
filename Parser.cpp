#include "Parser.h"

TriangleSoup STLParser::read(const std::string & filename)
{
	return TriangleSoup();
}

void STLParser::write(const TriangleSoup & triangleSoup, const std::string & filename)
{
	std::ofstream stlfile;
	stlfile.open(filename);

	stlfile.precision(17);

	stlfile << "solid " << filename << "\n";

	for (size_t i = 0; i < triangleSoup.size(); i += 3)
	{
		stlfile << "\tfacet normal " << std::fixed << std::setprecision(8)
			<< triangleSoup[i].normal.x << " "
			<< triangleSoup[i].normal.y << " "
			<< triangleSoup[i].normal.z << " "
			<< "\n";

		stlfile << "\t\touter loop\n";
		for (int k = 0; k < 3; k++) {
			stlfile << "\t\t\tvertex "
				<< triangleSoup[i + k].pos.x << " "
				<< triangleSoup[i + k].pos.y << " "
				<< triangleSoup[i + k].pos.z << " "
				<< "\n";
		}
		stlfile << "\t\tendloop\n"
			<< "\tendfacet\n";
	}

	stlfile << "endsolid " << filename << "\n";

	stlfile.close();
}
