package com.umeng.soexample;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Method;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.umeng.soexample.R;
import com.umeng.commonsdk.UMConfigure;
import com.umeng.socialize.PlatformConfig;
import com.umeng.socialize.ShareAction;
import com.umeng.socialize.UMShareListener;
import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.media.UMImage;


public class MainActivity extends Activity {

    static private MainActivity instance = null;
    public String zzz = "B1:A3:50:10:AC:CA:3B:03:36:B4:2A:99:29:9A:E8:AD:85:57:EA:3A";
    private static final int BITS_PER_UNIT = 8;
    public static native void getSuccessKey();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        
        
        
        //UMConfigure.init(this,"5a12384aa40fa3551f0001d1"
        //        ,"umeng",UMConfigure.DEVICE_TYPE_PHONE,"");//58edcfeb310c93091c000be2 5965ee00734be40b580001a0
        
        //PlatformConfig.setTwitter("3aIN7fuF685MuZ7jtXkQxalyi", "MK6FEYG63eWcpDFgRYw4w9puJhzDl0tyuqWjZ3M7XJuuG7mMbO");
        //PlatformConfig.set ("3aIN7fuF685MuZ7jtXkQxalyi", "MK6FEYG63eWcpDFgRYw4w9puJhzDl0tyuqWjZ3M7XJuuG7mMbO");
    
        instance = this;
        
        Log.e("SHA1Fingerprint ", "Msg = " + getCertificateSHA1Fingerprint());
         
        if (zzz.equals(getCertificateSHA1Fingerprint()))
        { 
        	Log.e("JavaValidateSign ", "验证成功 ") ;
        	Toast.makeText(MainActivity.this,"验证成功",Toast.LENGTH_LONG).show();
        	
        }else
        {
        	 Log.e("JavaValidateSign ", "验证失败" );
        	 Toast.makeText(MainActivity.this,"验证失败",Toast.LENGTH_LONG).show();
        }
        
        
        
        JNITest.getSuccessKey();
        
