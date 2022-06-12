#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"

#define LINE_BUFFER 128

typedef struct Employee {
	short code;
	char* name;
	char* department;
	double salary;
}Employee;

typedef struct Node {
	Employee* emp;
	struct Node* nextNode;
}Node;



/*functions' signatures for memory management*/
Employee* createEmployee(short , char* , char* , double );
Node* createNode( Employee* emp);

/*functions' signatures for list operations*/
void insertTail(Node**, Employee*);
void printList(const Node* );
void printEmployee(Employee* );
void insertHead(Node** , Employee* );
void insertOnPosition(Node**, Employee*, int pos);
void deletePosition(Node** , int );
Node* deleteListPos(Node* head, int pos);

void main()
{
	Node* head = NULL;
	Employee* emp = NULL;
	FILE* f = fopen("Data.txt", "r");

	char lineBuffer[LINE_BUFFER];
	char* token;
	char sep_list[] = ",\n";

	if (f)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), f))
		{
			emp = (Employee*)malloc(sizeof(Employee));

			token = strtok(lineBuffer, sep_list);
			emp->code = atoi(token);

			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);

			token = strtok(NULL, sep_list);
			emp->department = (char*)malloc(strlen(token) + 1);
			strcpy(emp->department, token);

			token = strtok(NULL, sep_list);
			emp->salary = atof(token);

			insertTail(&head, emp);
			
		}

		printList(head); //daca nu ii dau pass by address nu se modifica valoarea lui in functie

		Employee* empl = createEmployee(1234, "Chivu Monica", "Facem teste", 750);
		
		printf("CACA\n");

		//insertHead(&head, empl);
		insertOnPosition(&head, empl, 3);
		printList(head);
		printf("CACA\n");

		deletePosition(&head, 4);
		printList(head);
	}
}



void deletePosition(Node** head, int pos)
{
	int index = 1;
	Node* aux = NULL;
	
	if (pos <= 1)
	{
		(*head) = (*head)->nextNode;
	}
	else {
		
		Node* node = *head;
		while (node->nextNode && index++ < pos-1)
		{
			node = node->nextNode;
			
		}
		if (node->nextNode)
		{
			node->nextNode = node->nextNode->nextNode;
		}
		
		
	}

	
}

void insertOnPosition(Node** head, Employee* emp,int pos)
{
	Node* node = createNode(emp);
	int index = 1;

	if (pos <= 1)
	{
		insertHead(head, emp);
	}
	else {
		Node* tmp = *head;
		while (tmp->nextNode && index++<pos-1)
		{
			tmp = tmp->nextNode;

		}
		node->nextNode = tmp->nextNode;
		tmp->nextNode = node;
		
	}

}

void printEmployee(Employee* emp)
{
	printf("Code: %d  ,Department: %s ,Name: %s, Salary: %f \n " , emp->code, emp->department , emp->name , emp->salary );
}

void printList( const Node* head)
{
	while (head)
	{
		printEmployee(head->emp);
		head = head->nextNode;
	}

}

void insertHead(Node** head, Employee* emp)
{
	Node* newHead = createNode(emp);
	newHead->nextNode = (*head);
	(*head) = newHead;
}

void insertTail(Node** head, Employee* emp)
{
	Node* newNode = createNode(emp);
	Node* tmp = (Node*)malloc(sizeof(Node));

	if ((*head) == NULL)
	{
		*head = newNode;
	}
	else {
		tmp = *head;
		while (tmp->nextNode)
		{
			tmp = tmp->nextNode;
		}
		tmp->nextNode = newNode;
	}
	
	//tmp->nextNode = newNode;
}

Node* createNode(Employee* emp)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->emp = emp;
	node->nextNode = NULL;
	
	return node;
}

Employee* createEmployee(short code, char* name, char* department, double salary)
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));

	emp->code = code;
	emp->salary = salary;

	emp->name = (char*)malloc(sizeof(strlen(name) + 1));
	strcpy(emp->name, name);

	emp->department = (char*)malloc(sizeof(department) + 1);
	strcpy(emp->department, department);

	return emp;

}