#include <stdio.h>
#include <string.h>
#include <math.h>

FILE* fout;

void readfile(char *FileName, int *ar)
{
	FILE *f = fopen(FileName,"r");
	fscanf(f,"%d", &ar[1]);
	fscanf(f,"%d", &ar[2]);	
	fclose(f);
}

int upperlg2(long long int num)
{
	if (num<2) {return 1;}
	else {return 1+upperlg2(num/2);}
}

int lowerlg2(long long int num)
{
	if (num == 0) {return 1;} else {return upperlg2(num)-1;};
}

long long int fact(int a)
{
	if (a<=1) {return 1;} else {return a*fact(a-1);}
}

int sumto(int n)
{
	int i=0;
	int res = 0;
	for (i=1;i<=n;i++)
	{
		res = res + i; 
		//fprintf(fout,"%d%c%d%c%c",i,'-',res,';',' ');
	}
	//int* final = &res;
	return res;
}

//Return how many 1s can be got from all number in 2-base representation of n length 
long long int AllPossibleOnes(int n)
{
	int j; long long int res=0;
	for (j=0;j<n;j++)
	{
		res = res + fact(n)/fact(n-j-1);
	}
	return res;
}

long long int Power2(int a)
{
	if (a==0) {return 1;}
	if (a==1) 
	{
		return 2;
	}
	else
	{ return 2*Power2(a-1);}
}

//Function returns lower integer, that is equal integer 2 degree
long long int LowerBenchmark(long long int a)
{
	
	return Power2(lowerlg2(a));
}

//Like previous but the greater integer instead of lower and 1 is subtracted so to stay within the degree limit
long long int UpperBenchmark(long long int a)
{
	return Power2(upperlg2(a))-1;
}

//Returns number of 1s in 2-base representation between lower benchmark of a and upper benchmark of b
long long int total(long long int a, long long int b)
{
	int i = upperlg2(a);
	int j = upperlg2(b);
	//printf("\ni = %d' 'j = %d\n",i,j);
	//printf("%d%c%d",j,' ',j)
	long long int res = 0;
	for (i=i;i<=j;i++)
		{
			res = res + AllPossibleOnes(i-1) + Power2(i-1);
		}
	return res;
}


//Gives number of ones in a certain number represented in 2-base. Additional parameters given after n allow to calculate faster. 
int ones(long long int n, long long int CalculatedLowerBenchmark , int PreviousValueReturn, int PreviousValueEnd)
{
	
	long long int LB;
	
	if (PreviousValueReturn > 0) { if (PreviousValueEnd < 2) 
	{
		return PreviousValueReturn + 1 - PreviousValueEnd; 
	}}
	
	if (CalculatedLowerBenchmark == 0) 
	{
		LB = LowerBenchmark(n);
		return 1 + floor((n-LB+1)/2);
	}
	else
	{
		return 1 + floor((n-CalculatedLowerBenchmark)/2);
	}
	
	
	
}

//Gives number of zeros between two numbers (strictly within one 2-power group limit)
long long int SumOfOnes(long long int a,long long int b, long long int CalculatedLowerBenchmark)
{
	if (a==b) {return ones(a,0,0,2);}
	
	long long int res;
	long long int i;
	long long int LB;
	long long int OperatingValue;
	int end;
	
	
	
	if (CalculatedLowerBenchmark == 0) {LB = LowerBenchmark(a);} else {LB = CalculatedLowerBenchmark;}
	
	end = rint((a - LB) % 2);
	OperatingValue = ones(a,CalculatedLowerBenchmark,0,2);
	res = OperatingValue;
	
	for (i=a+1;i<=b;i++) 
	{
		OperatingValue = ones(i,CalculatedLowerBenchmark, OperatingValue, end);
		res = res + OperatingValue;
		end = 1-end;
	}
	
	return res;

}

//Final function that processes arguments from different 2-power groups
unsigned long long int segment(long long int a, long long int b, 
long long int CalculatedLowerBenchmark, long long int CalculatedUpperBenchmark, int CalculatedABOneUpperLg)
{
	
	if (b-a == 1)
		{
			return 2*ones(b, CalculatedLowerBenchmark,0,2)-1;
		}		
	if (a==b)
		{
			return ones(a,CalculatedLowerBenchmark,0,2);
		}
		
	long long int t;
	long long int s1; long long int s2;
	long long int LB; long long int UB;
	unsigned long long int res;
	int ABOneUpperLg;
	
	if (CalculatedLowerBenchmark == 0) {LB = LowerBenchmark(a);} else {LB = CalculatedLowerBenchmark;}
	if (CalculatedUpperBenchmark == 0) {UB = UpperBenchmark(b);} else {UB = CalculatedUpperBenchmark;}
	if (CalculatedABOneUpperLg == 2) { if (upperlg2(a)==upperlg2(b)) {ABOneUpperLg = 1; } else {ABOneUpperLg = 0;};  } else {ABOneUpperLg = CalculatedABOneUpperLg;}
	
	if (a-LB>0) {s1 = SumOfOnes(LB,a,LB);} else {s1 = 0;}
	if (UB-b>0) {s2 = SumOfOnes(b+1,UB,0);} else {s2 = 0;}
	t = total(a,b);
	return t-s1-s2;
			
}

int main()
{
	int ar[3];
	long long int a = 0; long long int b = 0;
	
	//readfile("in.txt",ar);
	
	//FILE* 
	//fout = fopen("out.txt","w"); 
	printf("\n");
	
	printf("%s%c","Print the segment in 2 numbers:",'\n');
	scanf("%lld%lld",&a,&b);
		
	unsigned long long int sum = segment(a,b,0,0,2);
	
	printf("\nanswer = %llu\n",sum);
	
	printf("\n");
	
	//fclose(fout);
		
}
