//#include "project_2_syst_call.h"
#include "project_2_usr_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int operationSelectedNumber;
  char topicName[MAX_TOPIC_NAME];
  char topicContent[MAX_MSG_CONTENT];
  char c;
  do{
    puts("----------- Welcome -----------");
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
    } while (((scanf("%d%c", &operationSelectedNumber, &c)!=2 || c!='\n')) || operationSelectedNumber<1 || operationSelectedNumber>10);
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
