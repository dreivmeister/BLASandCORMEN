#include <stdio.h>
#include <stdlib.h>


// define the structures
typedef struct queueNode{
	void* data;
	struct queueNode* nextNode;
	struct queueNode* prevNode;
}queueNode;

typedef struct Queue{
	queueNode* firstNode;
	queueNode* lastNode;
	int numOfNodes;
} Queue;


// constructors
Queue* createQueue(){
	Queue* tempQueue = malloc(sizeof(Queue));
	tempQueue->numOfNodes = 0;
	tempQueue->firstNode = NULL;
	tempQueue->lastNode = NULL;

	return tempQueue;
}
queueNode* createqueueNode(void* data){
	queueNode* node = malloc(sizeof(queueNode));
	node->data = data;
	node->nextNode = NULL;
	node->prevNode = NULL;
	return node;
}


// insert new node with data as value
int QueuePush(Queue* queue, void* data){
	queueNode* newNode = createqueueNode(data);

	if(queue->firstNode==NULL) {
		queue->firstNode = newNode;
		queue->lastNode = newNode;
    }else {
		queue->lastNode->nextNode = newNode;
		newNode->prevNode = queue->lastNode;
		queue->lastNode = newNode;
	}
	queue->numOfNodes++;

	return 0;
}
// delete top node and return its value
void* QueuePop(Queue* queue){
	queueNode * tempNode = queue->firstNode;

	if(queue->firstNode==NULL) {
		return NULL;
	}else {
		queueNode * tempNode = queue->firstNode;
		queue->firstNode = tempNode->nextNode;
		if(queue->firstNode != NULL)
			queue->firstNode->prevNode = NULL;
	}

	queue->numOfNodes--;
	void * data = tempNode->data;
	free(tempNode);

	return data;
}


// check if queue is empty
int emptyQueue(Queue* queue){
	return (queue->numOfNodes == 0 ? 1:0);
}
// free node memory and queue memory
int deleteQueue(Queue* queue){
	queueNode* tempNode = queue->firstNode,*rmNode;
	while(tempNode!=NULL){
		rmNode = tempNode;
		tempNode = tempNode->nextNode;
		free(rmNode);
	}
	free(queue);

	return 0;
}

// print queue
int printQueue(Queue* queue){
	queueNode* tempNode = queue->firstNode;
	while(tempNode!=NULL){
		printf("%d ", *(int*)tempNode->data);
		tempNode = tempNode->nextNode;
	}
	return 0;
}


int main(){
    Queue* q = createQueue();

    int *p = &(int){42};

    int i = 40;
    int *p1 = &i;

    QueuePush(q, p);
    QueuePush(q, p1);


    printQueue(q);
}