#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//funtion prototypes
long long int strBin(char bn[]);
int binInt(int bin);
void Display();
void decode(long long int bin);
void simulate(int temp_pc);
void read(FILE *bn);
void func();

//global variable
int TR = 0;
int PSW[16] = {0};//status flag register(n,z,ov) 
int MR;
int PC;
int CP;
long long int IR;
int LR;
char fName[20]="bn.txt";
char pName[20]="pss.txt";
int labe[20]={0};
int reg[20]={0};

//Binary to integer8
int binInt(int n)
{
	int i,bin=0,c=1;
	
	for(i=n;i>0;i=i/10)
	{
		bin=bin+(i%10)*c;
		c=c*2;
	}
	return bin;
}
//function to convert string to binary
long long int strBin(char bn[])
{
	long long int i,bin=0;
	for(i=0;i<=15;i++)
	{
		if(bn[i]=='1')
		{
			bin=(bin*10)+1;
			//printf("%ld\n",bin);
		}
		else
		{
			bin=bin*10;
			//printf("%ld\n",bin);
		}
	}
	//printf("%d\n",bin);
	return bin;
}

//managing labels
void func()
{
	FILE *tp=fopen("ins.txt","r+");
	char s[50];
    	int lab_cnt=0;
    	int line_count=0;
    
    	while(fgets(s,50,tp)!=NULL)
    	{
    		if(s[0]=='L')
        	{
            		lab_cnt++;
            		labe[line_count]=lab_cnt;
            	}
            	line_count++;
    	}
}

//Used for displaying Instructions
void read(FILE *bn)
{
	int i;
	char temp[20];
	while(1)
	{
		i=fscanf(bn,"%s'\n",temp);
		if(i==-1)
		break;
		printf("%s\n",temp);	
	}
	printf("\n");
}

//Displaying the simulation
void Display()
{
	int i;
	
	printf("General purpose registers\n");
	
	for(i=0;i<8;i++)
	{
		printf("R%d:%d	",i,reg[i]);
		if((i+1)%4==0)
			printf("\n");
	}
	
	printf("value of special registers\n");
	printf("TR%d\n",TR);
	printf("PSW:%d %d %d\n",PSW[2], PSW[1], PSW[0]);
	printf("MR:%d\n",MR);
	printf("RC:%d\n",CP);
	printf("PC:%d\n",PC);
	printf("IR:%lld\n",IR);
	printf("LR:%d\n",LR);
	printf("\n");
	
}

//Controlling execution
void simulate(int temp_pc)
{

	int i,k;
	int c=0;
	long long int bin;
	char temp[20];
	FILE *bn=fopen(fName,"r+");
	while(1)
	{
		i=fscanf(bn,"%s\n",temp);
                if(i==-1)
                	break;
		if(c>=temp_pc)//condition to jump to particular instruction line
		{
			//printf("%s\n",temp);
			bin=strBin(temp);
		//	printf("teri %lld\n",bin);
			//printf("%lld	%d\n",x,length(x));
			IR=bin;
			PC=c+1;
			decode(bin);
			Display();
		}
		c=c+1;
		PC=c;
		//Display();
	}
	printf("\n");
	//Display();
}

