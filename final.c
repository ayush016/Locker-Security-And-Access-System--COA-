#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int Addressing(char t[])//returning the type of opcode
{
	if(strcmp(t,"RESET_PSS") == 0)
		return 3;
	else if((strcmp(t,"MOV")==0)||(strcmp(t,"ADD")==0)||(strcmp(t,"SUB")==0)||(strcmp(t,"CMP")==0)||(strcmp(t,"IN")==0)||(strcmp(t,"OUT")==0)||(strcmp(t,"ULOGIN")==0))
		return 2;
	else if((strcmp(t,"JNE")==0)||(strcmp(t,"JGE")==0)||(strcmp(t,"JLE")==0)||(strcmp(t,"MSF")==0)||(strcmp(t,"JMP")==0)||(strcmp(t,"MAIL")==0)||(strcmp(t,"OPEN")==0)||(strcmp(t,"CLOSE")==0)||(strcmp(t,"RECEIPT")==0))
		return 1;
	else if((strcmp(t,"ALRM")==0) || (strcmp(t,"IL_ALRM")==0) || (strcmp(t,"DSPLY")==0)|| (strcmp(t,"RET")==0)|| (strcmp(t,"HLT")==0)|| (strcmp(t,"RESET")==0))
		return 0;
	else if((strcmp(t,"L0")==0)||(strcmp(t,"L1")==0)||(strcmp(t,"L2")==0)||(strcmp(t,"L3")==0)||(strcmp(t,"L4")==0)||(strcmp(t,"L5")==0)||(strcmp(t,"L6")==0)||(strcmp(t,"L7")==0)||(strcmp(t,"L8")==0)||(strcmp(t,"L9")==0))
		return -1;
}

void zero_add(char t[], FILE *bn)
{
	char code[20];
	char temp[]="11111111";
	if(strcmp(t,"ALRM")==0)
		strcpy(code,"00000000");
	else if(strcmp(t,"IL_ALRM")==0)
		strcpy(code,"00000001");
	else if(strcmp(t,"DSPLY")==0)
		strcpy(code,"00000010");
	else if(strcmp(t,"RET")==0)
		strcpy(code,"00000011");
    else if(strcmp(t,"HLT")==0)
		strcpy(code,"00000100");
    else if(strcmp(t,"RESET")==0)
		strcpy(code,"00000101");

	strcat(temp,code);
//	printf("%s\n",temp);
	fprintf(bn,"%s\n",temp);
}

//converting to binary -> three address
void address(char t1[], char code[]){
		//Register addressing
	if(strcmp(t1,"R0") == 0)
        	strcat(code,"10000");
	else if(strcmp(t1,"R1") == 0)
		strcat(code,"10001");
	else if(strcmp(t1,"R2") == 0)
        	strcat(code,"10010");
	else if(strcmp(t1,"R3") == 0)
		strcat(code,"10011");
	else if(strcmp(t1,"R4") == 0)
		strcat(code,"10100");
	else if(strcmp(t1,"R5") == 0)
		strcat(code,"10101");
	else if(strcmp(t1,"R6") == 0)
		strcat(code,"10110");
	else if(strcmp(t1,"R7") == 0)
		strcat(code,"10111");
	else if(strcmp(t1,"TR") == 0)
		strcat(code,"11000");
	else if(strcmp(t1,"PSW") == 0)
		strcat(code,"11001");
	else if(strcmp(t1,"MR") == 0)
        	strcat(code,"11010");
	else if(strcmp(t1,"CP") == 0)
        	strcat(code,"11011");
	else if(strcmp(t1,"PC") == 0)
        	strcat(code,"11100");
    else if(strcmp(t1,"IR") == 0)
        	strcat(code,"11101");
	else if(strcmp(t1,"LR") == 0)
        	strcat(code,"11110");

	//Indirect addressing
    else if(strcmp(t1,"@R0") == 0)
        	strcat(code,"00000");
	else if(strcmp(t1,"@R1") == 0)
		strcat(code,"00001");
	else if(strcmp(t1,"@R2") == 0)
        	strcat(code,"00010");
	else if(strcmp(t1,"@R3") == 0)
		strcat(code,"00011");
	else if(strcmp(t1,"@R4") == 0)
		strcat(code,"00100");
	else if(strcmp(t1,"@R5") == 0)
		strcat(code,"00101");
	else if(strcmp(t1,"@R6") == 0)
		strcat(code,"00110");
	else if(strcmp(t1,"@R7") == 0)
		strcat(code,"00111");
}


