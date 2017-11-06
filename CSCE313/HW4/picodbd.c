#include <stdio.h>

int main() {
	int c;
	while (c != EOF) {
		c = getchar();
		getchar();
		putchar(c);
	}
}
