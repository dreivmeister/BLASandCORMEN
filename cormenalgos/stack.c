#include <stdio.h>
#include <stdlib.h>


// define the structures
typedef struct stackNode{
	void* data;
	struct stackNode* prevNode;
}stackNode;

typedef struct Stack{
	stackNode* top;
	int numOfNodes;
} Stack;


// constructors
Stack* createStack(){
	Stack* tempStack = malloc(sizeof(Stack));
	tempStack->numOfNodes = 0;
	tempStack->top = NULL;
	return tempStack;
}
stackNode* createstackNode(void* data){
	stackNode* node = malloc(sizeof(stackNode));
	node->data = data;
	node->prevNode = NULL;
	return node;
}



// insert new node with data as value
int StackPush(Stack* stack, void* data){
	stackNode* newNode = createstackNode(data);
	if(stack->top==NULL) {
		stack->top = newNode;
    }else {
        newNode->prevNode = stack->top;
		stack->top = newNode;
	}
	stack->numOfNodes++;
	return 0;
}

// delete top node and return its value
void* StackPop(Stack* stack){
    stackNode* tempNode = stack->top;
	if(stack->top==NULL) {
		return NULL;
	}else {
		stack->top = tempNode->prevNode;
	}
	stack->numOfNodes--;
	void* data = tempNode->data;
	free(tempNode);
	return data;
}


// check if stack is empty
int emptyStack(Stack* stack){
	return (stack->numOfNodes == 0 ? 1:0);
}


// free node memory and stack memory
int deleteStack(Stack* stack){
	stackNode* tempNode = stack->top,*rmNode;
	while(tempNode!=NULL){
		rmNode = tempNode;
		tempNode = tempNode->prevNode;
		free(rmNode);
	}
	free(stack);
	return 0;
}

// print stack
int printStack(Stack* stack){
	stackNode* tempNode = stack->top;
	while(tempNode!=NULL){
		printf("%d ", *(int*)tempNode->data);
		tempNode = tempNode->prevNode;
	}
    printf("\n");
	return 0;
}


int main(){
    Stack* s = createStack();

    int *p = &(int){42};

    int i = 40;
    int *p1 = &i;

    StackPush(s, p);
    StackPush(s, p1);
    printStack(s);
    StackPop(s);
    printStack(s);

}