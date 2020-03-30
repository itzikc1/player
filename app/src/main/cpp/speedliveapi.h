
#ifndef SPEEDLIVE_H
#define SPEEDLIVE_H
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif

#include <cstdint>
#define BIT(b) (1<<(b))

typedef size_t speedlive_handle_t ;
#ifdef LINUX
typedef void* HWND ;
#endif
											 
#define SPEEDLIVE_WINDOW_SIZE_FROM_VIDEO   0   // resulation by video
#define SPEEDLIVE_WINDOW_SIZE_FROM_SETUP   1   // resulation by setup
#define SPEEDLIVE_VIDEO_SIZE_FROM_WINDOW   2   // resulation by user application window (hwnd)
#define SPEEDLIVE_YUV_OVERLAY         	   3
#define  SPEEDLIVE_SETUP_DEBUG       	   4
#define  SPEEDLIVE_MULTICAST_ENABLE    	   5    // 
#define  SPEEDLIVE_DISABLE_DISPLAY         6
#define  SPEEDLIVE_ENABLE_LOOP_ANALIZE     9    // analogize
#define  SPEEDLIVE_ENABLE_TRANSCODE		   10	// transcode the input to destionation

enum{
	sync_mode_auto,		// sync automatic 
	sync_mode_delay		// use the delay setup
};


enum{
	ACTIVE_TASK_STREAM,
	ACTIVE_TASK_RECORD,
	ACTIVE_TASK_PLAYFILE,
	ACTIVE_TASK_PLAYSTREAM,
};

enum APP_SRC{
	STREAMING_APP,
	PLAYBACK_APP,
	OTHER_APP
};

enum{
	PIXEL_FORMAT_YUV420P,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
    PIXEL_FORMAT_YUYV422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
    PIXEL_FORMAT_RGB24,     ///< packed RGB 8:8:8, 24bpp, RGBRGB...
    PIXEL_FORMAT_BGR24,     ///< packed RGB 8:8:8, 24bpp, BGRBGR...	
};	



typedef struct{

	enum{
		SEEK_EVENT,
		PLAYBACK_TAG_EVENT,
		RECORD_TAG_EVENT,
		UPDATE_EVENT
	};

	int event_type;
	int sec; //for tag and seek
	int dir;
	int speed;
}playback_event_t;

#define PLAYBACK_NAME_LEN 200
//#define RECORD_PATH_LEN 100
typedef size_t speedlive_handle_t ;
//typedef void (*          splitmovie_bmp_callback_t)(void *param,unsigned int pixelformat,int witdh,int height,int pitch ,void *bitmap,void *md);
typedef void (__stdcall * speedlive_data_callback_t)(void *param,void* buffer,int buffer_size);

//typedef  void (*speedlive_data_callback_t)(void *param,void* buffer,int buffer_size);
typedef  void (*speedlive_user_overlay_callback_t)(void *param,int video_ch,unsigned int pixelformat,int witdh,int height,int pitch ,void *bitmap,void *ext_param);
typedef  void (*speedlive_user_record_callback_t)(void *param,int video_ch,void *enc_frame,int enc_frame_size);
typedef  void (*speedlive_user_index_callback_t)(void *param,int iframe); 
#define DATA_BUFF_MAX_AIZE 0X2800




typedef struct {
    int state;
    int second;
    int direction;
	int speed;
    int type;
    int total_second;
	int is_recording;
	int eof;
	int sof;
	char full_file_name[PLAYBACK_NAME_LEN];
enum{
    PLAYRE_STATUS_OFF,
    PLAYRE_STATUS_PLAYING,
    PLAYRE_STATUS_PAUSING,
    PLAYRE_STATUS_EOF,
    PLAYRE_STATUS_SOF
};
}player_sdx_status;


enum IS_MODE{
     MODE_OFF,
     MODE_ON
};

enum PROTOCOL{
        Protocol_PRIVATE,
        Protocol_UDPTS,
        Protocol_RTPUDP,
        Protocol_RTSPUDP,
        Protocol_RTSPTCP,
        Protocol_Split,
        Protocol_HTTP
};

typedef struct{
	char			file_name[PLAYBACK_NAME_LEN];   // The file name (full path)to playback
    int             is_cyclic;                          // Play a cyclically file
    int             is_trick_mode;                      // Play with indexe
    //parameters for trick mode:
    int				direction;                          // see enum for direction in trick_mode file
    int				speed;                              // see enum for speed in trick_mode file
    int				play_slow_on_end;                   // see enum play_slow_on_end in trick_mode
    int				s_transport;
    int             protocol;                   // streaming protocol
    int				ip;
    int				port;


	enum{
    PLAYER_SPD_PAUSE,
    PLAYER_SPD_NORMAL,
    PLAYER_SPD_X2,
    PLAYER_SPD_X3,
    PLAYER_SPD_X4,
    PLAYER_SPD_X5,
    PLAYER_SPD_FAST
	};

	enum{
    PLAYER_DIR_FORWARD,
    PLAYER_DIR_PREVWARD
	};


}playback_setup_t;

