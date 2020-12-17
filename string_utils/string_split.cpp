#include <stdio.h>
#include <string.h>

int max_items = 1024;
int main(int argc, char *argv[])
{
	char *pItems[max_items] = {0};
	int nItems[max_items] = {0}, index = 0;
	int i = 0, buf_size;
	char *pchar = NULL, *p, *p1, *pend;
	const char *p_arg_str = NULL, *pTags = ";";
	bool end = false;

	if (argc >= 3) {
		p_arg_str = argv[1];
		pTags = argv[2];
	} else if ( argc == 2) {
		p_arg_str = argv[1];
	} else {
		printf("arg can not less than two\n");
		return -1;
	}
	buf_size = strlen(p_arg_str) + 1;
	pchar = new char[buf_size];
	if (!pchar) {
		printf("alloc memory fail\n");
		return -1;
	}
	memcpy(pchar, p_arg_str, buf_size);
	p = pchar;
	pend = pchar + buf_size;
	while(p < pend) {/*;;;;*/
		p1 = strchr(p, pTags[0]);
		if (p1) {
			p1[0] = '\0';
		} else {
			end = true;
		}
		pItems[index] = p;
		nItems[index] = strlen(pItems[index]);
		index ++;
		if (end)
			break;
		p = p1 + 1;
	}
	for(i = 0; i < index; i++) {
		printf("%04dst part[len:%04d]: %s\n", i, nItems[i], pItems[i]);
	}
exit:
	//if(pItems) 
	if (pchar)
		delete[] pchar;
}

