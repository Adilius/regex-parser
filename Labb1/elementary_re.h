#ifndef ELEMENTARY_RE_H
#define ELEMENTARY_RE_H

#include "op.h"

struct elementary_re : op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<elementary-RE>";
	}
};

#endif