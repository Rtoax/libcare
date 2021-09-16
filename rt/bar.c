// bar.c                                                                                   
#include <stdio.h>
#include <time.h>

#if 0
void print_hello2()
{
	printf("hello world2.\n");
}
#endif
void print_hello(void)
{
    printf("Hello world %s!\n", "being patched");
//	print_hello2();
}

int main(void)
{
    while (1) {
        print_hello();
        sleep(1);
    }
}
