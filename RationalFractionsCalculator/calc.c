#include <stdio.h>	
#include <string.h>
#include <stdlib.h>
#include "rational/rational.h"
#include "rational/rat_io.h"
#include "rational/rat_math.h"

int main() {

	rational_t last = rational(1,10);

	char a1[10],a2[10],a3[10];

while(1) {
		scanf("%s %s %s", a1,a2,a3);

		rational_t n = qwe(a1, last);
		rational_t d = qwe(a3, last);

		rational_t c;
		
		if (strstr(a2,"+") != NULL) {
			c = rat_add(n,d);
		}
        else if (strstr(a2,"-") != NULL) {
            c = rat_sub(n,d);
        }
        else if (strstr(a2,"*") != NULL) {
            c = rat_mul(n,d);
        }
        else if (strstr(a2,"/") != NULL) {
            c = rat_div(n,d);
        }

    last.num = rat_num(c);
    last.denom = rat_denom(c);

    printf ("= ");
    printio(last);
    printf ("\n"); 
}
return 0;	
}	