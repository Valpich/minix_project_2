
#include "project_2_syst_call.h"


#include <signal.h>

#include <sys/resource.h>
#include <sys/utsname.h>

#include <string.h>

#include <assert.h>

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include <sys/wait.h>

#define MAX_MSG 5	/* Number of message for each topic */
#define MAX_TOPIC 10	/* Number of allowed topics for each topic */
#define MAX_USR 30	/* Number of allowed user */
typedef int semaphore;	/* Define semaphore as a type */
static semaphore mutex[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 1};	/* Controls access to critical region */
static semaphore empty[MAX_TOPIC] = {[0 ... MAX_TOPIC-1] = MAX_MSG};	/* Count empty buffer slots */
static semaphore full[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 0};		/* Count full buffer slots */

typedef struct UserTopic{
    int id; /* Topic id */
    char * name;    /* Topic name */
    char * messageContent[MAX_MSG]; /* Message content of a Topic */
    bool read[MAX_MSG]; /* If the message was read */
    void (*toString)(const struct UserTopic *); /* Pointer to the display function of a UserTopic*/
}UserTopic;

typedef struct Subscriber{
    pid_t pid_subscriber;   /* Subscriber pid_t */
    struct UserTopic topic[MAX_TOPIC];   /* Topics subscribed */
    void (*toString)(const struct Subscriber *); /* Pointer to the display function of a Subscriber */
}Subscriber;

static int messageOfTopicToRead[MAX_TOPIC][MAX_MSG] = {[0 ... MAX_TOPIC-1] = 0, [0 ... MAX_MSG-1] = 0};   /* Count the topics that  subscribed */
static struct Subscriber subscribers[MAX_USR];
static int  topicsSize = 0;
static int  subscriberSize = 0;
static char * topicNames[MAX_TOPIC];


/********* BEGIN OF TO STRING FUNCTIONS **********/

void toStringUserTopic(const UserTopic * userTopic){
    if(userTopic != NULL){
        printf("UserTopic is:\nid: %d, name: %s, messageContent: ", userTopic->id, &userTopic->name);
        int i = 0;
        for(i = 0; i<MAX_MSG ;i++){
            printf("%s, ", &userTopic->messageContent[i]);
        }
        printf(" read: ");
        for(i = 0; i<MAX_MSG ;i++){
            printf("%d", userTopic->read[i]);
            if(i<MAX_MSG-1){
                printf(",");
            }
        }
        printf(".\n");
    }else{
        printf("UserTopic is NULL.\n");
    }
}

void toStringSubscriber(const Subscriber * subscriber){
    if(subscriber != NULL){
        printf("Subscriber is:\npid: %d, ", subscriber->pid_subscriber);
        if(subscriber->toString != NULL){
            subscriber->toString(subscriber->topic);
        }
        printf(".\n");
    }else{
        printf("UserTopic is NULL.\n");
    }
}

/********* END OF TO STRING FUNCTIONS **********/

void down(semaphore * s){
    printf("s in down is %d\n", *s);
    while(*s == 0)sleep(1);
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
    char *name = NULL;
    // strcpy(name,m_in.m3_ca1);
    printf("received value : %s \n",name);
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


/**
 * @Precondition Is into a critical region
 */
bool create_topic(const char * name){
    printf("Topic creation \n");
    if(topicsSize < MAX_TOPIC){
        int i = 0;
        for(i=0; i< MAX_TOPIC; i++) {
            if(strcmp("\0",&topicNames[i]) == 0){
                printf("Empty find at %d\n", i);
                printf("Entering create topic lock with empty %d", empty[i]);
                down(&empty[i]);
                enter_critical_region_topic(i);
                printf("Setting name \n");
                strcpy(&topicNames[i],name);
                printf("Topic name is %s\n",&topicNames[i]);
                topicsSize++;
                printf("Topic size is %d\n",topicsSize);
                printf("Topic created \n");
                leave_critical_region_topic(i);
                up(&full[i]);
                printf("Leaving publish lock with full %d", full[i]);
                return true;
            }
        }
        return true;
    }else{
        printf("Topic size is %d, max amount reached\n",topicsSize);
        printf("Topic %s not created \n", name);
        return false;
    }
}

/**
 * @Precondition Is into a critical region
 */
bool delete_topic(const char * name){
    printf("Topic deletion \n");
    int i = 0;
    for(i=0; i< MAX_TOPIC; i++) {
        if(strcmp(name,&topicNames[i]) == 0){
            printf("Topic find at %d\n", i);
            printf("Entering publish lock with full %d", full[i]);
            down(&full[i]);
            enter_critical_region_topic(i);
            strcpy(&topicNames[i], "\0");
            topicsSize--;
            printf("Topic deleted \n");
            leave_critical_region_topic(i);
            up(&empty[i]);
            printf("Leaving publish lock with empty %d", empty[i]);
            
            return true;
        }
    }
    printf("Topic size is %d, max amount reached\n",topicsSize);
    printf("Unable to delete topic %s n\n", name);
    return false;
}

/**
 * @Precondition Is into a critical region
 */
void create_new_user_topic(const int id, const char * name){
    printf("UserTopic creation\n");
    UserTopic userTopic;
    printf("Setting userTopicToString method\n");
    userTopic.toString = toStringUserTopic;
    printf("Setting id \n");
    userTopic.id = id;
    printf("Setting user topic name \n");
    strcpy(&userTopic.name,name);
    printf("Setting messages to \0 in user topic\n");
    int i = 0;
    for(i = 0; i<MAX_MSG ;i++){
        strcpy(&userTopic.messageContent[i],"\0");
    }
    printf("Setting messages read to true in user topic\n");
    for(i = 0; i<MAX_MSG ;i++){
        userTopic.read[i] = true;
    }
    printf("Printing user topic\n");
    userTopic.toString(&userTopic);
    printf("UserTopic created\n");
}

/**
 * @Precondition Is into a critical region
 */
void publish_into_user_topic(const UserTopic * userTopic, const char * msg, const int msgLocation){
    printf("Publishing into a user topic\n");
    strcpy(userTopic->messageContent[msgLocation],msg);
    //    userTopic->read[msgLocation] = false;
    printf("UserTopic created\n");
}