typedef struct{
    int             port;                       // Network port to leasen on it
    unsigned int    multicast_addr;             // multicast address
    int             protocol;                   // streaming protocol
    char           *rtsp_url;                   // For Protocol_RTSPUDP and Protocol_RTSPTCP
    char           *rtsp_sdp;                   // For Protocol_RTSPUDP and Protocol_RTSPTCP
    int             rtsp_port;                  // For Protocol_RTSPUDP and Protocol_RTSPTCP
    int             dst_port;                   // dest port
    unsigned int    dst_ip;                     // dest ip
    int             sync_delay_ms;		// only used with sync_mode = 1
    int             analize_mode;               //????
    int             src_app;
    int             hw_acc;                     // 1 = hw accelarator  

}streaming_setup_t;

typedef struct{
    int is_encryption;
    char key[255];
    int len;
}encryption_setup_t;

typedef struct{
	char directory_path[PLAYBACK_NAME_LEN]; // must allocate by the user
	char *file_name;	  // can be null	
	int   time_seconds;
	int   is_cyclic;
    int   cyclic_time_sec;
    int   is_trick_mode;                  // record with index file
}record_setup_t;

typedef struct{
    int				is_send_by_eth;
    int				is_save_by_file;
	unsigned int	ip;
	int				port;
	char *file_name;
}data_setup_t;



typedef  struct  {
	int flags;
    int self_draw;
    //

	HWND hwnd;							// The user application window.

	int  width; 						// height for WINDOW_SIZE_FROM_SETUP
    int  height;
    int hw_acc;
    // width for WINDOW_SIZE_FROM_SETUP
}speedlive_setup_t;


enum ACTION_BIT{
    PLAYBACK_BIT,
    PLAYBACK_STREAMING_BIT,
    STREAMING_BIT,
    RECORD_BIT
};


typedef struct{
	char*	file_name;
	int		kb_size;
	int		sec_size;
}record_info_t;


typedef struct{
	int inp_fps;
    int imp_bitrate;
    int inp_dec_error;
    int inp_dec_frame;
    int inp_disp_frames;
    int protocol; // see Protocol_t
    int v_codec;
    //audio
    int a_codec;
    int a_sample_rate;
    int a_bitrate;
    int a_channles;
    int a_bits_per_ch;
    // data
    int d_codec;
    int d_bitrate;
    int d_packets;
    // transcoding
    int transcode_tx_frames;
	unsigned int src_ip_addr;
}get_stream_info;


typedef struct{
	int protocol;
	int frame_count;
}stream_info_t;

typedef  struct  {
        int action_bit;
		//win
        int inp_width;
        int inp_height;
		int active_app;


        get_stream_info		get_strm_info;
		player_sdx_status	player_info;	
		record_info_t		record_info;
		stream_info_t		pb_stream_info;

}speedlive_info_t;



