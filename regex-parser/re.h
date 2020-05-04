#ifndef RE_H
#define RE_H

#include "op.h"

struct re : op {

	object* eval(object* obj) override{
		return operands[0]->eval(obj);
	}

	std::string id() override {
		return "<RE>";
	}
};

#endif