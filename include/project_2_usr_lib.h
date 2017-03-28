#ifndef PROJECT_2_USR_LIB_H
#define PROJECT_2_USR_LIB_H

#include <sys/types.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int topic_lookup(void);

int topic_create(const char * name);

int topic_publisher(const char * name);

int topic_subsriber(const char * name);

int topic_publish(const char * name);

int topic_retrieve(void);

#endif /* PROJECT_2_USR_LIB_H */