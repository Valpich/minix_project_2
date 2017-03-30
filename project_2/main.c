#include <project_2_usr_lib.h>

int main (){
    char * a = "aa";
    int ret = 0;
    ret = topic_lookup();
    printf("return is %d\n", ret);
    ret = topic_create(a);
    printf("return is %d\n", ret);
    ret = topic_publisher(a);
    printf("return is %d\n", ret);
    ret = topic_subscriber(a);
    printf("return is %d\n", ret);
    ret = topic_publish(a);
    printf("return is %d\n", ret);
    ret = topic_retrieve();
    printf("return is %d\n", ret);
    return 1;
}
