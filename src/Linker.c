#include <stdio.h>

int buildGlobalTable(FILE *in, int *valTable, int start){
	int n, fsize;
	char label;

	fscanf(in,"%d\n",&fsize);

	while(1){
		fscanf(in,"%c",&label); 
		
		if(label=='#')
			break;

		fscanf(in,"%d\n",&n);

		valTable[label - 'A'] = start + n;
	}

	return fsize;
}

int link(FILE *in, FILE *out, int *valTable, int start){
	char flag = '!';
	int va,vb,n;

	fscanf(in,"%d",&n);

	while(1){
		fscanf(in,"%c",&flag); 
		
		if(flag=='#')
			break;

		fscanf(in,"%*d");
	}

	while(fscanf(in,"%c", &flag) == 1){
		if(flag == '!'){
			fscanf(in,"%d %d\n", &va, &vb);
			fprintf(out, "!%d %d\n", va, vb);
		}else if(flag == '*'){
			fscanf(in,"%d\n", &va);
			fprintf(out,"*%d\n", va);
		}else if(flag ==  '&'){
			fscanf(in,"%d\n", &va);
			fprintf(out,"*%d\n", va + start);
		}else if(flag ==  '$'){
			fscanf(in,"%c %d\n", &flag, &vb);
			fprintf(out,"!18 %d\n", valTable[flag - 'A'] + vb - start );
		}
	}

	return n;
}

int main(int argc, char *argv[]){

	FILE *in, *out;	
	int valTable[58],i,start=0;

	for(i=0;i<58;i++){
		valTable[i] = -1;
	}

	
	for(i=1;i<argc-1;i++){
		in = fopen(argv[i],"r");

		start += buildGlobalTable(in,valTable,start);

		if(!start){
			fprintf(stderr, "Erro ao fazer ao fazer o pré-processamento dos arquivos\n");
		}

		fclose(in);
	}

	out = fopen(argv[argc-1],"w");
	start = 0;


	for(i=1;i<argc-1;i++){
		in = fopen(argv[i],"r");

		start += link(in, out, valTable, start);

		if(!start){
			fprintf(stderr, "Erro ao fazer ao fazer a linkagem\n");
		}

		fclose(in);
	}

	fclose(out);

	return 0;
}