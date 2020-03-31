package com.example.player1;

import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RadioButton;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private SurfaceView surfaceViewLay;
    private SurfaceHolder surfaceHolder;
    private ImageView play;
    private ImageView stopButton;

    private RadioButton radioButtonTransport;
    private RadioButton radioButtonSplit;
    private RadioButton radioButtonRTSP;

    private RadioButton radioButtonUdp;
    private RadioButton radioButtonTcp;

    private RadioButton radioButtonUnicast;
    private RadioButton radioButtonMulticast;

    private EditText portInputText;
    private EditText sdpInputText;
    private EditText ipInputText;


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

        radioButtonUdp = findViewById(R.id.radioButtonUdp);
        radioButtonTcp = findViewById(R.id.radioButtonTcp);
        radioButtonUnicast = findViewById(R.id.radioButtonUnicast);
        radioButtonMulticast = findViewById(R.id.radioButtonMulticast);


        stopButton = findViewById(R.id.stopButton);
        surfaceViewLay = findViewById(R.id.surface_view);
        surfaceHolder = surfaceViewLay.getHolder();

        // all the input is in the this param

        portInputText = findViewById(R.id.portInputText);
        sdpInputText = findViewById(R.id.sdpInputText);
        ipInputText = findViewById(R.id.ipInputText);


        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //stop button press
                Log.v("stop_button", "stop button press");

            }

        });

        radioButtonTransport.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //selected the radioButtonTransport
                radioButtonSplit.setChecked(false);
                radioButtonRTSP.setChecked(false);
                //stop button press
                Log.v("radioButtonTransport", "radio Button Transport");
            }
        });

        radioButtonSplit.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                radioButtonTransport.setChecked(false);
                radioButtonRTSP.setChecked(false);
                Log.v("radioButtonSplit", "radio Button Split");

            }
        });

        radioButtonRTSP.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //selected the radioButtonRTSP
                radioButtonTransport.setChecked(false);
                radioButtonSplit.setChecked(false);
                Log.v("radioButtonRTSP", "radio Button RTSP");

            }
        });

        radioButtonUdp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //stop button press
                Log.v("radioButtonUdp", "radio Button Udp");
                radioButtonTcp.setChecked(false);
                radioButtonUnicast.setChecked(false);
                radioButtonMulticast.setChecked(false);
            }
        });

        radioButtonTcp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //stop button press
                Log.v("radioButtonTcp", "radio Button Tcp");
                radioButtonUdp.setChecked(false);
                radioButtonUnicast.setChecked(false);
                radioButtonMulticast.setChecked(false);
            }
        });

        radioButtonUnicast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //stop button press
                Log.v("radioButtonUnicast", "radio Button Unicast");
                radioButtonUdp.setChecked(false);
                radioButtonTcp.setChecked(false);
                radioButtonMulticast.setChecked(false);
            }
        });

        radioButtonMulticast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //stop button press
                Log.v("radioButtonMulticast", "radio Button Multicast");
                radioButtonUdp.setChecked(false);
                radioButtonTcp.setChecked(false);
                radioButtonUnicast.setChecked(false);
            }
        });
    }

    public void play(View view) {
        Log.v("play_button", "play button press");

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
