/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

typedef struct Node 		//일반노드 구조체
{
	int key;					//데이터 값
	struct Node* link;			//다음 노드의 주소
} listNode;

typedef struct Head 		//헤드노드 구조체
{
	struct Node* first;
}headNode;

headNode* initialize(headNode* h);		//리스트 초기화
int freeList(headNode* h);				//리스트 공간 할당 해제

int insertFirst(headNode* h, int key);	//리스트의 맨앞에 노드 삽입
int insertNode(headNode* h, int key);	//오름차순에 따라 key 노드 삽입
int insertLast(headNode* h, int key);	//맨뒤에 노드 삽입

int deleteFirst(headNode* h);			//맨앞노드 삭제
int deleteNode(headNode* h, int key);	//key값을 가진 노드 삭제
int deleteLast(headNode* h);			//맨뒤 노드 삭제
int invertList(headNode* h);			//리스트 순서 반대로 나열

void printList(headNode* h);			//리스트 출력

int main()
{
	char command; 	//사용자가 선택한 명령
	int key;		//입력 받은 데이터 값
	headNode* headnode=NULL;
	printf("[----- [강은혜]  [2022041047] -----]\n");

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
		scanf(" %c", &command);//명령 받기

		switch(command) {
		case 'z': case 'Z'://singled linked list를 초기화 시킴
			headnode = initialize(headnode);
			break;
		case 'p': case 'P'://리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I'://하나의 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D'://노드하나 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N'://리스트 마지막에 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E'://마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F'://리스트 가장 앞에 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T'://첫번쨰 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R'://리스트를 역순으로 나열
			invertList(headnode);
			break;
		case 'q': case 'Q'://프로그램 종료
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) //singled linked list를 초기화 시킴
{
	//헤드가 이미 할당되었다면 할당해제
	if(h != NULL)
		freeList(h);

	//헤드 할당
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	
	//p에 첫번째 노드 주소 할당
	listNode* p = h->first;

	//prev선언: 이전노드 가리키는 포인터
	listNode* prev = NULL;

	//앞에서 부터 공간반환 시작
	while(p != NULL) {
		//끝이 나올떄까지 p에 다음 주소 넣고 prev를 반환하는 식으로 할당해제
		prev = p;
		p = p->link;
		free(prev);
	}
	//마지막으로 헤드노드 해제
	free(h);
	return 0;
}


int insertNode(headNode* h, int key) //키값 오름차순으로 노드 삽입
{
	//삽입할 노드 선언 후 key값 넣기
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	//헤드노드만 선언되어있다면,
	//첫번째에 노드 삽입 후 함수 종료
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	
	listNode* n = h->first;		//n: 현재 탐색하고있는 노드, 이하 현재노드라 칭.
	listNode* trail = h->first;	//trail: 삽입한 노드 뒤에 붙여줄 노드

	//노드를 오름차순
	while(n != NULL) {
		if(n->key >= key) 		//현재노드의 키 값이 입력값보다 크고
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) 	
			{
				h->first = node;//노드를 헤드노드 뒤에 삽입하고
				node->link = n;	//원래 있던 노드를 뒤에 연결
			} 
			else {/* 중간이거나 마지막인 경우 */			 		

				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		//마지막 노드까지 찾지 못한 경우, 마지막에 삽입
		trail = n; 	//trail에 현재노드 주소 넣고
		n = n->link;//n에 다음 주소 넣고
	}

	trail->link = node;//trail 뒤에 노드 삽입
	return 0;
}


int insertLast(headNode* h, int key) //맨뒤에 노드 삽입
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)	//헤드 노드밖에 없으면
	{
		h->first = node;	//첫노드에 삽입 후 함수 종료
		return 0;
	}

	listNode* n = h->first;	

	//맨 뒤 링크로 이동 후 맨뒤에 삽입
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}


/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	//(구)첫 노드와 헤드노드 사이에 노드 삽입
	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) 
{
	//리스트가 비었다면 오류문자 출력후 함수 종료
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} 
			else { 
			/* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;		//trail에 현재 주소 부여
		n = n->link;	//n에 다음 주소 부여
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	/*리스트가 비었을시 오류 문구 출력후 함수종료*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;//헤드링크 끊고
		free(n);		//n 할당 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n; 		//trail에 현재노드 주소넣고
		n = n->link;	//n에 다음 주소 삽입
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; 
	free(n);

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{
	/*리스트가 비었을시 오류 문구 출력후 함수종료*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//n에 첫번째 노드 주소 넣기
	listNode* n = h->first;

	//헤드가 두번째 노드를 가리키게 만들고 첫번째 노드 할당해제
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	/*리스트가 비었을시 오류 문구 출력후 함수종료*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;	//다음노드 주소저장 및 이동 포인터
	listNode *trail = NULL;	//앞에 노드 저장 포인터
	listNode *middle = NULL;//현재노드 주소저장 포인터

	while(n != NULL){
		
		trail = middle; 		//trail에 앞노드 값 넣기
		middle = n;				//middle의 현재 노드 주소 저장
		n = n->link;			//다음노드로 이동
		middle->link = trail;	//이후 노드의 링크가 앞노드를 가리키도 설정
	}

	h->first = middle;//헤드가 마지막 노드를 가리키도록 설정

	return 0;
}


void printList(headNode* h) //리스트 출력함수
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	/*리스트가 비었을시 오류 문구 출력후 함수종료*/
	if(h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	/*리스트 이동하며 출력*/
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
