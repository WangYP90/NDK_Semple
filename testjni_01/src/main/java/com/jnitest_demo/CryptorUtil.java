package com.jnitest_demo;

public class CryptorUtil {

    /**
     * 加密
     */
    public native static void crypt(String normal_path,String crypt_path);

    /**
     * 解密
     */
    public native static void decrypt(String crypt_path,String decrypt_path);

    static{
        System.loadLibrary("file-manage");
    }
}
