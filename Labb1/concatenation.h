#ifndef CONCATENATION_H
#define CONCATENATION_H

#include "op.h"
#include "object.h"

using IT = std::string::iterator;

struct concatenation : op {
	object* eval(object* obj) override {
		//Save pointer at start of <concatenation>
		IT obj_begin = obj->lhs;
		obj->lhs = obj->rhs;
		object* basic = operands[0]->eval(obj);

		//If first operand is not basic-RE, return nullptr
		if (!basic) {
			return nullptr;
		}

		//Proceed with basic-RE
		IT basic_begin = basic->lhs;
		basic->lhs = basic->rhs;
		object* simple = operands[1]->eval(basic);

		bool backtrack = false;

		//If <basic-RE> returned nullptr
		while(basic->rhs != basic_begin  && !simple) {
			backtrack = true;
			if (basic_begin == basic->rhs) {
				return nullptr;
			}
			simple = operands[1]->eval(basic);

			basic->rhs--;
			//basic->lhs--;
		}

		if (simple) {
			if (backtrack) {
				simple->cap.push_back({ basic_begin, basic->rhs + 1 });
				std::swap(simple->cap[1], simple->cap[0]);

				size_t size = 0;
				for (IT i = simple->cap[1].lhs; i != simple->cap[1].rhs; i++) {
					size++;
				}
				simple->cap[0].rhs -= size;
			}
			simple->lhs = obj_begin;

			return simple;
		}

		return nullptr;

	}

	std::string id() override {
		return "<concatenation>";
	}
};

#endif