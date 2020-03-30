#include <jni.h>
#include <string>
#include "speedliveapi.h"
#include "LOGE.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/log.h>



#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

ANativeWindow_Buffer window_buffer;
ANativeWindow *native_window;
speedlive_t *m_speedlive=0;
static int first_time=1;


unsigned int Socket_Str2Addr(char *pc_ip){
    if(pc_ip ==0 || pc_ip[0]==0)
        return 0;

    return htonl(inet_addr(pc_ip));
}



static void speedlive_user_overlay_callback(void *param,int video_ch,unsigned int pixelformat,int witdh,int height,int pitch ,void *bitmap,void *ext){
    static int frame=0;
//    unsigned int *pdest = ( unsigned int  *)window_buffer.bits;
    int result;
    if(first_time) {
        result = ANativeWindow_setBuffersGeometry(native_window, witdh, height, WINDOW_FORMAT_RGBX_8888);
        first_time =0;
    }

//    unsigned char *psrc_frame  = (unsigned char *)bitmap;
//    int y,x;
//
     result = ANativeWindow_lock(native_window, &window_buffer, NULL);
    unsigned int *pdest = ( unsigned int  *)window_buffer.bits;
    memcpy(pdest,bitmap,pitch*height);
   // memset(pdest,0x255,witdh*height);
//    for(y=0;y<576;y++){
//        unsigned char *p_src_line= psrc_frame;
//        for(x=0;x<720;x++){
//           memcpy((void*)pdest,(void*)p_src_line,3);
//           pdest += 1;
//           p_src_line +=3;
//        }
//        psrc_frame += pitch;
//    }


   ANativeWindow_unlockAndPost(native_window);
   // __android_log_print(ANDROID_LOG_INFO, "sometag", "test int = %d", frame++);
}

static int start_streaming_rtsp(void* m_VidHadle , char *url,char *sdp,int protocol){
    int bit_action=0;
    if(!m_VidHadle) {
        return -1;
    }
    streaming_setup_t streaming_param={0};

                // For Protocol_RTSPUDP and Protocol_RTSPTCP
    streaming_param.rtsp_url=strdup(url);                   // For Protocol_RTSPUDP and Protocol_RTSPTCP
    streaming_param.rtsp_sdp = strdup(sdp);                   // For Protocol_RTSPUDP and Protocol_RTSPTCP
    streaming_param.rtsp_port=554;
    switch(protocol){
        case 0 :
            streaming_param.protocol=Protocol_RTSPUDP;
        break;
        case 1:
            streaming_param.protocol=Protocol_RTSPTCP;
        break;
    }

    m_speedlive->Speedlive_set_streaming_param((speedlive_handle_t )m_VidHadle,streaming_param);
    bit_action=BIT(ACTION_BIT::STREAMING_BIT);
    m_speedlive->Speedlive_start((speedlive_handle_t )m_VidHadle,bit_action);

    return 0;
}


static int start_streaming(void* m_VidHadle,PROTOCOL protocol,char *ip,int port){
	int bit_action=0;
	int ret;
	if(!m_VidHadle)
		return -1;

	streaming_setup_t streaming_param={0};
	streaming_param.rtsp_url=0;
    streaming_param.port=1234;
	streaming_param.analize_mode=0;
	streaming_param.protocol=protocol;
	if(ip && strlen(ip)>0) {
        streaming_param.multicast_addr = Socket_Str2Addr(ip);
    }
	streaming_param.sync_delay_ms =0;


	m_speedlive->Speedlive_set_streaming_param((speedlive_handle_t )m_VidHadle,streaming_param);
	bit_action=BIT(ACTION_BIT::STREAMING_BIT);
	ret = m_speedlive->Speedlive_start((speedlive_handle_t )m_VidHadle,bit_action);
	return ret;
}




extern "C"
JNIEXPORT void JNICALL
Java_com_example_player1_Player_playVideo(JNIEnv *env, jobject thiz, jobject surface) {
    int result;
     int version=0;
     void *m_VidDisp1=0;
   ANativeWindow_Buffer window_buffer;
   speedlive_setup_t setup={0};
//    // TODO: implement playVideo()
    native_window = ANativeWindow_fromSurface(env, surface);
     m_speedlive = speedlive_get_handle();
    if(m_speedlive) {
        m_speedlive->Speedlive_get_dll_ver(&version);
//        fprintf(stderr,"%s.%d version(%d)\n\r",__func__,__LINE__,version);

//        LOGE("Player Error : Can not set native window buffer");
    }
//
//
//
//    if (result < 0){
////        LOGE("Player Error : Can not set native window buffer");
//        ANativeWindow_release(native_window);
//        return;
//    }
//
//    unsigned char *pbits = ( unsigned char *)window_buffer.bits;
//
       result = m_speedlive->Speedlive_open(setup,(speedlive_handle_t *)(&m_VidDisp1));
//        __android_log_print(ANDROID_LOG_INFO, "player", "test int = %d , handl(%d) results(%d)", version,m_VidDisp1,result);
       m_speedlive->Speedlive_register_user_overlay((speedlive_handle_t )m_VidDisp1, speedlive_user_overlay_callback,0);
       result  = start_streaming(m_VidDisp1,Protocol_UDPTS,"",1234);
       //result = start_streaming_rtsp(m_VidDisp1,"192.168.0.44","mux1.sdp",0);
//
//    /*
//    for(int y=0;y<800;y++){
//        for(int x=0;x<1280;x++){
//            pbits[0] = 255;
//            pbits[1] = 0;
//            pbits[2] = 0;
//            pbits[3] = 0;
//            pbits += 4;
//        }
//    }
//    */
//
    

}
