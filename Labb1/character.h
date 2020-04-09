#ifndef CHARACTER_H
#define CHARACTER_H

#include <algorithm>
#include "op.h"
#include "object.h"

struct character : op {
	std::string _id; //Identifier

	object* eval(object* obj) override {
		if (obj->lowercase) { std::transform(_id.begin(), _id.end(), _id.begin(), ::tolower); }
		for (int i = 0; i < _id.size(); i++) {
			if (*(obj->rhs + i) != *(_id.begin() + i)) {
				return nullptr;
			}
		}
		obj->cap.push_back({ obj->rhs , obj->rhs += _id.size() });

	}

	std::string id() override {
		return "character(" + this->_id + ")";
	}
};

#endif