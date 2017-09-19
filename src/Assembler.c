#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse(FILE *in, FILE *out, int *valTable, int n){
	char symbol;
	char inst[4];
	char opr[8];
	int iCount=0;
	int jump = 2;

	fprintf(out,"%d\n",n);

	for(iCount=0;iCount<48;iCount++){
		if(valTable[iCount]!=-1){
			fprintf(out,"%c %d\n", iCount+'A', valTable[iCount]);
		}
	}

	fprintf(out, "#\n");

	iCount = 0;

	while(!feof(in)){
		fscanf(in,"%c%*c%s",&symbol,inst);
		iCount += jump;

		if(strcmp(inst,"HLT")==0){
			fprintf(out, "!11 00\n");
			jump = 2;
			while(getc(in)!='\n');
			continue;
		}else if(strcmp(inst,"RET")==0){
			fprintf(out, "!19 00\n");
			jump = 2;
			while(getc(in)!='\n');
			continue;
		}else if(strcmp(inst,"LAI")==0){
			fprintf(out, "!20 00\n");
			jump = 2;
			while(getc(in)!='\n');
			continue;
		}else if(strcmp(inst,"SAI")==0){
			fprintf(out, "!21 00\n");
			jump = 2;
			while(getc(in)!='\n');
			continue;
		}

		fscanf(in,"%s%*c",opr);

		if(strcmp(inst,"LAD")==0){
			fprintf(out, "!01 ");
			jump = 2;
		}else if(strcmp(inst,"SAD")==0){
			fprintf(out, "!02 ");
			jump = 2;
		}else if(strcmp(inst,"ADD")==0){
			fprintf(out, "!03 ");
			jump = 2;
		}else if(strcmp(inst,"SUB")==0){
			fprintf(out, "!04 ");
			jump = 2;
		}else if(strcmp(inst,"INP")==0){
			fprintf(out, "!05 ");
			jump = 2;
		}else if(strcmp(inst,"OUT")==0){
			fprintf(out, "!06 ");
			jump = 2;
		}else if(strcmp(inst,"JMP")==0){
			fprintf(out, "!07 ");
			jump = 2;
		}else if(strcmp(inst,"JGZ")==0){
			fprintf(out, "!08 ");
			jump = 2;
		}else if(strcmp(inst,"JLZ")==0){
			fprintf(out, "!09 ");
			jump = 2;
		}else if(strcmp(inst,"JZE")==0){
			fprintf(out, "!10 ");
			jump = 2;
		}else if(strcmp(inst,"LXD")==0){
			fprintf(out, "!12 ");
			jump = 2;
		}else if(strcmp(inst,"SXD")==0){
			fprintf(out, "!13 ");
			jump = 2;
		}else if(strcmp(inst,"LAX")==0){
			fprintf(out, "!14 ");
			jump = 2;
		}else if(strcmp(inst,"SAX")==0){
			fprintf(out, "!15 ");
			jump = 2;
		}else if(strcmp(inst,"LCD")==0){
			fprintf(out, "!16 ");
			jump = 2;
		}else if(strcmp(inst,"JCC")==0){
			fprintf(out, "!17 ");
			jump = 2;
		}else if(strcmp(inst,"CAL")==0){
			if(valTable[opr[0] - 'A']!=-1)
				fprintf(out, "!18 %02d\n", (int) valTable[opr[0] - 'A'] - iCount);
			else
				fprintf(out, "$%c\n",opr[0]);
			jump = 2;
			continue;
		}else if(strcmp(inst,"DOB")==0){
			fprintf(out, "!22 ");
			jump = 2;
		}else if(strcmp(inst,"MET")==0){
			fprintf(out, "!23 ");
			jump = 2;
		}else if(strcmp(inst,"JPA")==0){
			fprintf(out, "!24 ");
			jump = 2;
		}else if(strcmp(inst,"DC")==0){
			fprintf(out, "*%s\n",opr);
			jump = 1;
			continue;
		}else if(strcmp(inst,"DA")==0){
			fprintf(out, "*%02d\n", (int) valTable[opr[0] - 'A']);
			jump = 1;
			continue;
		}else if(strcmp(inst,"DS")==0){
			if(opr[0]>'0'+9){
				jump = (int) valTable[opr[0] - 'A'];
			}else{
				jump = (int) atoi(opr);
			}
			while(jump--){
				fprintf(out, "*0\n");
				iCount++;
			}
			continue;
		}else{
			continue;
		}
		
		if(opr[0]>'0'+9){
			fprintf(out, "%02d\n", (int) valTable[opr[0] - 'A'] - iCount);
		}else{
			fprintf(out, "%02d\n", (int) atoi(opr) - iCount);
		}	
	}

	return 0;
}

int process(FILE *in, int *valTable, int *iCount){
	char symbol;
	char inst[4];
	char opr[8];
	int jump = 0;

	while(!feof(in)){
		(*iCount) += jump;

		fscanf(in,"%c%*c%s",&symbol,inst);
		
		if(symbol!=' '){
			valTable[symbol - 'A'] = (*iCount);
		}

		if(strcmp(inst,"HLT")==0 || 
			strcmp(inst,"RET")==0 ||
			strcmp(inst,"LAI")==0 ||
			strcmp(inst,"SAI")==0){
			getc(in);
			getc(in);
			jump = 2;
			while(getc(in)!='\n');
			continue;
		}

		fscanf(in,"%s%*c",opr);

		if(strcmp(inst,"DC")==0){
			jump = 1;
		}else if(strcmp(inst,"DA")==0){
			jump = 1;
		}else if(strcmp(inst,"DS")==0){
			jump = (int) atoi(opr);
		}else{
			jump = 2;
		}
		
	}

	return 0;
}

int main(int argc, char *argv[]){

	FILE *in, *out;	
	int valTable[58],iCount=0;

	for(iCount=0;iCount<58;iCount++){
		valTable[iCount] = -1;
	}

	iCount = 0;

	in = fopen(argv[1],"r");

	if(process(in,valTable,&iCount)){
		fprintf(stderr, "Erro ao fazer ao fazer o pré-processamento\n");
	}

	fclose(in);

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");

	if(parse(in,out,valTable,iCount)){
		fprintf(stderr, "Erro ao fazer a montagem\n");
	}

	fclose(in);
	fclose(out);

	return 0;
}