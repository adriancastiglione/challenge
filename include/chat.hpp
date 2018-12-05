#ifndef CHAT_H
#define CHAT_H

#include <memory>
#include <cstdlib>
#include <restbed>
#include "json.hpp"

struct f{

	int fact(unsigned x){
		if (x <= 1) return 1;
		return x*fact(x-1);
	}
};

#endif