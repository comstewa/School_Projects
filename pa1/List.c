//Connor Stewart
//Comstewa
//this is a double linked list used by the other files
//
//
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include "List.h" 

typedef struct NodeObj{
   struct NodeObj* next;
   struct NodeObj* prev;
   int data;
}NodeObj;
typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
}ListObj;
//typedef ListObj* List;

Node newNode(int data){
	Node B = malloc(sizeof(NodeObj));// allocating memory for the new blocks 
	assert(B!=NULL);// safty measure to terminate 
	B->data=data;
	B->next= NULL;
	B->prev=NULL;
	return B;
}
List newList(void){
	List L = malloc(sizeof(ListObj));// allocating memory for the new blocks 
	assert(L!=NULL);// safty measure to terminate 
	L->front=NULL;
	L->back=NULL;
	L->cursor=NULL;
	L->length=0;
	L->index=NULL;
	return L;
}
void freeList(List* pL){
	List del = *pL;
	int pp=length(*pL);
	for(int i=0;i<pp;i++){
		moveBack(*pL);
		delete(*pL);
		
		
	}

	//List poopoo = *pL;

	
	//List lastone=*pL;
	//Nod
	//while(letsgo!=NULL){
	//	Node* next=letsgo->next;
	//	free(letsgo);
	//	letsgo=next;
	//	deleteFront(*pL);

	//while(front(*pL) != NULL){
	//	deleteFront(*pL);
//	}
	//if(pL!=NULL && *pL!=NULL){
		

		free(*pL);
		*pL=NULL;
	
	//}
} // Frees all heap memory associated with *pL, and sets
 	// *pL to NULL.
	// Access functions -----------------------------------------------------------
int length(List L){
	if(L->length==NULL){
		L->length=0;
		return 0;

	}

	return L->length;
}
int index(List L){
	if(L->cursor == L->front && L->front != NULL){
		return 0;
	}
	if(L->cursor!=NULL){
		return L->index;

	}else{
		return -1;
	}
} // Returns index of cursor element if defined, -1 otherwise.

int front(List L){
	if(length(L) > 0){
		Node B = L->front;	//returns front data
		return(B->data);
	}
	return -1;
} // Returns front element of L. Pre: length()>0

int back(List L){
	if(length(L)>0){
		Node B = L->back;
		return(B->data);	//returns back data
	}
	return -1;; // Returns back element of L. Pre: length()>0
}
int get(List L){
	if(length(L)>0 && index(L)>=0){
		Node pk=L->cursor;
		return(pk->data);		//returns cursor data
	}
	return -1; // Returns cursor element of L. Pre: length()>0, index()>=0
}
void moveFront(List L){
	if(length(L)>0){
		L->cursor = L->front;
		L->index=0;
		//((L->cursor)->data);
	}
	return;
}
int equals(List A, List B){
	if((front(A) == front(B)) && (back(A) == back(B)) && (length(A) == length(B))){
		moveFront(A);
		moveFront(B);
		for(int i = 0; i++; i<length(A)){
			moveNext(A);
			moveNext(B);
			if(get(A) != get(B)){
				return 0;
			}
		}
		return 1;
	}
	return 0;
} // Returns true (1) iff Lists A and B are in same
	 // state, and returns false (0) otherwise.
	// Manipulation procedures ----------------------------------------------------
