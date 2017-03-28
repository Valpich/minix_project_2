
#ifndef PROJECT_2_SYST_CALL_H
#define PROJECT_2_SYST_CALL_H

#define MAX_MSG 5	/* Number of message for each topic */
#define MAX_TOPIC 10	/* Number of allowed topics for each topic */
typedef int semaphore;	/* Define semaphore as a type */
semaphore mutex[MAX_TOPIC]  = {1};	/* Controls access to critical region */
semaphore empty[MAX_TOPIC] = {MAX_MSG};	/* Count empty buffer slots */
semaphore full[MAX_TOPIC]  = {0};		/* Count full buffer slots */

int do_topic_lookup(void);

int do_topic_create(void);

int do_topic_publisher(void);

int do_topic_subscriber(void);

int do_topic_publish(void);

int do_retrieve(void);

#endif /** PROJECT_2_SYST_CALL_H */
