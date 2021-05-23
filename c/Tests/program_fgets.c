#include <stdio.h>

int main(void)
{
    char test[10];
    puts("nyuryokusitekudasai");
    fgets(test, 10, stdin);
    puts("ikanomojiwonyuryokusimasita");
    printf("%s", test);
    return 0;
}