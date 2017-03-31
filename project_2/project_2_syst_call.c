
#include "project_2_syst_call.h"

const UserTopic defaultUserTopic = {.id = -1,.messageContent = {[0 ... MAX_MSG-1] = "\0"},.name="\0",.read = {[0 ... MAX_MSG-1] = true}, .toString=toStringUserTopic};
const Topic defaultTopic = {.id=-1,.msgSlotAvailable = {[0 ... MAX_MSG-1] = true}, .name = "\0", .toString=toStringTopic};

static semaphore mutex[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 1};	/* Controls access to critical region */

static int messageOfTopicToRead[MAX_TOPIC][MAX_MSG] = {[0 ... MAX_TOPIC-1] = 0, [0 ... MAX_MSG-1] = 0};   /* Count the topics that  subscribed */

static Subscriber subscribers[MAX_USR];
static Publisher publishers[MAX_USR];
static int  topicsSize = 0;
static int  subscriberSize = 0;

/********* BEGIN OF TO STRING FUNCTIONS **********/

void toStringUserTopic(const UserTopic * userTopic){
    if(userTopic != NULL){
        printf("UserTopic is:\nid: %d, name: %s, messageContent: ", userTopic->id, userTopic->name);
        int i = 0;
        for(i = 0; i<MAX_MSG ;i++){
            printf("%s, ", userTopic->messageContent[i]);
        }
        printf(" read: ");
        for(i = 0; i<MAX_MSG ;i++){
            printf("%d", userTopic->read[i]);
            if(i<MAX_MSG-1){
                printf(",");
            }
        }
        printf(".\n");
    }else{
        printf("UserTopic is NULL.\n");
    }
}

void toStringSubscriber(const Subscriber * subscriber){
    if(subscriber != NULL){
        printf("Subscriber is:\npid: %d, UserTopic are: \n", subscriber->pid_subscriber);
        if(subscriber->toString != NULL){
            subscriber->topic->toString(subscriber->topic);
        }
        printf(".\n");
    }else{
        printf("UserTopic is NULL.\n");
    }
}

void toStringPublisher(const Publisher * publisher){
    if(publisher != NULL){
        printf("Publisher is:\npid: %d,", publisher->pid_publisher);
        int i = 0;
        printf(" topics subscribed names: ");
        for(i = 0; i<MAX_TOPIC ;i++){
            printf("%s, ", publisher->topicNames[i]);
        }
        printf(".\n");
    }else{
        printf("Publisher is NULL.\n");
    }
}

void toStringTopic(const Topic * topic){
    if(topic != NULL){
        printf("Topic: name is %s, available slot are: ",  topic->name);
        int i =0 ;
        for(i = 0; i<MAX_TOPIC ;i++){
            printf(" %d,",  topic->msgSlotAvailable[i]);
        }
    }else{
        printf(" Topics is NULL.\n");
    }
}

void toStringTopics(const Topics * topic){
    if(topic != NULL){
        int i =0 ;
        for(i = 0; i<MAX_TOPIC ;i++){
            printf("Topic: id is %d, name is %s, can be removed is %d.\n", i, topic->topicArray[i].name, topic->canBeRemoved[i]);
        }
    }else{
        printf(" Topics is NULL.\n");
    }
}

/********* END OF TO STRING FUNCTIONS **********/

static Topics topics = {.canBeRemoved = {[0 ... MAX_TOPIC-1] =1}, .toString=toStringTopics};


void down(semaphore * s){
    printf("s in down is %d.\n", *s);
    while(*s == 0)sleep(1);
    *s = *s - 1;
}

void up(semaphore * s){
    printf("s in up is %d.\n", *s);
    *s = *s + 1;
}

void enter_critical_region_topic(int topic_id){
    printf("Entering critical region.\n");
    down(&mutex[topic_id]);
}

void leave_critical_region_topic(int topic_id){
    printf("Leaving critical region.\n");
    up(&mutex[topic_id]);
}

