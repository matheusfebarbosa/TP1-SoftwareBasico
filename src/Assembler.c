#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int assembler(FILE *in, FILE *out, int *valTable){
	char symbol;
	char inst[4];
	char opr[8];
	int iCount=0;

	while(!feof(in)){
		fscanf(in,"%c%*c%s%*c%s%*c",&symbol,inst,opr);

		iCount+=2;

		if(strcmp(inst,"LAD")==0){
			fprintf(out, "01 ");
		}else if(strcmp(inst,"SAD")==0){
			fprintf(out, "02 ");
		}else if(strcmp(inst,"ADD")==0){
			fprintf(out, "03 ");
		}else if(strcmp(inst,"SUB")==0){
			fprintf(out, "04 ");
		}else if(strcmp(inst,"INP")==0){
			fprintf(out, "05 ");
		}else if(strcmp(inst,"OUT")==0){
			fprintf(out, "06 ");
		}else if(strcmp(inst,"JMP")==0){
			fprintf(out, "07 ");
		}else if(strcmp(inst,"JGZ")==0){
			fprintf(out, "08 ");
		}else if(strcmp(inst,"JLZ")==0){
			fprintf(out, "09 ");
		}else if(strcmp(inst,"JZE")==0){
			fprintf(out, "10 ");
		}else if(strcmp(inst,"HLT")==0){
			fprintf(out, "11 00\n");
			return 0;
		}else if(strcmp(inst,"LXD")==0){
			fprintf(out, "12 ");
		}else if(strcmp(inst,"SXD")==0){
			fprintf(out, "13 ");
		}else if(strcmp(inst,"LAX")==0){
			fprintf(out, "14 ");
		}else if(strcmp(inst,"SAX")==0){
			fprintf(out, "15 ");
		}else if(strcmp(inst,"LCD")==0){
			fprintf(out, "16 ");
		}else if(strcmp(inst,"JCC")==0){
			fprintf(out, "17 ");
		}

		if(opr[0]>'0'+9){
			fprintf(out, "%02d\n", (int) valTable[opr[0] - 'A'] - iCount);
		}else{
			fprintf(out, "%02d\n", (int) atoi(opr));
		}	
	}

	return 1;
}

int process(FILE *in, int *valTable){
	char symbol;
	char inst[4];
	char opr[8];
	int iCount=0;

	while(!feof(in)){
		fscanf(in,"%c%*c",&symbol);
		fscanf(in,"%s%*c",inst);
		
		if(strcmp(inst,"HLT")==0){
			getc(in);
			getc(in);
			iCount+=2;
			continue;
		}

		fscanf(in,"%s%*c",opr);

		if(symbol!=' '){
			if(strcmp(inst,"DC")==0){
				valTable[symbol - 'A'] = iCount++ + atoi(opr);	
				continue;
			}else{
				valTable[symbol - 'A'] = iCount;
			}	
		}


		iCount+=2;
	}

	return 0;
}

int main(int argc, char *argv[]){

	FILE *in, *out;	
	int valTable[26];

	in = fopen(argv[1],"r");

	if(process(in,valTable)){
		fprintf(stderr, "Erro ao fazer ao fazer o pré-processamento\n");
	}

	fclose(in);

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");

	if(assembler(in,out,valTable)){
		fprintf(stderr, "Erro ao fazer a montagem\n");
	}

	fclose(in);
	fclose(out);

	return 0;
}