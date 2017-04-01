
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
#define MAX_MSG 5                                       /* Number of message for each topic */
#define MAX_TOPIC 3                                    /* Number of allowed topics for each topic */
#define MAX_USR 30                                      /* Number of allowed user */
#define MAX_TOPIC_NAME 20                               /* Number of characters allowed for topic name */
#define MAX_MSG_CONTENT 100                             /* Number of characters allowed for topic content */

#define INVALID_POSITION -1                             /* Constant declaration for Invalid Position code return */
#define INVALID_PID -1                                  /* Constant declaration for Invalid Pid code return */
#define INVALID_ID -1                                   /* Constant declaration for Invalid Id code return */
#define TOPIC_NOT_FOUND -2                              /* Constant declaration for Topic Not Found code return */
#define NO_SLOT_AVAILABLE -3                            /* Constant declaration for No Slot Available code return */
#define USR_NOT_REGISTRED_AS_PUBLISHER -4               /* Constant declaration for User Not Registred As Publisher code return */
#define MSG_NOT_PUBLISHED_SLOTS_FULL -5                 /* Constant declaration for Message Not Published because Slots are Full code return */
#define NOT_ENOUGH_SPACE_IN_PUBLISHER_SLOTS -6          /* Constant declaration for Not Enough Space In Publisher Slots code return */
#define INVALID_TOPIC_NAME -7                           /* Constant declaration for Invalid Topin Name code return */
#define ALREADY_REGISTRED -8                            /* Constant declaration for Already Registred code return */
#define FAIL_TO_REGISTER -9                             /* Constant declaration for Fail To Register code return */

#define NEW_REGISTRATION 100                            /* Constant declaration for New Registration code return */
#define PUBLISHER_REGISTRED 101                         /* Constant declaration for Publisher Registred code return */
#define MSG_PUBLISHED 102                               /* Constant declaration for Message Published code return */

#define DO_TOPIC_LOOKUP_SUCCESS_RETURN 200              /* Constant declaration for Do Topic Lookup Success code return */
#define DO_TOPIC_CREATE_SUCCESS_RETURN 201              /* Constant declaration for Do Topic Create Success code return */
#define DO_TOPIC_CREATE_FAILURE_RETURN -201             /* Constant declaration for Do Topic Create Failure code return */
#define DO_TOPIC_PUBLISHER_FAILURE_RETURN -202          /* Constant declaration for Do Topic Publisher Failure code return */
#define DO_TOPIC_SUBSCRIBER_SUCCESS_RETURN 203          /* Constant declaration for Do Topic Subscriber Success code return */
#define DO_TOPIC_SUBSCRIBER_FAILURE_RETURN -203         /* Constant declaration for Do Topic Subscriber Failure code return */
#define DO_RETRIEVE_SUCCESS_RETURN 204                  /* Constant declaration for Do Topic Retrieve Success code return */
#define DO_RETRIEVE_FAILURE_RETURN -204                 /* Constant declaration for Do Topic Retrieve Failure code return */
#define DO_PRINT_SUBSCRIBERS_SUCCESS_RETURN 205         /* Constant declaration for Do Topic Subscribers Success code return */
#define DO_PRINT_PUBLISHERS_SUCCESS_RETURN 206          /* Constant declaration for Do Topic Publishers Success code return */
#define DO_TOPIC_DELETE_SUCCESS_RETURN 207              /* Constant declaration for Do Topic Delete Success code return */
#define DO_TOPIC_DELETE_FAILURE_RETURN -207             /* Constant declaration for Do Topic Delete Failure code return */

typedef int semaphore;                                  /* Define semaphore as a type */

typedef enum {false = 0, true = 1} bool;                /* Define boolean type bool */

typedef struct UserTopic{                               /* Define UserTopic as a structure */
    int id;                                             /* Topic id */
    char * name;                                        /* Topic name */
    char * messageContent[MAX_MSG];                     /* Message content of a Topic */
    bool read[MAX_MSG];                                 /* Boolean read to know if the message was read */
    void (*toString)(const struct UserTopic *);         /* Pointer to the display function of a UserTopic*/
}UserTopic;

typedef struct Subscriber{                              /* Define Subscriber as a structure */
    pid_t pid_subscriber;                               /* Subscriber pid_t */
    struct UserTopic userTopic[MAX_TOPIC];              /* Topics subscribed */
    void (*toString)(const struct Subscriber *);        /* Pointer to the display function of a Subscriber */
}Subscriber;

