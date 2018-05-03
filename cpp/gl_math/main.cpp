#include <iostream>
#include <iterator>

#include "matrix.h"
#include "vector.h"
#include "vector_math.h"
#include "vector_output.h"

int main(int argc, char* argv[])
{
  // dot product
  vec3<float> v1(1.0f, 0.0f, 0.0f);
  vec3<float> v2(0.0f, 1.0f, 0.0f);
  std::cout << Dot(v1, v2) << "\n";

  // cross product
  vec3<float> v3(Cross(v1, v2));
  std::cout << v3 << "\n";

  // normalization
  vec3<float> unnorm(3.0f, 0.0f, 0.0f);
  vec3<float> norm = Normalize(unnorm);
  std::cout << norm << "\n";
  matrix<float, 3> mat(1.0f);
  std::cout << "\n" << mat << "\n";
}
