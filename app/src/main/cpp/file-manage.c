//
// Created by user on 2018/12/21.
//
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include "WYPFileManage.h"

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"WYP_",FORMAT,__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"WYP_",FORMAT,__VA_ARGS__);

//拆分
JNIEXPORT void JNICALL Java_com_jnitest_1demo_WYPFileManage_splitFile
        (JNIEnv *jniEnv, jclass cls, jstring path, jint split_count, jstring split_txt) {
    char *c_path = (*jniEnv)->GetStringUTFChars(jniEnv, path, NULL);
    char *c_split_txt_path = (*jniEnv)->GetStringUTFChars(jniEnv, split_txt, NULL);
    // 不断读取path文件 ,循环 写入file_count 个文件中
    char **patches = malloc(sizeof(char*) * split_count);
    int i = 0;
    for(;i < split_count;i++){
        patches[i] = malloc(sizeof(char) *100);
        //元素赋值, 需要分割的文件:
        sprintf(patches[i],c_split_txt_path,(i+1));
        LOGI("patch --path:%s",patches[i]);
    }
    i= 0;
    for(; i < split_count;i++){
        free(patches[i]);
    }
    free(patches);
    //官方建议 释放
    (*jniEnv)->ReleaseStringChars(jniEnv,path,c_path);
    (*jniEnv)->ReleaseStringChars(jniEnv,split_txt,c_split_txt_path);
};

/* 合并
 */
JNIEXPORT void JNICALL Java_com_jnitest_1demo_WYPFileManage_mergeFile
        (JNIEnv *jniEnv, jclass cls, jstring path, jstring manage_path) {

};
