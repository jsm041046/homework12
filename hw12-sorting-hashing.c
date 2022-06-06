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

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- 2021041046 전설민 -----]\n"); //학번 이름 출력 
	do{
        // 안내문 출력
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
		scanf(" %c", &command); //명령 입력

		switch(command) { //입력된 명령어에 따른 분기
		case 'z': case 'Z':
			initialize(&array); //array초기화
			break;
		case 'q': case 'Q':
			freeArray(array); //array메모리 할당 해제
			break;
		case 's': case 'S':
			selectionSort(array); //array 선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); //array 삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); //array 버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); //array 쉘 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //array 출력
			quickSort(array, MAX_ARRAY_SIZE); //13크기의 배열을 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); //array 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //array 출력
			hashing(array, &hashtable); //array를 해쉬 테이블에 해싱
			printArray(hashtable); //해쉬테이블 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //해쉬 키 입력
			printArray(hashtable); //해쉬테이블 출력
			index = search(hashtable, key); //해쉬 키 탐색
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //해쉬 결과 출력
			break;

		case 'p': case 'P':
			printArray(array); //array 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못된 명령어 입력 시
			break;
		}

	}while(command != 'q' && command != 'Q'); //q입력시 종료

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); //포인터 a의 메모리가 할당돼있을 경우 할당 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); //프린트할 포인터 a가 정의되지 않았을 경우 함수에서 빠져나감
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //인덱스 0부터 최대까지 인덱스 안내문 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //인덱스 0부터 최대까지 포인터 a의 값 출력
	printf("\n");
    //1줄에 배열의 몇번째 인덱스인지 안내하고, 2줄에 해당 배열을 출력하는 함수다
}


int selectionSort(int *a)
{
	int min; //최소값을 저장하는 변수
	int minindex; //최소값의 인덱스를 저장하는 변수
	int i, j; //반복자

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //배열 크기만큼 반복
	{
		minindex = i; //i부터 최대까지의 범위 내에서 최소값을 찾기 전 초기화
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
            //이전까지의 최소값보다 현재 탐색하고 있는 값이 적을 경우 최소값 갱신
		}
		a[minindex] = a[i]; //본래 최소값이 있었던 자리에 i에 위치하는 값 대입
		a[i] = min; //최소값을 i번째에 대입
	}
    //가장 작은 값을 찾아 적은 인덱스값으로 이동하는 선택 정렬을 시행하는 이중 반복문이다
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t; //변수 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //i를 1부터 배열의 최대 인덱스까지 반복
	{
		t = a[i]; //a[i]를 t에 임시로 저장
		j = i; //j에 i를 대입
		while (a[j-1] > t && j > 0) //j가 0보다 크거나, a[j-1]이 t보다 클 때 동안
		{
			a[j] = a[j-1]; //a[j-1]을 a[j]에 대입
			j--; //j를 1감소
		}
		a[j] = t; //t의 값을 a[j]에 대입
	}
    //일정한 인덱스의 값을 임시로 저장한 후 그 값보다 작은 값이 나올 때 까지 적은 값을 밀쳐가면서 이동시키는 삽입 정렬을 시행하는 함수다
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
			if (a[j-1] > a[j]) //a[j-1]이 a[j]보다 클 경우
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
                //두 인덱스의 값을 교환
			}
		}
	}
    //인접한 값 두개를 비교해서 큰 값이 작은 값보다 적은 인덱스에 있을 때 자리를 바꾸는 버블 정렬을 시행하는 함수다
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

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //배열 최대 인덱스의 절반의 크기를 정렬의 간격인 h에 저장
	{
		for (i = 0; i < h; i++) //0부터 h까지 i를 반복자로 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //h만큼을 띄어가며 배열의 최대 인덱스까지 j를 반복자로 반복
			{
				v = a[j]; //v를 a[j]에 저장
				k = j; //k에 j를 저장
				while (k > h-1 && a[k-h] > v) //k가 h-1보다 크고, a[k-h] > v를 만족할 때 까지 반복
				{
					a[k] = a[k-h]; //a[k]에 a[k-h]대입
					k -= h; //k는 h만큼 감소
                    //삽입 정렬과 유사한 알고리즘을 가짐
                }
				a[k] = v; //v를 a[k]에 대입
			}
		}
	}
    //일정 간격을 기준으로 점점 줄여가며 정렬 한 후 삽입정렬을 해서 시행 시간을 감소시키는 쉘 정렬을 시행하는 알고리즘이다
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t; //임시 변수 대입
	int i, j; //반복자 대입

	if (n > 1)
	{
		v = a[n-1]; //피벗 결정
		i = -1; //i에 최소인덱스 대입
		j = n - 1; //j에 최대인덱스 대입

		while(1)
		{
			while(a[++i] < v); //피벗보다 a[i]가 작을 경우 i 1증가
			while(a[--j] > v); //피벗보다 a[j]가 클을 경우 j 1감소

			if (i >= j) break; //i가 j보다 클 경우 반복문에서 빠져나감
			t = a[i];
			a[i] = a[j];
			a[j] = t;
            //i와 j인덱스의 값 교환
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
        //피벗의 위치를 i로 이동시킴

		quickSort(a, i); //피벗보다 작은 인덱스만 모아서 재귀적으로 퀵 정렬 시행
		quickSort(a+i+1, n-i-1); //피벗보다 큰 인덱스만 모아서 재귀적으로 퀵 정렬 시행
	}
    //피벗을 기준으로 작은 값을 적은 인덱스에, 큰 값을 큰 인덱스에 이동시키는 퀵 정렬을 시행하는 함수다

	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
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



