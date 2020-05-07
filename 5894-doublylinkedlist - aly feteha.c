#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;
typedef struct {
	Node* head;
	Node* tail;
} DoublyLinkedList;
const DoublyLinkedList EmptyList = {NULL, NULL};
DoublyLinkedList convertArrayToDoublyLinkedList(int array[], int size) {
	DoublyLinkedList list = {NULL, NULL};
	Node *firstnode=(Node*)malloc(sizeof(Node));
	firstnode->prev=NULL;
	firstnode->data=array[0];
	list.head=firstnode;
	int i;
	for(i=1;i<size;i++)
    {
        Node *newnode=(Node*)malloc(sizeof(Node));
        firstnode->next=newnode;
        newnode->data=array[i];
       newnode->next=NULL;
       newnode->prev=firstnode;
       firstnode=newnode;
        if(i==size-1)
            list.tail=newnode;

    }
	return list;
}

void destroy(DoublyLinkedList* list) {
   Node*newx;
while(list->head->next!=NULL){
    newx=list->head;
    list->head=list->head->next;
    free(newx);
}
list->head=NULL;
list->tail=NULL;
}
DoublyLinkedList dup(DoublyLinkedList list) {
 DoublyLinkedList newlist = {NULL, NULL};
 if(list.head==NULL)
    return newlist;
 Node*x=malloc(sizeof(Node));
 Node*nextnode=malloc(sizeof(Node));
 nextnode=list.head;
 x=NULL;
 while(nextnode!=NULL)
 {
     Node*newnode=malloc(sizeof(Node));
     newnode->data=nextnode->data;
     if(x==NULL)
     {
         x=newnode;
         x->next=NULL;
         x->prev=NULL;
         newlist.head=x;
     }
     else{
x->next=newnode;
        newnode->prev=x;
        newnode->next=NULL;
        x=newnode;
     }
     newlist.tail=nextnode;
     nextnode=nextnode->next;
 }

	/*Node *firstnode=(Node*)malloc(sizeof(Node));
	while(list.head!=NULL)
    {
        Node *nodex=malloc(sizeof(Node));
        nodex->data=list.head->data;
        if(firstnode==NULL)
        {
            firstnode=nodex;
            firstnode->next=NULL;
            firstnode->prev=NULL;
            newlist.head=list.head;
            list.head=list.head->next;
        }
        else{
            firstnode->next=nodex;
            nodex->prev=firstnode;
            firstnode=nodex;
            list.head=list.head->next;
        }
    }
    newlist.tail=firstnode;
	/*if(list.head==NULL)
        return newlist;
	firstnode->data=list.head->data;
	newlist.head=firstnode;
	while(firstnode!=NULL)
    {
        Node *newnode=(Node*)malloc(sizeof(Node));
        firstnode->next=newnode;
        newnode->data=firstnode->data;
       newnode->prev=firstnode;
       firstnode=newnode;
       if(newnode->next==NULL)
        newlist.tail=newnode;
    }*/

	return newlist;
}
DoublyLinkedList concatenate(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList newlist = {NULL, NULL};
	if(list1.head==NULL && list2.head==NULL)
        return newlist;
	if(list1.head==NULL)
        return list2;
	if(list2.head==NULL)
        return list1;
    else{
       list1.tail->next=list2.head;
       list2.head->prev=list1.tail;
       newlist.head=list1.head;
       newlist.tail=list2.tail;
       newlist.head->prev=NULL;
       newlist.tail->next=NULL;
    }
    return newlist;
}
size_t length(DoublyLinkedList list) {
	size_t count = 0;
	Node*co=list.head;
	while(co!=NULL){
        count++;
        co=co->next;
	}
	return count;
}

int isPalindrome(DoublyLinkedList list) {
	Node*q=list.head;
	Node*x=list.tail;
	while(q!=x){
        if(q->data!=x->data)
            return 0;
        q=q->next;
        x=x->prev;
	}
	return 1;
}

int areEqual(DoublyLinkedList list1, DoublyLinkedList list2) {
	Node*a=list1.head;
	Node*b=list2.head;
	int flag=0;
	int d=length(list1);
	int g=length(list2);
	if(a==NULL && b==NULL)
        return 1;
	while(d==g &&(a!=NULL && b!=NULL)){
    if(a->data!=b->data){
        flag=0;
        return 0;
    }
    else
        flag=1;
       a=a->next;
       b=b->next;
	}
	return flag;
}
void printlnListForward(DoublyLinkedList list) {
	Node*printer=list.head;
	if(printer==NULL)
     printf(" ");
	while(printer!=NULL){
            printf("%d",printer->data);
            printf(" ");
    printer=printer->next;
}
}
void printlnListBackward(DoublyLinkedList list) {
	//Node*printer=list.tail;
	if(list.tail==NULL)
     printf("   ");
	while(list.tail!=NULL){
            printf("%d  ",list.tail->data);
            printf(" ");
    list.tail=list.tail->prev;
}
}

