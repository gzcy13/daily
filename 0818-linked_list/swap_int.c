void swap3(int *px, int *py)
{
	int *tmp;
	tmp = px;
	px = py;
	py = tmp;
	printf("px=%d,py=%d\n", *px, *py);
}


int main()
{
	int a = 2;
	int *b = 3;
//	swap3(&a, &b);
	printf("a=%d,b=%d", a, b);
	return 0;
}
