int mul(int x, int y)
{
	int sum = x + y;
	return sum;
}

int sum(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int s = mul(a, b);
	int sub = a - b;
	int t = s + c + d + e + f + g + h;
	int res = t + s;
	int useless1 = 0;
	int useless2 = 0;
	return res;
}

int main(void)
{
	int useless1 = 1;
	int useless2 = 2;
	int useless3 = 3;
	int useless4 = 4;
	int useless5 = 5;
	int useless6 = 6;
	int useless7 = 7;
	int useless8 = 8;
	int useless_sum = useless1 + useless2 + useless3 + useless4;
	const int size_int = sizeof(int);
	const int size_long = sizeof(long);
	const int size_longlong = sizeof(long long);
	int p = sum(useless1, useless2, useless3, useless4, useless5, useless6,
		    useless7, useless8);
	return p;
}
