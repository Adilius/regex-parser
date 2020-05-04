#ifndef COUNT_H
#define COUNT_H

#include "op.h"

struct count : op {
	int countAmount = 0;		//Count amount
	int countAmountTemp = 0;	//Used in function

	object* eval(object* obj) override {
		countAmountTemp = countAmount;
		object save = *obj;	//Object saved for when <count> fails
		object* temp = obj;

		while (countAmountTemp > 0) {
			temp = operands[0]->eval(obj);
			//std::cout << "I am iterating: " << countAmountTemp << " Current lhs: " << std::endl;

			if (temp == nullptr) {
				*obj = save;
				return nullptr;
			}

			countAmountTemp--;
		}
		//(std::cout << "I am returning" << std::endl;
		obj = temp;
		return obj;
	}

	std::string id() override {
		return "<count>(" + std::to_string(countAmount) + ")";
	}
};

#endif