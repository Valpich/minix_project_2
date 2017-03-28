
#ifndef PROJECT_2_SYST_CALL_H
#define PROJECT_2_SYST_CALL_H

extern int do_topic_lookup(void);
extern int do_topic_create(char[]);
extern int do_topic_publisher(char[],int);
extern int do_topic_subscriber(char[],int);
extern int do_topic_publish(char[],int);
extern int do_retrieve(void);

#endif /** PROJECT_2_SYST_CALL_H */
