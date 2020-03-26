#ifndef PLUS_H
#define PLUS_H
#include "op.h"

struct plus :op {
	object* eval(object* obj) override {
		return operands[0]->eval(obj);
	}
	std::string id() override {
		return "plus";
	}
};

#endif