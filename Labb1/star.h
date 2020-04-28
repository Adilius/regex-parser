#ifndef STAR_H
#define STAR_H

#include "op.h"

struct star : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<star>";
	}
};

#endif