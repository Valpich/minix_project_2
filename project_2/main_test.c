//#include "project_2_syst_call.h"
#include "project_2_usr_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int continueProgram(){
    char choice;
    int resultYes;
    int resultNo;
    char c;
    do {
        puts("----------- Continue(y/n) :");
        c = getchar();
        resultYes = c == 'y' ? 1 : 0;
        resultNo = c == 'n' ? 1 : 0;
    }while(!(resultYes == 1 || resultNo == 1));
    return resultYes == 1 ? 1 : 0;
}

int main(){
  int operationSelectedNumber;
  char topicName[MAX_TOPIC_NAME];
  char topicContent[MAX_MSG_CONTENT];
  int continueResult = 1;
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
    puts("");
    do{
        puts("Enter your choice:");
    } while (((scanf("%d%c", &operationSelectedNumber, &c)!=2 || c!='\n')) || operationSelectedNumber<1 || operationSelectedNumber>9);
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
        continueResult = continueProgram();
      break;
      case 2:
        puts("TOPIC LOOKUP");
        topic_lookup();
        continueResult = continueProgram();
      break;
      case 3:
        puts("REGISTER AS PUBLISHER");
        topic_lookup();
        puts("Enter the Topic you want to be register as a publisher:");
        scanf("%[^\n]%*c", topicName);
        topic_publisher(topicName);
        continueResult = continueProgram();
      break;
      case 4:
        puts("REGISTER AS SUBSCRIBER");
        topic_lookup();
        puts("Enter the Topic you want to be register as a subscriber:");
        scanf("%[^\n]%*c", topicName);
        topic_subscriber(topicName);
        continueResult = continueProgram();
      break;
      case 5:
        puts("PUBLISHER DETAILS");
        continueResult = continueProgram();
      break;
      case 6:
        puts("SUBSCRIBER DETAILS");
        continueResult = continueProgram();
      break;
      case 7:
        puts("PUBLISH");
        topic_lookup();
        puts("Enter the Topic you want to publish into:");
        scanf("%[^\n]%*c", topicName);
        puts("Enter the Content of your topic (max. 100 char):");
        scanf("%[^\n]%*c", topicContent);
        topic_publish(topicName, topicContent);
        continueResult = continueProgram();
      break;
      case 8:
        puts("RETRIEVE");
        topic_lookup();
        puts("Enter the Topic you want to be retrieve a message:");
        scanf("%[^\n]%*c", topicName);;
        topic_retrieve(topicName);
        continueResult = continueProgram();
      break;
      case 9:
        puts("CLEAR");
        topic_lookup();
        topic_lookup();
        puts("Enter the Topic you want to delete! This may result");
        scanf("%[^\n]%*c", topicName);;
        continueResult = continueProgram();
      break;
      default:
        puts("Default Operation selected");
        break;
      }
    }while(continueResult == 1);
  return 0;
}
