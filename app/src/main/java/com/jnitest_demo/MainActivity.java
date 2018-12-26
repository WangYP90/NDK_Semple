package com.jnitest_demo;

import android.Manifest;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.io.File;

import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

    String[] s = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            requestPermissions(s, 100);
        }
    }

    @OnClick({R.id.m_btn_crypt, R.id.m_btn_decrypt,R.id.m_btn_split, R.id.m_btn_merge})
    public void onViewClicked(View view) {
        ///Environment.getExternalStorageDirectory().getAbsolutePath()  ---- storage/emulated/0
        //如果是在根目录
        //String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "Download" + File.separator;
        String path = Environment.getExternalStoragePublicDirectory("").getAbsolutePath() + File.separator;
        // String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator;


        String normal_path = path + "timg.jpeg";
        String cyrpt_path = path + "cyrpt_timg.jpeg";
        String decyrpt_path = path + "decyrpt_timg.jpeg";



        String split_path = path+ "timg.jpeg";
        String split_text = path+ "timg_%d.jpeg";
        String manage_finish_path = path+"timg_meage.jpeg";
        int split_count = 5;
        switch (view.getId()) {
            case R.id.m_btn_crypt:
                try {
                    CryptorUtil.crypt(normal_path, cyrpt_path);
                } catch (Throwable e) {
                    e.printStackTrace();
                }
                break;
            case R.id.m_btn_decrypt:
                try {
                    CryptorUtil.decrypt(cyrpt_path, decyrpt_path);
                } catch (Throwable e) {
                    e.printStackTrace();
                }
                break;

            case R.id.m_btn_split:
                try{
                    WYPFileManage.splitFile(split_path, split_count,split_text);
                }catch (Throwable e){
                    e.printStackTrace();
                }
                break;
            case R.id.m_btn_merge:

                try{
                    WYPFileManage.mergeFile(split_text,split_count,manage_finish_path);
                }catch (Throwable e){
                    e.printStackTrace();
                }
                break;
        }
    }

//
//    private String disposeFile(String normal_path) {
//        String path = "";
//        try {
//            path = parUri(new File(normal_path)).getPath();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//        return path;
//    }
//
//
//    private Uri parUri(File cameraFile) {
//        Uri imageUri;
//        String authority = this.getPackageName() + ".provider";
//        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.M) {
//            //通过FileProvider创建一个content类型的Uri
//            imageUri = FileProvider.getUriForFile(this, authority, cameraFile);
//        } else {
//            imageUri = Uri.fromFile(cameraFile);
//        }
//        return imageUri;
//    }

}
