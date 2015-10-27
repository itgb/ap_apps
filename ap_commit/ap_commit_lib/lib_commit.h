#ifndef _LIB_COMMIT_H_
#define _LIB_COMMIT_H_
#include <stdint.h>
#include <stdarg.h>
#include "commit_common.h"

/*libcommit.soʹ�÷�����*/
/*1.wireless_commit_init��ʼ����*/
/*2.ʹ��create_config_obj�����Ӷ��󣨵�ǰ֧��CONF_BASIC,CONF_RADIO,CONF_WLAN�������Ͷ���*/
/*3.���������Ӷ����ʹ��pack_config_objs�ɽ������Ӷ�������һ����Ķ���PACKED_OBJ*/
/*4.��PACKED_OBJ���ݸ�config_deliver,��Ч����*/
/*5.���ýӿ�free_config_obj�ͷ�PACKED_OBJ*/
/*6.����wireless_commit_uninit�ͷſ���Դ*/
/*NOTE:display_config_objs�����ڴ�ӡ��������֤���������Ƿ����Ԥ��*/
/*NOTE:set_xxx_xxx����������Ӧ���������ӦԪ��*/


int32_t wl_set_log_cb(log_print print);



int32_t wirless_commit_init();

/**
* @brief �����·��ӿ�
* @param	 cfg_info
* @return
* @remark 		�ýӿ��ṩ���ⲿ���ã����ڽ����ⲿ����
* @see
* @author tgb
**/
int32_t config_deliver(const struct ap_cfg_info_st  *cfg_info);

void  wireless_commit_uninit();

/**
* @brief		����ָ�����ͣ���������
* @remark null
* @author tgb
**/
struct ap_cfg_info_st *create_config_obj(CONFIG_CATEGORY conf_type);

/**
* @brief		�����Ӷ����һ����Ķ��󣬲��ͷ��Ӷ���
* @return	��NULL����ʾ����ɹ������ɹ��ͷ��Ӷ���NULL����ʧ�ܣ��Ӷ���δ�ͷ�
* @remark null
* @see
* @author tgb
**/
struct ap_cfg_info_st *pack_config_objs(uint8_t obj_cnt,...);

void free_config_obj(struct ap_cfg_info_st *obj);

void display_config_objs(const struct ap_cfg_info_st *info);

/*======================CONF_BASIC======================*/
int32_t set_basic_country_code(struct ap_cfg_info_st *obj, const int32_t country_code);

/**
* @brief		��������- ����ģʽ
* @param 	
* @param 	
* @return	
* @remark  normal, hybrid, monitor���ֹ���ģʽ
* @see
* @author tgb
**/
int32_t set_basic_work_mode(struct ap_cfg_info_st *obj, const int8_t work_mode);

/**
* @brief		��������-ap����
* @param 	
* @param 	
* @return	
* @remark  normal, hybrid, monitor���ֹ���ģʽ
* @see
* @author tgb
**/
int32_t set_basic_ap_desc(struct ap_cfg_info_st *obj, const char* ap_desc);

int32_t set_basic_ap_devid(struct ap_cfg_info_st *obj, const uint64_t dev_id);


/*======================CONF_RADIO======================*/
int32_t set_radio_rf_type(struct ap_cfg_info_st *obj, const uint8_t rf_type);

int32_t set_radio_rf_enable(struct ap_cfg_info_st *obj, const uint8_t rf_enable);

int32_t set_radio_rf_mode(struct ap_cfg_info_st *obj, const char* rf_mode);

int32_t set_radio_channel_width(struct ap_cfg_info_st *obj, const uint8_t chan_width);

int32_t set_radio_channel_id(struct ap_cfg_info_st *obj, const uint8_t chan_id);

int32_t set_radio_power(struct ap_cfg_info_st *obj, const uint8_t power);

int32_t set_radio_users_uplimit(struct ap_cfg_info_st *obj, const uint32_t user_limit);


/*======================CONF_WLAN======================*/
/**
* @brief		��������-wlan֧�ֵ���Ƶ����
* @param 	
* @param 	
* @return	
* @remark  
* @see
* @author tgb
**/
int32_t set_wlan_rf_type(struct ap_cfg_info_st *obj, const uint8_t rf_type);

int32_t set_wlan_id(struct ap_cfg_info_st *obj, const uint16_t wlan_id);

int32_t set_wlan_hide_ssid(struct ap_cfg_info_st *obj, const uint8_t hide_enable);

int32_t set_wlan_ssid(struct ap_cfg_info_st *obj, const char* ssid);


int32_t set_wlan_enable(struct ap_cfg_info_st *obj, const uint8_t enable);
#endif
