//
// Created by Administrator on 2017/1/13.
//
#include "Test.h"
#include <string.h>
#include <stdio.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "Sgin.h"

#include <android/log.h>
#define  LOG_TAG    "test"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

/**
 *这个key是和服务器之间通信的秘钥
 */
const char* AUTH_KEY = "服务器通信秘钥";

/**
 * 发布的app 签名,只有和本签名一致的app 才会返回 AUTH_KEY
 * 这个RELEASE_SIGN的值是上一步用java代码获取的值
 */
const char* RELEASE_SIGN = "65:5A:13:62:17:24:EB:0B:C6:3D:72:B1:77:FA:13:17:8D:56:D0:4E";

/**
 * 发布的app 签名 的HashCode
 */
const int RELEASE_SIGN_HASHCODE = -332752192;



#if(JUDGE_THUMB)
#define GETPC_KILL_IDAF5_SKATEBOARD \
__asm __volatile( \
"mov r0,pc \n\t" \
"adds r0,0x9 \n\t" \
"push {r0} \n\t" \
"pop {r0} \n\t" \
"bx r0 \n\t" \
\
".byte 0x00 \n\t" \
".byte 0xBF \n\t" \
\
".byte 0x00 \n\t" \
".byte 0xBF \n\t" \
\
".byte 0x00 \n\t" \
".byte 0xBF \n\t" \
:::"r0" \
);
#else
#define GETPC_KILL_IDAF5_SKATEBOARD \
__asm __volatile( \
"mov r0,pc \n\t" \
"add r0,0x10 \n\t" \
"push {r0} \n\t" \
"pop {r0} \n\t" \
"bx r0 \n\t" \
".int 0xE1A00000 \n\t" \
".int 0xE1A00000 \n\t" \
".int 0xE1A00000 \n\t" \
".int 0xE1A00000 \n\t" \
:::"r0" \
);
#endif
// 常量标签版本
#if(JUDGE_THUMB)
#define IDAF5_CONST_1_2 \
__asm __volatile( \
"b T1 \n\t" \
"T2: \n\t" \
"adds r0,1 \n\t" \
"bx r0 \n\t" \
"T1: \n\t" \
"mov r0,pc \n\t" \
"b T2 \n\t" \
:::"r0" \
);
#else
#define IDAF5_CONST_1_2 \
__asm __volatile( \
"b T1 \n\t" \
"T2: \n\t" \
"bx r0 \n\t" \
"T1: \n\t" \
"mov r0,pc \n\t" \
"b T2 \n\t" \
:::"r0" \
);
#endif




JNIEXPORT void JNICALL Java_com_umeng_soexample_JNITest_getSuccessKey //

        (JNIEnv *env, jclass jclazz){


	//sleep(3000);//暂停3秒  S要大写
    LOGD("%s ", getSgin());

    int i = 5;
    int j = 5;
    int test = i + j;


    //env->DeleteLocalRef(result);
    //env->DeleteLocalRef(methodId);
    //env->DeleteLocalRef(clazz);
}


//反调试方法一 ：一个进程最多只能被一个进程ptrace 自己调试自己
void anit_debug1()
{
    //ptrace(PTRACE_TRACEME,0,0,0);

	// 常量标签版本

	__asm __volatile( \
	"mov r0,pc \n\t" \
	"add r0,0x10 \n\t" \
	"push {r0} \n\t" \
	"pop {r0} \n\t" \
	"bx r0 \n\t" \
	".int 0xE1A00000 \n\t" \
	".int 0xE1A00000 \n\t" \
	".int 0xE1A00000 \n\t" \
	".int 0xE1A00000 \n\t" \
	:::"r0" \
	);

    int iRet=ptrace(PTRACE_TRACEME, 0, 0, 0);
    if(-1 == iRet)
    {
           LOGD("ptrace失败，进程正在被调试\n");
           //return;
    }
    else
    {
           LOGD("ptrace的返回值为:%d\n",iRet);
           //return;
    }


}

//反调试方法一 ：检测Tracerpid的值  只要TtracerPid的值不等于0 表示正在被调试
void anit_debug2()
{

        const int bufsize = 1024;
        char filename[bufsize];
        char line[bufsize];
        int pid = getpid();
        sprintf(filename,"/proc/%d/status",pid);
        FILE* fd = fopen(filename,"r");
        if(fd != NULL)
        {
        	while(fgets(line,bufsize,fd)) //读取每一行
        	{
        		if( strncmp(line,"TtracerPid",9) == 0 ) //比較两个字符串前n位 如果是TtracerPid
        		{
        			int status = atoi(&line[10]);
        			if( status != 0 )
        			{
        				fclose(fd);
        				int ret = kill(pid,SIGKILL);
        			}
        			break;
        		}
        	}
        }


}


