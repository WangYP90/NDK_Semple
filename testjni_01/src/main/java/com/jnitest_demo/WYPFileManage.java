package com.jnitest_demo;

public class WYPFileManage {
    public static native void splitFile(String path,int split_count,String split_txt);
    public static native void mergeFile(String split_txt,int split_count,String managePath);
    static{
        System.loadLibrary("file-manage");
    }
}
