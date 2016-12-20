#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    /* hello1 */
    printf("hello world!\n");

    /* hello2 */
    char name[100];
    printf("Enter your name: \n");
    scanf("%99s", name);
    printf("hello %s! \n", name);

    /* hello3 */
    /* generate a random number first */
    srand(time(0)); /* seed the generator */
    int randomInt = (rand() % 10) + 1;
    printf("the number was %d \n", randomInt);

    int i;
    for(i = 0; i < randomInt; i++){
        if(randomInt%2 == 0){
            printf("hello %s! \n", name);
        }else{
            printf("hi there, %s! \n", name);
        }
    }
    return 0;
}
