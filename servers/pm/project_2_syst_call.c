#include "project_2_syst_call.h"


/********* BEGIN OF TO STRING FUNCTIONS **********/

void toStringUserTopic(const UserTopic * userTopic){
    if(userTopic != NULL){
        printf("UserTopic is:\nid: %d, name: %s, messageContent: ", userTopic->id, userTopic->name);
        int i = 0;
        for(i = 0; i<MAX_MSG ;i++){
            printf("%s, ", userTopic->messageContent[i]);
        }
        printf("read: ");
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
        printf(" topics publisher names: ");
        for(i = 0; i<MAX_TOPIC-1 ;i++){
            printf("%s, ", publisher->topicNames[i]);
        }
        printf("%s", publisher->topicNames[MAX_TOPIC-1]);
        printf(".\n");
    }else{
        printf("Publisher is NULL.\n");
    }
}

void toStringTopic(const Topic * topic){
    if(topic != NULL){
        printf("Topic: name is %s, id is %d, available slot are: ", topic->name, topic->id);
        int i =0 ;
        for(i = 0; i<MAX_MSG-1 ;i++){
            printf(" %d,",  topic->msgSlotAvailable[i]);
        }
        printf(" %d",  topic->msgSlotAvailable[MAX_MSG-1]);
        printf(".\n");
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

/********* BEGIN OF PUBLIC VARIABLE DECLARATION **********/

const Topic defaultTopic = {.id=INVALID_ID,.msgSlotAvailable = {[0 ... MAX_MSG-1] = true}, .name = "\0", .toString=toStringTopic};

static semaphore mutex[MAX_TOPIC]  = {[0 ... MAX_TOPIC-1] = 1};	/* Controls access to critical region */

static Subscriber subscribers[MAX_USR];

static Publisher publishers[MAX_USR];

static int topicsSize = 0;

static bool initDone = false;

static Topics topics = {.canBeRemoved = {[0 ... MAX_TOPIC-1] =1}, .toString=toStringTopics};

/********* END OF PUBLIC VARIABLE DECLARATION **********/

/********* BEGIN OF SEMAPHORE METHODS **********/

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
        printf("Waiting critical region to be available.\n");
        sleep(1);
    }
}

void wait_read_critical_region_topic(int topic_id){
    checkNotDown(&mutex[topic_id]);
}

/********* END OF SEMAPHORE METHODS **********/

/********* BEGIN OF SYSTEM CALL METHODS **********/

int do_topic_lookup(void){
    if(initDone == false){
        doInit();
    }
    printf("do_topic_lookup\n");
    lookup();
    return DO_TOPIC_LOOKUP_SUCCESS_RETURN;
}

int do_topic_create(void){
    if(initDone == false){
        doInit();
    }
    printf("do_topic_create\n");
    char *topic_name = malloc(sizeof(m_in.m3_ca1));
    bool success = false;
#ifdef MINIX
    strcpy(topic_name,m_in.m3_ca1);
#endif
    printf("received value : %s \n",topic_name);
    success = create_topic(topic_name);
    if(success){
        return DO_TOPIC_CREATE_SUCCESS_RETURN;
    }else {
        return DO_TOPIC_CREATE_FAILURE_RETURN;
    }
}

int do_topic_publisher(void){
    if(initDone == false){
        doInit();
    }
    printf("do_topic_publisher\n");
    char *topic_name = malloc(sizeof(m_in.m3_ca1));
    int id = INVALID_ID;
    int returnValue = DO_TOPIC_PUBLISHER_FAILURE_RETURN;
#ifdef MINIX
    strcpy(topic_name,m_in.m3_ca1);
    id=m_in.m1_i1;
    returnValue = topic_publisher(topic_name, id);
#endif
    return returnValue;
}

