#include <project_2_usr_lib.h>

int main (){
    char * a = "aa";
    int ret = 0;
    ret = topic_lookup();
    printf("return is %d", ret);
    return 1;
}
