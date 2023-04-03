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
void delete_queue(void);
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
        } else if (type == 1) {
            delete_queue();
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
        queue_pointer trail = NULL;
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

void delete_queue() {
    head_pointer q = NULL;
    int i;
    for (i = 0; i < 3; i++) {
        if (queues[i]->front != NULL) {
            q = queues[i];
            break;
        }
    }
    if (q == NULL) {
        printf("Queue is empty.\n");
        return; 
    }

    queue_pointer p = q->front;
    queue_pointer max = p;
    while (p != NULL) {
        if (p->priority > max->priority) {
            max = p;
        }
        p = p->right_link;
    }

    if (max == q->front) {
        q->front = max->right_link;
        if (q->front != NULL) {
            q->front->left_link = NULL;
        }
    } else if (max == q->rear) {
        q->rear = max->left_link;
        if (q->rear != NULL) {
            q->rear->right_link = NULL;
        }
    } else {
        max->left_link->right_link = max->right_link;
        max->right_link->left_link = max->left_link;
    }
    free(max);
}

void print_queue(head_pointer q) {
    queue_pointer p = q->front;
    while (p != NULL) {
        printf("%d\t%d\t\t%d\n", p->id, p->priority, p->computing_time);
        p = p->right_link;
    }
    printf("\n");
}