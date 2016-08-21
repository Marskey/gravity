#ifndef _ANDROIDINTERFACE_H
#define _ANDROIDINTERFACE_H

#define CLICK_ADVIEW_NOTI_NAME "CLICK_AD_VIEW_NOTI"

#ifdef ANDROID
#include <cstddef>
#include <jni.h>
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_com_fjnucdio_devilHiding_devilHiding_initJVM(JNIEnv *env, jclass);

	//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_onClickAd(JNIEnv *env,jclass);

	//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_closeLoading(JNIEnv *env,jclass);

#ifdef __cplusplus
}
#endif
#endif

//extern int g_clickad_flag;
//extern int g_loading_show;

//void set_adview_visible(int showflag);
void share_to_freinds();
//void exit_game();

#endif