int do_topic_lookup(void){
    int i = 0;
    for(i= 0; i< MAX_TOPIC;i++){
        if(strcmp("\0",topics.topicArray[i].name) != 0){
            printf("Topic #%d : %s\n",i,topics.topicArray[i].name);
        }
    }
    return 1;
}

int do_topic_create(void){
  printf("do_topic_create\n");
  char *topic_name = NULL;
  int Return_value;
  strcpy(topic_name,m_in.m3_ca1);
  printf("received value : %s \n",topic_name);
  Return_value = create_topic(topic_name);
  return Return_value;
}

int do_topic_publisher(void){
  printf("do_topic_publisher\n");
  char *topic_name = NULL;
  int id,Return_val;
  strcpy(name_p,m_in.m3_ca1);
  id=m_in.m1_i1;
  Return_value = topic_publisher(topic_name, id);
  return Return_value;
}

int do_topic_subscriber(void){
  printf("do_topic_subscriber\n");
  char *topic_name = NULL;
  int id,Return_val;
  strcpy(topic_name,m_in.m3_ca1);
  id=m_in.m1_i1;
  Return_value = subscribe_to_topic(topic_name, id);
  return Return_value;
}

int do_topic_publish(void){
  printf("do_topic_publish\n");
  char *topic_name = NULL;
  char *topic_content = NULL;
  int id,Return_val;
  strcpy(topic_name,m_in.m3_ca1);
  strcpy(topic_content,m_in.m2_ca1);
  id=m_in.m1_i1;
  Publisher * publisher = findPublisherById(id);
  Return_val = publish_msg_into_topic(topic_name, topic_content, publisher);
  return Return_val;
}

int do_retrieve(void){
    return 6;
}

// PUBLISHER TO TEST

int is_ID_set(const char * name, pid_t id){

int i = 0;

for(i=0 ; i<MAX_USR ; i++){
		// find ID
		if( id == subscribers[i].pid_subscriber){
			// look through its UserTopic to find the name
			int j = 0;
			for(j=0;j<MAX_TOPIC; j++){
				 if(strcmp(name, subscribers[i].topic[j].name) == 0){
					printf("already subscribed to this topic\n");
					// return 5 -> already subscribed
					return 5;
				 }
			 }
			 // means was not found the first time -> first empty
			 for(j=0;j<MAX_TOPIC; j++){
				 if(-1 == subscribers[i].topic[j].id){
					char *a = malloc(sizeof(name));
					strcpy(a,"\0");
					subscribers[i].topic[j].name = a;
					subscribers[i].topic[j].id = j;
					// return 1 -> ok
					return 1;
				 }
			}
		}
	}
// mean could not find ID
return 0;
}

// used if the id was not found in the subscribers list -> not subscribed yet to any topic
int subscribers_init(const char * name, pid_t id){
int i = 0;
// means the id was not found  in the subscribers -> first  init
for(i=0 ; i<MAX_USR ; i++){
		// Look for the first available size
		if(-1 == subscribers[i].pid_subscriber){
			// assign correct value to pid
			subscribers[i].pid_subscriber =  id;
			// look through its UserTopic to find the name
			int j = 0;
			// should not happen - delete later if else works
			for(j=0;j<MAX_TOPIC; j++){
				 if(strcmp(name, subscribers[i].topic[j].name) == 0){
					printf("already subscribed to this topic\n");
					// 5 -> already subscribed
					return 5;
				 }
			}
			 // means was not found the first time -> first empty
			 for(j=0;j<MAX_TOPIC; j++){
				 if(-1 == subscribers[j].topic[j].id){
					char *a = malloc(sizeof(name));
					strcpy(a,"\0");
					subscribers[i].topic[j].name = a;
					subscribers[i].topic[j].id = j;
					// 1-> ok
					return 1;
				 }
			}
	}
}
// could not find -1
return 0;
}

