
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

void toStringUserTopic(const UserTopic * userTopic);     /* Display available UserTopic */

void toStringSubscriber(const Subscriber * subscriber);  /* Display available Subscribers */

void toStringPublisher(const Publisher * publisher);     /* Display available Publishers*/

void toStringTopic(const Topic * topic);                 /* Display available Topic */

void toStringTopics(const Topics * topic);               /* Display available Topics */

void toStringAllPublisher(const Publisher publisher[]); /* Display all Publishers */

void toStringAllSubscriber(const Subscriber subscriber[]);  /* Display all Subscribers */

/********* END OF TO STRING FUNCTIONS **********/

/********* BEGIN OF SEMAPHORE METHODS **********/

void down(semaphore * s);                                 /* Give back Semaphore */

void up(semaphore * s);                                   /* Take Semaphore */

void enter_critical_region_topic(int topic_id);           /* Enter the critical region for specified Topic id */

void leave_critical_region_topic(int topic_id);           /* Leave the critical region for specified Topic id */

void checkNotDown(semaphore * s);                         /* Check that the Semaphore haven't been giving back */

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

Topic * findTopicByName(const char * user_pid);                                         /* Return a Topic id for a specified Topic name */

Subscriber * findSubscriberByPid(const pid_t user_pid);                                 /* Return a Subscriber name for a specified Subscriber pid */

Publisher * findPublisherById(pid_t user_pid);                                          /* Return a Publisher name for a specified Publisher id */

int findUserTopicPosition(const Subscriber * subscriber, const Topic * topic);          /* Return the position of a Subscriber for a specified Topic */

int findAndLockAvailableSlot(Topic * topic);                                            /* Return if there is an available slot for a Topic, if possible, it's locking the position for this Topic */

bool checkAllRetrieved(const Topic * topic, const int slot);                            /* Return if all Messages have been Retrieved by the Subscribers for a specified Topic */

bool userIsRegistredAsPublisher(const char * topicName, const Publisher * publisher);   /* Return if an User is Registred As A Publisher for a specified Publisher and a Specified Topic */

int is_ID_set(const char * name, pid_t user_pid);                                       /* Return if a Subscriber have is ID set for a Topic for a specified Subscriber name and pid */

int subscribers_init(const char * name, pid_t user_pid);                                /* Return the Initialization of a Subscriber for a specified Topic */

/********* END OF UTILITY METHODS **********/

/********* BEGIN OF CORE METHODS **********/

void lookup();                                                                                       /* Display the list of all Topics Available*/

bool create_topic(const char * name);                                                                /* Create a Topic for a Specified Name */

int topic_publisher(const char * name, pid_t user_pid);                                              /* Set a specified User as a Publisher by is id for a selected Topic */

bool subscribe_to_topic(const char * name, pid_t user_pid);                                          /* Set a specified User as a Subscriber by is id of a selected Topic*/

void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation);        /* Publish a message into a specified UserTopic */

int publish_into_all_user_topic(Topic * topic, const char * msg);                                    /* Publish a message into all UserTopic */

int publish_msg_into_topic(const char * topicName, const char * msg, const Publisher * publisher);   /* Publish a message into a specified Topic */

char * retrieve_msg_of_topic(const pid_t user_pid, const char * topicName);                          /* Retrieve a message for a specified Subscriber for a a specified Topic */

char * readMessage(UserTopic *userTopic);                                                            /* Read a Message in a specified UserTopic */

bool delete_topic(const char * name);                                                                /* Delete a specified Topic */

void printAllPublishers();                                                                           /* Display the list of All Registered Publishers */

void printAllSubscribers();                                                                          /* Display the list of All Registered Subscribers */

/********* END OF CORE METHODS **********/

/********* END OF INTERNAL METHODS **********/

/********* BEGIN OF DEBUG METHODS **********/

void toStringData();                                                                                 /* Display all the Data available */

/********* END OF DEBUG METHODS **********/

#endif /** PROJECT_2_SYST_CALL_H */
