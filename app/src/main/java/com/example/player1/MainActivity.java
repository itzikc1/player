package com.example.player1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private SurfaceView surfaceViewLay;
    private SurfaceHolder surfaceHolder;
    private Button play;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        surfaceViewLay = findViewById(R.id.surface_view);
//        surfaceViewLay.getHolder().setFixedSize(1280, 720);
        surfaceHolder = surfaceViewLay.getHolder();

    }

    public void play(View view) {

        Thread d = new Thread(new Runnable() {  // asynchronously save image to parse
            @Override
            public void run() {
                Player player = new Player();
                player.playVideo(surfaceHolder.getSurface());
            }
        });
        d.start();


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
