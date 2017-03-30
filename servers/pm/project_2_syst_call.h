
#ifndef PROJECT_2_SYST_CALL_H
#define PROJECT_2_SYST_CALL_H

typedef enum {false = 0, true = 1} bool;

int do_topic_lookup(void);

int do_topic_create(void);

int do_topic_publisher(void);

int do_topic_subscriber(void);

int do_topic_publish(void);

int do_retrieve(void);

bool create_new_topic(const char * name);

void create_new_user_topic(const int id, const char * name);

#endif /** PROJECT_2_SYST_CALL_H */
