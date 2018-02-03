#include "reg_perlin_noise.h"
#include <iostream>
#include <math.h>

namespace chunk
{
	namespace noise
	{
		Reg_PerlinNoise::Reg_PerlinNoise(signed int seed)
			: MAX(20), m_permutations{ glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, -1.0f), glm::vec2(-1.0f, 1.0f), glm::vec2(-1.0f, -1.0f) }
		{
			m_seed = seed;
		}
		float Reg_PerlinNoise::Height(const glm::vec2& blockwCoordXZ, const CCorners& corners, const GradientVectors& gv)
		{
			DifferenceVectors dv = DVectors(blockwCoordXZ / 128.0f, corners);
			float dotnn = sin(glm::dot(gv.nn, dv.nn));
			//std::cout << dotnn << " \t";
			float dotnp = sin(glm::dot(gv.np, dv.np));
			//std::cout << dotnp << " \t";
			float dotpn = sin(glm::dot(gv.pn, dv.pn));
			//std::cout << dotpn << " \t";
			float dotpp = sin(glm::dot(gv.pp, dv.pp));
			//std::cout << dotpp << " \t" << std::endl;
			
			//float av = (dotnn + dotnp + dotpn + dotpp) / 4.0f;
			//std::cout << av << std::endl;
			float nx = Lerpy(glm::vec2(corners.nn.x, dotnn), glm::vec2(corners.pn.x, dotpn), blockwCoordXZ.x);
			float px = Lerpy(glm::vec2(corners.np.x, dotnp), glm::vec2(corners.pp.x, dotpp), blockwCoordXZ.x);

			float av = Lerpy(glm::vec2(corners.np.y, px), glm::vec2(corners.nn.y, nx), blockwCoordXZ.y);

			return av * MAX;
		}
		const PerlinNoise::GradientVectors Reg_PerlinNoise::GVectors(const CCorners& coords)
		{
			return { GenerateGradientVector(coords.nn), GenerateGradientVector(coords.np), 
				GenerateGradientVector(coords.pn), GenerateGradientVector(coords.pp) };
		}
		const glm::vec2 Reg_PerlinNoise::GenerateGradientVector(const glm::vec2& corner)
		{
			signed int h1 = std::hash<signed int>()(static_cast<signed int>(corner.x * 0x123a)) % 0xffff;
			signed int h2 = std::hash<signed int>()(static_cast<signed int>(corner.y * 0x12fb)) % 0xffff;
			signed int hash = h1 + h2;
		//	std::cout << "\t\t\t" << hash + m_seed << std::endl;
			srand(hash + m_seed);

			float rx = rand() % 0xff;
			float rz = rand() % 0xff;
	
		//	std::cout << rx << " " << rz << std::endl;
			return glm::normalize(glm::vec2((rx / 0xff) - 0.5f, (rz / 0xff) - 0.5f)) * 16.0f;
			//return glm::normalize(m_permutations[rand() % 4]);
			//return glm::vec2(1.0f, 1.0f);
		}
		const PerlinNoise::DifferenceVectors Reg_PerlinNoise::DVectors(const glm::vec2& blockwCoordXZ, const CCorners& corners)
		{
			glm::vec2 nn = blockwCoordXZ - corners.nn;
			glm::vec2 np = blockwCoordXZ - corners.np;
			glm::vec2 pn = blockwCoordXZ - corners.pn;
			glm::vec2 pp = blockwCoordXZ - corners.pp;
			return { nn, np, pn, pp };
		}
	}
}