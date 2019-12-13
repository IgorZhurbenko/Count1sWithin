#include <stdio.h>

void readfile(char[] FileName, char *ar)
{
	FILE *f = fopen(FileName,"r");
	fscanf(f,"%d%d", ar[1], ar[2]);	
	fclose(f);
}

int main()
{
	int ar[2];
	
	readfile("in.txt",ar);

	printf("%d%d", ar[1],ar[2]);
	
}
