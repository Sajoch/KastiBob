//https://gist.github.com/albertz/1551304
//Author albertz
//Changed
#include <stdio.h>

int main(int argc, char** argv) {
	if(argc != 2){
			printf("using: <file>\n");
			return 1;
	}
	char* fn = argv[1];
	FILE* f = fopen(fn, "r");
	printf("unsigned char a[] = {");
	unsigned long n = 0;
	while(!feof(f)) {
		unsigned char c;
		if(fread(&c, 1, 1, f) == 0) break;
		printf("0x%.2X,", (int)c);
		++n;
	}
	fclose(f);
	printf("};\n");
	printf("unsigned long al=%d;\n",n);
	return 0;
}
