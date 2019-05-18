package com.umeng.soexample;

/**
 * Created by Administrator on 2017/1/12.
 *
 */

public class JNITest {
    static{
        
        System.loadLibrary("test");
    }
    public static native void getSuccessKey();
    public static String getKey()
    {
		return null;
    	
    }
}





