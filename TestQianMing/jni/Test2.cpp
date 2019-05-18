#include <stdlib.h>
#include <string>

void test2()
{
	char buf[16] = {0};
	sprintf(buf, "mgwl$flfffffy_%c",'p');

    std::string strKey = buf; //mgwl$fly_p
    char filename[1024];
    sprintf(filename,"/proc/%d/status",123);
}
