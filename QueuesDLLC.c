#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include <stdbool.h>
#define LINE_BUFFER 128

typedef struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
}Employee;

typedef struct Node {
	Employee* emp;
	struct Node* prev, *next;
}Node;

typedef Node Queue;

//functions for memory management
Employee* createInfo(short , char* , char* , double );
Employee* createNode(Employee* );
//functions for working with dll - queues
void put(Queue**, Employee*);
void printInfo(Employee* );
void printQueue(Queue* );
Employee* get(Queue** );
bool isEmpty(Queue* );
void deleteQueue(Queue** );
Employee* peek(Queue* );


void main()
{
	Queue* queue = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			token = strtok(lineBuffer, sepList);
			code = atoi(token);
			name = strtok(NULL, sepList);
			dept = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			salary = atof(token);

			Employee* info = createInfo(code, name, dept, salary);

			put(&queue, info);

		}

		printQueue(queue);

		printf("caca\n");
		get(&queue);
		printQueue(queue);

		

		Employee* pee = peek(queue);
		printf("REsult of peek: \n");
		printInfo(pee);

		printf("DE AICI INCEP SA STRG TOATE ELEMENTELE DUPA CE LE AFISEZ\n");
		deleteQueue(&queue);
		if (isEmpty(queue))
			printf("IS EMPTY GOOD JOB\n");
		else printf("NOT EMPTY TRY AGAIN\n");

		
	}
}

Employee* peek(Queue* queue)
{
	Employee* emp = createInfo(queue->prev->emp->code, queue->prev->emp->name, queue->prev->emp->dept, queue->prev->emp->salary);
	return emp;
}

void deleteQueue(Queue** queue)
{
	Employee* emp = NULL;
	while (*queue)
	{
		emp = get(queue);
		printInfo(emp);
	}
}

bool isEmpty(Queue* queue)
{
	if (queue == NULL)
	{
		return true;
	}
	else return false;
}

Employee* get(Queue** queue)
{
	Employee* emp = NULL;

	if ((*queue) != NULL)
	{
		emp = (*queue)->emp;
		Node* index = *queue;
		if (index->next != index && index->prev != index)
		{
			index->prev->next = index->next;
			index->next->prev = index->prev;
			*queue = index->next;
		}
		else {
			*queue = NULL;
		}
		free(index);
	}
	return emp;
}

void printQueue(Queue* queue)
{
	/*while (queue)
	{
		printInfo(queue->emp);
		queue = queue->next;
	}*/

	Queue* tmp = queue;
	do {
		printInfo(tmp->emp);
		tmp = tmp->next;
	} while (tmp != queue);
}

void put(Queue** queue, Employee* emp)
{
	Node* newNode = createNode(emp);
	if (*queue == NULL) //if the queue is null
	{
		newNode->next = newNode->prev = newNode;  //we insert the first node in the queue
		*queue = newNode;  
	}
	else {
		newNode->next = *queue;
		newNode->prev = (*queue)->prev;

		(*queue)->prev->next = newNode;
		(*queue)->prev = newNode;
	}
}

void printInfo(Employee* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
}

Employee* createInfo(short code, char* name, char* dept, double salary)
{
	 Employee* emp = (Employee*)malloc(sizeof(Employee));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}

Employee* createNode(Employee* info)
{
	Node* node = (Node*)malloc(sizeof(Node));

	node->emp = info;
	node->next = NULL;
	node->prev = NULL;
	return node;
}