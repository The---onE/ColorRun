#include "XMX_Vibrator.h"

void XMX_Vibrator::vibrate(int time)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
 	JniMethodInfo t;  
 	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "(I)V"))  
 	{  
 		t.env->CallStaticVoidMethod(t.classID, t.methodID, time);  
 		t.env->DeleteLocalRef(t.classID);  
 	}  
#endif 
}

void XMX_Vibrator::cancelVibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	JniMethodInfo t;  
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "cancelVibrate", "()V"))  
	{  
		t.env->CallStaticVoidMethod(t.classID, t.methodID);  
		t.env->DeleteLocalRef(t.classID);  
	}  
#endif 
}