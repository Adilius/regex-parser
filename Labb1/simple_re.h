#ifndef SIMPLE_RE_H
#define SIMPLE_RE_H

#include "op.h"

struct simple_re : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<simple-RE>";
	}
};

#endif