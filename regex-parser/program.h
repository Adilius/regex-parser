#ifndef PROGRAM_H
#define PROGRAM_H

#include "op.h"

struct program : op {
	object* eval(object* obj) override {
		//While we have not reached the end of the text
		while (obj->rhs != obj->end) {
			object* re = operands[0]->eval(obj);

			//If we got valid result back
			if (re) {
				return re;
			}

			//Move to next character
			obj->lhs = ++obj->rhs;
		}
		return nullptr;
	}

	std::string id() override {
		return "<program parse>";
	}
};

#endif