#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char BYTE;
#define BLOCK_SIZE  512

void P_RC4(BYTE * buf, USHORT len)
{
	BYTE S[256],K[256],temp;
	USHORT i,j,t,x;
	BYTE key[16]={222,178,4,22,11,5,3,4,233,44,67,56,67,89,99,1};
	
	j = 0;
	for(i=0; i<256; i++){
		S[i] = (BYTE)i;
		j&=0x0f;
		K[i] = key[j];
		j++;
	}
	
	j = 0;
	for(i=0; i<256; i++){
		j = (j + S[i] + K[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
	
	i = j = 0;
	for(x=0; x<len; x++){
		i = (i+1) % 256;
		j = (j + S[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
		t = (S[i] + (S[j] % 256)) % 256;
		buf[x] = buf[x] ^ S[t];
	}
}

int main(int argc, char *argv[])
{
	int ret = -1;
	FILE *fpIn = NULL;
	FILE *fpOut = NULL;
	char *input_file = NULL;
	char *output_file = NULL;
	unsigned char *buf = NULL;
	unsigned int ifile_size;
	int i;
	int read_size;

	if (argc < 3) {
		printf("invalid arguments!!!\n");
		printf("USAGE: %s input_file output_file\n", argv[0]);

	} else {
		input_file = argv[1];
		output_file = argv[2];
	}
	buf = malloc(BLOCK_SIZE);
	if (!buf) {
		printf("alloc %d fail\n", BLOCK_SIZE);
		goto exit;
	}
	fpIn = fopen(input_file, "rb");
	if (!fpIn) {
		printf("opening %s fail\n", input_file);
		goto exit;
	}
	fpOut = fopen(output_file, "wb");
	if (!fpOut) {
		printf("creating %s fail\n", output_file);
		goto exit;
	}
	fseeko(fpIn, 0, SEEK_END);
	ifile_size = ftello(fpIn);
	printf("%s file size is %d bytes\n", input_file, ifile_size);
	fseeko(fpIn, 0, SEEK_SET);
	read_size = BLOCK_SIZE;
	for(i = 0; i < ifile_size/BLOCK_SIZE; i++) {
		memset(buf, 0, BLOCK_SIZE);
		if( fread(buf, 1, read_size, fpIn) != read_size ) {
			goto exit;
		}
		P_RC4(buf, BLOCK_SIZE);
		if( fwrite(buf, 1, read_size, fpOut) != read_size ) {
			goto exit;
		}
	}
	ret = 0;
exit:
	if (!ret) {
		printf("success!!!\n");
	} else {
		printf("fail!!!\n");
	}
	if (buf)
		free(buf);
	if (fpOut)
		fclose(fpOut);
	if (fpIn)
		fclose(fpIn);
	return ret;
}
