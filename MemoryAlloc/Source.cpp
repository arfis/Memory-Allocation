/*
Memory allocation simulation. Using and array as a memory. Odd numbers mean memory taken and vice versa (3 free, 2 taken).
One block of memory represents INT_SIZE bytes, so the minimal allocation size is INT_SIZE bytes.
*/
#include<stdio.h>
#include<stdlib.h>

const int MEM_SIZE = 1000;
const int INT_SIZE = 4;
const int HLAVICKY = 2;

int *pamat;
int *poz;
void init();
int alloc(int size);
void printArray(int *arr);
void mfree(int position);

int main()
{
	init();
	for(int i=1;i<80;i++)
	{
	*(poz+i-1) = alloc(i);
	}
	printf("ende");
	mfree(0);
	//mfree(poz[22]);
	mfree(poz[21]);
	mfree(poz[20]);
	mfree(poz[19]);
	printArray(pamat);
	scanf("%d",pamat[0]);
	return 0;
}

void init()
{
	pamat = (int*) calloc (MEM_SIZE,sizeof(int));
	poz = (int *) calloc (80,sizeof(int));

	*(pamat+0)= MEM_SIZE*INT_SIZE+1;
	*(pamat+MEM_SIZE-1) = MEM_SIZE*INT_SIZE+1;
	printf("pamat bola inicializovana");
}

//prepocitanie velkosti aby bola zarovnana - delitelna 4
int calc_size(int size)
{

switch (size % INT_SIZE){
		case 0: return size;
		break;
		default: return size + (INT_SIZE - size % INT_SIZE); 
}
}

int alloc(int size)
{
	int i = 0;
	int old_size;
	bool find = false;
	size = calc_size(size);
	int start;
	int free_size;

	while(!find)
	{
		//najdenie prveho volneho bloku - neparne cislo && velkost musi byt rovna alebo vacsia -> first fit
		if(*(pamat+i)%2 == 1 && (*(pamat+i)-1*INT_SIZE) >= size)
		{
			start = i;
			find = true;
			old_size = *(pamat+i);
			*(pamat+i) = size;
			i += size/INT_SIZE + 1;
			*(pamat+i) = size;
			*(pamat+i+1) = old_size - size - HLAVICKY*INT_SIZE;

			free_size = i+(old_size-1-size-HLAVICKY*INT_SIZE)/INT_SIZE;
			//printf("%d",free_size);
			*(pamat+free_size) = old_size - size - HLAVICKY*INT_SIZE;
			return start;
		}
		else
		{
		i += (*(pamat+i))/INT_SIZE+HLAVICKY;
		}
	}
}
void printArray(int *arr)
{
	int i = 0;
	for(i=0;i<MEM_SIZE;i++)
	{
		printf(" %d ",*(arr+i));
	}
	/*
	for(i=0;i<60;i++)
	{
		printf(" %d ",*(poz+i));
	}
	*/
}
void mfree(int position)
{
	int shift;
	int free_size = *(pamat+position) - 1;
	int left_free=0, right_free=0, original_size;
	bool left = false,right = false, both = false;
	//free the given position
	*(pamat+position) += 1;
	shift = *(pamat+position)/INT_SIZE + 1;
	*(pamat+position+shift) += 1;
	//checking the left and right side of the array - if there are also free blocks which can be added togehter
	
	if(position > 0 && *(pamat+position - 1) % 2)	left = true;
	if(position + shift + 1 < MEM_SIZE && *(pamat+position + shift + 1) % 2) right = true;
	if(left && right) both = true;
	
	if(both)
	{
		//left size adding size
		free_size += pamat[position-1] - 1;
		//right size adding size
		free_size += pamat[position + pamat[position]/INT_SIZE + 2] -1;
	}
	if(left)
	{
		//ulozenie hodnoty ktoru chceme zmazat
		original_size = *(pamat + position);
		//ulozenie hodnoty lavej volnej pamete
		left_free = *(pamat+position-1);
		//celkova volna pamat ktora vznikne
		free_size += left_free+2*INT_SIZE;

		//premenna ktora ma v sebe ulozene ako daleko je pozicia lavej hlavicky 
		//+2 koli dvom hlavickam ked sa ide do lava
		shift = left_free/INT_SIZE +2;
		//nastavenie lavej hlavicky na velkost novej volnej pamete
		*(pamat+position-shift) = free_size+1;
		//vynulovanie strednej hlavicky a paticky
		*(pamat+position-1) = 0;
		*(pamat+position) = 0;
		//nastavenie pravej paticky +1 koli jednej hlavicke ked sa ide do prava
		*(pamat + position + original_size/INT_SIZE + 1) = free_size+1;
	}
	if(right)
	{
		//ulozenie hodnoty ktoru chceme zmazat
		original_size = *(pamat + position);
		//ulozenie hodnoty lavej volnej pamete
		right_free = *(pamat+position+original_size/INT_SIZE + 1);
		//celkova volna pamat ktora vznikne
		free_size += right_free+2*INT_SIZE;
	
		//premenna ktora ma v sebe ulozene ako daleko je prava paticka
		//+3 koli trom hlavickam ked sa ide do prava
		shift = (original_size+right_free)/INT_SIZE +3;

		*(pamat+position) = free_size+1;
		*(pamat+position+right_free/INT_SIZE+2) = 0;
		//+1 koli jednej hlavicke ked sa ide do prava
		*(pamat + position + right_free/INT_SIZE + 1) = 0;
		*(pamat+position+shift) = free_size+1;
	}
}