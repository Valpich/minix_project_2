
#include "project_2_syst_call.h"

#include "pm.h"
#include <minix/callnr.h>
#include <signal.h>
#include <sys/svrctl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/sysinfo.h>
#include <minix/type.h>
#include <minix/vm.h>
#include <string.h>
#include <machine/archtypes.h>
#include <lib.h>
#include <assert.h>
#include "mproc.h"
#include "param.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <lib.h>
#include <malloc.h>

#define MAX_MSG 5	/* Number of message for each topic */
#define MAX_TOPIC 10	/* Number of allowed topics for each topic */
typedef int semaphore;	/* Define semaphore as a type */
static semaphore mutex[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 1};	/* Controls access to critical region */
static semaphore empty[MAX_TOPIC] = {[0 ... MAX_TOPIC-1] = MAX_MSG};	/* Count empty buffer slots */
static semaphore full[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 0};		/* Count full buffer slots */


void down(semaphore * s){
    printf("s in down is %d\n", *s);
    while(*s == 0)wait();
    *s = *s - 1;
}

void up(semaphore * s){
    printf("s in up is %d\n", *s);
    *s = *s + 1;
}

void enter_critical_region(int topic_id){
    printf("Entering critical region");
    down(&mutex[topic_id]);
}

void leave_critical_region(int topic_id){
    printf("Leaving critical region");
    up(&mutex[topic_id]);
}

void publish_lock(int topic_id){
    printf("Entering publish lock with empty %d", empty[topic_id]);
    down(&empty[topic_id]);
    enter_critical_region(topic_id);
    // TODO: Add the published topic
    leave_critical_region(topic_id);
    up(&full[topic_id]);
    printf("Leaving publish lock with full %d", full[topic_id]);
}

void unpublish_lock(int topic_id){
    printf("Entering publish lock with full %d", full[topic_id]);
    down(&full[topic_id]);
    enter_critical_region(topic_id);
    // TODO: Remove the published topic
    leave_critical_region(topic_id);
    up(&empty[topic_id]);
    printf("Leaving publish lock with empty %d", empty[topic_id]);
}

int do_topic_lookup(void){
    return 1;
}

int do_topic_create(void){
    printf("coucou\n");
    //char name[3];
    //strcpy(name,m_in.m3_ca1);
    //printf("received value : %s \n",name);
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
