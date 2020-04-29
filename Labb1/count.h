#ifndef COUNT_H
#define COUNT_H

#include "op.h"

struct count : op {
	int countAmount = 0;		//Count amount

	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<count>(" + std::to_string(countAmount) + ")";
	}
};

#endif