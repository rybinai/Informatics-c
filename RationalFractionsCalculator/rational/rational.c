#include <stdio.h>
#include "rational.h"

rational_t rational(int n,int d) {
	int s,q;
	s = abs(n);
	q = abs(d);
	while ((s != 0) && (q != 0)) {
		if (s > q) {
			s = s % q;
		}
		else {
			q = q % s;
		}
	} 
		n = n/(s+q); 
		d = d/(s+q);

	 if (n == 0) {
		rational_t abba = {0, 1};
		return abba;
	}
	 if (d == 0) {
		rational_t abba = {0, 0};
		return abba;
	} 

	rational_t abba = {n, d};
    return abba;
}

int rat_num(rational_t r) {
	return r.num;
}

int rat_denom(rational_t r) {
	return r.denom;
}