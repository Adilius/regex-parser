#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

using IT = std::string::iterator;

struct iter {
	IT lhs;
	IT rhs;
};

struct object {
	IT lhs;
	IT rhs;
	IT end;
	size_t captured = 0;
	std::vector<iter> cap;
};

#endif