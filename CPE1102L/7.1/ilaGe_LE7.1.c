#include <stdio.h>

int main(){

    int num[10], max, min, i;
    for(i = 0; i < 10; i++)
    {
        printf("Enter your number #%d: ", i+1);
        scanf("%d", &num[i]);
        if(i == 0)
        {
            max = num[i];
            min = num[i];
        }
        else if(num[i] > max)
            max = num[i];
        else if(num[i] < min)
            min = num[i];
    }
    printf("The numbers you entered are: ");
    for(i = 0; i < 10; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\nThe largest number is: %d\n", max);
    printf("The smallest number is: %d", min);

    return 0;
}