typedef struct Publisher{                                /* Define Publisher as a structure */
    pid_t pid_publisher;                                 /* Publisher pid_t */
    char * topicNames[MAX_TOPIC];                        /* Topics declared as published */
    void (*toString)(const struct Publisher *);          /* Pointer to the display function of a Publisher */
}Publisher;

typedef struct Topic{                                    /* Define Topic as a structure */
    int id;                                              /* Topic id */
    char * name;                                         /* List of all topics */
    bool msgSlotAvailable[MAX_MSG];                      /* If a message can be removed */
    void (*toString)(const struct Topic *);              /* Pointer to the display function of a Topic */
}Topic;

typedef struct Topics{                                   /* Define Topics as a structure, that contains structure topic */
    Topic topicArray[MAX_TOPIC];                         /* List of all topics */
    bool canBeRemoved[MAX_TOPIC];                        /* If a Topic can be removed */
    void (*toString)(const struct Topics *);             /* Pointer to the display function of a Topics */
}Topics;

/********* BEGIN OF TO STRING FUNCTIONS **********/

/**
 * @Param: *userTopic, the list of UserTopic
 */
void toStringUserTopic(const UserTopic * userTopic);     /* Display available UserTopic */

/**
 * @Param: *subscriber, the list of Subscriber
 */
void toStringSubscriber(const Subscriber * subscriber);  /* Display available Subscribers */

/**
 * @Param: *publisher, the list of Publisher
 */
void toStringPublisher(const Publisher * publisher);     /* Display available Publishers*/

/**
 * @Param: *topic, the list of Topic
 */
void toStringTopic(const Topic * topic);                 /* Display available Topic */

/**
 * @Param: *topics, the list of Topics
 */
void toStringTopics(const Topics * topic);               /* Display available Topics */

/**
 * @Param: publisher[], the list all existing Publisher
 */
void toStringAllPublisher(const Publisher publisher[]); /* Display all Publishers */

/**
 * @Param: subscriber[], the list of all existing Subscriber
 */
void toStringAllSubscriber(const Subscriber subscriber[]);  /* Display all Subscribers */

/********* END OF TO STRING FUNCTIONS **********/

/********* BEGIN OF SEMAPHORE METHODS **********/

/**
 * @Param: semaphore, the semaphore you want to give back
 */
void down(semaphore * s);                                 /* Give back Semaphore */

/**
 * @Param: semaphore, the semaphore you want to take
 */
void up(semaphore * s);                                   /* Take Semaphore */

/**
 * @Param: topic_id, the topic in which you want to enter its critical region by specified its id
 */
void enter_critical_region_topic(int topic_id);           /* Enter the critical region for specified Topic id */

/**
 * @Param: topic_id, the topic in which you want to leave its critical region by specified its id
 */
void leave_critical_region_topic(int topic_id);           /* Leave the critical region for specified Topic id */

/**
 * @Param: semaphore, the semaphore you want to check
 */
void checkNotDown(semaphore * s);                         /* Check that the Semaphore haven't been giving back */

/**
 * @Param: topic_id, the topic in which you want to know if its critical region is still read by specified its id
 */
void wait_read_critical_region_topic(int topic_id);       /* Wait that other process have finished to read the critical region of specified Topic id */

/********* END OF SEMAPHORE METHODS **********/

/********* BEGIN OF SYSTEM CALL METHODS **********/

int do_topic_lookup(void);                                /* Syscall of do_topic_lookup function */

int do_topic_create(void);                                /* Syscall of do_topic_create function */

int do_topic_publisher(void);                             /* Syscall of do_topic_publisher function */

int do_topic_subscriber(void);                            /* Syscall of do_topic_subscriber function */

int do_topic_publish(void);                               /* Syscall of do_topic_publish function */

int do_retrieve(void);                                    /* Syscall of do_retrieve function */

int do_print_subscribers(void);                           /* Syscall of do_print_subscribers function */

int do_print_publishers(void);                            /* Syscall of do_print_publishers function */

int do_topic_delete(void);                                /* Syscall of do_topic_delete function */

/********* END OF SYSTEM CALL METHODS **********/

/********* BEGIN OF INTERNAL METHODS **********/

/********* BEGIN OF UTILITY METHODS **********/

int doInit();                                                                           /* Initialization of Publishers, Subscribers and Topics */

/**
 * @Param: user_pid, the pid for which you want to know its topic
 */
Topic * findTopicByName(const char * user_pid);                                         /* Return a Topic id for a specified Topic name */

/**
 * @Param: user_pid, the pid for which you want to know its subscriber
 */
Subscriber * findSubscriberByPid(const pid_t user_pid);                                 /* Return a Subscriber name for a specified Subscriber pid */

