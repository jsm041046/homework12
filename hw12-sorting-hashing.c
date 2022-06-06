/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- 2021041046 ������ -----]\n"); //�й� �̸� ��� 
	do{
        // �ȳ��� ���
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��� �Է�

		switch(command) { //�Էµ� ��ɾ ���� �б�
		case 'z': case 'Z':
			initialize(&array); //array�ʱ�ȭ
			break;
		case 'q': case 'Q':
			freeArray(array); //array�޸� �Ҵ� ����
			break;
		case 's': case 'S':
			selectionSort(array); //array ���� ����
			break;
		case 'i': case 'I':
			insertionSort(array); //array ���� ����
			break;
		case 'b': case 'B':
			bubbleSort(array); //array ���� ����
			break;
		case 'l': case 'L':
			shellSort(array); //array �� ����
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //array ���
			quickSort(array, MAX_ARRAY_SIZE); //13ũ���� �迭�� �� ����
			printf("----------------------------------------------------------------\n");
			printArray(array); //array ���

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //array ���
			hashing(array, &hashtable); //array�� �ؽ� ���̺� �ؽ�
			printArray(hashtable); //�ؽ����̺� ���
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //�ؽ� Ű �Է�
			printArray(hashtable); //�ؽ����̺� ���
			index = search(hashtable, key); //�ؽ� Ű Ž��
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //�ؽ� ��� ���
			break;

		case 'p': case 'P':
			printArray(array); //array ���
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�߸��� ��ɾ� �Է� ��
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�Է½� ����

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); //������ a�� �޸𸮰� �Ҵ������ ��� �Ҵ� ����
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); //����Ʈ�� ������ a�� ���ǵ��� �ʾ��� ��� �Լ����� ��������
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //�ε��� 0���� �ִ���� �ε��� �ȳ��� ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //�ε��� 0���� �ִ���� ������ a�� �� ���
	printf("\n");
    //1�ٿ� �迭�� ���° �ε������� �ȳ��ϰ�, 2�ٿ� �ش� �迭�� ����ϴ� �Լ���
}


int selectionSort(int *a)
{
	int min; //�ּҰ��� �����ϴ� ����
	int minindex; //�ּҰ��� �ε����� �����ϴ� ����
	int i, j; //�ݺ���

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //�迭 ũ�⸸ŭ �ݺ�
	{
		minindex = i; //i���� �ִ������ ���� ������ �ּҰ��� ã�� �� �ʱ�ȭ
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
            //���������� �ּҰ����� ���� Ž���ϰ� �ִ� ���� ���� ��� �ּҰ� ����
		}
		a[minindex] = a[i]; //���� �ּҰ��� �־��� �ڸ��� i�� ��ġ�ϴ� �� ����
		a[i] = min; //�ּҰ��� i��°�� ����
	}
    //���� ���� ���� ã�� ���� �ε��������� �̵��ϴ� ���� ������ �����ϴ� ���� �ݺ����̴�
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t; //���� ����

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //i�� 1���� �迭�� �ִ� �ε������� �ݺ�
	{
		t = a[i]; //a[i]�� t�� �ӽ÷� ����
		j = i; //j�� i�� ����
		while (a[j-1] > t && j > 0) //j�� 0���� ũ�ų�, a[j-1]�� t���� Ŭ �� ����
		{
			a[j] = a[j-1]; //a[j-1]�� a[j]�� ����
			j--; //j�� 1����
		}
		a[j] = t; //t�� ���� a[j]�� ����
	}
    //������ �ε����� ���� �ӽ÷� ������ �� �� ������ ���� ���� ���� �� ���� ���� ���� ���İ��鼭 �̵���Ű�� ���� ������ �����ϴ� �Լ���
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]�� a[j]���� Ŭ ���
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
                //�� �ε����� ���� ��ȯ
			}
		}
	}
    //������ �� �ΰ��� ���ؼ� ū ���� ���� ������ ���� �ε����� ���� �� �ڸ��� �ٲٴ� ���� ������ �����ϴ� �Լ���
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //�迭 �ִ� �ε����� ������ ũ�⸦ ������ ������ h�� ����
	{
		for (i = 0; i < h; i++) //0���� h���� i�� �ݺ��ڷ� �ݺ�
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //h��ŭ�� ���� �迭�� �ִ� �ε������� j�� �ݺ��ڷ� �ݺ�
			{
				v = a[j]; //v�� a[j]�� ����
				k = j; //k�� j�� ����
				while (k > h-1 && a[k-h] > v) //k�� h-1���� ũ��, a[k-h] > v�� ������ �� ���� �ݺ�
				{
					a[k] = a[k-h]; //a[k]�� a[k-h]����
					k -= h; //k�� h��ŭ ����
                    //���� ���İ� ������ �˰����� ����
                }
				a[k] = v; //v�� a[k]�� ����
			}
		}
	}
    //���� ������ �������� ���� �ٿ����� ���� �� �� ���������� �ؼ� ���� �ð��� ���ҽ�Ű�� �� ������ �����ϴ� �˰����̴�
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t; //�ӽ� ���� ����
	int i, j; //�ݺ��� ����

	if (n > 1)
	{
		v = a[n-1]; //�ǹ� ����
		i = -1; //i�� �ּ��ε��� ����
		j = n - 1; //j�� �ִ��ε��� ����

		while(1)
		{
			while(a[++i] < v); //�ǹ����� a[i]�� ���� ��� i 1����
			while(a[--j] > v); //�ǹ����� a[j]�� Ŭ�� ��� j 1����

			if (i >= j) break; //i�� j���� Ŭ ��� �ݺ������� ��������
			t = a[i];
			a[i] = a[j];
			a[j] = t;
            //i�� j�ε����� �� ��ȯ
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
        //�ǹ��� ��ġ�� i�� �̵���Ŵ

		quickSort(a, i); //�ǹ����� ���� �ε����� ��Ƽ� ��������� �� ���� ����
		quickSort(a+i+1, n-i-1); //�ǹ����� ū �ε����� ��Ƽ� ��������� �� ���� ����
	}
    //�ǹ��� �������� ���� ���� ���� �ε�����, ū ���� ū �ε����� �̵���Ű�� �� ������ �����ϴ� �Լ���

	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



