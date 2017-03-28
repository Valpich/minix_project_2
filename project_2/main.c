#include <project_2_usr_lib.h>

int main (){
    char * a = "aa";
    int ret = 0;
    ret = topic_lookup();
    printf("return is %d", ret);
    ret = topic_create();
    printf("return is %d", ret);
    ret = topic_publisher();
    printf("return is %d", ret);
    ret = topic_subscriber();
    printf("return is %d", ret);
    ret = topic_publish();
    printf("return is %d", ret);
    ret = topic_retrieve();
    printf("return is %d", ret);
    return 1;
}
