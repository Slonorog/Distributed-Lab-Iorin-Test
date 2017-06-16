#include "controller.h"

int main() {
	Controller c;
	c.Load("data.xml");
	c.makeMatrPrice();
	c.DeikstraforPriceLess();
	return 0;
}