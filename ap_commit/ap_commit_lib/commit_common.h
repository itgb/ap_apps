#ifndef _COMMIT_COMMON_H_
#define _COMMIT_COMMON_H_

typedef int (*log_print) ( const char * format, ... );


/*������𣬱��ڷ������,��ǰ֧��ǰ3������*/
typedef enum CONFIG_CATEGORY_TAG
{
	CONF_BASIC	= 0,
	CONF_RADIO,
	CONF_WLAN,
	CONF_NETWORK,
	CONF_AC,
	CONF_OTHER,
	CONF_MAX,
}CONFIG_CATEGORY;

/*header+content ��ʽʹ�øýṹ*/
#define 	WL_MGMT_MAGIC	(0xF1F2F3F4)
struct ap_cfg_info_st
{
	uint32_t 			magic;			/*ħ��������У�����õ���Ч��*/
	CONFIG_CATEGORY		conf_type;		/*�������*/
	uint8_t 			rf_type;		/*2g,5g,all--1,2,3*/
	int8_t				more;			/*�Ƿ��и��������:1,���ڵ�ǰ��λ�����ƫ�ƣ�����������0����ֹͣ����*/
	uint16_t			len;			/*��ǰ������ĳ��ȣ����������ݽ���ṹ�����*/
//  int8_t				data[0];			/*����*/
};

/*��Ƶ����*/
typedef enum RF_TYPE_TAG
{
  RF_2G = 1,	/*2G*/
  RF_5G = 2,	/*5G*/
  RF_ALL = 3,	/*2G&5G*/
}RF_TYPE;

/*��������*/
#define 	IF_NAME_LEN           8		/*�豸�����ȣ�����ath2xxx����wifiX*/
#define 	IEEE80211_ADDR_LEN    6		/*mac��ַ����*/
#define 	AP_DESC_MAX_SIZE	  32	/*ap�����ĳ���*/
#define 	ENCRYPT_MODE_SIZE     32	/*����ģʽ*/
#define		PASSWORD_MAX_SIZE 	  32	/*���볤��*/
#define 	RADIO_MODE_MAX_SIZE	  16	/*����Э��*/
#define		SSID_MAX_SIZE     	  32	/*ssid����*/
#define 	CONF_HEADER_SIZE 	  sizeof(struct ap_cfg_info_st)	/*ͷ������*/

#define 	POPEN_CMD_LEN	256
#define 	POPEN_RESULT_LEN 256

#define COMMIT_LIB_LAUNCH_FLAG			"/tmp/commit_lib_launch_flag"	/*�������*/


/*********ap�����������*********/
/*ap����ģʽ*/
typedef enum WORK_MODE_TAG
{
  NORMAL_MODE = 0,
  HYBRID_MODE = 1,
  MONITOR_MODE = 2,
}WORK_MODE;


/*********radio�������*********/
/*�ŵ�����*/
typedef enum  BANDWIDTH_TYPE_TAG
{
  BANDWIDTH_AUTO = 0,
  BANDWIDTH_20,
  BANDWIDTH_40_MINUS,
  BANDWIDTH_40_PLUS,
}CHANNEL_WIDTH;

/*�ŵ�IDѡ��*/
typedef enum CHANNEL_ID_TAG
{
  CHANNEL_AUTO = 0,
  CHANNEL_001 = 1,
}CHANNEL_ID;

/*��������*/
typedef enum POWER_TYPE_TAG
{
  POWER_AUTO = 0,
  POWER_003 = 3,
}POWER_TYPE;

/*ɨ���������*/
typedef enum SCAN_CHANNEL_SCALE_TAG
{
  RECOMMEND_CHANNELS = 0,
  COUNTRY_CHANNELS = 1,
  ALL_CHANNELS  = 2,
}SCAN_CHANNEL_SCALE;


/*********wlan�������*********/
/*��������*/
typedef enum ENTRYPT_STYLE_TAG
{
	WAP2 = 0,
	PSK = 1,
}ENTRYPT_STYLE;


/*****************�����������********************/
/*��������*/
typedef enum IP_ACCQUIRE_STYLE_TAG
{
    STATIC_STYLE  = 1,
    DHCP_STYLE    = 2,
}IP_ACCQURE_STYLE;

/*ac����*/
struct ac_cfg_st
{
  uint32_t ac_host;
  uint16_t ac_port;
};


/*AP��������*/
struct ap_basic_cfg_st
{
	int32_t	country_code;            /*������*/
	WORK_MODE	work_mode;
	char		ap_desc[AP_DESC_MAX_SIZE]; /*ap������*/
	uint64_t  	ap_devid;
	uint8_t     debug_enable;          /*���Կ���*/
};

/*radio����*/
struct radio_cfg_st
{
  /*���߻�������*/
  RF_TYPE		rf_type;
  uint8_t 		rf_enable;
  char 			rf_mode[RADIO_MODE_MAX_SIZE];
  CHANNEL_WIDTH channel_width;
  uint8_t     	channel_id;
  uint8_t   		rf_power;
  int16_t      	rf_users_limit;
  uint8_t       band_ampdu;
  uint8_t       band_amsdu;
  uint16_t      band_beacon;
  uint16_t      band_dtim;
  uint8_t       band_leadcode;
  uint8_t       band_remax;
  uint16_t      band_rts;
  uint8_t       band_shortgi;
  /*�����Ż�����*/
  uint8_t vap_bridge;
  uint8_t mult_inspeed;
  uint8_t sta_rate_limit;
  uint8_t mult_optim_enable;
  uint8_t fairtime_enable;

 
  uint8_t 		ld_enable;
  uint16_t  report_radio_info_cycle;
  uint16_t  report_sta_info_cycle;
  /*ɨ�����*/
  uint16_t  hybrid_scan_cycle;
  uint16_t  hybrid_scan_time;
  uint16_t  monitor_scan_cycle;
  uint16_t  monitor_scan_time;
  uint16_t  normal_scan_cycle;
  uint16_t  normal_scan_time;
  SCAN_CHANNEL_SCALE scan_channels;
};

/*wlan����*/
struct wlan_cfg_st
{
  RF_TYPE rf_type;
  uint32_t wlan_id;
  uint8_t   hide;
  char	    encryption[ENCRYPT_MODE_SIZE];
  char      password[PASSWORD_MAX_SIZE];
  char      ssid[SSID_MAX_SIZE];
  uint8_t   wlan_enable;
};

/*�����Ż�����*/
struct wl_optim_cfg_st
{
	uint8_t vap_bridge;
	uint8_t mult_inspeed;
	uint8_t sta_rate_limit;
	uint8_t mult_optim_enable;
	uint8_t fairtime_enable;
};
#endif
