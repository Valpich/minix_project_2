#ifndef PROJECT_2_USR_LIB_H
#define PROJECT_2_USR_LIB_H

#include <sys/types.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

int topic_subsriber(const char * name){
    int a;
    message m;
    a=getpid();
    strcpy(m.m3_ca1,name);
    m.m1_i1=a;
    return ( _syscall(PM_PROC_NR,TOPIC_SUBSCRIBER, &m) );
}

int topic_publish(const char * name){
    int a;
    message m;
    a=getpid();
    strcpy(m.m3_ca1,name);
    m.m1_i1=a;
    return ( _syscall(PM_PROC_NR,TOPIC_PUBLISH, &m) );
}

int topic_retrieve(void){
    message m;
    m.m1_i1=getpid();
    //	printf("\nAbout to recieve message...!!");
    
    return ( _syscall(PM_PROC_NR,TOPIC_RETRIEVE, &m) );
}

#endif /* PROJECT_2_USR_LIB_H */