int bin(int number , int length)
{
	int a = 1;
	int b = 0;//bits for binary
	int k = 0;//negative no.
	int bin=0;//final binary no.

	if(number<0)
  	{
       	k = 1;
       	number = number * -1;
  	}

    while(1)
    {
        if(number/a == 0)
            break;
            a  = a * 2;
 		 	b++;
	}

   	int* binary_no = calloc(length,sizeof(int));

	//setting all elements to zero
	memset(binary_no,0,sizeof(binary_no));

	int r = length - 1;

	if(k == 1)
   	{
		while(r > b)
		{
	    	binary_no[r] = 1;
	      	r--;
      	}
	}

	int x = b ;
    int g = a;

   	while(x>-1)//can be zero bit
   	{
	binary_no[x] = number/g;
      	 //printf("%d\n" , number/g);
         //printf("binary[%d] == %d" , x , binary_no[x]);
    number = number % g;
      	 //printf("%d\n" , number);
      	 x--;
      	 g = g/2;
	}
/*for(x = b ; x >-1 ; x = x - 1)

   printf("%d " , binary_no[x]);



   printf("\n");*/

if (k == 1)
{
    for(x = b ; x >-1 ; x = x - 1)
              {
                  binary_no[x] = binary_no[x] - 1;
                 // printf("%d\n" , binary_no[x]);
                  binary_no[x] = binary_no[x] * (-1);
  }


/*for(x = length - 1; x >-1 ; x = x - 1)
   printf("%d " , binary_no[x]);

*/


//printf("\n");

x = 0;
	while(x<b+1)
	{
		if(binary_no[x] == 0)
	    {
	        binary_no[x] = 1;
	         break;
	    }
	    else
	        binary_no[x] = 0;
	    x++;
	}
}
for(x = length - 1; x >-1 ; x = x - 1)
	bin = bin*10+binary_no[x];
  // printf("%d " , binary_no[x]);

 //printf("\n");

return bin;
}