/**
 * @Param: user_pid, the pid for which you want to know its publisher
 */
Publisher * findPublisherById(pid_t user_pid);                                          /* Return a Publisher name for a specified Publisher id */

/**
 * @Param: *subscriber, the specified subscriber you want to know its position
 * @Param: *topic, the specified topic for the specified subscriber
 */
int findUserTopicPosition(const Subscriber * subscriber, const Topic * topic);          /* Return the position of a Subscriber for a specified Topic */

/**
 * @Param: *topic, the topic you want to know if there is space left for it
 */
int findAndLockAvailableSlot(Topic * topic);                                            /* Return if there is an available slot for a Topic, if possible, it's locking the position for this Topic */

/**
 * @Param: *topic, the topic you want to know if its message have been read
 * @Param: slot, the slot of the topic you want to know if the message contains have been read
 */
bool checkAllRetrieved(const Topic * topic, const int slot);                            /* Return if all Messages have been Retrieved by the Subscribers for a specified Topic */

/**
 * @Param: *topicName, the topic you want to check
 * @Param: *publisher, the publisher you want to check for specified topic
 */
bool userIsRegistredAsPublisher(const char * topicName, const Publisher * publisher);   /* Return if an User is Registred As A Publisher for a specified Publisher and a Specified Topic */

/**
 * @Param: *name, the topic you want to check
 * @Param: user_pid, the pid of the user you want to check if its a subscriber
 */
int is_ID_set(const char * name, pid_t user_pid);                                       /* Return if a Subscriber have is ID set for a Topic for a specified Subscriber name and pid */

/**
 * @Param: *name, the topic you want to subscribe to
 * @Param: user_pid, the user you want to set as a subscriber for the specified topic
 */
int subscribers_init(const char * name, pid_t user_pid);                                /* Return the Initialization of a Subscriber for a specified Topic */

/********* END OF UTILITY METHODS **********/

/********* BEGIN OF CORE METHODS **********/

void lookup();                                                                                       /* Display the list of all Topics Available*/

/**
 * @Param: *name, the name of the topic you want to create
 */
bool create_topic(const char * name);                                                                /* Create a Topic for a Specified Name */

/**
 * @Param: *name, the name of the topic you want to be a publisher
 * @Param: user_pid, the pid of the user you want to set as a publisher
 */
int topic_publisher(const char * name, pid_t user_pid);                                              /* Set a specified User as a Publisher by is id for a selected Topic */

/**
 * @Param: *name, the name of the topic you want to be a subscriber
 * @Param: user_pid, the pid of the user you want to set as a subscriber
 */
bool subscribe_to_topic(const char * name, pid_t user_pid);                                          /* Set a specified User as a Subscriber by is id of a selected Topic*/

/**
 * @Param: *userTopic, the list of all UserTopic
 * @Param: *msg, the message you want to publish into UserTopic
 * @Param: msgLocation, the location of the message you want to send
 */
void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation);        /* Publish a message into a specified UserTopic */

/**
 * @Param: *topic, the list of all Topic
 * @Param: *msg, the message you want to publish
 */
int publish_into_all_user_topic(Topic * topic, const char * msg);                                    /* Publish a message into all UserTopic */

/**
 * @Param: *topicName, the topic in which you want to publish
 * @Param: *msg, the message you want to publish for the specified topic
 * @Param: *publisher, the publisher that is going to publish the message
 */
int publish_msg_into_topic(const char * topicName, const char * msg, const Publisher * publisher);   /* Publish a message into a specified Topic */

/**
 * @Param: user_pid, the pid of the user who want to retrieve a message from a specified topic
 * @Param: *topicName, the topic name for which you want to retrieve a message
 */
char * retrieve_msg_of_topic(const pid_t user_pid, const char * topicName);                          /* Retrieve a message for a specified Subscriber for a a specified Topic */

/**
 * @Param: *userTopic, the user topic in which you want to read message
 */
char * readMessage(UserTopic *userTopic);                                                            /* Read a Message in a specified UserTopic */

/**
 * @Param: *name, the name of the topic you want to delete
 */
bool delete_topic(const char * name);                                                                /* Delete a specified Topic */

void printAllPublishers();                                                                           /* Display the list of All Registered Publishers */

void printAllSubscribers();                                                                          /* Display the list of All Registered Subscribers */

/********* END OF CORE METHODS **********/

/********* END OF INTERNAL METHODS **********/

/********* BEGIN OF DEBUG METHODS **********/

void toStringData();                                                                                 /* Display all the Data available */

/********* END OF DEBUG METHODS **********/

#endif /** PROJECT_2_SYST_CALL_H */
