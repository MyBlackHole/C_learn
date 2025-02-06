
static void test(int a, int b, int c, int d, int e, int f, int g, int h, int i,
		 int j)
{
	a = a + 5;
	b = b + 5;
	c = c + 5;
	d = d + 5;
	e = e + 5;
	f = f + 5;
	g = g + 5;
	h = h + 5;
	i = i + 5;
	j = j + 5;
	int sum = a + b + c + d + e + f + g + h + i + j;
	sum = sum + 5;
}

int demo_disassemble_main()
{
	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	int e = 50;
	int f = 60;
	int g = 70;
	int h = 80;
	int i = 90;
	int j = 100;
	test(a, b, c, d, e, f, g, h, i, j);
	return 0;
}
