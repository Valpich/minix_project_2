#include "project_2_syst_call.h"

int test1(){
    doInit();
    create_topic("Salut");
    create_topic("aude");
    create_topic("sale");
    create_topic("pute");
    create_topic("tu");
    create_topic("es");
    create_topic("vraiment");
    create_topic("trop");
    create_topic("pleine");
    create_topic("!");
    create_topic("Fail");
    delete_topic("!");
    create_topic("Fail");
    create_topic("Fail2");
}

int test2(){
    UserTopic userTopic = {.id = getpid(),.messageContent = {[0 ... MAX_MSG-1] = "\0"},.name="\0",.read = {[0 ... MAX_MSG-1] = true}, .toString=toStringUserTopic};
    userTopic.toString(&userTopic);
    publish_into_user_topic(&userTopic, "Hi", 3);
    userTopic.toString(&userTopic);
}

int test3(){
    Publisher publisher;
    publisher.pid_publisher= getpid();
    int j = 0;
    for(j = 0; j<MAX_TOPIC; j++){
        char * name = malloc(sizeof("\0"));
        strcpy(name,"\0");
        publisher.topicNames[j] = name;
    }
    publisher.toString = toStringPublisher;
    int ret = publish_msg_into_topic("Hi", "Hello",&publisher);
    printf("ret is %d.",ret);
}

int test4(){
    doInit();
    Publisher publisher;
    publisher.pid_publisher= getpid();
    int j = 0;
    for(j = 0; j<MAX_TOPIC; j++){
        char * name = malloc(sizeof("\0"));
        strcpy(name,"\0");
        publisher.topicNames[j] = name;
    }
    publisher.toString = toStringPublisher;
    create_topic("Hi");
    int retour = subscribe_to_topic("Hi",getpid());
    printf("retour subscribe is %d.\n",retour);
    int result = topic_publisher("Hi", getpid());
    printf("retour publisher is %d.\n",result);
    int ret = publish_msg_into_topic("Hi", "Hello",&publisher);
    printf("ret publish is %d.\n",ret);
    ret = publish_msg_into_topic("Hi", "You",&publisher);
    printf("ret publish is %d.\n",ret);
    ret = publish_msg_into_topic("Hi", "!",&publisher);
    printf("ret publish is %d.\n",ret);
    ret = publish_msg_into_topic("Hi", "Stop",&publisher);
    printf("ret publish is %d.\n",ret);
    ret = publish_msg_into_topic("Hi", "Please",&publisher);
    printf("ret publish is %d.\n",ret);
    ret = publish_msg_into_topic("Hi", "Full",&publisher);
    printf("ret publish is %d.\n",ret);
    char * msg = retrieve_msg_of_topic(getpid(),"Hi");
    printf("message retrieved is %s.\n",msg);
    ret = publish_msg_into_topic("Hi", "Full",&publisher);
    printf("ret publish is %d.\n",ret);
    msg = retrieve_msg_of_topic(getpid(),"Hi");
    printf("message retrieved is %s.\n",msg);
    msg = retrieve_msg_of_topic(getpid(),"Hi");
    printf("message retrieved is %s.\n",msg);
    printAllPublisher();
}

int main() {
    test4();
    return 0;
}