        isApkInDebug(this);
        isEmulator(this);
        position(3); 
    }

    
    public void shareFacebook(View view){
    	
    	 UMImage imagelocal = new UMImage(this, R.drawable.logo);
         imagelocal.setThumb(new UMImage(this, R.drawable.thumb));
         new ShareAction(MainActivity.this).withMedia(imagelocal )
             .setPlatform(SHARE_MEDIA.FACEBOOK)
             .setCallback(umShareListener).share();
    	
    }
    

    private UMShareListener umShareListener = new UMShareListener() {
           /**
            * @descrption 分享开始的回调
            * @param platform 平台类型
            */
           @Override
           public void onStart(SHARE_MEDIA platform) {

           }

           /**
            * @descrption 分享成功的回调
            * @param platform 平台类型
            */
           @Override
           public void onResult(SHARE_MEDIA platform) {
               Toast.makeText(MainActivity.this,"成功                                        了",Toast.LENGTH_LONG).show();
           }

           /**
            * @descrption 分享失败的回调
            * @param platform 平台类型
            * @param t 错误原因
            */
           @Override
           public void onError(SHARE_MEDIA platform, Throwable t) {
               Toast.makeText(MainActivity.this,"失                                            败"+t.getMessage(),Toast.LENGTH_LONG).show();
           }

           /**
            * @descrption 分享取消的回调
            * @param platform 平台类型
            */
           @Override
           public void onCancel(SHARE_MEDIA platform) {
               Toast.makeText(MainActivity.this,"取消                                          了",Toast.LENGTH_LONG).show();

           }
       };
       
       
   	public static MainActivity getInstance()
   	{
   		
   		return instance;
   	}
       
   	/**
         * 判断当前应用是否是debug状态
         */
     
     public void isApkInDebug(Context context) 
     {
      
        ApplicationInfo info = context.getApplicationInfo();                           
        if ((info.flags & ApplicationInfo.FLAG_DEBUGGABLE) != 0)
        {
        	Toast.makeText(MainActivity.this,"应用在调试模式",Toast.LENGTH_SHORT).show();   	
        }
        else{
        	Toast.makeText(MainActivity.this,"应用不在调试模式",Toast.LENGTH_SHORT).show();   	
        }

     }
     
     public void isApkInDebug() 
     {
         if (android.os.Debug.isDebuggerConnected()) {	//检测调试器
          	Log.e("com.droider.antidebug", "检测到测试器");
          	android.os.Process.killProcess(android.os.Process.myPid());
          }       
          
     }
     

     //对抗dex2jar
     private int position(int idx) { // bits big-endian in each unit
         return 1 << (BITS_PER_UNIT - 1 - (idx % BITS_PER_UNIT));        
     }
   	
     

   //判断当前设备是否是模拟器1。如果返回TRUE，则当前是模拟器，不是返回FALSE
   public  boolean isEmulator(Context context){
	   try{
		   TelephonyManager tm = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
		   String imei = tm.getDeviceId();
		   if (imei != null && imei.equals("000000000000000")){
			   Toast.makeText(MainActivity.this,"应用在模拟器运行1",Toast.LENGTH_SHORT).show();   	
			   return true;
		   
	       }
		   if (Build.MODEL.equals("sdk") || (Build.MODEL.equals("google_sdk")) ) 
		   {
			   Toast.makeText(MainActivity.this,"应用在模拟器运行2",Toast.LENGTH_SHORT).show();   	
			   return true;
		   }
		   
	   }catch (Exception ioe) {
	
	   }
	   Toast.makeText(MainActivity.this,"应用不在模拟器运行",Toast.LENGTH_SHORT).show();   	
	   return false;
   }
   	
   
   //判断当前设备是否是模拟器2。如果返回TRUE，则当前是模拟器，不是返回FALSE
   boolean isRunningInEmualtor() {
   	boolean qemuKernel = false;
   	Process process = null;
       DataOutputStream os = null;
       try{  
           process = Runtime.getRuntime().exec("getprop ro.kernel.qemu");  
           os = new DataOutputStream(process.getOutputStream());
           BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream(),"GBK"));
           os.writeBytes("exit\n");  
           os.flush();
           process.waitFor();
           qemuKernel = (Integer.valueOf(in.readLine()) == 1);
           Log.d("com.droider.checkqemu", "检测到模拟器:" + qemuKernel);             
       } catch (Exception e){  
       	qemuKernel = false;
           Log.d("com.droider.checkqemu", "run failed" + e.getMessage()); 
       } finally {
           try{  
               if (os != null) {  
                   os.close();  
               }  
               process.destroy();  
           } catch (Exception e) {
           	
           }  
           Log.d("com.droider.checkqemu", "run finally"); 
       }
       return qemuKernel;
   }
   
   public static String getProp(Context context, String property) {
   	try {
   		ClassLoader cl = context.getClassLoader();
   		Class SystemProperties = cl.loadClass("android.os.SystemProperties");
   		Method method = SystemProperties.getMethod("get", String.class);
   		Object[] params = new Object[1];
   		params[0] = new String(property);
   		return (String)method.invoke(SystemProperties, params);
   	} catch (Exception e) {
   		return null;
   	}
   }
   	
   //对classes.dex进行校验
   private boolean checkCRC() {
   	boolean beModified = false;
   	long crc = Long.parseLong(getString(597918297));
   	ZipFile zf;
		try {
			zf = new ZipFile(getApplicationContext().getPackageCodePath());
	    	ZipEntry ze = zf.getEntry("classes.dex");
	    	Log.d("com.droider.checkcrc", String.valueOf(ze.getCrc()));
	    	if (ze.getCrc() == crc) {
	    		beModified = true;
	    	} 
		} catch (IOException e) {
			e.printStackTrace();
			beModified = false;
		}
		return beModified;
   } 


       
    public static String getCertificateSHA1Fingerprint() {
               //获取包管理器
   			PackageManager pm = instance.getPackageManager();
   			//获取当前要获取SHA1值的包名，也可以用其他的包名，但需要注意，
   			//在用其他包名的前提是，此方法传递的参数Context应该是对应包的上下文。
   			String packageName = instance.getPackageName();
   			//返回包括在包中的签名信息
   			int flags = PackageManager.GET_SIGNATURES;
   			PackageInfo packageInfo = null;
   			try {
   			    //获得包的所有内容信息类
   				packageInfo = pm.getPackageInfo(packageName, flags);
   			} catch (PackageManager.NameNotFoundException e) {
   				e.printStackTrace();
   			}
   			 //签名信息
   			Signature[] signatures = packageInfo.signatures;
   			byte[] cert = signatures[0].toByteArray();
   			 //将签名转换为字节数组流
   			InputStream input = new ByteArrayInputStream(cert);
   			//证书工厂类，这个类实现了出厂合格证算法的功能
   			CertificateFactory cf = null;
   			try {
   				cf = CertificateFactory.getInstance("X509");
   			} catch (CertificateException e) {
   				e.printStackTrace();
   			}
   			//X509证书，X.509是一种非常通用的证书格式
   			X509Certificate c = null;
   			try {
   				c = (X509Certificate) cf.generateCertificate(input);
   			} catch (CertificateException e) {
   				e.printStackTrace();
   			}
   			String hexString = null;
   			try {
   			    //加密算法的类，这里的参数可以使MD4,MD5等加密算法
   				MessageDigest md = MessageDigest.getInstance("SHA1");
   			    //获得公钥
   				byte[] publicKey = md.digest(c.getEncoded());
   			    //字节到十六进制的格式转换
   				hexString = byte2HexFormatted(publicKey);
   			} catch (NoSuchAlgorithmException e1) {
   				e1.printStackTrace();
   			} catch (CertificateEncodingException e) {
   				e.printStackTrace();
   			}
   			return hexString;
       }
       
       //这里是将获取到得编码进行16进制转换
   	private static String byte2HexFormatted(byte[] arr) {
   		StringBuilder str = new StringBuilder(arr.length * 2);
   		for (int i = 0; i < arr.length; i++) {
   			String h = Integer.toHexString(arr[i]);
   			int l = h.length();
   			if (l == 1)
   				h = "0" + h;
   			if (l > 2)
   				h = h.substring(l - 2, l);
   			str.append(h.toUpperCase());
   			if (i < (arr.length - 1))
   				str.append(':');
   		}
   		return str.toString();
   	}

   	
   	
       /**
        * md5编码
        * @param string
        * @return
        */
       public static String md5(String string) {
           byte[] hash = null;
           try {
               hash = MessageDigest.getInstance("MD5").digest(string.getBytes("UTF-8"));
           } catch (NoSuchAlgorithmException e) {
               throw new RuntimeException("Huh, MD5 should be supported?", e);
           } catch (UnsupportedEncodingException e) {
   			// TODO Auto-generated catch block
   			e.printStackTrace();
   		}

           StringBuilder hex = new StringBuilder(hash.length * 2);
           for (byte b : hash) {
               if ((b & 0xFF) < 0x10) hex.append("0");
               hex.append(Integer.toHexString(b & 0xFF));
           }
           return hex.toString();
       }

   	
       /**
        * 验证是否是合法的签名
        * @return
        */
       private boolean JavaValidateSign(){

           boolean isValidated  = false;
           try {
               //得到签名
               PackageInfo packageInfo = getPackageManager().getPackageInfo(getPackageName(),PackageManager.GET_SIGNATURES);
               Signature[] signs = packageInfo.signatures;

               //将签名文件MD5编码一下
               String signStr = md5(signs[0].toCharsString());
               //Log.e("JavaValidateSign ", "Msg = " + signStr);
               //将应用现在的签名MD5值和我们正确的MD5值对比
               return signStr.equals("这里写正确的签名的MD5加密后的字符串");
           } catch (PackageManager.NameNotFoundException e) {
               e.printStackTrace();
           }

           return isValidated;
       }    

}
