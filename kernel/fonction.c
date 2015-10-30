#include "fonction.h"


void *memset (void * dst, int value, unsigned int count) {
	char *dp = dst;
	unsigned int i;
	for (i = 0; i < count; ++i)
		{
			dp[i] = value;
		}	
	return dst;
}


void *memcpy (void * dst, void *src, unsigned int count) {
	unsigned int i;
	char * dp = dst;
	const char * sp = src;
	for (i = 0; i < count; ++i)
	{
		dp[i] = sp[i];
	}
	return dst;
}


int strncmp (const char *p, const char *q, unsigned int n) {
	unsigned int i;
	for (i = 0; i < n; ++i)
	{
		if(p[i] != q[i]) {
			if(p[i] < q[i])
				//the first character that does not match has a lower value in p than in q
				return -1;
			else
				//the first character that does not match has a greater value in p than in q
				return 1;
		}
	}

	//the contents of both strings are equal
	return 0;
}