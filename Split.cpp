
#include "Split.h"

const std::string & Split::getName() const
{
	
	return nameSpl;
}

int Split::execute(const std::map<std::string, std::string>& args)
{
	TriangleSoup tringlsoup, tringlsoup_left, tringlsoup_right;
	Vec xyz1,xyz2, xyz_normal, origin = {1,0,0}, n_direction = { 4.2,-5.0,0 };
	double point_1, point_2, point_3;


	std::ifstream stlfile;
	stlfile.open("HalfDonut.stl");

	std::string s;

//read stl file	
	if (stlfile.is_open())
	{
		while (stlfile >>s)
		{
			if (s == "normal")
			{
				stlfile >> xyz1.x;
				stlfile >>xyz1.y;
				stlfile >>xyz1.z;
				tringlsoup.push_back(Vertex{ {0,0,0},xyz1 });
			}
			if (s == "vertex")
			{
				xyz_normal = tringlsoup.at(tringlsoup.size()-1).normal;
				tringlsoup.pop_back();

				for (int i = 0; i < 3; i++)
				{
					
					stlfile >> xyz1.x;
					stlfile >> xyz1.y;
					stlfile >> xyz1.z;
					stlfile >> s;
					tringlsoup.push_back(Vertex{ xyz1,xyz_normal });
				}
			
			}
			
		}
	}
	stlfile.close();

	
	for (int  i = 0; i < tringlsoup.size(); i+=3)
	{
		xyz_normal = { tringlsoup[i].normal };

		//calculation point orientation relative to the plane
		point_1 = n_direction.x*(tringlsoup[i].pos.x - origin.x) + n_direction.y*(tringlsoup[i].pos.y - origin.y) + n_direction.z*(tringlsoup[i].pos.z - origin.z);
		point_2 = n_direction.x*(tringlsoup[i + 1].pos.x - origin.x) + n_direction.y*(tringlsoup[i + 1].pos.y - origin.y) + n_direction.z*(tringlsoup[i + 1].pos.z - origin.z);
		point_3 = n_direction.x*(tringlsoup[i + 2].pos.x - origin.x) + n_direction.y*(tringlsoup[i + 2].pos.y - origin.y) + n_direction.z*(tringlsoup[i + 2].pos.z - origin.z);
		
		

		if (point_1 == 0.0)
		{
			if ((point_2 > 0 && point_3 < 0) || (point_2 < 0 && point_3 > 0))
			{
				xyz1 = GetMidPoint(tringlsoup[i+1].pos, tringlsoup[i + 2].pos, origin, n_direction);

				if (point_2 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0} });
					tringlsoup_left.push_back(tringlsoup[i + 1]);
				
					tringlsoup_right.push_back({ tringlsoup[i].pos , xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i + 2]);
				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0} });
					tringlsoup_right.push_back(tringlsoup[i + 1]);

					tringlsoup_left.push_back({ tringlsoup[i].pos , xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0,0,0} });
					tringlsoup_left.push_back(tringlsoup[i + 2]);

				}
				continue;
			}

			if ((point_2 > 0 && point_3 > 0) || (point_2 < 0 && point_3 < 0))
			{
				
				if (point_2 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i+1]);
					tringlsoup_left.push_back(tringlsoup[i + 2]);

				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back(tringlsoup[i+1]);
					tringlsoup_right.push_back(tringlsoup[i + 2]);


				}

			}
			continue;
		}
		if (point_2 == 0.0)
		{
			if ((point_1 > 0 && point_3 < 0) || (point_1 < 0 && point_3 > 0))
			{
				xyz1 = GetMidPoint(tringlsoup[i].pos, tringlsoup[i + 2].pos, origin, n_direction);

				if (point_1 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0} });
					tringlsoup_left.push_back(tringlsoup[i + 1]);

					tringlsoup_right.push_back({ tringlsoup[i+1].pos , xyz_normal });
					tringlsoup_right.push_back(tringlsoup[i + 2]);
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					
				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0} });
					tringlsoup_right.push_back(tringlsoup[i + 1]);

					tringlsoup_left.push_back({ tringlsoup[i + 1].pos , xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i + 2]);
					tringlsoup_left.push_back({ xyz1,{0,0,0} });

				}
				continue;
			}

			if ((point_1 > 0 && point_3 > 0) || (point_1 < 0 && point_3 < 0))
			{

				if (point_1 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i + 1]);
					tringlsoup_left.push_back(tringlsoup[i + 2]);

				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back(tringlsoup[i + 1]);
					tringlsoup_right.push_back(tringlsoup[i + 2]);


				}

			}
			continue;
		}
		if (point_3 == 0.0)
		{
			if ((point_2 > 0 && point_1 < 0) || (point_2 < 0 && point_1 > 0))
			{
				xyz1 = GetMidPoint(tringlsoup[i + 1].pos, tringlsoup[i].pos, origin, n_direction);

				if (point_1 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0} });
					tringlsoup_left.push_back(tringlsoup[i + 2]);

					tringlsoup_right.push_back({ tringlsoup[i+1].pos , xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i + 2]);
				}
				else
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0} });
					tringlsoup_left.push_back(tringlsoup[i + 2]);

					tringlsoup_right.push_back({ tringlsoup[i + 1].pos , xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i + 2]);

				}
				continue;
			}

			if ((point_2 > 0 && point_1 > 0) || (point_2 < 0 && point_1 < 0))
			{

				if (point_2 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i + 1]);
					tringlsoup_left.push_back(tringlsoup[i + 2]);

				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back(tringlsoup[i + 1]);
					tringlsoup_right.push_back(tringlsoup[i + 2]);


				}

			}
			continue;
		}


		if (point_1 > 0.0 && point_2 > 0.0 && point_3 > 0.0)
		{
			tringlsoup_left.push_back(tringlsoup[i]);
			tringlsoup_left.push_back(tringlsoup[i+1]);
			tringlsoup_left.push_back(tringlsoup[i+2]);
			continue;
		}

		if (point_1 < 0.0 && point_2 < 0.0 && point_3 < 0.0)
		{
			tringlsoup_right.push_back(tringlsoup[i]);
			tringlsoup_right.push_back(tringlsoup[i + 1]);
			tringlsoup_right.push_back(tringlsoup[i + 2]);
			continue;
		}
		
		
		

		if ((point_1 > 0.0 && point_2 > 0.0) || (point_1 < 0.0 && point_2 < 0.0))
		{
		
			//point between p1 and p3
			xyz1 = GetMidPoint(tringlsoup[i].pos, tringlsoup[i + 2].pos, origin, n_direction);
		
			//point between p2 and p3
			xyz2 = GetMidPoint(tringlsoup[i+1].pos, tringlsoup[i + 2].pos, origin, n_direction);

			//FillVec(point_1, tringlsoup, tringlsoup_left, tringlsoup_right, xyz1, xyz2, xyz_normal, i);
			if (point_1 > 0.0)
			{
				tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
				tringlsoup_left.push_back(tringlsoup[i + 1]);
				tringlsoup_left.push_back({ xyz1,{0} });

				tringlsoup_left.push_back({ tringlsoup[i + 1].pos,xyz_normal });
				tringlsoup_left.push_back({ xyz2,{0} });
				tringlsoup_left.push_back({ xyz1,{0} });

				tringlsoup_right.push_back({ xyz1,xyz_normal });
				tringlsoup_right.push_back({ xyz2,{0} });
				tringlsoup_right.push_back(tringlsoup[i + 2]);
			}
			else
			{
				tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
				tringlsoup_right.push_back({ xyz1,{0,0,0} });
				tringlsoup_right.push_back({ xyz2,{0,0,0} });

				tringlsoup_right.push_back({ tringlsoup[i].pos , xyz_normal });
				tringlsoup_right.push_back({ xyz2,{0,0,0} });
				tringlsoup_right.push_back(tringlsoup[i + 1]);

				tringlsoup_left.push_back({ tringlsoup[i + 2].pos,xyz_normal });
				tringlsoup_left.push_back({ xyz2,{0,0,0} });
				tringlsoup_left.push_back({ xyz1,{0,0,0} });
			}
		}
		else
		{
			if ((point_1 > 0.0 && point_3 > 0.0) || point_1 < 0.0 && point_3 < 0.0)
			{
				//point between p2 and p3
				xyz1 = GetMidPoint(tringlsoup[i+1].pos, tringlsoup[i + 2].pos, origin, n_direction);

				//point between p2 and p1
				xyz2 = GetMidPoint(tringlsoup[i + 1].pos, tringlsoup[i].pos, origin, n_direction);

				//FillVec(point_1, tringlsoup, tringlsoup_left, tringlsoup_right, xyz1, xyz2, xyz_normal, i);
				if (point_1 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i + 2]);
					tringlsoup_left.push_back({ xyz2,{0,0,0} });

					tringlsoup_left.push_back({ tringlsoup[i + 2].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0,0,0} });
					tringlsoup_left.push_back({ xyz2,{0,0,0} });

					tringlsoup_right.push_back({ xyz2,xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i + 1]);
				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_right.push_back({ xyz2,{0,0,0} });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });

					tringlsoup_right.push_back({ xyz1 , xyz_normal });
					tringlsoup_right.push_back({ tringlsoup[i+2] });
					tringlsoup_right.push_back(tringlsoup[i]);

					tringlsoup_left.push_back({ tringlsoup[i + 1].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0,0,0} });
					tringlsoup_left.push_back({ xyz2,{0,0,0} });
				}
			}
			else
			{
				//point between p1 and p3
				xyz1 = GetMidPoint(tringlsoup[i].pos, tringlsoup[i + 2].pos, origin, n_direction);
				//std::cout<<"p1:  " << tringlsoup[i].pos.x<<" " << tringlsoup[i].pos.y << " " << tringlsoup[i].pos.z << " "<<std::endl;
				//std::cout << "p2:  " << tringlsoup[i+2].pos.x << " " << tringlsoup[i+2].pos.y << " " << tringlsoup[i+2].pos.z << " " << std::endl;
				//std::cout << "mid:  " << xyz1.x << " " << xyz1.y << " " << xyz1.z << " \n" << std::endl;
				//point between p1 and p2
				xyz2 = GetMidPoint(tringlsoup[i].pos, tringlsoup[i+1].pos, origin, n_direction);

				//FillVec(point_2, tringlsoup, tringlsoup_left, tringlsoup_right, xyz1, xyz2, xyz_normal, i);
				if (point_2 > 0.0)
				{
					tringlsoup_left.push_back({ tringlsoup[i+1].pos,xyz_normal });
					tringlsoup_left.push_back(tringlsoup[i + 2]);
					tringlsoup_left.push_back({ xyz2,{0,0,0} });

					tringlsoup_left.push_back({ tringlsoup[i + 2].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0,0,0} });
					tringlsoup_left.push_back({ xyz2,{0,0,0} });

					tringlsoup_right.push_back({ xyz2,xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i]);
				}
				else
				{
					tringlsoup_right.push_back({ tringlsoup[i+1].pos,xyz_normal });
					tringlsoup_right.push_back({ xyz2,{0,0,0} });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });

					tringlsoup_right.push_back({ tringlsoup[i + 1].pos, xyz_normal });
					tringlsoup_right.push_back({ xyz1,{0,0,0} });
					tringlsoup_right.push_back(tringlsoup[i + 2]);

					tringlsoup_left.push_back({ tringlsoup[i].pos,xyz_normal });
					tringlsoup_left.push_back({ xyz1,{0,0,0} });
					tringlsoup_left.push_back({ xyz2,{0,0,0} });
				}

			}
		}

	}
	
	STLParser pars;
	pars.write(tringlsoup_left, "sphere_left.stl");
	pars.write(tringlsoup_right, "sphere_right.stl");
	return 0;
}

Vec Split::GetMidPoint(Vec & p1 ,Vec & p2,Vec & origin, Vec & direction)
{
	double t;
	t = (direction.x*(origin.x-p1.x)+ direction.y*(origin.y - p1.y)+ direction.z*(origin.z - p1.z)) / (direction.x*(p2.x-p1.x)+ direction.y*(p2.y - p1.y)+ direction.z*(p2.z - p1.z));

	return{ t*(p2.x-p1.x)+p1.x,t*(p2.y - p1.y) + p1.y,t*(p2.z - p1.z) + p1.z };
}