void Investigate(char* title, DoublyLinkedList list) {
	printf("%s\n", title);
	printf("List =         ");
	printlnListForward(list);
	printf("Reverse List = ");
	printlnListBackward(list);
	printf("List Length = %u\n", length(list));
	printf("List isPalindrome = %d\n", isPalindrome(list));
	printf("...................................................\n");
}
/*
 *
 */
void testConcatenate1(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;

	list3 = dup(list1);
	Investigate("List3 = dup(List1)\n==================", list3);
	emptyList1 = dup(EmptyList);
	Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
	DoublyLinkedList list5 = concatenate(list3, emptyList1);
	Investigate("List5 = List3<->EmptyList1\n==========================", list5);
	destroy(&list5);
	Investigate("List5 (after destroy)\n=====================", list5);
	//destroy(&list3);			//already destroyed when list5 got destroyed
	//destroy(&emptyList1);		//already destroyed when list5 got destroyed
}
/*
 *
 */
void testConcatenate2(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;
	list3 = dup(list1);
	emptyList1 = dup(EmptyList);
	DoublyLinkedList list6 = concatenate(emptyList1, list3);
	Investigate("List6 = EmptyList1<->List3\n==========================", list6);
	destroy(&list6);
	Investigate("List6 (after destroy)\n=====================", list6);
	//destroy(&list3);			//already destroyed when list6 got destroyed
	//destroy(&emptyList1);		//already destroyed when list6 got destroyed
}
/*
 *
 */
void testConcatenate3(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;
	list3 = dup(list1);
	list4 = dup(list2);
	DoublyLinkedList list7 = concatenate(list3, list4);
	Investigate("List7 = List3<->List4\n=====================", list7);
	destroy(&list7);
	Investigate("List7 (after destroy)\n=====================", list7);
	//destroy(&list3);			//already destroyed when list7 got destroyed
	//destroy(&list4);			//already destroyed when list7 got destroyed
}
/*
 *
 */
void testConcatenate() {
	int array1[] = {0, 1, 2, 3, 4, 5, 6};
	int array2[] = {7, 8, 9};

	DoublyLinkedList list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
	Investigate("List1\n=====", list1);
	DoublyLinkedList list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
	Investigate("List2\n=====", list2);

	testConcatenate1(list1, list2);
	testConcatenate2(list1, list2);
	testConcatenate3(list1, list2);

	destroy(&list1);
	destroy(&list2);
}
/*
 *
 */
void testPalindrome() {
	int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
	int array4[] = {7, 8, 9, 9, 8, 7};

	DoublyLinkedList list8 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
	Investigate("List8\n=====", list8);
	DoublyLinkedList list9 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
	Investigate("List9\n=====", list9);

	destroy(&list8);
	destroy(&list9);
}
/*
 *
 */
void testAreEqual() {
	int array5[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
	int array6[] = {7, 8, 9, 9, 8, 7};
	int array7[] = {0, 1, 2, 3, 4, 5};

	DoublyLinkedList list10 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
	Investigate("List10\n=====", list10);
	DoublyLinkedList list11 = convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
	Investigate("List11\n=====", list11);
	DoublyLinkedList list12 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
	Investigate("List12\n=====", list12);
	DoublyLinkedList emptyList1 = dup(EmptyList);
	Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
	DoublyLinkedList emptyList2 = dup(EmptyList);
	Investigate("EmptyList2 = dup(EmptyList)\n===========================", emptyList2);

	printf("areEqual(List10, List10) = %d\n", areEqual(list10, list10));
	printf("areEqual(List10, List11) = %d\n", areEqual(list10, list11));
	printf("areEqual(List10, List12) = %d\n", areEqual(list10, list12));
	printf("areEqual(List11, List10) = %d\n", areEqual(list11, list10));
	printf("areEqual(List10, EmptyList1) = %d\n", areEqual(list10, emptyList1));
	printf("areEqual(EmptyList1, List10) = %d\n", areEqual(emptyList1, list10));
	printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

	destroy(&list10);
	destroy(&list11);
	destroy(&list12);

}
main() {
	testConcatenate();
	testPalindrome();
	testAreEqual();
	return 0;
}
