
#ifndef PROJECT_2_SYST_CALL_H
#define PROJECT_2_SYST_CALL_H

#include <sys/resource.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define MINIX 0
#include "pm.h"
#include "mproc.h"
#include "param.h"
#include <sys/svrctl.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/sysinfo.h>
#include <minix/type.h>
#include <minix/vm.h>
#include <machine/archtypes.h>
#include <lib.h>
#ifdef  MINIX

#endif
#define MAX_MSG 5   /* Number of message for each topic */
#define MAX_TOPIC 10    /* Number of allowed topics for each topic */
#define MAX_USR 30  /* Number of allowed user */
#define MAX_TOPIC_NAME 20
#define MAX_MSG_CONTENT 100

#define INVALID_POSITION -1
#define INVALID_PID -1
#define INVALID_ID -1
#define TOPIC_NOT_FOUND -2
#define NO_SLOT_AVAILABLE -3
#define USR_NOT_REGISTRED_AS_PUBLISHER -4
#define MSG_NOT_PUBLISHED_SLOTS_FULL -5
#define NOT_ENOUGH_SPACE_IN_PUBLISHER_SLOTS -6
#define INVALID_TOPIC_NAME -7
#define ALREADY_REGISTRED -8
#define FAIL_TO_REGISTER -9

#define NEW_REGISTRATION 100
#define PUBLISHER_REGISTRED 101
#define MSG_PUBLISHED 102

#define DO_TOPIC_LOOKUP_SUCCESS_RETURN 200
#define DO_TOPIC_CREATE_SUCCESS_RETURN 201
#define DO_TOPIC_CREATE_FAILURE_RETURN -201
#define DO_TOPIC_PUBLISHER_FAILURE_RETURN -202
#define DO_TOPIC_SUBSCRIBER_SUCCESS_RETURN 203
#define DO_TOPIC_SUBSCRIBER_FAILURE_RETURN -203
#define DO_RETRIEVE_SUCCESS_RETURN 204
#define DO_RETRIEVE_FAILURE_RETURN -204
#define DO_PRINT_SUBSCRIBERS_SUCCESS_RETURN 205
#define DO_PRINT_PUBLISHERS_SUCCESS_RETURN 206
#define DO_TOPIC_DELETE_SUCCESS_RETURN 207
#define DO_TOPIC_DELETE_FAILURE_RETURN -207

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
    struct UserTopic userTopic[MAX_TOPIC];   /* Topics subscribed */
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
    bool canBeRemoved[MAX_TOPIC];    /* If a Topic can be removed */
    void (*toString)(const struct Topics *);  /* Pointer to the display function of a Topics */
}Topics;

/********* BEGIN OF TO STRING FUNCTIONS **********/

void toStringUserTopic(const UserTopic * userTopic);

void toStringSubscriber(const Subscriber * subscriber);

void toStringPublisher(const Publisher * publisher);

void toStringTopic(const Topic * topic);

void toStringTopics(const Topics * topic);

void toStringAllPublisher(const Publisher publisher[]);

void toStringAllSubscriber(const Subscriber subscriber[]);

/********* END OF TO STRING FUNCTIONS **********/

/********* BEGIN OF SEMAPHORE METHODS **********/

void down(semaphore * s);

void up(semaphore * s);

void enter_critical_region_topic(int topic_id);

void leave_critical_region_topic(int topic_id);

void checkNotDown(semaphore * s);

void wait_read_critical_region_topic(int topic_id);

/********* END OF SEMAPHORE METHODS **********/

/********* BEGIN OF SYSTEM CALL METHODS **********/

int do_topic_lookup(void);

int do_topic_create(void);

int do_topic_publisher(void);

int do_topic_subscriber(void);

int do_topic_publish(void);

int do_retrieve(void);

/********* END OF SYSTEM CALL METHODS **********/

/********* BEGIN OF INTERNAL METHODS **********/

/********* BEGIN OF UTILITY METHODS **********/

int doInit();

Topic * findTopicByName(const char * user_pid);

Subscriber * findSubscriberByPid(const pid_t user_pid);

Publisher * findPublisherById(pid_t user_pid);

int findUserTopicPosition(const Subscriber * subscriber, const Topic * topic);

int findAndLockAvailableSlot(Topic * topic);

bool checkAllRetrieved(const Topic * topic, const int slot);

bool userIsRegistredAsPublisher(const char * topicName, const Publisher * publisher);

int is_ID_set(const char * name, pid_t user_pid);

int subscribers_init(const char * name, pid_t user_pid);

/********* END OF UTILITY METHODS **********/

/********* BEGIN OF CORE METHODS **********/

void lookup();

bool create_topic(const char * name);

int topic_publisher(const char * name, pid_t user_pid);

bool subscribe_to_topic(const char * name, pid_t user_pid);

void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation);

int publish_into_all_user_topic(Topic * topic, const char * msg);

int publish_msg_into_topic(const char * topicName, const char * msg, const Publisher * publisher);

char * retrieve_msg_of_topic(const pid_t user_pid, const char * topicName);

char * readMessage(UserTopic *userTopic);

bool delete_topic(const char * name);

void printAllPublishers();

void printAllSubscribers();

/********* END OF CORE METHODS **********/

/********* END OF INTERNAL METHODS **********/

/********* BEGIN OF DEBUG METHODS **********/

void toStringData();

/********* END OF DEBUG METHODS **********/

#endif /** PROJECT_2_SYST_CALL_H */