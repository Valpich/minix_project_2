
#include"project_2_usr_lib.h"

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

int topic_publish(const char * name)
{
    int a;
    message m;
    a=getpid();
    strcpy(m.m3_ca1,name);
    m.m1_i1=a;
    return ( _syscall(PM_PROC_NR,TOPIC_PUBLISH_MSG, &m) );
}

int topic_lookup(void)
{
    message m;
    return ( _syscall(PM_PROC_NR,TOPIC_DISPLAY_TOPIC, &m) );
}

int topic_retrieve(void)
{
    message m;
    m.m1_i1=getpid();
    //	printf("\nAbout to recieve message...!!");
    
    return ( _syscall(PM_PROC_NR,TOPIC_RECEIVE_MSG, &m) );
}
