#ifndef _WIRELESS_H_
#define _WIRELESS_H_

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>   
#include <errno.h>
#include <strings.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "commit_common.h"
#include "ap_ioctl.h"
#include "custom_utility.h"


#define WL_SUCCESS          0
#define WL_FAILED           -1
#define RF_VAP_MAX_SIZE     16              /*ÿ����Ƶ���֧��16��VAP*/
#define AP_RF_MAX_SIZE      2               /*ÿ��AP���֧��2����Ƶ*/
#define RADIO_NAME_FORMAT   "wifi%d"        /*radio�豸��*/
#define VAP_NAME_2G_PREFIX  "ath2"          /*vap�豸��ǰ׺athN(ath2xxx,ath5xxx)*/
#define VAP_NAME_5G_PREFIX  "ath5"          /*vap�豸��ǰ׺*/
#define VAP_NAME_SUFFIX_LEN  3              /*vap�豸��׺����xxx(ath2xxx,ath5xxx).*/

struct ap_basic_info_st
{
  struct ap_basic_cfg_st basic_cfg;       
};


/**************************** ����vap *********************************/

/*wlan��������*/
typedef enum wlan_index_enum
{
    INDEX_WLAN_ID = 0,
    INDEX_HIDE_SSID,
    INDEX_ENCRYPT_AND_PWD,
    INDEX_WLAN_SSID,
    INDEX_WLAN_ENABLE,
    INDEX_WLAN_MAX
}wlan_index_t;


/*vap���ýṹ*/
struct wl_vap_st
{
    uint8_t                 is_used;                /*��ǰ�ڵ��Ƿ�ʹ��*/
    char                    vap_name[IF_NAME_LEN];      /*ath2xxx or ath5xxx*/
    struct wlan_cfg_st      wlan;
};

/**************************** ����radio ********************************/

/*rf��������������*/
typedef enum rf_index_enum
{
    INDEX_RF_ENABLE = 0,
    INDEX_RF_MODE,
    INDEX_CHANNEL_WIDTH,
    INDEX_CHANNEL_ID,
    INDEX_RF_POWER,
    INDEX_USERS_LIMIT,
    INDEX_AMPDU_ENABLE,
    INDEX_AMSUD_ENABLE,
    INDEX_BEACON_INTVAL,
    INDEX_DTIM,
    INDEX_LEAD_CODE,
    INDEX_RETRANS_MAX,
    INDEX_RTS,
    INDEX_SHORTGI,
    INDEX_BRIDGE_ENABLE,
    INDEX_FAIRTIME_ENABLE,
    INDEX_STA_RATE_LIMIT,
    INDEX_MULTI_INSPEED,
    INDEX_MULT_OPTIM_ENABLE,
    INDEX_LD_SWITCH, 

    INDEX_RF_MAX
}rf_index_enum_t;

/*radio���ø�����Ϣ�ṹ*/
struct radio_assist_info_st
{
  uint8_t is_used;               /*�ڵ��Ƿ��Ѿ�ʹ��*/
  uint8_t is_support;
  uint8_t is_configured;        /*�����Ƿ���Ч����ʼ��ʱ����Ϊ��Ч����*/
};

/*radio������Ϣ�ṹ*/
struct wl_radio_st
{
  struct radio_assist_info_st   assist;
  uint8_t                       rf_type;      
  char                          wifi_name[IF_NAME_LEN + 1];     /*radio�豸��,wifi0����wifi1*/
  int32_t                       ioctl_sock;
  struct radio_cfg_st           radio_cfg;
  uint8_t                       wlan_cnt;                       /*��ǰwlan����*/
  struct wl_vap_st              vaps[RF_VAP_MAX_SIZE];
};


/*���߹�����Ϣ�ṹ*/
struct wl_mgmt_st
{
    struct ap_basic_info_st     basic_info;
    struct wl_radio_st          radio[AP_RF_MAX_SIZE];          /*radio[0]-->2G, radio[1]-->5G*/
};

extern log_print g_log_print;
#define SAFE_FREE(_ptr)         if (_ptr) { free(_ptr); _ptr = NULL;}
#define SAFE_BEZERO(_ptr)       if (_ptr) { bzero(_ptr, sizeof(*_ptr));}
#define LOG_DEBUG(format,...)   do { g_log_print("d %s %d "format, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_INFO(format,...)    do { g_log_print("i %s %d "format, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_WARN(format,...)    do { g_log_print("w %s %d "format, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)

#endif

