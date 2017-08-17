#include "graphics\Context.h"
#include <iostream>

int main() {
	Context context;
	context.init();		

	while (context.step()) {
		
		
	}
	context.exit();

	return 0;
}