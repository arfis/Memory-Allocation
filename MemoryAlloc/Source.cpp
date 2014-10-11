/*
Memory allocation simulation. Using and array as a memory. Odd numbers mean memory taken and vice versa (3 free, 2 taken).
One block of memory represents 4 bytes, so the minimal allocation size is 4 bytes.
*/
#include<stdio.h>

const int MEM_SIZE = 1000;

int pamat [MEM_SIZE];
int poz [MEM_SIZE];
void init();
int alloc(int size);

int main()
{
	init();
	for(int i=1;i<81;i++)
	{
	poz[i-1] = alloc(i);
	}
	scanf("%d",pamat[0]);
	printf("ende");
	return 0;
}

void init()
{
	pamat[0]= 3993;
	pamat[MEM_SIZE-1] = 3993;
	printf("pamat bola inicializovana");
}
int calc_size(int size)
{

switch (size % 4){
case 0: return size;
		break;
default: return size + (4 - size % 4); 
}
}

int alloc(int size)
{
	int i = 0;
	int old_size;
	bool find = false;
	size = calc_size(size);

	while(!find)
	{
		if(pamat[i]%2 == 1 && (pamat[i]-1)*4 >= size)
		{
			find = true;
			old_size = pamat[i];
			pamat[i] = size;
			i += size/4 + 1;
			pamat[i] = size;
			pamat[i+1] = old_size - size - 8;
			pamat[i+1+(old_size-1-size-2)/4] = old_size - size - 8;
			return i;
		}
		else
		{
		i += (pamat[i])/4+2;
		}
	}
}
void free(int position)
{
	int shift;
	int free_size = pamat[position] - 1;
	bool left = false,right = false, both = false;
	//free the given position
	pamat[position] -= 1;
	shift = pamat[position]/4 + 1;
	pamat[position+shift] -= 1;
	//checking the left and right side of the array - if there are also free blocks which can be added togehter
	
	if(position > 0 && pamat[position - 1] % 1)	left = true;
	if(position + shift + 1 < MEM_SIZE && pamat[position + shift + 1] % 1) right = true;
	if(left && right) both = true;
	
	if(both)
	{
		//left size adding size
		free_size += pamat[position-1] - 1;
		//right size adding size
		free_size += pamat[position + pamat[position]/4 + 2] -1;
	}

}