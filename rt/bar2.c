// bar.c                                                                                   
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void print_hello2()
{
	printf("hello2.\n");
}

void print_hello(void)
{
    printf("Hello world %s!\n", "being patched Version2");
	print_hello2();
}
int main(void)
{
    while (1) {
        print_hello();
        sleep(1);
    }
}
