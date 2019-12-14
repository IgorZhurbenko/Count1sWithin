#include <stdio.h>
#include <string.h>

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
	if (num == 1) {return 1;} else {return upperlg2(num)-1;};
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
	if (a==1) 
	{
		return 2;
	}
	else
	{ return 2*Power2(a-1);}
}

long long int total(long long int a, long long int b)
{
	int i = upperlg2(a);
	int j = upperlg2(b);
	printf("\ni = %d' 'j = %d\n",i,j);
	//printf("%d%c%d",j,' ',j)
	long long int res = 0;
	for (i=i;i<=j;i++)
		{
			res = res + AllPossibleOnes(i-1) + Power2(i-1);
		}
	return res;
}



int ones(long long int n)
{
	int i = 0; long long int a = n;
	while (a>0)
	{
		i++;
		a = a - Power2(lowerlg2(a));
	}
	return i;
}

int segment(long long int a, long long int b)
{
	if (b-a == 1)
		{
			return 2*ones(b)-1;
		}		
	if (a==b)
		{
			return ones(a);
		}
	else
		{
			long long int t = total(a,b);
			long long int s1; long long int s2;
			if ( Power2(lowerlg2(a))-a < 0 ) 
			{s1 = segment(Power2(lowerlg2(a)),a-1);}
			else
			{s1 = 0;}
			if ( Power2(upperlg2(b))-b > 1 )
			{s2 = segment(b+1,Power2(upperlg2(b))-1);}
			else
			{s2 = 0;}
			
			long long int res = t-s1-s2;
			
			printf("%d%c%d%c%d%c%d%c%d",a,' ', b,' ', t,'-',s1,'-',s2);
			printf("\n");
			return res;
		}
}

int main()
{
	int ar[3];
	long long int a = 0; long long int b = 0;
	readfile("in.txt",ar);
	
	//FILE* 
	fout = fopen("out.txt","w"); 
	
	//printf("%d%c%d%c", ar[1],' ',ar[2],' ');
	//printf("%d%c%d%c", ar[1],' ',ar[2],' ');
	printf("\n");
	//while (5==5)
	//{
	printf("%s%c","Print the segment in 2 numbers:",'\n');
	scanf("%lld%lld",&a,&b);
	printf("%lld %lld",a,b);
	scanf("");
	long long int sum = segment(a,b);
	printf("answer = %lld\n",sum);
	//printf("count possible ones = %lld\n",AllPossibleOnes(3));
	//printf("%lld", upperlg2(b));
	printf("\n%d", total(a,b));
	//printf("%d%c%d", lowerlg2(4),' ',upperlg2(4));
	printf("\n");
	//}
	fclose(fout);
		
}
