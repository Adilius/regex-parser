#ifndef BASIC_RE_H
#define BASIC_RE_H

#include "op.h"

struct basic_re : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<basic-RE>";
	}
};

#endif