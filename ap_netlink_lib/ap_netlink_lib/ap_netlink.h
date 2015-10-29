#ifndef AP_NETLINK_H__
#define AP_NETLINK_H__

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>
#include <inttypes.h>

#ifndef NETLINK_WIRELESS
#define NETLINK_WIRELESS              (NETLINK_GENERIC + 10) //netlinkЭ���
#endif

#define NETLINK_GROUP_ID    1     /*ʹ�õ�netlink��IP*/
#define MAX_PAYLOAD (128 * 1024)  /*��󻺴�*/
#define IEEE80211_NWID_LEN 32
#define IEEE80211_ADDR_LEN 6

#pragma pack(push)

#pragma pack(4)


/*netlink�ϱ���Ϣ������*/
typedef enum ugw_report_type
{
    UGW_NEIGHBOR_WLAN_INFO  = 1,    //ɨ���ھ�AP��Ϣ�ϱ�
    UGW_ASSOC_STA_INFO      = 2,    //�����ն���Ϣ�ϱ�
    UGW_RADIO_INFO          = 3,    //RADIO״̬��Ϣ�ϱ�
    UGW_STA_AUTH_NOTIF      = 4,    //�ն���֤֪ͨ
    UGW_SCAN_STA_INFO       = 5,    //ɨ���ն���Ϣ
}ugw_report_type_t;


/*netlink��Ϣ�ṹ��*/
typedef struct ugw_netlink_data
{
    u_int32_t type;     //netlink��Ϣ����
    u_int32_t subtype;  //��һ��������Ϣ����ʹ��
    u_int32_t count;    //�ṹ�����
    u_int8_t  buf[0];   //�ṹ������
}ugw_netlink_data_t;


/*����WLAN��Ϣ�ṹ��*/
typedef struct ugw_nwlan_info_
{
    u_int64_t    ap_devid;
    u_int32_t    rf_type;
    u_int32_t    channel_id;
    u_int32_t    rssi;
    u_int32_t    wlan_id;
    u_int8_t     ssid[IEEE80211_NWID_LEN+1];   
    u_int8_t     bssid[IEEE80211_ADDR_LEN];

	/* add end */
}ugw_nwlan_info_t;

#define IP_LEN 4
/*�����ն���Ϣ�ṹ��*/
typedef struct ugw_sta_info_
{
    u_int8_t       sta_mac[IEEE80211_ADDR_LEN];
    u_int8_t       ip[IP_LEN];
    u_int8_t       bssid[IEEE80211_ADDR_LEN];
    u_int8_t       ssid[IEEE80211_NWID_LEN+1];
    u_int32_t      rssi;
    u_int32_t      rf_type;         //����Ƶ�� 0��ʾ2G,1��ʾ5G,��radio rf_typeһ��
    u_int32_t      is_dualband;     //�Ƿ�˫Ƶ
    u_int32_t      channel_id;      //�ն��ŵ�
    u_int32_t      avg_tx_bytes;    //ƽ������������
    u_int32_t      avg_rx_bytes;    //ƽ������������
}ugw_sta_info_t;


#define MODE_LEN  30//����Э����ַ�������,11nght40
/*radio״̬��Ϣ�ϱ�*/
typedef struct ugw_radio_info_
{
    u_int8_t    mode[MODE_LEN];
    u_int32_t   rf_type;       //0��ʾ2G,1��ʾ5G
    u_int32_t   channel_id;    
    u_int32_t   txpower;       //dBm
    u_int32_t   curr_users;    //��ǰ�û���
    u_int32_t   channel_use;   //�ٷֱ� 65��ʾ65%
    int32_t     noise;         //����

}ugw_radio_info_t;


/*�ն���������Ϣ�ϱ�*/
typedef struct ugw_sta_auth_notif_
{
    u_int8_t    sta_mac[IEEE80211_ADDR_LEN];//�ն�MAC��ַ
    u_int64_t   ap_devid;                   //�ն˽����ap
    u_int32_t   rf_type;                    //0��ʾ2G,1��ʾ5G
    u_int32_t   curr_users;                 //radio��ǰ���û���
    u_int8_t    bssid[IEEE80211_ADDR_LEN];  //�ն˽����vap bssid
    u_int32_t   wlan_id;                    //����WLAN ID
    u_int32_t   action;                     //1��ʾ��֤�ɹ� 0��ʾ�����֤
}ugw_sta_auth_notif_t;


#define FULL_AMOUNT_REPORT  1  //ɨ���ն�ȫ���ϱ�
#define INCREMENT_REPORT    2  //ɨ���ն������ϱ�
/*ɨ���ն���Ϣ�ϱ��ṹ��*/
typedef struct ugw_scan_sta_info_
{
    u_int8_t    sta_mac[IEEE80211_ADDR_LEN];//�ն�MAC��ַ
    u_int8_t    rssi;                       //�����
    u_int8_t    rf_type;                    //Ƶ������
}ugw_scan_sta_info_t;


/*MAC��ַ�ַ�����ʽ*/
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"

/*AP ID�ַ�����ʽ*/
#define DEVIDSTR "%02x%02x%02x%02x%02x%02x%02x%02x"


int ugw_netlink_sock();  //����netlink sock
int ugw_netlink_init();   //ʹ��ǰ��Ҫ����,ֻ��һ��
int ugw_netlink_destroy(); //�����˳�����һ��
int ugw_netlink_sendmsg(void *data, int len); //����������Ϣ
int ugw_netlink_recvmsg(void **data, int *len); //����������Ϣ

inline const char* MAC_STR(const u_int8_t mac[]);

inline const char* PRINT_APID(u_int64_t devid);

#pragma pack(pop)

#endif  //~AP_NETLINK_H__