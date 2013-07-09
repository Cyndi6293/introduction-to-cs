#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main()
{
    float money;
    int pennies, coins;
    //ensure correct input
    money=-1.0;
    while(money<0)
    {
        printf("Enter the amount of money: ");
        money=GetFloat(); 
    } //end of while
    //convert value in dollars into pennies     
    money*=100;
    money=roundf(money);
    pennies=(int) money;    
    coins=0;
    //try quarter
    while (pennies>=25 )
    {
        pennies-=25;
        coins+=1;    
    } //end of while
    //try dime
    while (pennies>=10 )
    {
        pennies-=10;
        coins+=1;   
    } //end of while
    //try nickel
    while (pennies>=5 )
    {
        pennies-=5;
        coins+=1;    
    } //end of while
    //rest are pennies
    while (pennies>0)
    {
        pennies-=1;
        coins+=1;   
    } //end of while
    printf("%d\n",coins);
    return 0;
} //end of main
