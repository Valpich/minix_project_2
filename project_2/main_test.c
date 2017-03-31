//#include "project_2_syst_call.h"
#include "project_2_usr_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clean_stdin(){
    while (getchar()!='\n');
    return 1;
}

int continueProgram(){
    char choice;
    int resultYes;
    int resultNo;
    do {
        clean_stdin();
        puts("----------- Continue(y/n) :");
        c = getchar();
        resultYes = c == 'y' ? 1 : 0;
        resultNo = c == 'n' ? 1 : 0;
    }while(!(resultYes == 1 || resultNo == 1));
    return resultYes == 1 ? 1 : 0;
}

int main(){

  int operationSelectedNumber;
  char TopicName[100];
  char TopicContent[100];
  int continueResult = 1;
  do{
    printf("\n----------- Welcome -----------");
    printf("\n1. Create new TOPIC (TopicCreate)");
    printf("\n2. Show Available Topics (TopicLookup)");
    printf("\n3. Register as Publisher (TopicPublisher)");
    printf("\n4. Register as Subscriber (TopicSubscriber)");
    printf("\n5. Publisher Details");
    printf("\n6. Subscriber Details");
    printf("\n7. Publish Message (Publish)");
    printf("\n8. Receive Message (Retrieve)");
    printf("\n9. Clear Buffer");
    puts("");
    char c;
    do{
        puts("Enter your choice:");
    } while (((scanf("%d%c", &operationSelectedNumber, &c)!=2 || c!='\n') && clean_stdin()) || operationSelectedNumber<1 || operationSelectedNumber>9);
    switch (operationSelectedNumber) {
      case 1:
        printf("\nTOPIC CREATE\n");
        printf("Enter Topic Name: ");
        scanf("%s", TopicName);
        if(topic_create(TopicName) == DO_TOPIC_CREATE_SUCCESS_RETURN){
          printf("\nTopic created !\n");
        }else{
          printf("\nTopic not created\n");
        }
        continueResult = continueProgram();
      break;
      case 2:
        printf("\nTOPIC LOOKUP\n");
        topic_lookup();
        continueResult = continueProgram();
      break;
      case 3:
        printf("\nREGISTER AS PUBLISHER\n");
        topic_lookup();
        printf("Enter the Topic you want to be register as a publisher: \n");
        scanf("%s",TopicName);
        topic_publisher(TopicName);
        continueResult = continueProgram();
      break;
      case 4:
        printf("\nREGISTER AS SUBSCRIBER\n");
        topic_lookup();
        printf("Enter the Topic you want to be register as a subscriber: \n");
        puts("");
        scanf("%s",TopicName);
        topic_subscriber(TopicName);
        continueResult = continueProgram();
      break;
      case 5:
        printf("\nPUBLISHER DETAILS\n");
        continueResult = continueProgram();
      break;
      case 6:
        printf("\nSUBSCRIBER DETAILS\n");
        continueResult = continueProgram();
      break;
      case 7:
        printf("\nPUBLISH\n");
        topic_lookup();
        printf("Enter the Topic you want to publish into:");
        scanf("%s", TopicName);
        printf("Enter the Content of your topic (max. 100 char): ");
        scanf("%s", TopicContent);
        topic_publish(TopicName, TopicContent);
        continueResult = continueProgram();
      break;
      case 8:
        printf("\nRECEIVE\n");
        topic_retrieve();
        continueResult = continueProgram();
      break;
      case 9:
        printf("\nCLEAR\n");
        continueResult = continueProgram();
      break;
      default:
        printf("\nDefault Operation selected\n");
        break;
      }
    }while(continueResult == 1);
  return 0;
}