//第三种:检测android_server端口号 默认是  23946 5D8A
void anit_debug3()
{
	 const int bufsize = 512;
	 char filename[bufsize];
	 char line[bufsize];
	 int pid = getpid();
	 sprintf(filename,"/proc/net/tcp");

	 FILE* fd = fopen(filename,"r");
	 if(fd != NULL)
	 {
		 	while(fgets(line,bufsize,fd)) //读取每一行
		    {
		 		if( strncmp(line,"5D8A",4) == 0 )
		 		 {
		 				int ret = kill(pid,SIGKILL);
		 		 }
		    }
	 }
}

//第四种:调试时候代码执行时间差异检测
void anit_debug4()
{
	int pid  =  getpid();
	struct  timeval    t1;
	struct  timeval    t2;
	struct  timezone   tz;
	gettimeofday(&t1,&tz);
	gettimeofday(&t2,&tz);

	int timeoff = ( t2.tv_sec ) - ( t1.tv_sec );
	if ( timeoff > 1)
	{
		int ret = kill(pid,SIGKILL);
	}

}

void anit_debug5(int ppid)
{

	char buf[256],readbuf[1024];
	int pid,wd,ret,len,i;
	int fd;
	fd_set readfds;


	//防止调试子进程
	ptrace(PTRACE_TRACEME,0,0,0);
	fd=  inotify_init();
	sprintf(buf,"/proc/%d/maps",ppid);

	//wd = inotify_add_watch(fd, "/proc/self/mem", IN_ALL_EVENTS);
	wd=inotify_add_watch(fd,buf,IN_ALL_EVENTS);
	if(wd<0){
		LOGD("can't watch %s",buf);
		return;
	}

	while(1){
		i=0;

		//注意要对fd_set进行初始化
		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);
		//第一个参数固定要+1，第二个参数是读的fdset，第三个是写的fdset，最后一个是等待的时间
		//最后一个为NULL则为阻塞
		ret = select(fd+1,&readfds,0,0,0);
		if(ret==-1)
		{
			break;
		}

		if(ret)
		{
			len=read(fd,readbuf,2048);
			while(i<len)
			{

				//返回的buf中可能存了多个inotify_event
				struct inotify_event *event=(struct inotify_event*)&readbuf[i];
				LOGD("event mask %d\n",(event->mask&IN_ACCESS)||(event->mask&IN_OPEN));
				//这里监控读和打开事件
				if((event->mask&IN_ACCESS)||(event->mask&IN_OPEN))
				{
					LOGD("kill!!!!!\n");
					//事件出现则杀死父进程
					//int ret=kill(ppid,SIGKILL);
					//LOGD("ret = %d",ret);
					return;
				}
					i+=sizeof(struct inotify_event)+event->len;
		     }
	     }
	}

	inotify_rm_watch(fd,wd);
	close(fd);
}


void myhandler(int sig)
{
	//signal(5, myhandler);
	printf("myhandler.\n");
	return;
}
int g_ret = 0;

void ani_test6()
{
	// 设置SIGTRAP信号的处理函数为myhandler()
	g_ret = (int)signal(SIGTRAP, myhandler);
	if ( (int)SIG_ERR == g_ret )
	{
		printf("signal ret value is SIG_ERR.\n");
	}

	// 打印signal的返回值(原处理函数地址)
	printf("signal ret value is %x\n",(unsigned char*)g_ret);
	// 主动给自己进程发送SIGTRAP信号
	raise(SIGTRAP);
	raise(SIGTRAP);
	raise(SIGTRAP);
	kill(getpid(), SIGTRAP);
}


void sub_0329(JNIEnv* env)
{
	    jclass clazz = NULL;
	    clazz = env->FindClass("com/umeng/soexample/MainActivity");
		    if (clazz == NULL) {
		        printf("找不到'com.umeng.soexample.MainActivity'这个类");
		        return;
		    }

		//参数列表：反射类，方法名称，方法签名
		jmethodID methodId = env->GetStaticMethodID(clazz, "getCertificateSHA1Fingerprint","()Ljava/lang/String;");

		//调用方法,CallStaticObjectMethod第一个参数是反射类名
		jstring result = (jstring) env->CallStaticObjectMethod(clazz, methodId);
	    char *c_msg = (char*)env->GetStringUTFChars(result,0);
	    LOGD("sgin  %s ",c_msg);
	    if(strcmp(c_msg,RELEASE_SIGN)==0)//签名一致  返回合法的 api key，否则返回错误
	    {
	    	LOGD("sgin suc");
	    }else
	    {
	    	LOGD("sgin fail");
	    	//LOGD(0)
	    }
}

jint JNI_OnLoad(JavaVM* vm, void* reserved){
	LOGD("in Jni_OnLoad ");

	anit_debug1();
	//anit_debug2();
	//anit_debug3();
	int pid  =  getpid();
	//LOGD("in Jni_OnLoad %d",pid);

	anit_debug2();
    JNIEnv* env;
    if ( vm->GetEnv( reinterpret_cast<void**>(&env), JNI_VERSION_1_6 ) != JNI_OK )
    {
    	return -1;
    }
    sub_0329(env);
    return JNI_VERSION_1_6;
}


