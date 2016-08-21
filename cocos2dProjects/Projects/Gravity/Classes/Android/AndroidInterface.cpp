#include "stdafx.h"
#include "AndroidInterface.h"
//int g_clickad_flag = 0;
//int g_loading_show = 0;

#ifdef ANDROID
JavaVM* g_javaVM = NULL;
jclass g_cls;

JNIEXPORT void JNICALL Java_com_fjnucdio_team6_Gravity_initJVM(JNIEnv *env, jclass)
{
	CCLOG("init jvm bengin");
	env->GetJavaVM(&g_javaVM);
	CCLOG("init jvm end");
}

//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_onClickAd(JNIEnv *env,jclass)
//{
//	CCLOG("click ad cpp");
//	g_clickad_flag = 1;
//}
//
//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_closeLoading(JNIEnv *env,jclass)
//{
//	CCLOG("close loading");
//	g_loading_show = 0;
//}

jmethodID getMethodID(JNIEnv* env, const char* method, const char* parames)
{
	jclass g_cls =  env->FindClass("com/fjnucdio/team6/Gravity");
	if (!g_cls)
	{
		CCLOG("com/fjnucdio/team6/Gravity class is not found.");
		return NULL;
	}
	jmethodID methodId = env->GetStaticMethodID(g_cls, method,parames);
	return methodId;
}

#endif
//
//void set_adview_visible(int showflag)
//{
//#ifdef ANDROID
//	JNIEnv *env;
//	g_javaVM->AttachCurrentThread(&env, NULL);
//	jmethodID methodId = getMethodID(env,"setAdViewVisable","(I)V");
//
//	if (!methodId)
//	{
//		CCLOG("setAdViewVisable function is not found.");
//		return;
//	}
//
//	env->CallStaticObjectMethod( g_cls, methodId,showflag);
//#endif
//}


void share_to_freinds()
{
	CCLog("weibo");
#ifdef ANDROID
	JNIEnv *env;
	g_javaVM->AttachCurrentThread(&env, NULL);
	jmethodID methodId = getMethodID(env,"shareToFreinds","()V");

	if (!methodId)
	{
		CCLOG("shareToFreinds function is not found.");
		return;
	}

	env->CallStaticObjectMethod(g_cls, methodId);
#endif
}

void exit_game()
{
#ifdef ANDROID
	JNIEnv *env;
	g_javaVM->AttachCurrentThread(&env, NULL);
	jmethodID methodId = getMethodID(env,"onClickBackButton","()V");

	if (!methodId)
	{
		CCLOG("shareToFreinds function is not found.");
		return;
	}

	env->CallStaticObjectMethod(g_cls, methodId);
#endif
}


