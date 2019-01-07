package org.fmod.example;

import java.io.File;

import org.fmod.FMOD;
import org.fmod.example.EffectUtils;


import android.Manifest;
import android.app.Activity;
import android.content.pm.PermissionInfo;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.wang.viucer_change.R;

public class QQActivity extends AppCompatActivity {
    String[] permissions = {Manifest.permission.RECORD_AUDIO, Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FMOD.init(this);

        ActivityCompat.requestPermissions(this, permissions, 100);
        setContentView(R.layout.activity_qq_change);
    }

    public void mFix(View btn) {
        String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "jaguar.wav";
        int i = btn.getId();
        if (i == R.id.btn_record) {
            EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
        } else if (i == R.id.btn_luoli) {
            EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
        } else if (i == R.id.btn_dashu) {
            EffectUtils.fix(path, EffectUtils.MODE_DASHU);
        } else if (i == R.id.btn_jingsong) {
            EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
        } else if (i == R.id.btn_gaoguai) {
            EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
        } else if (i == R.id.btn_kongling) {
            EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
        }

        Log.d("jason", "mFix");
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

}
