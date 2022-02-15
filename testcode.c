typedef struct structje{
	char *array;
}				t_struct;

void	func(t_struct *pointer)
{
	int i = 0;

	while (pointer->array[i])
	{
		printf("%c,", pointer->array[i]);
		i++;
	}
}

int main()
{
	char array[10];
	t_struct pointer;
	int i = 0;

	while (i < 10)
	{
		array[i] = 66;
		i++;
	}
	pointer.array = array;
	func(&pointer);
}