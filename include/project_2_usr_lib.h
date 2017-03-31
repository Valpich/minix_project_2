

#include <sys/types.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

int topic_lookup(void){
    message m;
    return ( _syscall(PM_PROC_NR,TOPIC_LOOKUP, &m) );
}

int topic_create(const char * name){
    message m;
    strcpy(m.m3_ca1,name);
    //	printf("\nM new one %s",m.m3_ca1);
    return ( _syscall(PM_PROC_NR, TOPIC_CREATE, &m) );
}

int topic_publisher(const char * name){
    int a;
    message m;
    a=getpid();
    strcpy(m.m3_ca1,name);
    m.m1_i1=a;
    return ( _syscall(PM_PROC_NR,TOPIC_PUBLISHER, &m) );
}

int topic_subscriber(const char * name){
    int a;
    message m;
    a=getpid();
    strcpy(m.m3_ca1,name);
    m.m1_i1=a;
    return ( _syscall(PM_PROC_NR,TOPIC_SUBSCRIBER, &m) );
}

int topic_publish(const char * name, const char * content){
    message m;
    m.m6_p1 = name;
    m.m6_p2 = content;
    m.m1_i1=getpid();
    return ( _syscall(PM_PROC_NR,TOPIC_PUBLISH, &m) );
}

int topic_retrieve(const char * name){
    message m;
    strcpy(m.m3_ca1,name);
    m.m1_i1=getpid();
    return ( _syscall(PM_PROC_NR,TOPIC_RETRIEVE, &m) );
}
