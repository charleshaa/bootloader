void *memset (void * dst, int valie, uint count);
void *memcpy (void * dst, void *src, uint count);
int strncmp (const char *p, cont char *qm uint n);



void *memset (void * dst, int value, uint count) {
	int i;
	for (int i = 0; i < count; ++i)
		{
			dst[i] = value;
		}	
	return dst;
}


void *memcpy (void * dst, void *src, uint count) {
	int i;
	for (int i = 0; i < count; ++i)
	{
		dst[i] = src[i];
	}
	return dst;
}


int strncmp (const char *p, cont char *qm uint n) {
	int i;
	for (int i = 0; i < n; ++i)
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