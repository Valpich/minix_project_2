//#include "project_2_syst_call.h"
#include "project_2_usr_lib.h"

int main(){

  int operationSelectedNumber;
  char choice;
  char TopicName[100];
  char TopicContent[100];

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
    printf("\n Enter your choice: ");
    scanf("%d", &operationSelectedNumber);

    switch (operationSelectedNumber) {

      case 1:
        printf("\nTOPIC CREATE\n");
        printf("Enter Topic Name: ");
        scanf("%s", TopicName);
        if(topic_create(TopicName) == 1){
          printf("\nTopic created !\n");
        }else{
          printf("\nTopic not created\n");
        }
      break;
      case 2:
        printf("\nTOPIC LOOKUP\n");
        topic_lookup();
      break;
      case 3:
        printf("\nREGISTER AS PUBLISHER\n");
        topic_lookup();
        printf("Enter the Topic you want to be register as a publisher: ");
        scanf("%s\n",TopicName);
        topic_publisher(TopicName);
      break;
      case 4:
        printf("\nREGISTER AS SUBSCRIBER\n");
        topic_lookup();
        printf("Enter the Topic you want to be register as a subscriber: ");
        scanf("%s\n",TopicName);
        topic_subscriber(TopicName);
      break;
      case 5:
        printf("\nPUBLISHER DETAILS\n");
      break;
      case 6:
        printf("\nSUBSCRIBER DETAILS\n");
      break;
      case 7:
        printf("\nPUBLISH\n");
        topic_lookup();
        printf("Enter the Topic you want to publish into:");
        scanf("%s\n", TopicName);
        printf("Enter the Content of your topic (max. 100 char): ");
        scanf("%s\n", TopicContent);
        topic_publish(TopicName, TopicContent);
      break;
      case 8:
        printf("\nRECEIVE\n");
        topic_retrieve();
      break;
      case 9:
        printf("\nCLEAR\n");
      break;
      default:
        printf("\nDefault Operation selected\n");
      }

      printf("\n\n----------- Continue(y/n) :");
      scanf(" %c",&choice);
    }while(choice=='y');

  return 0;
}
