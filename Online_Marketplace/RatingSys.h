#pragma once
#include "product.h"

class RatingSys
{

public:
	void avg_ratings(product*);
	void sorAsc(int catIndex);
	void sorDesc(int catIndex);
	void swapp(float* first, float* second);
};