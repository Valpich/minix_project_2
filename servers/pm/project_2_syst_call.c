
#include"project_2_syst_call.h"

#define MAX_MSG 5	/* Number of message for each topic */
#define MAX_TOPIC 10	/* Number of allowed topics for each topic */
typedef int semaphore;	/* Define semaphore as a type */
static semaphore mutex[MAX_TOPIC]  = {1};	/* Controls access to critical region */
static semaphore empty[MAX_TOPIC] = {MAX_MSG};	/* Count empty buffer slots */
static semaphore full[MAX_TOPIC]  = {0};		/* Count full buffer slots */


void down(semaphore * s){
    while(s == 0)wait();
    s = s - 1;
}

void up(semaphore * s){
    s = s + 1;
}

void enter_critical_region(int topic_id){
    down(&mutex[topic_id]);
}

void leave_critical_region(int topic_id){
    up(&mutex[topic_id]);
}

void publish_lock(int topic_id){
    down(&empty[topic_id]);
    enter_critical_region(topic_id);
    // TODO: Publish the topic
    leave_critical_region(topic_id);
    up(&full[topic_id]);
}

void unpublish_lock(int topic_id){
    down(&full[topic_id]);
    enter_critical_region(topic_id);
    // TODO: Remove the published topic
    leave_critical_region(topic_id);
    up(&empty[topic_id]);
}

int do_topic_lookup(void){
    return 1;
}

int do_topic_create(void){
    return 2;
}

int do_topic_publisher(void){
    return 3;
}

int do_topic_subscriber(void){
    return 4;
}

int do_topic_publish(void){
    return 5;
}

int do_retrieve(void){
    return 6;
}
