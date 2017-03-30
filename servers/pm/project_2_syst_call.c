
#include "project_2_syst_call.h"


#include <signal.h>

#include <sys/resource.h>
#include <sys/utsname.h>

#include <string.h>
#include <stdlib.h>

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
    void (*toString)(const struct Subscriber *);    /* Pointer to the display function of a Subscriber */
}Subscriber;

typedef struct Publisher{
    pid_t pid_publisher;   /* Publisher pid_t */
    char * topicNames[MAX_TOPIC];   /* Topics declared as published */
    void (*toString)(const struct Publisher *);    /* Pointer to the display function of a Publisher */
}Publisher;

typedef struct Topics{
    char * topicNames[MAX_TOPIC];    /* List of all topics */
    bool canBeRemoved[MAX_TOPIC];    /* If a topic can be removed */
    void (*toString)(const struct Topics *);  /* Pointer to the display function of a Topics */
}Topics;

static int messageOfTopicToRead[MAX_TOPIC][MAX_MSG] = {[0 ... MAX_TOPIC-1] = 0, [0 ... MAX_MSG-1] = 0};   /* Count the topics that  subscribed */
static struct Subscriber subscribers[MAX_USR];
static int  topicsSize = 0;
static int  subscriberSize = 0;

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

void toStringPublisher(const Publisher * publisher){
    if(publisher != NULL){
        printf("Publisher is:\npid: %d, ", publisher->pid_publisher);
        int i = 0;
        printf(" topics subscribed names: ");
        for(i = 0; i<MAX_TOPIC ;i++){
            printf("%s, ", &publisher->topicNames[i]);
        }
        printf(".\n");
    }else{
        printf("Publisher is NULL.\n");
    }
}

void toStringTopics(const Topics * topic){
    if(topic != NULL){
        int i =0 ;
        for(i = 0; i<MAX_TOPIC ;i++){
            printf("Topic %d : name is %s, can be removed is %d.\n", i, topic->topicNames[i], topic->canBeRemoved[i]);
        }
    }else{
        printf(" Topics is NULL.\n");
    }
}

/********* END OF TO STRING FUNCTIONS **********/


static Topics topics = {{[0 ... MAX_TOPIC-1] = "\0"}, {[0 ... MAX_TOPIC-1] =1}, .toString=toStringTopics};


void down(semaphore * s){
    printf("s in down is %d.\n", *s);
    while(*s == 0)sleep(1);
    *s = *s - 1;
}

void up(semaphore * s){
    printf("s in up is %d.\n", *s);
    *s = *s + 1;
}

void enter_critical_region_topic(int topic_id){
    printf("Entering critical region.\n");
    down(&mutex[topic_id]);
}

void leave_critical_region_topic(int topic_id){
    printf("Leaving critical region.\n");
    up(&mutex[topic_id]);
}

int do_topic_lookup(void){
    if(topics != NULL){
        int i = 0;
        for(i= 0; i< MAX_TOPIC;i++){
            printf("Topic #%d : %s\n",i,topics->topicNames[i]);
        }
    }
    else {
        printf("Topics is null\n");
    }
    return 1;
}

int do_topic_create(void){
    printf("coucou\n");

    // create_topic(name);

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
    topics.toString(&topics);
    if(topicsSize < MAX_TOPIC){
        int i = 0;
        for(i=0; i< MAX_TOPIC; i++) {
            if(strcmp(name, topics.topicNames[i]) == 0) {
                printf("Topic %s is already in list\n", name);
                return false;
            }else if(strcmp("\0",topics.topicNames[i]) == 0){
                printf("Empty find at %d\n", i);
                enter_critical_region_topic(i);
                printf("Setting name\n");
                char *a = malloc(sizeof(name));
                strcpy(a,name);
                topics.topicNames[i] = a;
                printf("Topic name is %s\n",topics.topicNames[i]);
                topicsSize++;
                printf("Topic size is %d\n",topicsSize);
                printf("Topic created \n");
                leave_critical_region_topic(i);
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
        if(strcmp(name,topics.topicNames[i]) == 0){
            printf("Topic find at %d.\n", i);
            enter_critical_region_topic(i);
            char * toDelete = topics.topicNames[i];
            free(toDelete);
            char *a = malloc(sizeof("\0"));
            strcpy(a,"\0");
            topics.topicNames[i] = a;
            topicsSize--;
            printf("Topic deleted.\n");
            leave_critical_region_topic(i);
            return true;
        }
    }
    printf("Topic size is %d, max amount reached\n",topicsSize);
    printf("Unable to delete topic %s.\n", name);
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
