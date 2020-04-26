#ifndef CHARACTER_H
#define CHARACTER_H

#include <algorithm>	//std::transform
#include "op.h"
#include "object.h"

struct character : op {
	std::string _id; //Identifier

	object* eval(object* obj) override {

		if (obj->lowercase){
			std::transform(_id.begin(), _id.end(), _id.begin(), ::tolower);
		
		}

		//Check characters
		for (size_t i = 0; i < _id.size(); i++) {
			//Check if we reached end of string
			if (obj->rhs + i == obj->end) {
				return nullptr;
			}

			//If not match
			if ( *(obj->rhs + i) != *(_id.begin() + i) ) {
				return nullptr;
			}
		}
		obj->cap.push_back({ obj->rhs , obj->rhs += _id.size() });
		return obj;

	}

	std::string id() override {
		return "<character>(" + this->_id + ")";
	}
};

#endif