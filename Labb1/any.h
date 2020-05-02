#ifndef ANY_H
#define ANY_H

#include "op.h"

struct any : op {
	object* eval(object* obj) override{
		//Check if we reached end of string
		if (obj->rhs + 1 == obj->end) {
			obj->rhs++;	//Get the last character
			return nullptr;
		}

		obj->rhs++;
		return obj;
	}

	std::string id() override {
		return "<any>";
	}
};

#endif