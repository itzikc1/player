package com.example.player1;

import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioButton;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private SurfaceView surfaceViewLay;
    private SurfaceHolder surfaceHolder;
    private ImageView play;
    private RadioButton radioButtonTransport;
    private RadioButton radioButtonSplit;
    private RadioButton radioButtonRTSP;
    private LinearLayout linearLayoutTransport;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        radioButtonTransport = findViewById(R.id.radioButtonTransport);
        radioButtonSplit = findViewById(R.id.radioButtonSplit);
        radioButtonRTSP = findViewById(R.id.radioButtonRTSP);
        linearLayoutTransport  = findViewById(R.id.LinearLayoutTransport);

        surfaceViewLay = findViewById(R.id.surface_view);
        surfaceHolder = surfaceViewLay.getHolder();

        radioButtonTransport.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //selected the radioButtonTransport

                linearLayoutTransport.setVisibility(View.VISIBLE);
                //pgsBar.setVisibility(View.GONE);
            }

        });
        radioButtonSplit.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //selected the radioButtonSplit
            }

        });
        radioButtonRTSP.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //selected the radioButtonRTSP
            }

        });
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
