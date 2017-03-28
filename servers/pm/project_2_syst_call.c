
#include"project_2_syst_call.h"

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
#include "error_code.h"
#include <malloc.h>

int do_topic_lookup(void){
    return 1;
}

int do_topic_create(void){
    char name[10];
    strcpy(name,m_in.m3_ca1);
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
