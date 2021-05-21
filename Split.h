#pragma once
#include "Command.h"
#include "Parser.h"

class Split : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
	Vec GetMidPoint(Vec & p1, Vec & p2, Vec & origin, Vec & direction);
	void FillVec(double point_1, TriangleSoup &tringlsoup, TriangleSoup & tringlsoup_left, TriangleSoup tringlsoup_right, Vec xyz1, Vec xyz2, Vec xyz_normal, int i);
private:
	const std::string nameSpl = "Split";

};
