#include <stdio.h>
#include "max.h"

int main(){
	int x = 20;
	int y = 10;

	int max = 0;
	
	max = find_max(x, y);
	printf("max: %d\n", max);
	return 0;
}
