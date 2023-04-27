/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

typedef struct Node 		//�Ϲݳ�� ����ü
{
	int key;					//������ ��
	struct Node* link;			//���� ����� �ּ�
} listNode;

typedef struct Head 		//����� ����ü
{
	struct Node* first;
}headNode;

headNode* initialize(headNode* h);		//����Ʈ �ʱ�ȭ
int freeList(headNode* h);				//����Ʈ ���� �Ҵ� ����

int insertFirst(headNode* h, int key);	//����Ʈ�� �Ǿտ� ��� ����
int insertNode(headNode* h, int key);	//���������� ���� key ��� ����
int insertLast(headNode* h, int key);	//�ǵڿ� ��� ����

int deleteFirst(headNode* h);			//�Ǿճ�� ����
int deleteNode(headNode* h, int key);	//key���� ���� ��� ����
int deleteLast(headNode* h);			//�ǵ� ��� ����
int invertList(headNode* h);			//����Ʈ ���� �ݴ�� ����

void printList(headNode* h);			//����Ʈ ���

int main()
{
	char command; 	//����ڰ� ������ ���
	int key;		//�Է� ���� ������ ��
	headNode* headnode=NULL;
	printf("[----- [������]  [2022041047] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//��� �ޱ�

		switch(command) {
		case 'z': case 'Z'://singled linked list�� �ʱ�ȭ ��Ŵ
			headnode = initialize(headnode);
			break;
		case 'p': case 'P'://����Ʈ ���
			printList(headnode);
			break;
		case 'i': case 'I'://�ϳ��� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D'://����ϳ� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N'://����Ʈ �������� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E'://������ ��� ����
			deleteLast(headnode);
			break;
		case 'f': case 'F'://����Ʈ ���� �տ� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T'://ù���� ��� ����
			deleteFirst(headnode);
			break;
		case 'r': case 'R'://����Ʈ�� �������� ����
			invertList(headnode);
			break;
		case 'q': case 'Q'://���α׷� ����
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) //singled linked list�� �ʱ�ȭ ��Ŵ
{
	//��尡 �̹� �Ҵ�Ǿ��ٸ� �Ҵ�����
	if(h != NULL)
		freeList(h);

	//��� �Ҵ�
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	
	//p�� ù��° ��� �ּ� �Ҵ�
	listNode* p = h->first;

	//prev����: ������� ����Ű�� ������
	listNode* prev = NULL;

	//�տ��� ���� ������ȯ ����
	while(p != NULL) {
		//���� ���Ë����� p�� ���� �ּ� �ְ� prev�� ��ȯ�ϴ� ������ �Ҵ�����
		prev = p;
		p = p->link;
		free(prev);
	}
	//���������� ����� ����
	free(h);
	return 0;
}


int insertNode(headNode* h, int key) //Ű�� ������������ ��� ����
{
	//������ ��� ���� �� key�� �ֱ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	//����常 ����Ǿ��ִٸ�,
	//ù��°�� ��� ���� �� �Լ� ����
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	
	listNode* n = h->first;		//n: ���� Ž���ϰ��ִ� ���, ���� ������� Ī.
	listNode* trail = h->first;	//trail: ������ ��� �ڿ� �ٿ��� ���

	//��带 ��������
	while(n != NULL) {
		if(n->key >= key) 		//�������� Ű ���� �Է°����� ũ��
		{
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) 	
			{
				h->first = node;//��带 ����� �ڿ� �����ϰ�
				node->link = n;	//���� �ִ� ��带 �ڿ� ����
			} 
			else {/* �߰��̰ų� �������� ��� */			 		

				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		//������ ������ ã�� ���� ���, �������� ����
		trail = n; 	//trail�� ������ �ּ� �ְ�
		n = n->link;//n�� ���� �ּ� �ְ�
	}

	trail->link = node;//trail �ڿ� ��� ����
	return 0;
}


int insertLast(headNode* h, int key) //�ǵڿ� ��� ����
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)	//��� ���ۿ� ������
	{
		h->first = node;	//ù��忡 ���� �� �Լ� ����
		return 0;
	}

	listNode* n = h->first;	

	//�� �� ��ũ�� �̵� �� �ǵڿ� ����
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}


/*
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	//(��)ù ���� ����� ���̿� ��� ����
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) 
{
	//����Ʈ�� ����ٸ� �������� ����� �Լ� ����
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = n->link;
			} 
			else { 
			/* �߰��� ���ų� �������� ��� */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;		//trail�� ���� �ּ� �ο�
		n = n->link;	//n�� ���� �ּ� �ο�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	/*����Ʈ�� ������� ���� ���� ����� �Լ�����*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {
		h->first = NULL;//��帵ũ ����
		free(n);		//n �Ҵ� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {
		trail = n; 		//trail�� ������ �ּҳְ�
		n = n->link;	//n�� ���� �ּ� ����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL; 
	free(n);

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) 
{
	/*����Ʈ�� ������� ���� ���� ����� �Լ�����*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//n�� ù��° ��� �ּ� �ֱ�
	listNode* n = h->first;

	//��尡 �ι�° ��带 ����Ű�� ����� ù��° ��� �Ҵ�����
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	/*����Ʈ�� ������� ���� ���� ����� �Լ�����*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;	//������� �ּ����� �� �̵� ������
	listNode *trail = NULL;	//�տ� ��� ���� ������
	listNode *middle = NULL;//������ �ּ����� ������

	while(n != NULL){
		
		trail = middle; 		//trail�� �ճ�� �� �ֱ�
		middle = n;				//middle�� ���� ��� �ּ� ����
		n = n->link;			//�������� �̵�
		middle->link = trail;	//���� ����� ��ũ�� �ճ�带 ����Ű�� ����
	}

	h->first = middle;//��尡 ������ ��带 ����Ű���� ����

	return 0;
}


void printList(headNode* h) //����Ʈ ����Լ�
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	/*����Ʈ�� ������� ���� ���� ����� �Լ�����*/
	if(h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	/*����Ʈ �̵��ϸ� ���*/
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