#ifdef __cplusplus
extern "C" {
#endif
#ifdef WIN32
__declspec (dllexport) int  __stdcall speedlive_open_cs(speedlive_setup_t  *pSetup   ,  speedlive_handle_t  *hVidDisp);
__declspec(dllexport)  void	__stdcall speedlive_stop_cs(speedlive_handle_t  hVidDisp,int action_bit);
__declspec (dllexport) void __stdcall speedlive_close_cs (speedlive_handle_t  hVidDisp);								// temporary pause
__declspec (dllexport) int  __stdcall speedlive_start_cs (speedlive_handle_t  hVidDisp ,int action_bit);
__declspec (dllexport) int  __stdcall speedlive_set_playback_param_cs(speedlive_handle_t  hVidDisp,playback_setup_t *playback_param);
__declspec (dllexport) int  __stdcall speedlive_set_streaming_param_cs(speedlive_handle_t  hVidDisp,streaming_setup_t *streaming_param);								// call after stop or at the beginning
__declspec (dllexport) int  __stdcall speedlive_set_record_param_cs(speedlive_handle_t  hVidDisp,record_setup_t *record_param);		
__declspec (dllexport) int  __stdcall speedlive_switch_dispatch_cs(speedlive_handle_t  hVidDisp,int dispatch_src);	
__declspec (dllexport) int  __stdcall speedlive_set_data_param_cs(speedlive_handle_t  hVidDisp,data_setup_t *data_param);		
__declspec (dllexport) int  __stdcall speedlive_get_action_cs();
__declspec (dllexport) void __stdcall speedlive_get_dll_ver_cs (int* dll_version);
__declspec (dllexport) void __stdcall speedlive_setup_port_cs                    (speedlive_handle_t hVidDisp,int port);
__declspec (dllexport) void __stdcall speedlive_get_info_cs                      (speedlive_handle_t hVidDisp,speedlive_info_t *p_info,int reset_info);
__declspec (dllexport) int __stdcall  speedlive_get_tag_by_i_cs                  (speedlive_handle_t hVidDisp,int i);
__declspec (dllexport) void __stdcall speedlive_set_event_cs                     (speedlive_handle_t hVidDisp,playback_event_t *params);
__declspec (dllexport) void __stdcall speedlive_get_plbck_status_cs              (speedlive_handle_t hVidDisp,player_sdx_status* p_status);
__declspec (dllexport) void __stdcall speedlive_register_data                (speedlive_handle_t hVidDisp,speedlive_data_callback_t func,void *callback_param);

__declspec (dllexport) void __stdcall speedlive_register_user_overlay_cs         (speedlive_handle_t hVidDisp,speedlive_user_overlay_callback_t func,void *callback_param);
__declspec (dllexport) void __stdcall speedlive_register_record_encode_frame_cs  (speedlive_handle_t hVidDisp,speedlive_user_record_callback_t callback,void *callback_param,speedlive_user_index_callback_t index_func);
__declspec (dllexport) void __stdcall speedlive_put_encode_frame_cs              (speedlive_handle_t hVidDisp,void *enc_frame,int enc_frame_size);
__declspec (dllexport) void __stdcall speedlive_read_data_cs               (speedlive_handle_t hVidDisp,BYTE* buffer,uint64_t *pc_time);
__declspec (dllexport) int __stdcall speedlive_read_frame_cs              (speedlive_handle_t hVidDisp,int* w,int*h ,BYTE* buffer);


#endif





	
typedef struct{
//===========  basic functions ========================================
        void (*Speedlive_close)(speedlive_handle_t  hVidDisp);
        int  (*Speedlive_open) (speedlive_setup_t   pSetup , speedlive_handle_t  *hVidDisp);  // return hVidDisp handle should use by all the functions
        void (*Speedlive_stop) (speedlive_handle_t  hVidDisp,int action_bit);								// temporary pause
        int  (*Speedlive_start)(speedlive_handle_t  hVidDisp ,int action_bit);

        int  (*Speedlive_set_playback_param)(speedlive_handle_t  hVidDisp,playback_setup_t playback_param);
		int  (*Speedlive_set_streaming_param)(speedlive_handle_t  hVidDisp,streaming_setup_t streaming_param);								// call after stop or at the beginning
        int  (*Speedlive_set_encryption_param)(speedlive_handle_t  hVidDisp,encryption_setup_t encryption_params);								// call after stop or at the beginning

        int  (*Speedlive_set_record_param)(speedlive_handle_t  hVidDisp,record_setup_t playback_param);		
		
		int  (*Speedlive_switch_dispatch)(speedlive_handle_t  hVidDisp,int dispatch_src);	
		int  (*Speedlive_set_data_param)(speedlive_handle_t  hVidDisp,data_setup_t data_param);		
		int (*Speedlive_get_action)	();
		 // call after stop or at the beginning

   
//=========  extended functions =======================================

        void (*Speedlive_register_data_callback)             (speedlive_handle_t hVidDisp,speedlive_data_callback_t func,void *callback_param);
        void (*Speedlive_register_user_overlay)         (speedlive_handle_t hVidDisp,speedlive_user_overlay_callback_t func,void *callback_param);
        void (*Speedlive_register_record_encode_frame)  (speedlive_handle_t hVidDisp,speedlive_user_record_callback_t func,void *callback_param,speedlive_user_index_callback_t index_func);
        void (*Speedlive_put_encode_frame)              (speedlive_handle_t hVidDisp,void *enc_frame,int enc_frame_size);
        void (*Speedlive_setup_port)                    (speedlive_handle_t hVidDisp,int port);
        void (*Speedlive_get_info)                      (speedlive_handle_t hVidDisp,speedlive_info_t *p_info,int reset_info);
        void (*Speedlive_get_dll_ver)                   (int* dll_version);
        void (*Speedlive_get_plbck_status)              (speedlive_handle_t hVidDisp,player_sdx_status* p_status);
        void (*Speedlive_set_event)                     (speedlive_handle_t hVidDisp,playback_event_t params);
        int  (*Speedlive_get_tag_by_i)                  (speedlive_handle_t hVidDisp,int i);
        int  (*Speedlive_read_data)                     (speedlive_handle_t hVidDisp,char* p_data,uint64_t *pc_time);
        int  (*Speedlive_set_hw_acc)                    (speedlive_handle_t hVidDisp,int hw_acc);

        //mmvoid (*Speedlive_get_volume)(unsigned int* volume);
        //void (*Speedlive_set_volume)(unsigned int volume);

}speedlive_t;
speedlive_t  *speedlive_get_handle(void);
#ifdef __cplusplus
}
#endif
#endif
