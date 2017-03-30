
#ifndef PROJECT_2_SYST_CALL_H
#define PROJECT_2_SYST_CALL_H

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

#define MAX_MSG 5   /* Number of message for each topic */
#define MAX_TOPIC 10    /* Number of allowed topics for each topic */
#define MAX_USR 30  /* Number of allowed user */
#define TOPIC_NOT_FOUND -2
#define NOT_SLOT_AVAILABLE -3

typedef int semaphore;  /* Define semaphore as a type */

typedef enum {false = 0, true = 1} bool;

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

typedef struct Topic{
    int id; /* Topic id */
    char * name;    /* List of all topics */
    bool msgSlotAvailable[MAX_MSG];    /* If a message can be removed */
    void (*toString)(const struct Topic *);  /* Pointer to the display function of a Topic */
}Topic;

typedef struct Topics{
    Topic topicArray[MAX_TOPIC];    /* List of all topics */
    bool canBeRemoved[MAX_TOPIC];    /* If a topic can be removed */
    void (*toString)(const struct Topics *);  /* Pointer to the display function of a Topics */
}Topics;

void toStringUserTopic(const UserTopic * userTopic);

void toStringSubscriber(const Subscriber * subscriber);

void toStringPublisher(const Publisher * publisher);

void toStringTopic(const Topic * topic);

void toStringTopics(const Topics * topic);

int do_topic_lookup(void);

int do_topic_create(void);

int do_topic_publisher(void);

int do_topic_subscriber(void);

int do_topic_publish(void);

int do_retrieve(void);

bool create_topic(const char * name);

void create_new_user_topic(const int id, const char * name);

bool delete_topic(const char * name);

Topic * findTopicByName(const char * name);

void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation);

int publish_into_all_user_topic(const char * topicName, const char * msg, const int msgLocation);

int findAndLockAvailableSlot(Topic * topic);

#endif /** PROJECT_2_SYST_CALL_H */
