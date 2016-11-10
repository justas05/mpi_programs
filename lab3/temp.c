#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	char msg[] = "hello world";

	printf("string - %s\nlen = %d", msg, strlen(msg));

	return 0;
}
