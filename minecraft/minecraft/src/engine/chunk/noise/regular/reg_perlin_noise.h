#ifndef REG_PERLIN_NOISE_HEADER
#define REG_PERLIN_NOISE_HEADER

#include "../perlinnoise.h"

namespace chunk
{
	namespace noise
	{
		class Reg_PerlinNoise
			: public PerlinNoise
		{
		public:
			explicit Reg_PerlinNoise(signed int seed);
		public:
			float Height(const glm::vec2& blockwCoordXZ, const CCorners& coords, const GradientVectors& gv) override;
			const GradientVectors GVectors(const CCorners& ccoords) override;
		private:
			const glm::vec2 GenerateGradientVector(const glm::vec2& corner);
			const DifferenceVectors DVectors(const glm::vec2& blockwCoordXZ, const CCorners& coords);
			__forceinline float Lerpx(glm::vec2 a, glm::vec2 b, float y)
			{
				return a.x + ((y - a.y) / (b.y - a.y)) * (b.x - a.x);
			}
			__forceinline float Lerpy(glm::vec2 a, glm::vec2 b, float x)
			{
				return a.y + ((x - a.x) / (b.x - a.x)) * (b.y - a.y);
			}
		private:
			const signed int MAX;
			const glm::vec2 m_permutations[4];
		};
	}
}

#endif