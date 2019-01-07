//
// Created by user on 2018/12/21.
//
#include <jni.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <android/log.h>
#include "WYPFileManage.h"

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"WYP_",FORMAT,__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"WYP_",FORMAT,__VA_ARGS__);

//static long get_file_size(char *path) {
////    FILE *fp = fopen(path, "rb");
////    fseek(fp, 0, SEEK_END);
////    long file_size = ftell(fp);
////    fclose(fp);
////    return file_size;
////}

unsigned long get_file_size(const char *path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0){
        return filesize;
    }else{
        filesize = statbuff.st_size;
    }
    return filesize;
}


//拆分
JNIEXPORT void JNICALL Java_com_jnitest_1demo_WYPFileManage_splitFile
        (JNIEnv *jniEnv, jclass cls, jstring path, jint split_count, jstring split_txt) {
    char *c_path = (*jniEnv)->GetStringUTFChars(jniEnv, path, NULL);
    char *c_split_txt_path = (*jniEnv)->GetStringUTFChars(jniEnv, split_txt, NULL);
    // 不断读取path文件 ,循环 写入file_count 个文件中
    char **patches = malloc(sizeof(char *) * split_count);
    int i = 0;
    for (; i < split_count; i++) {
        patches[i] = malloc(sizeof(char) * 100);
        //元素赋值, 需要分割的文件:
        sprintf(patches[i], c_split_txt_path, (i + 1));
        LOGI("patch --path:%s", patches[i]);
    }
    long filesize = get_file_size(c_path);
    FILE *fpr = fopen(c_path, "rb");
    if (filesize % split_count == 0) {
        //整除
        //单个文件的大小
        int part = filesize / split_count;
        i = 0;

        //逐一写入不同的分割子文件中
        for (; i < split_count; i++) {
            FILE *fpw = fopen(patches[i], "wb");
            int j = 0;
            for (; j < part; j++) {
                fputc(fgetc(fpr), fpw);
            }
            fclose(fpw);
        }
    } else {
        //不整除
        //单个文件的大小
        int part = filesize / (split_count - 1);
        i = 0;
        //逐一写入不同的分割子文件中
        for (; i < split_count - 1; i++) {
            FILE *fpw = fopen(patches[i], "wb");
            int j = 0;
            for (; j < part; j++) {
                fputc(fgetc(fpr), fpw);
            }
            fclose(fpw);
        }

        //最后一个
        FILE *fpw = fopen(patches[split_count - 1], "wb");
        int i = 0;
        for (; i < filesize % (split_count - 1); i++) {
            fputc(fgetc(fpr), fpw);
        }
        fclose(fpw);
    }

    fclose(fpr);

    i = 0;
    for (; i < split_count; i++) {
        free(patches[i]);
    }
    free(patches);
    LOGI("split File %s", "拆分文件完成");
    //官方建议 释放
    (*jniEnv)->ReleaseStringChars(jniEnv, path, c_path);
    (*jniEnv)->ReleaseStringChars(jniEnv, split_txt, c_split_txt_path);
};

/* 合并
 */
JNIEXPORT void JNICALL Java_com_jnitest_1demo_WYPFileManage_mergeFile
        (JNIEnv *jniEnv, jclass cls, jstring path_pattern_jstr, jint split_count,
         jstring merge_path_jstr) {
    char *c_path_pattern = (*jniEnv)->GetStringUTFChars(jniEnv, path_pattern_jstr, NULL);
    char *c_merge_path = (*jniEnv)->GetStringUTFChars(jniEnv, merge_path_jstr, NULL);


    //得到分割之后的子文件的路径列表
    char **patches = malloc(sizeof(char *) * split_count);
    int i = 0;
    for (; i < split_count; i++) {
        patches[i] = malloc(sizeof(char) * 100);
        sprintf(patches[i], c_path_pattern, (i + 1));
        LOGI("patch --path:%s", patches[i]);
    }
    FILE *fpw = fopen(c_merge_path, "wb");
    i = 0;
    for (; i < split_count; i++) {
        long filesize = get_file_size(patches[i]);
        FILE *fpr = fopen(patches[i], "rb");
        int j = 0;
        for (; j < filesize; j++) {
            fputc(fgetc(fpr), fpw);
        }
        fclose(fpr);
    }
    fclose(fpw);


    i = 0;
    for (; i < split_count; i++) {
        free(patches[i]);
    }
    free(patches);
    LOGI("meage File %s", "合并文件完成");
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, merge_path_jstr, c_merge_path);
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, path_pattern_jstr, c_path_pattern);
};
