#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define BUFFER_SIZE 10 // Buffer size
#define NUM_ITEMS 30 // total number of producing and consuming

char buffer[BUFFER_SIZE]; //Buffer
int i_in = 0, i_out = 0; //Two buffer indexes for producer/consumer
int num_items = 0; //how many items in the buffer
int empty = 1, full = 0; //buffer is empty and not full at beginning
int i =0, j=0; //track any producer or consumer action
//producer code
void put(char ch) {
buffer[i_in] = ch; // put character in circular buffer
i_in = (i_in + 1) % BUFFER_SIZE; // incr. producer inde//keep track of number of items in buffer
num_items++; // # of items in buffer
if(num_items == 1) empty = 0; // buffer is not empty anymore
if(num_items==BUFFER_SIZE) full = 1; // buffer is now full
}
void produce(int tid) {
int need_new_item = 1; //need to generate new item
while (i < NUM_ITEMS) {
char ch;
if(need_new_item) {ch = 'A' + rand()%26; need_new_item=0;}
#pragma omp critical
if (!full) {
put(ch);
printf("T%d:Produced %c\t\tnow is %s\n",tid,ch,full?"Full":"Not full");
i++; // only increment if item added
need_new_item =1; // after putting an item, need the next item
}}}
char get() {
char ch = buffer[i_out]; // read item from circular buffer
i_out = (i_out + 1) % BUFFER_SIZE; // incr. consumer index
//keep track of number of items in buffer
num_items--; // decr. # of items
if (num_items == BUFFER_SIZE-1) full = 0; // buffer is not full anymore
if (num_items == 0) empty = 1; // buffer is now empty
return ch;
}
void consume(int tid) {
char ch;
while (j < NUM_ITEMS) {
#pragma omp critical
if (!empty) {
ch = get();
printf("T%d:Consumed %c\t\tnow is %s\n",tid,ch,empty?"Empty":"Not empty");
j++;
}
}}
int main(){
    #pragma omp parallel for num_threads(2) schedule(static)
    for(int i=0; i<5; i++){
        printf("T%d gets iteration %d \n", omp_get_thread_num(), i);
    }

}