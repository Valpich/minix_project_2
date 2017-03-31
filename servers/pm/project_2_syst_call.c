#include "project_2_syst_call.h"

const Topic defaultTopic = {.id=-1,.msgSlotAvailable = {[0 ... MAX_MSG-1] = true}, .name = "\0", .toString=toStringTopic};

static semaphore mutex[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 1};	/* Controls access to critical region */

static Subscriber subscribers[MAX_USR];
static Publisher publishers[MAX_USR];
static int  topicsSize = 0;

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
            int i = 0;
            for(i = 0; i<MAX_TOPIC ;i++){
                UserTopic userTopic = subscriber->userTopic[i];
                userTopic.toString(&userTopic);
            }
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

void toStringAllPublisher(const Publisher publisher[]){
    if(publisher != NULL){
        printf("Publisher list is:\n");
        int i = 0;
        for(i = 0; i<MAX_USR ;i++){
            Publisher pub = publisher[i];
            pub.toString(&pub);
        }
        printf(".\n");
    }else{
        printf("Publishers is NULL.\n");
    }
}

void toStringAllSubscriber(const Subscriber subscriber[]){
    if(subscriber != NULL){
        printf("Subscriber list is:\n");
        int i = 0;
        for(i = 0; i<MAX_USR ;i++){
            Subscriber sub = subscriber[i];
            sub.toString(&sub);
        }
        printf(".\n");
    }else{
        printf("Publisher is NULL.\n");
    }
}

/********* END OF TO STRING FUNCTIONS **********/

static Topics topics = {.canBeRemoved = {[0 ... MAX_TOPIC-1] =1}, .toString=toStringTopics};


void down(semaphore * s){
    printf("s in down is %d.\n", *s);
    int test = *s == 0;
    while(test){
        test = *s == 0;
        sleep(1);
    }
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

void checkNotDown(semaphore * s){
    int test = *s == 0;
    while(test){
        test = *s == 0;
        printf("Waiting critical region to be free.\n");
        sleep(1);
    }
}

void wait_read_critical_region_topic(int topic_id){
    checkNotDown(&mutex[topic_id]);
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

/**
 * Not critical
 */
// PUBLISHER TO TEST

int is_ID_set(const char * name, pid_t id){

    int i = 0;

    for(i=0 ; i<MAX_USR ; i++){
        // find ID
        if( id == subscribers[i].pid_subscriber){
            // look through its UserTopic to find the name
            int j = 0;
            for(j=0;j<MAX_TOPIC; j++){
                if(strcmp(name, subscribers[i].userTopic[j].name) == 0){
                    printf("already subscribed to this userTopic\n");
                    // return 5 -> already subscribed
                    return 5;
                }
            }
            // means was not found the first time -> first empty
            for(j=0;j<MAX_TOPIC; j++){
                if(-1 == subscribers[i].userTopic[j].id){
                    char *a = malloc(sizeof(name));
                    strcpy(a,"\0");
                    subscribers[i].userTopic[j].name = a;
                    subscribers[i].userTopic[j].id = j;
                    // return 1 -> ok
                    return 1;
                }
            }
        }
    }
    // mean could not find ID
    return 0;
}

// used if the id was not found in the subscribers list -> not subscribed yet to any userTopic
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
            // means was not found the first time -> first empty
            for(j=0;j<MAX_TOPIC; j++){
                if(-1 == subscribers[j].userTopic[j].id){
                    char *a = malloc(sizeof(name));
                    strcpy(a,"\0");
                    subscribers[i].userTopic[j].name = a;
                    subscribers[i].userTopic[j].id = j;
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
    printf("retourValue is %d\n.",retourValue);
    if(retourValue != 0)
        return true;
    retourValue  = subscribers_init(name,id);
    printf("retourValue is %d\n.",retourValue);
    if(retourValue != 0)
        return true;
    return false;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




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
    printf("Unable to delete userTopic %s.\n", name);
    return false;
}


/**
 * @Precondition Is into a critical region
 */
void publish_into_user_topic(UserTopic * userTopic, const char * msg, const int msgLocation){
    printf("Publishing into a user userTopic\n");
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
        int j = 0;
        for(j=0;j<MAX_TOPIC;j++){
            UserTopic defaultUserTopic = {.id = -1,.messageContent = {[0 ... MAX_MSG-1] = "\0"},.name="\0",.read = {[0 ... MAX_MSG-1] = true}, .toString=toStringUserTopic};
            subscribers[i].userTopic[j] = defaultUserTopic;
        }
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
    toStringAllPublisher(publishers);
    toStringAllSubscriber(subscribers);
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

/**
 * @Precondition Is into a critical region
 */
int publish_into_all_user_topic(const char * topicName, const char * msg){
    printf("Publishing into all user userTopic.\n");
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
            if(subscribers[i].userTopic[j].id == topic->id) {
                publish_into_user_topic(&subscribers[i].userTopic[j], msg, slot);
            }
        }
    }
    printf("End of publish into all user userTopic.\n");
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
    printf("Start publishing message into a userTopic.\n");
    if(userIsRegistredAsPublisher(topicName, publisher)){
        puts("1");
        Topic * topic = findTopicByName(topicName);
        enter_critical_region_topic(topic->id);
        publish_into_all_user_topic(topic->name,msg);
        leave_critical_region_topic(topic->id);
        printf("End of publishing message into a userTopic.\n");
        return MSG_PUBLISHED;
    }else{
        puts("2");
        printf("End of publishing message into a userTopic with failure.\n");
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
                    puts("User registred as publisher");
                    return true;
                }
            }
        }
    }
    puts("User not registred as publisher");
    return false;
}



int findUserTopicPosition(const Subscriber * subscriber, const Topic * topic){
    int i = 0;
    for(i =0;i<MAX_TOPIC; i++){
        if(strcmp(subscriber->userTopic[i].name, topic->name)){
            return i;
        }
    }
    return -1;
}

bool checkAllRetrieved(const Topic * topic){
    int i = 0;
    int j = 0;
    for(i=0;i<MAX_USR;i++){
        for(j=0;j<MAX_MSG;j++){
            if(subscribers[i].userTopic[topic->id].read[j] == true){
                return false;
            }
        }
    }
    return true;
}

char * readMessage(UserTopic *userTopic){
    int i = 0;
    for(i = 0; i<MAX_MSG ; i++){
        if(userTopic->read[i] == false){
            userTopic->read[i] = true;
            char * msg = malloc(sizeof(userTopic->messageContent));
            strcpy(msg,userTopic->messageContent);
            free(userTopic->messageContent);
            char * erased = malloc(sizeof("\0"));
            strcpy(erased,"\0");
            userTopic->messageContent[i]= erased;
            return msg;
        }
    }
}

char * retrieve_msg_of_topic(const Subscriber * subscriber, const char * topicName) {
    Topic *topic = findTopicByName(topicName);
    if (topic != NULL) {
        wait_read_critical_region_topic(topic->id);
        int positionOfTheTopic = findUserTopicPosition(subscriber, topic);
        UserTopic userTopic = subscriber->userTopic[positionOfTheTopic];
        char *msg = readMessage(&userTopic);
        if (checkAllRetrieved(topic)) {
            int i = 0;
            for (i = 0; i < MAX_MSG; i++) {
                topic->msgSlotAvailable[i] = true;
            }
        }
        return msg;
    } else {
        return NULL;
    }
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

Publisher * findPublisherById(pid_t id){
  int i = 0;
  for(i=0;i,MAX_USR;i++){
    if(publisher[i].pid_publisher == id){
      return publisher[i];
    }
  }
  return NULL;
}