int do_topic_subscriber(void){
    if(initDone == false){
        doInit();
    }
    printf("do_topic_subscriber\n");
    char *topic_name = malloc(sizeof(m_in.m3_ca1));
    int id = INVALID_ID;
    bool success = false;
#ifdef MINIX
    strcpy(topic_name,m_in.m3_ca1);
    id=m_in.m1_i1;
    success = subscribe_to_topic(topic_name, id);
#endif
    if(success){
        return DO_TOPIC_SUBSCRIBER_SUCCESS_RETURN;
    }else {
        return DO_TOPIC_SUBSCRIBER_FAILURE_RETURN;
    }
}

int do_topic_publish(void){
    if(initDone == false){
        doInit();
    }
    printf("do_topic_publish\n");
    char *topic_name = malloc(sizeof(m_in.m6_p1));
    char *topic_content = malloc(sizeof(m_in.m6_p2));
    int id,returnValue = INVALID_ID;
#ifdef MINIX
    strcpy(topic_name,m_in.m6_p1);
    strcpy(topic_content,m_in.m6_p2);
    id=m_in.m1_i1;
    Publisher * publisher = findPublisherById(id);
    printf("Trying to publish the message: \"%s\" for the topic %s\n",topic_content, topic_name);
    returnValue = publish_msg_into_topic(topic_name, topic_content, publisher);
#endif
    toStringData();
    return returnValue;
}

int do_retrieve(void){
    if(initDone == false){
        doInit();
    }
    printf("do_retrieve\n");
    char * msg = NULL;
    char *topic_name = malloc(sizeof(m_in.m3_ca1));
    int id = INVALID_ID;
#ifdef MINIX
    strcpy(topic_name,m_in.m3_ca1);
    id=m_in.m1_i1;
    printf("Trying to retrieve message from the topic %s\n", topic_name);
    msg = retrieve_msg_of_topic(id, topic_name);
#endif
    if(msg != NULL){
        printf("%s", msg);
        return DO_RETRIEVE_SUCCESS_RETURN;
    }else {
        printf("Noting to retrieve.\n");
        return DO_RETRIEVE_FAILURE_RETURN;
    }
}

/********* END OF SYSTEM CALL METHODS **********/

/********* BEGIN OF INTERNAL METHODS **********/

/********* BEGIN OF UTILITY METHODS **********/

