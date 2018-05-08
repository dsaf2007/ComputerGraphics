#pragma once

#include <iostream>
/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/


#include <fstream>
#include <vector>
#include "Vector3.h"
#include <algorithm>

class OBJReader
{
public:
	std::vector<Vector3<float> > pos_stack_;
	std::vector<Vector3<unsigned int> > ix_stack_;
	//Note: vector push_back is slow
	//Note: use unsigned int for indices

	void readObj(const char* filename)
	{
		using namespace std;

		std::cout << "Start reading OBJ file " << filename << std::endl;

		// to check if this obj file contains vt or vn data 
		bool read_vt(false), read_vn(false);

		const float max_limit = std::numeric_limits<float>::max();
		const float min_limit = std::numeric_limits<float>::min();

		Vector3<float> min(max_limit, max_limit, max_limit);
		Vector3<float> max(min_limit, min_limit, min_limit);

		ifstream file(filename);

		// check if file is opened correctly
		if (file.is_open() == false) { 
			std::cout << filename << " does not exist. Program terminated." << std::endl; exit(-1); }

		char c[255];

		while (true)
		{
			file >> c;

			if (file.eof() != 0) break;						// finish reading if file is ended

			if (strcmp(c, "#") == 0) file.getline(c, 255);  // comments (less than 255 characters)
			else if (strcmp(c, "v") == 0) // vertices
			{
				float x, y, z;
				file >> x >> y >> z;
				//std::cout << x << " " << y << " " << z << std::endl;

				pos_stack_.push_back(Vector3<float>(x, y, z));

				// bounding box
				max.x_ = std::max(max.x_, x);
				max.y_ = std::max(max.y_, y);
				max.z_ = std::max(max.z_, z);
				min.x_ = std::min(min.x_, x);
				min.y_ = std::min(min.y_, y);
				min.z_ = std::min(min.z_, z);
			}
			else if (strcmp(c, "vt") == 0)
			{
				read_vt = true;

				float u, v;
				file >> u >> v;

				//TODO: save texture coordinates

			}
			else if (strcmp(c, "vn") == 0)
			{
				read_vn = true;

				float nx, ny, nz;
				file >> nx >> nz >> ny;

				//TODO: save normal vectors
			}
			else if (strcmp(c, "f") == 0)
			{
				int v[3], vt[3], vn[3];
				if (read_vt == true && read_vn == true)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i]; file.get(c, 2);
						file >> vt[i]; file.get(c, 2);
						file >> vn[i];

						v[i]--;
						vt[i]--;
						vn[i]--;
					}
				}
				else if (read_vt == false && read_vn == true)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i]; file.get(c, 2); file.get(c, 2);
						file >> vn[i];
						v[i]--;
						vn[i]--;
					}
				}
				else if (read_vt == false && read_vn == false)
				{
					for (int i = 0; i < 3; i++)
					{
						file >> v[i];
						v[i]--;
					}
				}

				ix_stack_.push_back(Vector3<unsigned int>(v[0], v[1], v[2]));

				if (read_vt == true) {
					//TODO
				}

				if (read_vn == true) {
					//TODO
				}

				//std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
			}
		}

		file.clear();
		file.close();

		std::cout << "Reading complete." << std::endl;
		std::cout << "# of vertices " << pos_stack_.size() << std::endl;
		std::cout << "# of triangles " << ix_stack_.size() << std::endl;

		min.print();
		std::cout << " ";
		max.print();

		// move to min corner to origin
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			pos_stack_[i].x_ += min.x_/2;
			pos_stack_[i].y_ += min.y_/2;
			//pos_stack_[i].z_ += min.z_/2;
		}

		const float x_length = max.x_ - min.x_;// of bounding box 
		const float y_length = max.y_ - min.y_;
		const float z_length = max.z_ - min.z_;
		float max_length;
		if (x_length > y_length && x_length > z_length) {
			max_length = x_length;
		}
		else if (y_length > x_length && y_length > z_length) {
			max_length = y_length;
		}
		else {
			max_length = z_length;
		}
		// scale down the BB for the make largest length to be one (bounding box)
		// scale down the BB to a unit cube
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			pos_stack_[i].x_ /= max_length;
			pos_stack_[i].y_ /= max_length;
			pos_stack_[i].z_ /= max_length;
		}
   }

	void dump()
	{
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			pos_stack_[i].print();
			std::cout << std::endl;
		}

		// scale down the BB to a unit cube
		for (int i = 0; i < pos_stack_.size(); i++)
		{
			ix_stack_[i].print();
			std::cout << std::endl;
		}
	}
};
