#ifndef PROGRAM_H
#define PROGRAM_H

#include "op.h"
#include "object.h"

struct program : op {
	object* eval(object* obj) override {
		while (obj->rhs != obj->end) {
			object* re = operands[0]->eval(obj);
			if (re) {
				return re;
			}
			obj->lhs = ++obj->rhs;
		}
		return nullptr;
	}

	std::string id() override {
		return "program";
	}
};

#endif