void clear(List L){

	for(int i =length(L); i<0;i--){
		deleteFront(L);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = NULL;
	return;
} // Resets L to its original empty state.

 // If L is non-empty, sets cursor under the front element,
	 // otherwise does nothing.

void moveBack(List L){
	if(length(L)>0){
		L->cursor = L->back;
		L->index=(length(L)-1);
		//(L->cursor)->data;
	}
	return; // If L is non-empty, sets cursor under the back element,
	 // otherwise does nothing.
}
void movePrev(List L){
	if(L->cursor != NULL && L->cursor != L->front){
		Node temp = L->cursor;
		L->cursor= temp->prev;
		(L->index)--;
		//(L->cursor)->data;
	}
	else if(L->cursor != NULL && L->cursor == L->front){
		L->cursor = NULL;
		L->index=-1;
	}
	return;
} // If cursor is defined and not at front, move cursor one
	 // step toward the front of L; if cursor is defined and at
	 // front, cursor becomes undefined; if cursor is undefined
	 // do nothing
void moveNext(List L){
	if(L->cursor != NULL && L->cursor != L->back){
		Node temp = L->cursor;
		L->cursor = temp->next;
		(L->index)++;
		//(L->cursor)->data;
	}
	else if(L->cursor != NULL && L->cursor == L->back){
		L->cursor = NULL;
		L->index=-1;
	}
	return;
} // If cursor is defined and not at back, move cursor one
	 // step toward the back of L; if cursor is defined and at
	 // back, cursor becomes undefined; if cursor is undefined
	 // do nothing
void prepend(List L, int data){
	Node B = newNode(data);
	if (length(L)==0){
		L->front=B;
		L->back=B;
		L->length=1;
		return;
	}

	if(length(L)>0){
		Node temp = L->front;
		B->next = L->front;
		temp->prev = B;///
		L->front = B;
		(L->length)++;
		return;
	}
	L->front = B;
	L->back = B;
	(L->length)++;
	return;
} // Insert new element into L. If L is non-empty,
	 // insertion takes place before front element.
void append(List L, int data){
	Node B = newNode(data);
	if (length(L)==0){
		L->front=B;
		L->back=B;
		L->length=1;
		return;
	}
	if(length(L)>0){
		Node temp = L->back;
		B->prev = L->back;	
		temp->next = B;
		L->back = B;
		(L->length)++;
		return;
	}
	L->front = B;
	L->back = B;
	(L->length)++;
	return;
} // Insert new element into L. If L is non-empty,
	 // insertion takes place after back element.

void insertBefore(List L, int data){
	if(length(L)>0 && index(L)>=0){
		int i=length(L);
		if(L->cursor==L->front){
			prepend(L,data);
			return;
		}
		Node B = newNode(data);
		Node temp = L->cursor;/////
		Node C=temp->prev;
		B->prev = C;
		temp->prev = B;
		B->next = temp;
		C->next=B;
		(L->length)++;
	
		return;
	}
	return;
} // Insert new element before cursor.
	 // Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(length(L)>0 && index(L)>=0){
		int i=length(L);
		if(L->cursor==L->back){
			append(L,data);
			return;
		}
		Node B = newNode(data);
		Node temp = L->cursor;
		B->next = temp->next;
		temp->next = B;
		B->prev = temp;
		(L->length)++;
	
		return;
	}
} // Insert new element after cursor.
	 // Pre: length()>0, index()>=0
void deleteFront(List L){
	if(length(L)>0){
		if(L->cursor == L->front){
			L->cursor = NULL;
			L->index = NULL;

		}
		Node temp = L->front;
		L->front = temp->next;
		free(temp);
		(L->length)--;
		if(index(L)>= 0){			//if cursor was defined
			L->index = index(L)-1;	//L->index down one (closer to new front)
		}
		return;
	}
	return;
} // Delete the front element. Pre: length()>0

void deleteBack(List L){//need to FIX
	if(length(L)>0){
		if(L->cursor == L->back){
			L->cursor = NULL;
			L->index = NULL;
		}
	
		Node temp = L->back;
		L->back = temp->prev;

		free(temp);
		(L->length)--;
		return;
	}
	return;
} // Delete the back element. Pre: length()>0

void delete(List L){
		
	if(length(L)>0 && index(L)>=0){
		if(length(L)==1){
			L->length=0;
			free(L->front);
			L->index=NULL;
			L->cursor=NULL;
			return;
		}
		if(L->cursor==L->front){
			Node temp=L->front;
			L->front=temp->next;
			(L->length)--;
			free(temp);
			L->index=NULL;
			L->cursor=NULL;
			return;
		}
		if(L->cursor==L->back){
			Node temp=L->back;
			L->back=temp->prev;
			free(temp);
			(L->length)--;
			L->index=NULL;
			L->cursor=NULL;
			return;
		
		}
		Node temp = L->cursor;
		Node beT = temp->prev;
		Node nexTe = temp->next;
		beT->next = nexTe;
		nexTe->prev = beT;
		L->cursor=NULL;
		L->index=NULL;
		


		free(temp);
		(L->length)--;
		

		return;
	}
	return;
} // Delete cursor element, making cursor undefined.
	 // Pre: length()>0, index()>=0
	// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
	//moveFront(L);
	Node B= L->front;
	//for(int i=0;i<length(L)-1;i++){
	while(B!=NULL){
		fprintf(out,"%d ",(B->data));
		B=B->next;
		//moveNext(L);
	}
	return;
} /// Prints to the file pointed to by out, a
	 // string representation of L consisting
	 // of a space separated sequence of integers,
	// with front on left.
List copyList(List L){
	List B = newList();
	Node temp = L->front;
	for(int i=0;i<length(L);i++){
		//printf("%d", temp->data);
		
		append(B,(temp->data));
		
		temp=(temp->next);
	}
	//while(temp!=NULL){
	//	append(B,temp->data);
	//	(B->length)++;
	//	temp=temp->next;
	//}
	return B;
} // Returns a new List representing the same integer
	 // sequence as L. The cursor in the new list is undefined,
	// regardless of the state of the cursor in L. The state
	// of L is unchanged