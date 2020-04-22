#include<stdio.h>
#include "cs50.h"

int main(){
	
	float dollar;
	int quarter = 25;
	int dime = 10;
	int nickel = 5;
	int penny = 1;
	int result1;
	int result2;
	int result3;
	int result4;

do{
    printf("How much is your change");
     dollar = get_float("input your money id dollars");
} while(dollar<=0);
 int cent = (dollar * 100);

do{
	result1 = cent/quarter;
}
while (cent<=quarter && cent!=0);


do{
result2 = cent/dime;
}

while(cent<=dime && cent< quarter);

do{
	result3 = cent/nickel;
}
while(cent>=nickel && cent<penny);

do{
	result4 = cent/penny;
}
while(cent<nickel);

int total_change = result1 + result2 + result3 + result4;
printf("my output is %d\n",total_change);
}
