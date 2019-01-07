#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CryptorUtil.h"

char password[] = "mynameisjava8888";

JNIEXPORT void JNICALL Java_com_jnitest_1demo_CryptorUtil_crypt
        (JNIEnv *jniEnv, jclass cls, jstring normal_path_jstr, jstring crypt_path_jstr) {
    char *normal_path = (*jniEnv)->GetStringUTFChars(jniEnv, normal_path_jstr, JNI_FALSE);
    char *crypt_path = (*jniEnv)->GetStringUTFChars(jniEnv, crypt_path_jstr, JNI_FALSE);
    //打开文件
    FILE *normal_fp = fopen(normal_path, "rb");
    FILE *crypt_fp = fopen(crypt_path, "wb+");
    char th_str[50];
    if (normal_fp == NULL) {
        jthrowable newExcCls = (*jniEnv)->FindClass(jniEnv, "java/lang/NullPointerException");
        strcpy(th_str,"normal_fp为Null---");
        strcat(th_str,normal_path);
        (*jniEnv)->ThrowNew(jniEnv,newExcCls,th_str);
        printf("normal_fp 为null");
        return;
    }
    if (crypt_fp == NULL) {
        jthrowable newExcCls = (*jniEnv)->FindClass(jniEnv, "java/lang/NullPointerException");
        (*jniEnv)->ThrowNew(jniEnv,newExcCls,"crypt_fp为Null");
        printf("crypt_fp 为null");
        return;
    }
    //一次读取一个字符
    int ch;
    int i = 0;
    int pwd_len = strlen(password);
    while ((ch = fgetc(normal_fp)) != EOF) {
        fputc(ch ^ password[i % pwd_len], crypt_fp);
        if (i == pwd_len) {
            i = 0;
        } else {
            i++;
        }
    }

    fclose(normal_fp);
    fclose(crypt_fp);
};

/*
 * Class:     com_jnitest_demo_CryptorUtil
 * Method:    decrypt
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_jnitest_1demo_CryptorUtil_decrypt
        (JNIEnv *jniEnv, jclass cls, jstring crypt_path_jstr, jstring decrypt_path_jstr) {
    char *crypt_path = (*jniEnv)->GetStringUTFChars(jniEnv, crypt_path_jstr, JNI_FALSE);
    char *decrypt_path = (*jniEnv)->GetStringUTFChars(jniEnv, decrypt_path_jstr, JNI_FALSE);
    //打开文件
    FILE *crypt_fp = fopen(crypt_path, "rb");
    FILE *decrypt_fp = fopen(decrypt_path, "wb+");

    //一次读取一个字符
    int ch;
    int i = 0;
    int pwd_len = strlen(password);
    while ((ch = fgetc(crypt_fp)) != EOF) {
        fputc(ch ^ password[i % pwd_len], decrypt_fp);
        if (i == pwd_len) {
            i = 0;
        } else {
            i++;
        }
    }

    fclose(crypt_fp);
    fclose(decrypt_fp);
};