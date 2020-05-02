#ifndef OP_H
#define OP_H

#include "object.h"

struct op {
	virtual object* eval(object* obj) = 0;
	virtual std::string id() = 0;
	std::vector<op*> operands;
};

#endif