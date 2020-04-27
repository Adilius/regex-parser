#ifndef GROUP_H
#define GROUP_H

#include "op.h"

struct group : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<group>";
	}
};

#endif