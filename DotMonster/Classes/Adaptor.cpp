//
//  AdaptorHelper.cpp
//  DotMonster
//
//  Created by 김선철 on 2016. 2. 3..
//
//

#include "Adaptor.h"
#include "cocos2d.h"
#include "GameScene.h"

bool Adaptor::isAdShowing = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>


const char* AppActivityClassName = "com/tronplay/etc/Helper";

#ifdef __cplusplus
extern "C"
{
#endif
    
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeVideoSuccess()
    {
        GameScene *scene = GameScene::runningScene();
        if(scene)
            scene->videoSuccess();
    }
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeVideoFail()
    {
        GameScene *scene = GameScene::runningScene();
        if(scene)
            scene->videoFail();
    }
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeVideoNotContent()
    {
        GameScene *scene = GameScene::runningScene();
        if(scene)
            scene->videoNotContent();
    }
    
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeCallAdmob()
    {
        Adaptor::createAdmob("ca-app-pub-4632355628993989/9398755959");
    }
    
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeCallInterstitial()
    {
        Adaptor::createInterstitalAd("ca-app-pub-4632355628993989/4711204356");
    }
    
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeGoogleService(JNIEnv* env,jobject object,jstring adkey)
    {
        jboolean isCopy;
        const char* str = env->GetStringUTFChars(adkey,&isCopy);
        string adKeyString = str;
        env->ReleaseStringUTFChars(adkey,str);
        
        if(adKeyString.compare("ca-app-pub-4632355628993989/9398755959"))
        {
            Director::getInstance()->end();
        }
    }
    
    JNIEXPORT void JNICALL
    Java_com_tronplay_etc_Helper_nativeTapJoyConnect(JNIEnv* env,jobject object,jstring adkey)
    {
        jboolean isCopy;
        const char* str = env->GetStringUTFChars(adkey,&isCopy);
        string adKeyString = str;
        env->ReleaseStringUTFChars(adkey,str);
        
        if(adKeyString.compare("ca-app-pub-4632355628993989/4711204356"))
        {
            Director::getInstance()->end();
        }
    }
    
#ifdef __cplusplus
}
#endif

void Adaptor::hideAd()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAdMob", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = false;
    }
}



void Adaptor::showAd()
{
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAdMob", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }
    checkAdmobKey();
}
void Adaptor::showInterstitalAd()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "displayInterstitital", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }
    checkInterstitalAd();
}
void Adaptor::showVedio()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showVideoStart", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }
}

void Adaptor::login()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "loginGoogle", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }
}
void Adaptor::submitScore(int score)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "submitGoogleScore", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
        t.env->DeleteLocalRef(t.classID);
    }
}
void Adaptor::showLeaderBoard()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showLeaderBoard", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isAdShowing = true;
    }
}

void Adaptor::createAdmob(const char *adKey)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "setAdmob", "(Ljava/lang/String;)V"))
    {
        jstring stringArg = t.env->NewStringUTF(adKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }
}
void Adaptor::createInterstitalAd(const char *adKey)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "setInterstitial", "(Ljava/lang/String;)V"))
    {
        jstring stringArg = t.env->NewStringUTF(adKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }
}

void Adaptor::checkAdmobKey()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "googleService", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
void Adaptor::checkInterstitalAd()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "tapJoyViedoConnect", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
#else

#include "AdaptoriOS.h"

void Adaptor::hideAd()
{
    CCLOG("hideAd() called");
    isAdShowing = false;
    AdaptoriOS::hideAdMob();
    return; //nothing
}


void Adaptor::showAd()
{
    CCLOG("showAd() called");
    AdaptoriOS::showAdMob();
    isAdShowing = true;
    return; //nothing;
    
}

void Adaptor::showInterstitalAd()
{
    CCLOG("showInterstitalAd() called");
    AdaptoriOS::showInterstital();
    return;
}

void Adaptor::showVedio()
{
    CCLOG("showVedio() called");
    AdaptoriOS::showVideo();
    return;
}
void Adaptor::login()
{
    CCLOG("login () called");
    AdaptoriOS::loginGameCenter();
    return;
}
void Adaptor::submitScore(int score)
{
    CCLOG("submitScore () called");
    AdaptoriOS::submitScore(score);
    return;
}
void Adaptor::showLeaderBoard()
{
    CCLOG("showLeaderBoard () called");
    AdaptoriOS::showLeaderBoarder();
    return;
}
void Adaptor::videoSuccess()
{
    GameScene *scene = GameScene::runningScene();
    if(scene)
        scene->videoSuccess();
}
void Adaptor::videoNotContent()
{
    GameScene *scene = GameScene::runningScene();
    if(scene)
        scene->videoNotContent();
}
void Adaptor::videoFail()
{
    GameScene *scene = GameScene::runningScene();
    if(scene)
        scene->videoFail();
}
void Adaptor::createAdmob(const char *adKey)
{
}
void Adaptor::createInterstitalAd(const char *adKey)
{
}
void Adaptor::checkAdmobKey()
{
}
void Adaptor::checkInterstitalAd()
{
}

#endif