//Decoding instruction and generating, execution
void decode(long long int bin){
	long long int temp,temp1;
	int i,j;

	temp = bin/(1000000000000);
	temp1 = bin/100000000;
//two address	
	if(temp==1101) // COMPARE FUNCTION
	{
	//	printf("i am here\n");
		int reg1,reg2,value;
		long long int bin1=bin;
		long long int bin2=bin;
		long long int addr;
		//reg[0]=10;
		//printf("REG1----%lld\n",bin1);
		bin1=bin1%10000000000;
		bin1=bin1/1000000;
		bin2=bin2%10000;
		//bin2=bin2/10000;
		//printf("REG1----%lld\n",bin1);
		//printf("REG2----%lld\n",bin2);
		reg1=binInt(bin1);
		//printf("REG1----%lld\n",reg1);
		addr=bin;
		//printf("addr----%lld\n",addr);
		addr=bin%1000000;
		//printf("addr----%lld\n",addr);
		addr=addr/10000;
		//printf("addr----%lld\n",addr);
		//bin2=bin%10000;
		//printf("----%lld",reg1);

		if(addr==1)
		{
			reg2=binInt(bin2);
			if(reg1<8)
			{
				if(reg[reg1]==reg[reg2])
				{
					PSW[0]=0;PSW[1]=1;PSW[2]=0;
				}
				else if(reg[reg1]<reg[reg2])
				{
					PSW[0]=0;PSW[1]=0;PSW[2]=1;
				}
				else
				{
					PSW[0]=0;PSW[1]=0;PSW[2]=0;
				}
			}
		}
		else
		{
		//	printf("hoho ho\n");
			value=binInt(bin2);
			if(reg1<8)
			{
				if(reg[reg1]==value)
				{
					PSW[0]=0;PSW[1]=1;PSW[2]=0;
				}
				else if(reg[reg1]<value)
				{
					PSW[0]=0;PSW[1]=0;PSW[2]=1;
				}
				else
				{
					PSW[0]=0;PSW[1]=0;PSW[2]=0;
				}
			}
	}
		printf("CMP:OPERATION\n");
		printf("ALU STATUS:SUB operations performed\n");
	
	}
	else if(temp==1000) // MOV
	{
		int reg1,reg2,value;
		long long int bin1=bin;
		long long int bin2=bin;
		long long int addr;
		//reg[0]=10;
		//printf("REG1----%lld\n",bin1);
		bin1=bin1%10000000000;
		bin1=bin1/1000000;
		bin2=bin2%10000;
		//bin2=bin2/10000;
		//printf("REG1----%lld\n",bin1);
		//printf("REG2----%lld\n",bin2);
		reg1=binInt(bin1);
		//printf("REG1----%lld\n",reg1);
		addr=bin;
		//printf("addr----%lld\n",addr);
		addr=bin%1000000;
		//printf("addr----%lld\n",addr);
		addr=addr/10000;
		//printf("addr----%lld\n",addr);
		//bin2=bin%10000;
		reg2=binInt(bin2);
		printf("----%d\n",reg[reg2]);
		if(addr==1)
		{
			
			//printf("hi %d hi %d\n",reg1,reg2);
			if(reg2==11)
			{	
				reg[reg2]=CP;
			}
			if(reg1<8)
				reg[reg1]=reg[reg2];
			else if(reg1==8)
				TR=reg[reg2];
			else if(reg1==10)
				MR=reg[reg2];
			else if(reg1==11)
				CP=reg[reg2];
			else if(reg1==12)
				PC=reg[reg2];
			else if(reg1==13)
				IR=reg[reg2];
            		else if(reg1==14)
				LR=reg[reg2];
			
		}
		else
		{
			value=binInt(bin2);
		//	printf("hi %d hi %d\n",reg1,value);
			if(reg1<8)
				reg[reg1]=value;
			else if(reg1==8)
				TR=value;
            else if(reg1==10)
				MR=value;
			else if(reg1==11)
				{
				CP=value;}
			else if(reg1==12)
				PC=value;
			else if(reg1==13)
				IR=value;
            else if(reg1==14)
				LR=value;
		}
		printf("MOV:OPERATION\n");
		printf("ALU STATUS:no ALU operations performed\n");
		//printf("DATA MOVEMENT: data(value) moved to register %d \n",reg1);
	}
	else if(temp==1001) //ADD
	{
		int reg1,reg2,value;
		long long int bin1=bin;
		long long int bin2=bin;
		long long int addr;
		//reg[0]=10;
		//printf("REG1----%lld\n",bin1);
		bin1=bin1%10000000000;
		bin1=bin1/1000000;
		bin2=bin2%10000;
		//bin2=bin2/10000;
		//printf("REG1----%lld\n",bin1);
		//printf("REG2----%lld\n",bin2);
		reg1=binInt(bin1);
		//printf("REG1----%lld\n",reg1);
		addr=bin;
		//printf("addr----%lld\n",addr);
		addr=bin%1000000;
		//printf("addr----%lld\n",addr);
		addr=addr/10000;
		//printf("addr----%lld\n",addr);
		//bin2=bin%10000;
		//printf("----%lld",reg1);
		if(addr==1)
		{
			reg2=binInt(bin2);
			if(reg1<8)
			{
				reg[reg1]=reg[reg1]+reg[reg2];
			}
			else if(reg1==8)
			{
				TR=TR+reg[reg2];
			}

		}
		else
		{
			value=binInt(bin2);
			if(reg1<8)
			{
				reg[reg1]=reg[reg1]+value;
			}
			else if(reg1==8)
			{
				TR=TR+value;
			}
		}
		printf("ADD:OPERATION\n");
		printf("ALU STATUS:ADD ALU operations performed\n");
		//printf("DATA MOVEMENT:data(value) moved to register %d\n",reg1);
	}


	else if(temp==1010) //SUB
	{
		int reg1,reg2,value;
		long long int bin1=bin;
		long long int bin2=bin;
		long long int addr;
		reg[0]=10;
		reg[7]=4;
		//printf("REG1----%lld\n",bin1);
		bin1=bin1%10000000000;
		bin1=bin1/1000000;
		bin2=bin2%10000;
		//bin2=bin2/10000;
		//printf("REG1----%lld\n",bin1);
		//printf("REG2----%lld\n",bin2);
		reg1=binInt(bin1);
		//printf("REG1----%lld\n",reg1);
		addr=bin;
		//printf("addr----%lld\n",addr);
		addr=bin%1000000;
		//printf("addr----%lld\n",addr);
		addr=addr/10000;
		//printf("addr----%lld\n",addr);
		//bin2=bin%10000;
		//printf("----%lld",reg1);
		if(addr==1)
		{
			reg2=binInt(bin2);
			if(reg1<8)
			{
				reg[reg1]=reg[reg1]-reg[reg2];
			}
			else if(reg1==8)
			{
				TR=TR-reg[reg2];
			}

		}
		else
		{
			value=binInt(bin2);
			if(reg1<8)
			{
				reg[reg1]=reg[reg1]-value;
			}
			else if(reg1==8)
			{
				TR=TR+value;
			}
		}
		printf("SUB:OPERATION\n");
		printf("ALU STATUS:SUB ALU operations performed\n");
		//printf("DATA MOVEMENT:data(value) moved to register %d\n",reg1);
		
	}
	
	else if(temp == 1110){
		long long int bin1 = bin%1000000000000;
		long long int bin2 = bin1%1000000; // operand 2
		bin1 = bin1/1000000; // operand 1
		int id1, id2, val1 = 0,val2 = 0;
		id1 = bin1/10000;//register or immediate
		id2 = bin2/10000; 
		bin1 = bin1%10000;//only operand
		bin2 = bin2%10000;
		if(id1 == 0){
			val1 = binInt(bin1);
		}
		else if(id1 == 1){
			val1 = binInt(bin1);
			val1 = reg[val1];//passing value of register
		}
		MR = val1;
		
		if(id2 == 0){
			val2 = binInt(bin2);
		}
		else if(id2 == 1){
			val2 = binInt(bin2);
			val2 = reg[val2];//passing value of register
		}
		LR = val2*10;
		
		//putting password into CP
		/*int c = 1;
		long long int pss = 0;
		char tmp[20];
		FILE *bbn=fopen(pName,"r+");
		while(1)
		{
			i=fscanf(bbn,"%s\n",tmp);
	                if(i==-1)
	                	break;
	        printf("\n pass %s\n",tmp);
			if(c == val1 )//condition to jump to particular instruction line
			{
				//printf("%s\n",temp);
				pss = strBin(tmp);
				printf(" pass : %lld\n",pss);
				break;
			}
			c=c+1;
		
		}
		printf("%lld\n",binInt(pss));
		CP = binInt(pss);
		*/
		
			int c=0;
		long long int x;
		char te[20];
		FILE *pss=fopen(pName,"r+");
		while(1)
		{
			i=fscanf(pss,"%s\n",te);
	                if(i==-1)
	                	break;
			if(c>=0)
			{
				//printf("%s\n",temp);
				x=strBin(te);
				
				if(c==val1-1)
	            {
	                break;
	            }
				
			}
			c=c+1;
		}
		//printf("pass ----%lld\n",x);
		x=x/1000000000000;
		int k=binInt(x);
		CP=k;
		
	
	    printf("\n");
	    	
	}
	
	if(temp == 1111){// One address 
		long long int temp2;
		long long int bin1 = bin/100000000;
		temp2 = bin1%10000;// code for individual instruction
		int temp3 = bin%100000000;// operand 
		int id = temp/1000000;// just checking
		
		//printf(" Temp 2: %lld\n\n",temp2);
		if(temp2 == 0){ //JNE
			if(id == 0){//using label
				int labelNo;
				long long int bin1=bin;
				
				bin1=bin1%1000000;
				labelNo=binInt(bin1);//label no.
				int test=labe[labelNo-1];//finding total label till this label
				printf("JNE:OPERATION\n");
				if(PSW[1] != 1) //not zero
					simulate(labelNo-test);
			}
						
		}
		else if(temp2 == 1){//JGE
			if(id == 0){//label
				int labelNo;
				long long int bin1=bin;
				
				bin1=bin1%1000000;
				labelNo=binInt(bin1);//label no.
				int test=labe[labelNo-1];//finding total label till this label
				printf("JGE:OPERATION\n");
				if(PSW[2] != 1 )//not negative -> greater than/equal to
					simulate(labelNo-test);
			}
					
		}
		else if(temp2 == 10){//JLE
			if(id == 0){//label
				int labelNo;
				long long int bin1=bin;
				
				bin1=bin1%1000000;
				labelNo=binInt(bin1);//label no.
				int test=labe[labelNo-1];//finding total label till this label
				printf("JLE:OPERATION\n");
				if(PSW[2] == 1 || PSW[1] == 1 )//negative or zero
					simulate(labelNo-test);
			}
			
		}
		else if(temp2 == 100){//JMP
			if(id == 0){//label
				int labelNo;
				long long int bin1=bin;
				
				bin1=bin1%1000000;
				labelNo=binInt(bin1);//label no.
				int test=labe[labelNo-1];//finding total label till this label
				printf("JMP:OPERATION\n");
				simulate(labelNo-test);
			}
		}
		else if(temp2 == 101){//MAIL
			long long int bin1 = bin;
			bin1 = bin1%1000000;
			int reg1 = binInt(bin1);			
			
			printf("Mail sent to UserId: %d\n", reg[reg1]);
			char command[50];
	char str[10];

   	strcpy( command, "sh ./new.sh" );
	//printf("Enter Password\n");
	//scanf("%s",str);

	//{
		printf("Wrong password Mail sent to UserId: %d\n", reg[reg1]);
		system(command);
	//}
		

			exit(0);
						
		}
		else if(temp2 == 110){//OPEN
			long long int bin1 = bin%1000000;
			int reg1 = binInt(bin1);
			printf("Locker open to UserID: %d\n",reg[reg1]);
			LR += 1;
		}
		else if(temp2 == 111){//CLOSE
			long long int bin1 = bin%1000000;
			int reg1 = binInt(bin1);
			printf("Locker close to UserID: %d\n",reg[reg1]);
			LR -= 1;
		}
		
	}
	
	//Zero Address
	if(temp1==11111111)
	
    {
        long long int var;
        var=bin%(100000000);
        {
            if(var==0)
            {
                printf("Alarm is enable");
                exit(0);
            }
            else if(var==10)
            {
                if(LR%10==1)
                {
                    printf("Locker is open");
                    printf("User Locker number = %d",LR/10);
                }
                else
                {
                    printf("Locker is closed");
                }
            }
            else if(var==100)
            {
                printf("-----Program Ended------");
                exit(0);
            }
        }
    }
}


void main()
{
	FILE *bn;
	int choice;
	func();
	
	while(1)
	{
		bn=fopen(fName,"r+");
		printf("Select an option from below\n");
		printf("1>System\n");
		printf("2>Display Instructioons\n");
		printf("0>exit\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			simulate(0);
		}
		else if(choice==2)
			read(bn);
		else if(choice==0)
			break;
		else
			printf("wrong instructions\n");
		fclose(bn);
	}
	
}