void one_add(char t[],char t1[],FILE* bn)
{
	int flag=0,j=0;

//	printf("%c",t1[1]);
	char code[30];
	char codet[30];

	//searching for label in instruction
	if((strcmp(t1,"L0")==0)||(strcmp(t1,"L1")==0)||(strcmp(t1,"L2")==0)||(strcmp(t1,"L3")==0)||(strcmp(t1,"L4")==0)||(strcmp(t1,"L5")==0)||(strcmp(t1,"L6")==0)||(strcmp(t1,"L7")==0)||(strcmp(t1,"L8")==0)||(strcmp(t1,"L9")==0)){
		flag=1;
	}

	//converting opcode
	if(strcmp(t,"JNE")==0)
		strcpy(code,"11110000");
	else if(strcmp(t,"JGE")==0)
		strcpy(code,"11110001");
	else if(strcmp(t,"JLE")==0)
		strcpy(code,"11110010");
	else if(strcmp(t,"MSF")==0)
		strcpy(code,"11110011");
	else if(strcmp(t,"JMP")==0)
		strcpy(code,"11110100");
	else if(strcmp(t,"MAIL")==0)
		strcpy(code,"11110101");
	else if(strcmp(t,"OPEN")==0)
		strcpy(code,"11110110");
	else if(strcmp(t,"CLOSE")==0)
		strcpy(code,"11110111");
	else if(strcmp(t,"RECEIPT")==0)
		strcpy(code,"11111000");

	//Register addressing
	if(strcmp(t1,"R0") == 0)
        	strcat(code,"01000000");
	else if(strcmp(t1,"R1") == 0)
		strcat(code,"01000001");
	else if(strcmp(t1,"R2") == 0)
        	strcat(code,"01000010");
	else if(strcmp(t1,"R3") == 0)
		strcat(code,"01000011");
	else if(strcmp(t1,"R4") == 0)
		strcat(code,"01000100");
	else if(strcmp(t1,"R5") == 0)
		strcat(code,"01000101");
	else if(strcmp(t1,"R6") == 0)
		strcat(code,"01000110");
	else if(strcmp(t1,"R7") == 0)
		strcat(code,"01000111");
	else if(strcmp(t1,"TR") == 0)
		strcat(code,"01001000");
	else if(strcmp(t1,"PSW") == 0)
		strcat(code,"01001001");
	else if(strcmp(t1,"MR") == 0)
        	strcat(code,"01001010");
	else if(strcmp(t1,"CP") == 0)
        	strcat(code,"01001011");
	else if(strcmp(t1,"PC") == 0)
        	strcat(code,"01001100");
        else if(strcmp(t1,"IR") == 0)
        	strcat(code,"01001101");
	else if(strcmp(t1,"LR") == 0)
        	strcat(code,"01001110");

	//Indirect addressing
    else if(strcmp(t1,"@R0") == 0)
        	strcat(code,"10000000");
	else if(strcmp(t1,"@R1") == 0)
		strcat(code,"10000001");
	else if(strcmp(t1,"@R2") == 0)
        	strcat(code,"10000010");
	else if(strcmp(t1,"@R3") == 0)
		strcat(code,"10000011");
	else if(strcmp(t1,"@R4") == 0)
		strcat(code,"10000100");
	else if(strcmp(t1,"@R5") == 0)
		strcat(code,"10000101");
	else if(strcmp(t1,"@R6") == 0)
		strcat(code,"10000110");
	else if(strcmp(t1,"@R7") == 0)
		strcat(code,"10000111");

    else{
		//Direct addressing
        if(flag==0){ //Not a label
        	int c2,c1;
        	char tem[10];
        //	printf("%c,%c",t1[1],t1[0]);
        	if(t1[1]!='\0'){ //digit of length 2
        	 c1=((int)(t1[1])-(int)('0'))+10*((int)(t1[0])-(int)('0'));
 		}
 		else{//digit of length 1
        		c1=((int)(t1[0])-(int)('0'));
 		}
 	//	printf("%d",c1);
 		c2=bin(c1,6);
 	// 	printf("%04d",c2);
 		sprintf(tem,"%06d",c2);
 		strcat(code,"11");
 		strcat(code,tem);
        }
	}

    if(flag==1){
	//Labels are present

    	FILE *lb =fopen("label.txt","r+");
    	char s[50];
    	int i,count=0,it;
    	j=0;

    	while(1){
    	 	it = fscanf(lb,"%s\n",s);

			//file end
			if(it==-1)
            		break;

    	 	if (s[1]==t1[1]){

    	 			for(i=3;i<11;i++){
    	 			//	printf("%d",i);
    	 			//	printf("tu %c tu ",s[i]);
    	 				codet[i-3]=s[i];

    	 			}
    	 			codet[i-3]='\0';
    	 	}

    //	 printf(" %c",codet[10]);
    	}
        strcat(code,codet);
        fclose(lb);
    }

     //  printf("%s\n",codet);
//printf("%s\n",code);
fprintf(bn,"%s\n",code);
}



