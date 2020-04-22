#include "cs50.h"
#include<stdio.h>
#include<math.h>

int result1;
int result2;
int result3;
int result4;
int result5;

int quarter;
int nickel;
int dime;
int penny;

int one_method(int cented,int quartered){
      result1 = cented/quartered;
    do {
    continue;
    }
    while (result1==0);
    
    return result1;
}

int two_method(int a,int dimed){
    result1=a;
     result2 = a / dimed;
    do {
        continue;
    }
    while (result2==0);

    return result2;
}

int three_method(int b,int nickeled){
    b = result2;
     result3 = b / nickeled;
    do {
        continue;
    }
    while (result3==0);

    return result3;
}

int four_method( int c,int pennyed){
    result3 = c;
     result4 = c / pennyed;
    do {
       continue; 
    }
    while (result4==0);
    
    return result4;
}

void five_method( int d){
    result4 = d;
     result5 = d/result4;
    do {
        continue;
    }
    while (result5==0);
}

int main(){
  float dollar;
do{
    printf("How much is your change");
     dollar = input("Input your money in Dollars");
}
while(dollar<=0);
int cent = round(dollar * 100);

 int res1 = one_method(cent,quarter);
 int res2 = two_method(result1,dime);
 int res3 = three_method(result2,nickel);
 int res4 = four_method(result3,penny);

int final_output = res1 + res2 + res3 + res4;
printf("my output is %d\n",final_output);


}


