#include <stdio.h>

int main() {
	int c;
	while (c != EOF) {
		c = getchar();
		//if (c >= 65 && c < 122) {
			++c;
		//}
		putchar(c);
	}
}