void two_add(char t[],char t1[],char t2[],FILE *bn)
{
	char code[25];
	char codet[25];
	int flag=0,binary;
	int x;
	int c;
	int a;
	char tem[10];
	char tem1[10];
    char temp[10];
    char tem2[10];
    char tem3[10];

  //  printf("%s\n%s\n%s\n",t,t1,t2);
	if(strcmp(t,"MOV")==0)
		strcpy(code,"1000");
	else if(strcmp(t,"ADD")==0)
		strcpy(code,"1001");
	else if(strcmp(t,"SUB")==0)
		strcpy(code,"1010");
	else if(strcmp(t,"IN")==0)
		strcpy(code,"1011");
	else if(strcmp(t,"OUT")==0)
		strcpy(code,"1100");
	else if(strcmp(t,"CMP")==0)
		strcpy(code,"1101");
	else if(strcmp(t,"ULOGIN")==0)
		strcpy(code,"1110");

	if (strcmp(t1,"R0") == 0)
        	strcpy(codet,"010000");
	else if (strcmp(t1,"R1") == 0)
		strcpy(codet,"010001");
	else if (strcmp(t1,"R2") == 0)
        	strcpy(codet,"010010");
	else if (strcmp(t1,"R3") == 0)
		strcpy(codet,"010011");
	else if (strcmp(t1,"R4") == 0)
		strcpy(codet,"010100");
	else if (strcmp(t1,"R5") == 0)
		strcpy(codet,"010101");
	else if (strcmp(t1,"R6") == 0)
		strcpy(codet,"010110");
	else if (strcmp(t1,"R7") == 0)
		strcpy(codet,"010111");
	else if (strcmp(t1,"TR") == 0)
		strcpy(codet,"011000");
	else if (strcmp(t1,"PSW") == 0)
		strcpy(codet,"011001");
	else if (strcmp(t1,"MR") == 0)
        	strcpy(codet,"011010");
	else if (strcmp(t1,"CP") == 0)
        	strcpy(codet,"011011");
	else if (strcmp(t1,"PC") == 0)
        	strcpy(codet,"011100");
        else if (strcmp(t1,"IR") == 0)
        	strcpy(codet,"011101");
	else if (strcmp(t1,"LR") == 0)
        	strcpy(codet,"011110");

    if (strcmp(t1,"@R0") == 0)
        	strcpy(codet,"100000");
	else if (strcmp(t1,"@R1") == 0)
		strcpy(codet,"100001");
	else if (strcmp(t1,"@R2") == 0)
        	strcpy(codet,"100010");
	else if (strcmp(t1,"@R3") == 0)
		strcpy(codet,"100011");
	else if (strcmp(t1,"@R4") == 0)
		strcpy(codet,"100100");
	else if (strcmp(t1,"@R5") == 0)
		strcpy(codet,"100101");
	else if (strcmp(t1,"@R6") == 0)
		strcpy(codet,"100110");
	else if (strcmp(t1,"@R7") == 0)
		strcpy(codet,"100111");

		if(t1[0]=='#')
        {
        if(t1[2]!='\0')
        {
            //x=1900*t1[1]+t1[2];
            c = ((((int)t1[1]-48)*10)+((int)t1[2]-48));
            //printf("%d",c);
            binary = bin(c,4);
        }
        else
        {
            binary=bin(t1[1],4);
        }
        sprintf(tem,"%06d",binary);
        //printf("%s---",tem);
        strcpy(codet,tem);        //printf("%s",codet);

    }

        if(t1[0]!='R'&&t1[0]!='#'&&t1[0]!='@')
        {

            a = ((((int)t1[0]-48)*10)+(((int)t1[1]-48)));
            //sprintf(tem2,"%04d",a);
            //printf("%d-----",a);
            int k = bin(a,4);
            k=k+110000;
            sprintf(tem1,"%06d",k);
            strcpy(codet,tem1);

        }

		if (strcmp(t2,"R0") == 0)
        	strcat(codet,"010000");
	else if (strcmp(t2,"R1") == 0)
		strcat(codet,"010001");
	else if (strcmp(t2,"R2") == 0)
        	strcat(codet,"010010");
	else if (strcmp(t2,"R3") == 0)
		strcat(codet,"010011");
	else if (strcmp(t2,"R4") == 0)
		strcat(codet,"010100");
	else if (strcmp(t2,"R5") == 0)
		strcat(codet,"010101");
	else if (strcmp(t2,"R6") == 0)
		strcat(codet,"010110");
	else if (strcmp(t2,"R7") == 0)
		strcat(codet,"010111");
	else if (strcmp(t2,"TR") == 0)
		strcat(codet,"011000");
	else if (strcmp(t2,"PSW") == 0)
		strcat(codet,"011001");
	else if (strcmp(t2,"MR") == 0)
        	strcat(codet,"011010");
	else if (strcmp(t2,"RC") == 0)
        	strcat(codet,"011011");
	else if (strcmp(t2,"PC") == 0)
        	strcat(codet,"011100");
    else if (strcmp(t2,"IR") == 0)
        	strcat(codet,"011101");
	else if (strcmp(t2,"LR") == 0)
        	strcat(codet,"011110");


    if (strcmp(t2,"@R0") == 0)
        	strcat(codet,"100000");
	else if (strcmp(t2,"@R1") == 0)
		strcat(codet,"100001");
	else if (strcmp(t2,"@R2") == 0)
        	strcat(codet,"100010");
	else if (strcmp(t2,"@R3") == 0)
		strcat(codet,"100011");
	else if (strcmp(t2,"@R4") == 0)
		strcat(codet,"100100");
	else if (strcmp(t2,"@R5") == 0)
		strcat(codet,"100101");
	else if (strcmp(t2,"@R6") == 0)
		strcat(codet,"100110");
	else if (strcmp(t2,"@R7") == 0)
		strcat(codet,"100111");

    if(t2[0]=='#')
        {
        if(t2[2]!='\0')
        {
            //x=1900*t1[1]+t1[2];
            x = ((((int)t2[1]-48)*10)+((int)t2[2]-48));
            //printf("%d",c);
            binary=bin(x,4);
        }
        else
        {
            binary=bin(t2[1],4);
        }
        sprintf(tem1,"%06d",binary);
        //printf("%s---",tem);
        strcat(codet,tem1);
        //printf("%s",codet);

    }
    if(t2[0]!='R'&&t2[0]!='#'&&t2[0]!='@')
        {
            a = ((((int)t2[0]-48)*10)+(((int)t2[1]-48)));
            //sprintf(tem2,"%04d",a);
            //printf("%d-----",a);o
            int k = bin(a,4);
            k=k+110000;
            sprintf(tem3,"%06d",k);
            strcat(codet,tem3);

        }
    //printf("%04d",binary);
	strcat(code,codet);
  //  printf("%s",code);
    fprintf(bn,"%s\n",code);
}

