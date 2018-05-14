#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <string>
#if (defined __cplusplus) && (__cplusplus >= 201700L)
#include <optional>
#else
#include "optional.hpp"
#endif

extern std::string CopyBefore(const std::string& s, char delimiter);

#endif /* _ALGORITHM_H_ */