bool subscribe_to_topic(const char * name, pid_t id){

	int retourValue = is_ID_set(name,id);
	if(retourValue != 0)
		return true;
	retourValue  = subscribers_init(name,id);
	if(retourValue != 0)
		return true;

	return false;
}



// END OF PUBLISHER

/**
 * @Precondition Is into a critical region
 */
bool create_topic(const char * name){
    printf("Topic creation \n");
    topics.toString(&topics);
    if(topicsSize < MAX_TOPIC){
        int i = 0;
        for(i=0; i< MAX_TOPIC; i++) {
            if(strcmp(name, topics.topicArray[i].name) == 0) {
                printf("Topic %s is already in list.\n", name);
                return false;
            }else if(strcmp("\0",topics.topicArray[i].name) == 0){
                printf("Empty find at %d\n", i);
                enter_critical_region_topic(i);
                printf("Setting name.\n");
                char *a = malloc(sizeof(name));
                strcpy(a,name);
                topics.topicArray[i].name = a;
                printf("Topic name is %s.\n",topics.topicArray[i].name);
                topicsSize++;
                printf("Topic size is %d.\n",topicsSize);
                printf("Topic created.\n");
                leave_critical_region_topic(i);
                return true;
            }
        }
        return true;
    }else{
        printf("Topic size is %d, max amount reached.\n",topicsSize);
        printf("Topic %s not created.\n", name);
        return false;
    }
}

/**
 * @Precondition Is into a critical region
 */
bool delete_topic(const char * name){
    printf("Topic deletion \n");
    int i = 0;
    for(i=0; i< MAX_TOPIC; i++) {
        if(strcmp(name,topics.topicArray[i].name) == 0){
            printf("Topic find at %d.\n", i);
            enter_critical_region_topic(i);
            char * toDelete = topics.topicArray[i].name;
            free(toDelete);
            char *a = malloc(sizeof("\0"));
            strcpy(a,"\0");
            topics.topicArray[i].name = a;
            topicsSize--;
            printf("Topic deleted.\n");
            leave_critical_region_topic(i);
            return true;
        }
    }
    printf("Topic size is %d, max amount reached.\n",topicsSize);
    printf("Unable to delete topic %s.\n", name);
    return false;
}

/**
 * @Precondition Is into a critical region
 */
void create_new_user_topic(const int id, const char * name){
    printf("UserTopic creation\n");
    UserTopic userTopic;
    printf("Setting userTopicToString method\n");
    userTopic.toString = toStringUserTopic;
    printf("Setting id \n");
    userTopic.id = id;
    printf("Setting user topic name \n");
    strcpy(&userTopic.name,name);
    printf("Setting messages to \0 in user topic\n");
    int i = 0;
    for(i = 0; i<MAX_MSG ;i++){
        strcpy(&userTopic.messageContent[i],"\0");
    }
    printf("Setting messages read to true in user topic\n");
    for(i = 0; i<MAX_MSG ;i++){
        userTopic.read[i] = true;
    }
    printf("Printing user topic\n");
    userTopic.toString(&userTopic);
    printf("UserTopic created\n");
}

/**
 * @Precondition Is into a critical region
 */
void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation){
    printf("Publishing into a user topic\n");
    char *a = malloc(sizeof(msg));
    strcpy(a,msg);
    userTopic->messageContent[msgLocation] = a;
    userTopic->read[msgLocation] = false;
    printf("UserTopic created\n");
}

int doFakeInit(){
    create_topic("Salut");
    create_topic("aude");
}

int doInit(){
    int i = 0;
    for(i = 0; i<MAX_USR; i++){
        subscribers[i].pid_subscriber = -1;
        subscribers->topic[i] = defaultUserTopic;
        subscribers[i].toString = toStringSubscriber;
    }
    for(i = 0; i<MAX_USR; i++){
        publishers[i].pid_publisher= -1;
        int j = 0;
        for(j = 0; j<MAX_TOPIC; j++){
            char * name = malloc(sizeof("\0"));
            strcpy(name,"\0");
            publishers[i].topicNames[j] = name;
        }
        publishers[i].toString = toStringPublisher;
    }
    for(i = 0; i<MAX_TOPIC; i++){
        topics.topicArray[i] = defaultTopic;
    }
}

