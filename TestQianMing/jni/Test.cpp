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
 *���key�Ǻͷ�����֮��ͨ�ŵ���Կ
 */
const char* AUTH_KEY = "������ͨ����Կ";

/**
 * ������app ǩ��,ֻ�кͱ�ǩ��һ�µ�app �Ż᷵�� AUTH_KEY
 * ���RELEASE_SIGN��ֵ����һ����java�����ȡ��ֵ
 */
const char* RELEASE_SIGN = "65:5A:13:62:17:24:EB:0B:C6:3D:72:B1:77:FA:13:17:8D:56:D0:4E";

/**
 * ������app ǩ�� ��HashCode
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
// ������ǩ�汾
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


	//sleep(3000);//��ͣ3��  SҪ��д
    LOGD("%s ", getSgin());

    int i = 5;
    int j = 5;
    int test = i + j;


    //env->DeleteLocalRef(result);
    //env->DeleteLocalRef(methodId);
    //env->DeleteLocalRef(clazz);
}


//�����Է���һ ��һ���������ֻ�ܱ�һ������ptrace �Լ������Լ�
void anit_debug1()
{
    //ptrace(PTRACE_TRACEME,0,0,0);

	// ������ǩ�汾

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
           LOGD("ptraceʧ�ܣ��������ڱ�����\n");
           //return;
    }
    else
    {
           LOGD("ptrace�ķ���ֵΪ:%d\n",iRet);
           //return;
    }


}

//�����Է���һ �����Tracerpid��ֵ  ֻҪTtracerPid��ֵ������0 ��ʾ���ڱ�����
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
        	while(fgets(line,bufsize,fd)) //��ȡÿһ��
        	{
        		if( strncmp(line,"TtracerPid",9) == 0 ) //���^�����ַ���ǰnλ �����TtracerPid
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


//������:���android_server�˿ں� Ĭ����  23946 5D8A
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
		 	while(fgets(line,bufsize,fd)) //��ȡÿһ��
		    {
		 		if( strncmp(line,"5D8A",4) == 0 )
		 		 {
		 				int ret = kill(pid,SIGKILL);
		 		 }
		    }
	 }
}

//������:����ʱ�����ִ��ʱ�������
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


	//��ֹ�����ӽ���
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

		//ע��Ҫ��fd_set���г�ʼ��
		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);
		//��һ�������̶�Ҫ+1���ڶ��������Ƕ���fdset����������д��fdset�����һ���ǵȴ���ʱ��
		//���һ��ΪNULL��Ϊ����
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

				//���ص�buf�п��ܴ��˶��inotify_event
				struct inotify_event *event=(struct inotify_event*)&readbuf[i];
				LOGD("event mask %d\n",(event->mask&IN_ACCESS)||(event->mask&IN_OPEN));
				//�����ض��ʹ��¼�
				if((event->mask&IN_ACCESS)||(event->mask&IN_OPEN))
				{
					LOGD("kill!!!!!\n");
					//�¼�������ɱ��������
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
	// ����SIGTRAP�źŵĴ�����Ϊmyhandler()
	g_ret = (int)signal(SIGTRAP, myhandler);
	if ( (int)SIG_ERR == g_ret )
	{
		printf("signal ret value is SIG_ERR.\n");
	}

	// ��ӡsignal�ķ���ֵ(ԭ��������ַ)
	printf("signal ret value is %x\n",(unsigned char*)g_ret);
	// �������Լ����̷���SIGTRAP�ź�
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
		        printf("�Ҳ���'com.umeng.soexample.MainActivity'�����");
		        return;
		    }

		//�����б������࣬�������ƣ�����ǩ��
		jmethodID methodId = env->GetStaticMethodID(clazz, "getCertificateSHA1Fingerprint","()Ljava/lang/String;");

		//���÷���,CallStaticObjectMethod��һ�������Ƿ�������
		jstring result = (jstring) env->CallStaticObjectMethod(clazz, methodId);
	    char *c_msg = (char*)env->GetStringUTFChars(result,0);
	    LOGD("sgin  %s ",c_msg);
	    if(strcmp(c_msg,RELEASE_SIGN)==0)//ǩ��һ��  ���غϷ��� api key�����򷵻ش���
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


