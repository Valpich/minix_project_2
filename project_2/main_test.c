//#include "project_2_syst_call.h"
#include "/usr/src/include/project_2_usr_lib.sh"

int main(){

  int operationSelectedNumber;
  char choice;
  char NewTopicName[100];

  int i = 0;
  for(i = 0; i<MAX_USR; i++){
    publisher[i].pid_publisher = -1;
    publisher->topicNames[i] = "";
    publisher->toString = toStringPublisher;
  }

  do{
    printf("\n@@@@@@@@@@@ Welcome @@@@@@@@@@@@@@@@");
    printf("\n1. Create new TOPIC (TopicCreate) ");
    printf("\n2. Show Available Topics (TopicLookup)");
    printf("\n3. Publisher Details");
    printf("\n4. Subscriber Details");
    printf("\n5. Register as Publisher (TopicPublisher)");
    printf("\n6. Register as Subscriber (TopicSubscriber)");
    printf("\n7. Publish Message (Publish)");
    printf("\n8. Receive Message (Retrieve)");
    printf("\n9. Clear Buffer");
    printf("\n Entered choice: ");
    scanf("%d", &operationSelectedNumber);

    switch (operationSelectedNumber) {

      case 1:
        printf("\nTOPIC CREATE\n\n");
        printf("Enter Topic Name: ");
        scanf("%s", NewTopicName);
        if(create_topic(NewTopicName) == true){
          printf("\nTopic created !\n");
        }else{
          printf("\nTopic not created\n");
        }
      break;
      case 2:
        printf("\nTOPIC LOOKUP\n");
        do_topic_lookup();
      break;
      case 3:
        printf("\nPUBLISHER\n");
        do_topic_publisher();
      break;
      case 4:
        printf("\nSUBSCRIBER\n");
      break;
      case 5:
        printf("\nREGISTER PUBLISHER\n");
      break;
      case 6:
        printf("\nREGISTER SUBSCRIBER\n");
      break;
      case 7:
        printf("\nPUBLISH\n");
      break;
      case 8:
        printf("\nRECEIVE\n");
      break;
      case 9:
        printf("\nCLEAR\n");
      break;
      default:
        printf("\nDefault Operation selected\n");

      }

      printf("\n\n@@@@@@@@@@ Continue(y/n) :");
      scanf(" %c",&choice);
    }while(choice=='y');

  return 0;
}
