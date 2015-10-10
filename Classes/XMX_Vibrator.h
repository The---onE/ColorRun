#pragma once

#include "cocos2d.h"
USING_NS_CC;

/*
	Add in cocos2d\cocos\2d\platform\android\java\src\org\cocos2dx\lib\Cocos2dxHelper.java
	In public class Cocos2dxHelper
		public static void vibrate(int vibrateTime) {
		Vibrator vib = (Vibrator) sActivity.getSystemService(Service.VIBRATOR_SERVICE);
		vib.vibrate(vibrateTime);
	}
	public static void cancelVibrate() {
		Vibrator vib = (Vibrator) sActivity.getSystemService(Service.VIBRATOR_SERVICE);
		vib.cancel();
	}
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "platform/android/jni/JniHelper.h"
#endif 

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

class XMX_Vibrator
{
public:
	static void vibrate(int time);
	static void cancelVibrate();
};

