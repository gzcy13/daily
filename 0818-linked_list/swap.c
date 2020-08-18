void swap2(char *px, char *py)
{
	char*  tmp;
	tmp = px;
	px = py;
	py = tmp;
	printf("px=%s,py=%s\n", px, py);
}
int main()
{
	char *a = "left";
	char *b = "right";
	printf("a=%s,b=%s\n", a, b);
	swap2(a,b);
	printf("finished");
	printf("a=%s,b=%s\n", a, b);
	return 0;
}

