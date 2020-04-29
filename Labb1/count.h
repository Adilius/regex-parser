#ifndef COUNT_H
#define COUNT_H

#include "op.h"

struct count : op {
	int countAmount = 0;		//Count amount

	object* eval(object* obj) override {
		object* temp = nullptr;

		while (countAmount > 0) {
			temp = operands[0]->eval(obj);
			if (!temp) {
				return nullptr;
			}
			countAmount--;
		}
		return temp;
	}

	std::string id() override {
		return "<count>(" + std::to_string(countAmount) + ")";
	}
};

#endif