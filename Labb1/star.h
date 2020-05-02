#ifndef STAR_H
#define STAR_H

#include "op.h"

struct star : op {
	object* eval(object* obj) override {
		object* temp = obj;
		object* save = obj;

		save = temp;
		temp = operands[0]->eval(obj);

		if (temp != nullptr) {

			while (temp != nullptr) {
				save = temp;
				temp = operands[0]->eval(obj);
			}

		}


		return save;
	}

	std::string id() override {
		return "<star>";
	}
};

#endif