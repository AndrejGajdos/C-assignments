/*
   ============================================================================
   Name        : priority_queue.c
   Author      : 359234
   Copyright   : 359234@mail.muni.cz
   Description : Queue logic
   ============================================================================
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "priority_queue.h"



priority_queue create()  {

        priority_queue queue = {NULL, NULL, 0};

        return queue;

}


void push(priority_queue* queue, value_type value, uint remaining_time) {

        priority_queue_item* node;
        node = malloc(sizeof(priority_queue_item));
        memset(node, 0, sizeof(priority_queue_item));


        node->value = value;
        node->remaining_time = remaining_time;
        node->next = NULL;
        node->previous = NULL;


        if (queue->size == 0)
        {
                queue->first = node;
                queue->last = node;
        }


        else
        {

                priority_queue_item* item = queue->first;


                while (item != NULL) {

                        if (node->remaining_time <= item->remaining_time)
                        {
                                node->previous = item;
                                item->next = node;
                                queue->first = node;
                                break;
                        }

                        if ((node->remaining_time >= item->remaining_time) && (item == queue->last))
                        {
                                node->next = item;
                                item->previous = node;
                                queue->last = node;
                                break;
                        }

                        if  ((node->remaining_time >= item->remaining_time) && (node->remaining_time <= item->previous->remaining_time))
                        {
                                node->previous = item->previous;
                                node->next = item;
                                item->previous->next = node;
                                item->previous = node;
                                break;
                        }

                        item = item->previous;
                }

        }

        queue->size++;
}

void pop_top(priority_queue* queue){

        if (queue->size > 0) {
                priority_queue_item* firstItem = queue->first;

                if (queue->size == 1) {
                        queue->first = NULL;
                        queue->last = NULL;
                } else {
                        queue->first = queue->first->previous;
                        queue->first->next = NULL;
                }

                memset(firstItem, 0, sizeof(priority_queue_item));
                free(firstItem);
                queue->size--;
        }
}

uint top_priority(priority_queue const* queue) {

        if(queue->size > 0)
                return queue->first->remaining_time;
        else
                return 0;
}

value_type* top_value(priority_queue const* queue){

        if(queue->size > 0)
                return &(queue->first->value);
        else
                return NULL;
}

uint run_top(priority_queue* queue, uint run_time) {

        if(queue->size > 0)
        {
                queue->first->value();

                if(queue->first->remaining_time <= run_time)
                {
                        pop_top(queue);
                        return 0;
                }
                else {
                        queue->first->remaining_time -= run_time;
                        return queue->first->remaining_time;
                }

        }
        else
                return 0;

}

void clear(priority_queue* queue) {

        if(queue->size > 0)
                while (queue->size > 0)
                        pop_top(queue);
}

priority_queue copy(priority_queue const* q1) {

        priority_queue copyQueue = create();

        if (q1->size > 0)
        {
                priority_queue_item* uzolFronty = q1->first;

                while(uzolFronty != NULL) {
                        push(&copyQueue,uzolFronty->value,uzolFronty->remaining_time);
                        uzolFronty = uzolFronty->previous;
                }
        }
        return copyQueue;
}
