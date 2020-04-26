#ifndef RE_H
#define RE_H

#include "op.h"
#include "object.h"

//<RE>		::=		<substitute>	|	<simple-RE>
struct re : op {

	object* eval(object* obj) override{
		obj = operands[0]->eval(obj);
		if (obj) {
			if (obj->captured >= 1) {
				obj->lhs = obj->cap[obj->captured].lhs;
				obj->rhs = obj->cap[obj->captured].rhs;
			}
		}
		return obj;
	}

	std::string id() override {
		return "<RE>";
	}
};

#endif