Topic * findTopicByName(const char * name){
    int i = 0;
    for(i=0;i<MAX_TOPIC;i++) {
        if (strcmp(topics.topicArray[i].name, name) == 0) {
            return &topics.topicArray[i];
        }
    }
    return NULL;
}

Publisher * findPublisherById(pid_t id){
  int i = 0;
  for(i=0;i,MAX_USR;i++){
    if(publisher[i].pid_publisher == id){
      return publisher[i];
    }
  }
  return NULL;
}

/**
 * @Precondition Is into a critical region
 */
int publish_into_all_user_topic(const char * topicName, const char * msg){
    printf("Publishing into all user topic.\n");
    subscribers->toString(subscribers);
    int i = 0;
    Topic  * topic = findTopicByName(topicName);
    if(topic == NULL){
        return TOPIC_NOT_FOUND;
    }
    int slot = findAndLockAvailableSlot(topic);
    if(slot == -1){
        return NOT_SLOT_AVAILABLE;
    }
    for(i=0;i<MAX_USR;i++){
        int j = 0;
        for(j=0;j<MAX_TOPIC;j++){
            if(subscribers[i].topic[j].id == topic->id) {
                publish_into_user_topic(&subscribers[i].topic[j], msg, slot);
            }
        }
    }
    printf("End of publish into all user topic.\n");
    return slot;
}

int findAndLockAvailableSlot(Topic * topic){
    int i = 0;
    for(i = 0;i<MAX_MSG;i++){
        if(topic->msgSlotAvailable[i] == true){
            topic->msgSlotAvailable[i] = false;
            return i;
        }
    }
    return -1;
}

int publish_msg_into_topic(const char * topicName, const char * msg, const Publisher * publisher){
    printf("Start publishing message into a topic.\n");
    doInit();//TODO: Init at beginning
    if(userIsRegistredAsPublisher(topicName, publisher)){
        puts("1");
        Topic * topic = findTopicByName(topicName);
        enter_critical_region_topic(topic->id);
        publish_into_all_user_topic(topic->name,msg);
        leave_critical_region_topic(topic->id);
        printf("End of publishing message into a topic.\n");
        return MSG_PUBLISHED;
    }else{
        puts("2");
        printf("End of publishing message into a topic with failure.\n");
        return USR_NOT_REGISTRED_AS_PUBLISHER;
    }
}

bool userIsRegistredAsPublisher(const char * topicName, const Publisher * publisher){
    int i = 0;
    int j = 0;
    for(i = 0; i<MAX_USR; i++){
        if(publishers[i].pid_publisher == publisher->pid_publisher){
            for(j = 0; j<MAX_TOPIC; j++) {
                if (strcmp(publishers[i].topicNames[j], topicName) == 0) {
                    puts("User registred as published");
                    return true;
                }
            }
        }
    }
    puts("User not registred as published");
    return false;
}

int topic_publisher(const char * name, pid_t current_pid){
    int j, g;

    Topic  * topic = findTopicByName(name);
    if(topic == NULL){
        printf("Please enter a valid topic name in order to be a publisher\n");
        return 12;
    }else{
        for(j = 0 ; j < MAX_USR ; j++){
            if(publisher[j].pid_publisher == -1 || publisher[j].pid_publisher == current_pid){
                for(g = 0 ; g < MAX_TOPIC ; g++) {
                    if (strcmp(publisher[j].topicNames[g], "\0") == 0) {
                        printf("j: %d, g: %d\n", j, g);
                        publisher[j].pid_publisher = current_pid;
                        publisher[j].topicNames[g] = name;
                        printf("Publisher OK: %s\n", publisher[j].topicNames[g]);
                        return 1;
                    }
                }
                printf("There is no space available for you to be a publisher for this topic\n");
                return 0;
            }
        }
    }
}
