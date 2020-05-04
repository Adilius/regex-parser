#ifndef CHARACTER_H
#define CHARACTER_H

#include <algorithm>	//std::transform
#include "op.h"
#include "object.h"

struct character : op {
	std::string _id; //Identifier

	object* eval(object* obj) override {
		//Check if we reached end of string
		if (obj->rhs == obj->end) {
			return nullptr;
		}

		//If not match
		if (*obj->rhs != *_id.begin()) {
			return nullptr;
		}

		//Match, return character
		obj->rhs++;
		return obj;

	}

	std::string id() override {
		return "<character>(" + this->_id + ")";
	}
};

#endif