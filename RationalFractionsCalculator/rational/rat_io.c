#include <stdio.h>
#include <string.h>
#include "rational.h"

void printio(rational_t c) {

 if (rat_denom(c) == 1){
        printf("%d",rat_num(c));
    }
    else{
        printf("%d/%d",rat_num(c),rat_denom(c));
    }
}

 rational_t qwe (char val[], rational_t last) {

	if (strstr(val,"last") !=  NULL) {	
		return last;
	}
	else if (strstr(val,"/") != NULL) {
		int n,d;
		sscanf(val,"%d/%d", &n, &d);
		return rational(n,d);
	} 
	else {
		return rational(atoi(val),1);
	}
}