//#include "project_2_syst_call.h"
#include "project_2_usr_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clean_stdin(){
    while (getchar()!='\n');
    return 1;
}


int main(){
  int operationSelectedNumber;
  char topicName[MAX_TOPIC_NAME];
  char topicContent[MAX_MSG_CONTENT];
  char c;
  do{
    puts("----------- Welcome -----------");
    printf("My pid is: %d.\n",getpid());
    puts("1. Create new TOPIC (TopicCreate)");
    puts("2. Show Available Topics (TopicLookup)");
    puts("3. Register as Publisher (TopicPublisher)");
    puts("4. Register as Subscriber (TopicSubscriber)");
    puts("5. Publisher Details");
    puts("6. Subscriber Details");
    puts("7. Publish Message (Publish)");
    puts("8. Receive Message (Retrieve)");
    puts("9. Clear Buffer");
    puts("9. Exit");
    puts("");
    do{
        puts("Enter your choice:");
    } while (((scanf("%d%c", &operationSelectedNumber, &c)!=2 || c!='\n') && clean_stdin()) || operationSelectedNumber<1 || operationSelectedNumber>9);;
    switch (operationSelectedNumber) {
      case 1:
        puts("TOPIC CREATE");
        puts("Enter Topic Name: ");
        scanf("%[^\n]%*c", topicName);
        if(topic_create(topicName) == DO_TOPIC_CREATE_SUCCESS_RETURN){
          puts("Topic created !");
        }else{
          puts("Topic not created");
        }
      break;
      case 2:
        puts("TOPIC LOOKUP");
        topic_lookup();
      break;
      case 3:
        puts("REGISTER AS PUBLISHER");
        topic_lookup();
        puts("Enter the Topic you want to be register as a publisher:");
        scanf("%[^\n]%*c", topicName);
        topic_publisher(topicName);
      break;
      case 4:
        puts("REGISTER AS SUBSCRIBER");
        topic_lookup();
        puts("Enter the Topic you want to be register as a subscriber:");
        scanf("%[^\n]%*c", topicName);
        topic_subscriber(topicName);
      break;
      case 5:
        puts("PUBLISHER DETAILS");
        print_all_publishers();
      break;
      case 6:
        puts("SUBSCRIBER DETAILS");
        print_all_subscribers();
      break;
      case 7:
        puts("PUBLISH");
        topic_lookup();
        puts("Enter the Topic you want to publish into:");
        scanf("%[^\n]%*c", topicName);
        puts("Enter the Content of your topic (max. 100 char):");
        scanf("%[^\n]%*c", topicContent);
        topic_publish(topicName, topicContent);
      break;
      case 8:
        puts("RETRIEVE");
        topic_lookup();
        puts("Enter the Topic you want to be retrieve a message:");
        scanf("%[^\n]%*c", topicName);;
        topic_retrieve(topicName);
      break;
      case 9:
        puts("CLEAR");
        topic_lookup();
        puts("Enter the Topic you want to delete! This may result");
        scanf("%[^\n]%*c", topicName);
        topic_delete(topicName);
      break;
        case 10:
        exit(0);
      default:
        puts("Default Operation selected");
        break;
      }
    }while(1);
  return 0;
}

// UNUSED, The aim was to test each functionnality at the benning
#ifdef OLD_TEST
int test1(){
    doInit();
    create_topic("a");
    create_topic("b");
    create_topic("c");
    create_topic("d");
    create_topic("e");
    create_topic("f");
    create_topic("g");
    create_topic("h");
    create_topic("i");
    create_topic("full");
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

#endif
