#ifndef CONCATENATION_H
#define CONCATENATION_H

#include "op.h"

using IT = std::string::iterator;

struct concatenation : op {
	object* eval(object* obj) override {
		//Save pointers to start of <concatenation> which is <basic-RE>
		IT basic_begin = obj->lhs;
		obj->lhs = obj->rhs;

		//Evaluate <basic-RE>
		object* basic_re = operands[0]->eval(obj);

		//If <basic-RE> failed, return nullptr
		if (!basic_re) {
			obj->lhs = obj->rhs = basic_begin;	//Reset iterators
			return nullptr;
		}

		//Save pointers at start of <simple-RE>
		IT simple_begin = basic_re->lhs;
		basic_re->lhs = basic_re->rhs;

		//Evaluate <simple-RE>
		object* simple_re = operands[1]->eval(basic_re);

		//If <simple-RE> failed, return nullptr
		if (!simple_re) {
			obj->lhs = obj->rhs = basic_begin;	//Reset iterators
			return nullptr;
		}

		//Add the result of <basic-RE> to <simple-RE> and return it as <concatenation>
		simple_re->lhs = basic_begin;
		return simple_re;
	}

	std::string id() override {
		return "<concatenation>";
	}
};

#endif