int doInit(){
    int i = 0;
    puts("DOING INIT");
    for(i = 0; i<MAX_USR; i++){
        subscribers[i].pid_subscriber = INVALID_PID;
        int j = 0;
        for(j=0;j<MAX_TOPIC;j++){
            UserTopic defaultUserTopic = {.id = INVALID_ID,.messageContent = {[0 ... MAX_MSG-1] = "\0"},.name="\0",.read = {[0 ... MAX_MSG-1] = true}, .toString=toStringUserTopic};
            subscribers[i].userTopic[j] = defaultUserTopic;
        }
        subscribers[i].toString = toStringSubscriber;
    }
    for(i = 0; i<MAX_USR; i++){
        publishers[i].pid_publisher= INVALID_PID;
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
    initDone = true;
    puts("INIT DONE");
    return EXIT_SUCCESS;
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


Subscriber * findSubscriberByPid(const pid_t user_pid) {
    int i = 0;
    for(i =0;i<MAX_USR; i++){
        if(subscribers[i].pid_subscriber == user_pid){
            return &subscribers[i];
        }
    }
    return NULL;
}

Publisher * findPublisherById(pid_t user_pid){
    int i = 0;
    for(i=0;i<MAX_USR;i++){
        if(publishers[i].pid_publisher == user_pid){
            return &publishers[i];
        }
    }
    return NULL;
}

int findUserTopicPosition(const Subscriber * subscriber, const Topic * topic){
    int i = 0;
    for(i =0;i<MAX_TOPIC; i++){
        if(subscriber->userTopic[i].id == topic->id){
            return i;
        }
    }
    return INVALID_POSITION;
}

int findAndLockAvailableSlot(Topic * topic){
    int i = 0;
    for(i = 0;i<MAX_MSG;i++){
        if(topic->msgSlotAvailable[i] == true){
            topic->msgSlotAvailable[i] = false;
            return i;
        }
    }
    return INVALID_POSITION;
}

bool checkAllRetrieved(const Topic * topic, const int slot){
    int i = 0;
    for(i=0;i<MAX_USR;i++){
        if(subscribers[i].pid_subscriber != INVALID_POSITION){
            if(subscribers[i].userTopic->id!= INVALID_POSITION) {
                if (subscribers[i].userTopic[topic->id].read[slot] != true) {
                    return false;
                }
            }
        }
    }
    return true;
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

int is_ID_set(const char * name, pid_t user_pid){
    int i = 0;
    for(i=0 ; i<MAX_USR ; i++){
        // find ID
        if( user_pid == subscribers[i].pid_subscriber){
            // look through its UserTopic to find the name
            int j = 0;
            for(j=0;j<MAX_TOPIC; j++){
                if(strcmp(name, subscribers[i].userTopic[j].name) == 0){
                    printf("already subscribed to this userTopic\n");
                    // return 5 -> already subscribed
                    return ALREADY_REGISTRED;
                }
            }
            // means was not found the first time -> first empty
            for(j=0;j<MAX_TOPIC; j++){
                if(INVALID_ID == subscribers[i].userTopic[j].id){
                    char *a = malloc(sizeof(name));
                    strcpy(a,name);
                    subscribers[i].userTopic[j].name = a;
                    subscribers[i].userTopic[j].id = j;
                    // return 1 -> ok
                    return NEW_REGISTRATION;
                }
            }
        }
    }
    // mean could not find ID
    return INVALID_POSITION;
}

// used if the id was not found in the subscribers list -> not subscribed yet to any userTopic
int subscribers_init(const char * name, pid_t user_pid){
    int i = 0;
    // means the id was not found  in the subscribers -> first  init
    for(i=0 ; i<MAX_USR ; i++){
        // Look for the first available size
        if(INVALID_PID == subscribers[i].pid_subscriber){
            // assign correct value to pid
            subscribers[i].pid_subscriber =  user_pid;
            // look through its UserTopic to find the name
            int j = 0;
            // means was not found the first time -> first empty
            for(j=0;j<MAX_TOPIC; j++){
                if(INVALID_ID == subscribers[j].userTopic[j].id){
                    char *a = malloc(sizeof(name));
                    strcpy(a,name);
                    subscribers[i].userTopic[j].name = a;
                    subscribers[i].userTopic[j].id = j;
                    // 1-> ok
                    return NEW_REGISTRATION;
                }
            }
        }
    }
    // could not find INVALID_ID
    return INVALID_POSITION;
}

/********* END OF UTILITY METHODS **********/

/********* BEGIN OF CORE METHODS **********/

void lookup() {
    int i = 0;
    for(i= 0; i< MAX_TOPIC;i++){
        if(strcmp("\0",topics.topicArray[i].name) != 0){
            printf("Topic #%d : %s\n",i,topics.topicArray[i].name);
        }
    }
}

/**
 * @Precondition Is into a critical region
 */
bool create_topic(const char * name){
    printf("Topic creation \n");
    if(topicsSize < MAX_TOPIC){
        int i = 0;
        for(i=0; i< MAX_TOPIC; i++) {
            if(strcmp(name, topics.topicArray[i].name) == 0) {
                printf("Topic %s is already in list.\n", name);
                return false;
            }else if(strcmp("\0",topics.topicArray[i].name) == 0){
                printf("Empty find at %d\n", i);
                enter_critical_region_topic(i);
                printf("Setting id.\n");
                topics.topicArray[i].id = i;
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

int topic_publisher(const char * name, pid_t user_pid){
    int j, g;
    Topic  * topic = findTopicByName(name);
    if(topic == NULL){
        printf("Please enter a valid topic name in order to be a publisher\n");
        return INVALID_TOPIC_NAME;
    }else{
        for(j = 0 ; j < MAX_USR ; j++){
            if(publishers[j].pid_publisher == INVALID_PID || publishers[j].pid_publisher == user_pid){
                for(g = 0 ; g < MAX_TOPIC ; g++) {
                    if (strcmp(publishers[j].topicNames[g], "\0") == 0) {
                        printf("j: %d, g: %d\n", j, g);
                        publishers[j].pid_publisher = user_pid;
                        char * topicName = malloc(sizeof(name));
                        strcpy(topicName,name);
                        publishers[j].topicNames[g] = topicName;
                        printf("Publisher OK: %s\n", publishers[j].topicNames[g]);
                        return PUBLISHER_REGISTRED;
                    }
                }
                printf("There is no space available for you to be a publisher for this topic\n");
                return NOT_ENOUGH_SPACE_IN_PUBLISHER_SLOTS;
            }
        }
    }
    return FAIL_TO_REGISTER;
}

bool subscribe_to_topic(const char * name, pid_t user_pid){
    int returnValue = is_ID_set(name,user_pid);
    printf("returnValue is %d\n.",returnValue);
    if(returnValue != INVALID_POSITION)
        return true;
    returnValue  = subscribers_init(name,user_pid);
    printf("returnValue is %d\n.",returnValue);
    if(returnValue != INVALID_POSITION)
        return true;
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
    if(slot == INVALID_POSITION){
        return NO_SLOT_AVAILABLE;
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

int publish_msg_into_topic(const char * topicName, const char * msg, const Publisher * publisher){
    printf("Start publishing message into a userTopic.\n");
    if(userIsRegistredAsPublisher(topicName, publisher)){
        Topic * topic = findTopicByName(topicName);
        enter_critical_region_topic(topic->id);
        int ret = publish_into_all_user_topic(topic->name,msg);
        leave_critical_region_topic(topic->id);
        printf("End of publishing message into a userTopic.\n");
        if(ret >= 0 && ret <MAX_MSG){
            return MSG_PUBLISHED;
        }else{
            return MSG_NOT_PUBLISHED_SLOTS_FULL;
        }
    }else{
        printf("End of publishing message into a userTopic with failure.\n");
        return USR_NOT_REGISTRED_AS_PUBLISHER;
    }
}

char * retrieve_msg_of_topic(const pid_t user_pid, const char * topicName) {
    Topic *topic = findTopicByName(topicName);
    Subscriber * subscriber = findSubscriberByPid(user_pid);
    if (topic != NULL && subscriber != NULL) {
        wait_read_critical_region_topic(topic->id);
        int positionOfTheTopic = findUserTopicPosition(subscriber, topic);
        char *msg = readMessage(&subscriber->userTopic[positionOfTheTopic]);
        int i = 0;
        for(i=0;i<MAX_MSG;i++){
            if(checkAllRetrieved(topic,i)){
                topic->msgSlotAvailable[i] = true;
            }
        }
        return msg;
    } else {
        return NULL;
    }
}

char * readMessage(UserTopic *userTopic){
    int i = 0;
    for(i = 0; i<MAX_MSG ; i++){
        if(userTopic->read[i] == false){
            userTopic->read[i] = true;
            char * msg = malloc(sizeof(userTopic->messageContent[i]));
            strcpy(msg,userTopic->messageContent[i]);
            char * erased = malloc(sizeof("\0"));
            strcpy(erased,"\0");
            userTopic->messageContent[i]= erased;
            return msg;
        }
    }
    return NULL;
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

void printAllPublisher(){
    int i =0;
    for(i=0;i<MAX_USR;i++){
        if(publishers[i].pid_publisher != INVALID_PID){
            publishers[i].toString(&publishers[i]);
        }
    }
}
/********* END OF CORE METHODS **********/

/********* END OF INTERNAL METHODS **********/

/********* BEGIN OF DEBUG METHODS **********/

void toStringData(){
    int i = 0;
    for(i = 0; i<MAX_USR; i++){
        if(subscribers[i].pid_subscriber != INVALID_PID){
            subscribers[i].toString(&subscribers[i]);
        }
        if(publishers[i].pid_publisher != INVALID_PID){
            publishers[i].toString(&publishers[i]);
        }
    }
}

/********* END OF DEBUG METHODS **********/
