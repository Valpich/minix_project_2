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
    publish_into_all_user_topic("Hi", "Hello");
}

int test4(){
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

int test5(){
    int retour;
    retour = subscribe_to_topic("aaa",3);


}

int main() {
    test5();
    return 0;
}
