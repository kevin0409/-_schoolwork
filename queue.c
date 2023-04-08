#include <stdio.h>
#include <stdlib.h>

#define  _CRT_SECURE_NO_WARNINGS

typedef struct priority_queue *queue_pointer;

struct priority_queue {
    int id;
    int priority;
    int computing_time;
    queue_pointer left_link, right_link;
};

typedef struct queue_head *head_pointer;

struct queue_head {
    queue_pointer front, rear;
};

#define NUM_QUEUES 3  // 큐의 개수를 상수로 정의
head_pointer queues[NUM_QUEUES];

void initialize_queue(void);
void insert_queue(int priority, int computing_time);
int delete_queue(int priority);
void print_queue(head_pointer q);

int main() {
    int type, priority, computing_time;
    initialize_queue();

    FILE *input_file = fopen("input_file.txt", "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        exit(1);
    }

    while (fscanf(input_file, "%d %d %d", &type, &priority, &computing_time) == 3) {
        if (type == -1) {
            break;
        }
        if (type == 0) {
            insert_queue(priority, computing_time);
        } 
        else if (type == 1) {
            delete_queue(priority);
        }
    }

    printf("ID\tPriority\tComp. Time\n");
    for(int i = 0; i < NUM_QUEUES; i++){
        print_queue(queues[i]);
    }

    fclose(input_file);

    return 0;
}

void initialize_queue() {
    int i;
    for (i = 0; i < NUM_QUEUES; i++) {
        queues[i] = (head_pointer)malloc(sizeof(struct queue_head));
        queues[i]->front = queues[i]->rear = NULL;
    }
}

void insert_queue(int priority, int computing_time) {
    queue_pointer temp = (queue_pointer)malloc(sizeof(struct priority_queue));
    temp->priority = priority;
    temp->computing_time = computing_time;
    temp->left_link = temp->right_link = NULL;

    head_pointer q = NULL;
    if (priority >= 1 && priority <= 10) {
        q = queues[0];
        temp -> id = 1;
    } 
    else if (priority >= 11 && priority <= 20) {
        q = queues[1];
        temp -> id = 2;
    } 
    else if (priority >= 21 && priority <= 30) {
        q = queues[2];
        temp -> id = 3;
    }

    if (q->front == NULL) {
        q->front = q->rear = temp;
    } 
    else {
        queue_pointer p = q->front;
        //queue_pointer trail = NULL;
        queue_pointer trail = q->front->left_link;
        if (p == NULL) {
            trail->right_link = temp;
            temp->left_link = trail;
            q->rear = temp;
        } 
        else if (trail == NULL) {
            temp->right_link = q->front;
            q->front->left_link = temp;
            q->front = temp;
        } 
        else {
            trail->right_link = temp;
            temp->left_link = trail;
            temp->right_link = p;
            p->left_link = temp;
        }
    }
}

int delete_queue(int priority) {
    queue_pointer node;
    int queue_id;

    if (priority < 1 || priority > 30) {
        printf("Error: Invalid priority value.\n");
        return -1;
    }

    if (priority >= 1 && priority <= 10) {
        queue_id = 0;
    }
    else if (priority >= 11 && priority <= 20) {
        queue_id = 1;
    }
    else {
        queue_id = 2;
    }

    if (queues[queue_id]->front == NULL) return 0;
    if (queues[queue_id]->front->priority > priority) return 0;


    node = queues[queue_id]->front;

    if (node->right_link == NULL) {
        queues[queue_id]->front = NULL;   
    }
    else {
        queues[queue_id]->front = node->right_link;
        //node->right_link->left_link = queues[queue_id];
    }

    //printf("%d\t\t%d\t\t%d\n",queue_id+1, node->priority, node->computing_time);

    free(node);

    return 0;
}

void print_queue(head_pointer q) {
    
    queue_pointer p = q->front;
    while (p != NULL) {
        printf("%d\t%d\t\t%d\n", p->id, p->priority, p->computing_time);
        p = p->right_link;
    }
    //printf("\n");
}