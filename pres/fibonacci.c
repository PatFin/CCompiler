
void printnum(int64_t n) {
	while (n > 10) {
		putchar(48 + (n % 10));
		n = n / 10;
	}
	putchar('-');
	putchar('-');
}

void main(void) {
	int64_t i = 0, t, n0 = 0, n1 = 1;
	printnum(n0);
	printnum(n1);
	while (i < 10) {
		t = n1;
		n1 = n1 + n0;
		n0 = t;
		printnum(n1);
		i = i + 1 ;
	}
}