void three_add(char t[], char t1[], char t2[],FILE *bn){
	char code[30];
	strcpy(code,"0");//indicate three address instruction

	//passing operand one by one and appending in 'code'
	address(t,code);
	address(t1,code);
	address(t2,code);
	printf("%s\n%s\n%s\n",t,t1,t2);
	printf("%s",code);
	fprintf(bn,"%s\n",code);
}

void firstpass(){
int i;
    FILE *as=fopen("ins.txt","r");
    FILE *lb=fopen("label.txt","w");
    char s[50],lab[10],mem[10];
    int line_cnt=0,lab_cnt=0,c2;
    while(fgets(s,50,as)!=NULL)
    {
        s[strlen(s)-1]='\0';
        line_cnt++;
        if(s[0]=='L')
        {
            lab_cnt++;
            lab[0]=s[0];
            lab[1]=s[1];
            if(s[2]==':'||s[2]==',')
            {
                lab[2]='\0';
            }
            else
            {
                lab[2]=s[2];
                lab[2]='\0';
            }
            c2=bin(line_cnt,8);
            sprintf(mem,"%08d",c2);
            fprintf(lb,"%s,%s\n",lab,mem);
        }
    }
    fclose(as);
    fclose(lb);

}

int main(){
	FILE *fp,*bn;
	int it;
	fp=fopen("ins.txt","r+");
	bn=fopen("bn.txt","w+");
	//one_add("MSF","1",bn);
	firstpass();
	//three_add("R01","R1","@R2",bn);
	while(1){
	 	int i,j=0,k=0,count=0;
		char s[50],temp[10],temp1[10],temp2[10],temp3[10];
		int type;
		char ts[20];

		it = fscanf(fp,"%s\n",s);

		if(it==-1)//end of file
	        break;
	   // printf("%s\n",s);

	///printf("\n");


	//	printf("Enter string : ");
	//	scanf("%s",s);

		for(i=0;s[i]!=',';i++)
		{
			temp[i]=s[i];
		}
		temp[i]='\0';
		i++;
	//	printf("%s\n",temp);

		if(s[i]!='\0')
		{	//i=i-1;
			for(j = 0 ;s[i]!=',';i++,j++)
			{
				temp1[j]=s[i];
			}

		}
		temp1[j]='\0';
	//	printf("%s\n",temp1);
		i++;

		if(s[i]!='\0')
		{
		//	i=i-1;
			for(k = 0;s[i]!=',';i++,k++)
			{
				temp2[k]=s[i];
			}
		}
		temp2[k]='\0';
	//	printf("%s\n",temp2);
		i++;

		int l;
		if(s[i]!='\0')
		{
			for(l = 0;s[i]!=',';i++,l++)
			{
				temp3[l]=s[i];
			}
			temp3[l]='\0';
		}
	//	printf("%s\n",temp3);
	//	printf("%s\n",temp);
	//	printf("%s\n",temp1);
	//	if(s[i]==',')
	//	{
		//	printf("%s",temp2);
	//	}

		//strcpy(temp, "DSPLY");
	type = Addressing(temp);
		//printf("%d",type);


		switch(type)
		{
			case 0:
				zero_add(temp, bn);
				break;
			case 1:
			//	printf("%s",temp1);
				one_add(temp,temp1,bn);
				break;
			case 2:
				two_add(temp,temp1,temp2,bn);
				break;
			case 3:
				three_add(temp1, temp2, temp3, bn);//no need to pass temp -> only one instruction
			case -1:
				break;
		}

	}
	fclose(fp);
	fclose(bn);
return 0;
}
