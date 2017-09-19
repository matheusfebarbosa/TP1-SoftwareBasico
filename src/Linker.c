#include <stdio.h>

int buildGlobalTable(FILE *in, int *valTable){
	

	return 0;
}

int link(FILE *in, FILE *out, int *valTable){
	

	return 0;
}

int main(int argc, char *argv[]){

	FILE *in, *out;	
	int valTable[58],i;

	for(i=0;i<58;i++){
		valTable[i] = -1;
	}

	
	for(i=1;i<argc-1;i++){
		in = fopen(argv[i],"r");

		if(buildGlobalTable(in,valTable)){
			fprintf(stderr, "Erro ao fazer ao fazer o pré-processamento dos arquivos\n");
		}

		fclose(in);
	}

	out = fopen(argv[argc-1],"w");

	for(i=1;i<argc-1;i++){
		in = fopen(argv[i],"r");

		if(link(in,out,valTable)){
			fprintf(stderr, "Erro ao fazer ao fazer a linkagem\n");
		}

		fclose(in);
	}

	fclose(out)

	return 0;
}