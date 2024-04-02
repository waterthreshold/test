#ifndef _WLAN_UTIL_H_
#define _WLAN_UTIL_H_

#include "upnp.h"
#include "wlan_common.h"

/* PUT common WLAN APIs here */
/******************************************************************************/
extern int idxStrToLen(char *idxStr);
/******************************************************************************/

/******************************************************************************/


#define GUEST_NETWORK_NUM   1 //only support 1 guest network now

extern int get_cur_prefix_suffix(EBAND_TYPE band_type, EIF_TYPE if_type,
        char *prefix, char *suffix);
extern int get_tmp_prefix_suffix(EBAND_TYPE band_type, EIF_TYPE if_type,
        char *prefix, char *suffix);
extern char *set_nvram_name(char *prefix, char *suffix, char *name, char *buf);
extern char *get_wlan_ifname(EBAND_TYPE band, EIF_TYPE if_type);
/******************************************************************************/

/******************************************************************************/
#ifdef PROFILE_FEATURE
#define MAX_WIRE_PROFILE_NUM    10
#define MAX_WIFI_PROFILE_NUM    10
#define MAX_PROFILE_NUM         (MAX_WIRE_PROFILE_NUM + MAX_WIFI_PROFILE_NUM)

#define NTGR_IE_ALLOC_SIZE  64

typedef enum {
    SORT_USE_MARK_ASCENDING = 0,
    SORT_USE_MARK_DESCENDING = 1,
} PROFILE_SORT;

typedef struct profile_s
{
    int idx;
    int use_mark;
} profile_t;

extern char *profile_set_nvram_name(int idx, char* prefix, char* suffix,
        char *name, char *buf);
extern int profile_get_prefix_suffix(int idx, EBAND_TYPE band_type,
        EIF_TYPE if_type, char *prefix, char *suffix);

extern int profile_is_empty(int idx);
extern int profile_is_wired(int idx);
extern int profile_is_wireless(int idx);

extern int profile_get_use_mark(int idx);
extern int profile_set_use_mark(int idx, int use_mark);

extern int profile_init(profile_t *profiles, int *num);
extern int profile_sort(profile_t *profiles, int num, PROFILE_SORT sort);
extern int profile_apply(int idx);
extern int profile_delete(int idx);
extern int profile_save(int idx, char *name);
extern int profile_auto_save(void);
#endif
/******************************************************************************/

/******************************************************************************/
extern int convert_mode_params(char *src_mode,
        char *src_sta_band, char *src_ap_band,
        char *dst_mode, char *dst_sta_band, char *dst_ap_band);
/******************************************************************************/

/******************************************************************************/

//Jasmine add for QCA platform, 08/04/2016
/*
0~100 means: pscale_100=0
tpscale_75=1
tpscale_63=1
tpscale_50=2
tpscale_33=2
tpscale_25=3
tpscale_12=3
tpscale_min=4



*/

#ifdef CONFIG_QCA_SDK
    typedef enum {
    TPC_LEVEL_0 = 0, /* 100% */
    TPC_LEVEL_1 = 1, /* 75% */
    TPC_LEVEL_2,     /* 50% */
    TPC_LEVEL_3,     /* 25% */
    TPC_LEVEL_4,     /* 0% */
    TPC_LEVEL_DEF = TPC_LEVEL_4,

    TPC_LEVEL_MAX,
} TPC_LEVEL;



#else

typedef enum {
    /* start from 1 */
    TPC_LEVEL_1 = 1, /* 25% */
    TPC_LEVEL_2,     /* 50% */
    TPC_LEVEL_3,     /* 75% */
    TPC_LEVEL_4,     /* 100% */
    TPC_LEVEL_DEF = TPC_LEVEL_4,

    TPC_LEVEL_MAX,
} TPC_LEVEL;

#endif
/******************************************************************************/
#define NTGR_IE_ALLOC_SIZE  64
extern int init_ntgr_ie(EBAND_TYPE band);
extern int action_ntgr_ie(char *ifname, int action, unsigned char *ntgr_ie);
extern int save_ntgr_ie(char *name, unsigned char *ntgr_ie);
extern int notify_hop_count(unsigned int hot_count);

/******************************************************************************/
typedef enum {
    ACL_POLICY_DISABLE = 0,
    ACL_POLICY_ALLOW   = 1,
    ACL_POLICY_DENY    = 2,
} ACL_POLICY_MODE;

extern int acl_set_policy(ACL_POLICY_MODE policy);
extern int acl_add_entry(char *dev_mac);
extern int acl_del_entry(char *dev_mac);
/******************************************************************************/

#define MAX_NETWORK_NUM     128
#define MAX_GUI_NETWORK_NUM 64 /* Foxconn modified by Max Ding, 10/14/2017 change from 32 to 64 per Netgear Lancelot's request */
#define SECURITY_NONE       0x01
#define SECURITY_WEP        0x02
#define SECURITY_WPA_PSK    0x04
#define SECURITY_WPA_PSK2   0x08
#define SECURITY_MIX        0x0c //SECURITY_WPA_PSK | SECURITY_WPA_PSK2
#define SECURITY_WPA_RADIUS 0x10
#define SECURITY_TKIP       0x20
#define SECURITY_AES        0x40
#define SECURITY_WPA3       0x80
#define SECURITY_WPA3_MIX   0x88 //SECURITY_WPA_SAE | SECURITY_WPA_PSK2
#define SECURITY_ALL_MIX    0x8c //SECURITY_WPA_PSK | SECURITY_WPA_PSK2 | SECURITY_WPA3

#define NETWORK_MAX_RSSI    -20
#define NETWORK_MIN_RSSI    -93

#define CIPHER_TKIP         1
#define CIPHER_AES          2
#define CIPHER_SAE          4

#define WL_MODE_G_ONLY  0x0001
#define WL_MODE_HT20    0x0002
#define WL_MODE_HT40    0x0004
#define WL_MODE_HT80    0x0008
#define WL_MODE_HT160   0x0010
#define WL_MODE_N       0x0020
#define WL_MODE_AC      0x0040

#define WLAN_MASK_SSID                      0x00000001
#define WLAN_MASK_SECURITY                  0x00000002
#define WLAN_MASK_CHAN                      0x00000004
#define WLAN_MASK_MODE                      0x00000008
#define WLAN_MASK_SAME_SECU                 0x00000010
#define WLAN_MASK_ALL_NORMAL                0x0000001f
#define WLAN_MASK_BROADCAST                 0x00000020
#define WLAN_MASK_ENABLE                    0x00000040

#define MAX_SSID_LEN    32
typedef struct wifi_config_s
{
    char    ssid[MAX_SSID_LEN+1];
    int     channel;
    int     security_type;
    int     unicast_cipher;//crypto
    char    passphrase[64+1];
    int     wep_length;
    int     wep_defaKey;
    char    key[4][64];
    int     auth_type; /* no use now*/
    int     same_ssid; /* same ssid with root AP */
    int     same_secu; /* same security with root AP */
    int     disable; /* for wireless setting page */
    int     broadcast; /* for wireless setting page */
    int     coexist; /* for wireless setting page */
    int     mode; /* for wireless setting page */
} wifi_config_t;

typedef struct network_s
{
    char    ssid[32+1];
    int     channel;
    int     sig;
    int     security_type;
    char    operation_mode[12];
    int     unicast_cipher;
    unsigned char mac [6];
    #ifdef CONFIG_SMART_MESH
    int     smesh_support;
    #endif
    int     seamless_roaming;/* Foxconn added by Max Ding, 03/16/2017 */
    //char    bssid[18];
} network_t;

#define FILE_AVAILABLE_NETWORK      "/tmp/available_network"
#define FILE_AVAILABLE_5G_NETWORK   "/tmp/available_5g_network"
#define FILE_AVAILABLE_5G_1_NETWORK   "/tmp/available_5g_1_network"
#define FILE_AVAILABLE_5G_2_NETWORK   "/tmp/available_5g_2_network"
#define FILE_WL_TMP_RESULT          "/tmp/wl_tmp_result"

#define WLAN_IDLE_DEVICE_2G "/tmp/wlan_idle_devices_2g"
#define WLAN_IDLE_DEVICE_5G "/tmp/wlan_idle_devices_5g"
#define WLAN_IDLE_DEVICE_5G2 "/tmp/wlan_idle_devices_5g2"
/* Foxconn add start, Max Ding, 08/15/2018 */
#if defined(EXTENDER_GUEST)
#define WLAN_IDLE_DEVICE_2G_GUEST "/tmp/wlan_idle_devices_2g_guest"
#define WLAN_IDLE_DEVICE_5G_GUEST "/tmp/wlan_idle_devices_5g_guest"
#define WLAN_IDLE_DEVICE_5G2_GUEST "/tmp/wlan_idle_devices_5g2_guest"
#endif
/* Foxconn add end, Max Ding, 08/15/2018 */

#define VENDOR_IE_ADD       1
#define VENDOR_IE_UPDATE    2
#define VENDOR_IE_REMOVE    3

#define BLOCK_CHS_NUM               64

struct CH_INFO {
    unsigned short RemainTime;
    unsigned char Channel;
    unsigned char Flags;
};

struct BLOCK_CH {
    int Size;
    int Region;
    long UpdateTime;
    struct CH_INFO ChList[BLOCK_CHS_NUM];
};

/* Foxconn add start, Max Ding, 02/18/2016 */
/* use it in apply_wlan_fast() */
#define APPLY_WLAN_AP_SETTING_2G            0x00000001 /* include ssid, security type, passphrase */
#define APPLY_WLAN_AP_SETTING_5G            0x00000002
#define APPLY_WLAN_AP_SETTING_5G2           0x00000004
#define APPLY_WLAN_AP_SETTING_ALL           0x00000007
#define APPLY_WLAN_CLI_SETTING_2G           0x00000008
#define APPLY_WLAN_CLI_SETTING_5G           0x00000010
#define APPLY_WLAN_CLI_SETTING_5G2          0x00000020
#define APPLY_WLAN_CLI_SETTING_ALL          0x00000038
#define APPLY_WLAN_AP_CLI_SETTING           0x0000003f  /* 6 interfaces' ssid/security type/passphrase */
#define APPLY_WLAN_AP_CHAN_2G               0x00000040
#define APPLY_WLAN_AP_CHAN_5G               0x00000080
#define APPLY_WLAN_AP_CHAN_5G2              0x00000100
#define APPLY_WLAN_AP_MODE_2G               0x00000200
#define APPLY_WLAN_AP_MODE_5G               0x00000400
#define APPLY_WLAN_AP_MODE_5G2              0x00000800
//#define APPLY_WLAN_ALL_SETTING              0x00000fff /* include channel, mode, ssid, security type, passphrase */
#define APPLY_WLAN_AP_BC_2G                 0x00001000
#define APPLY_WLAN_AP_BC_5G                 0x00002000
#define APPLY_WLAN_AP_BC_5G2                0x00004000
#define APPLY_WLAN_COEX_2G                  0x00008000
#define APPLY_WLAN_REGION                   0x00010000
#define APPLY_WLAN_AP_2G_SETTING            0x00019241 //(APPLY_WLAN_AP_SETTING_2G|APPLY_WLAN_AP_CHAN_2G|APPLY_WLAN_AP_MODE_2G|APPLY_WLAN_AP_BC_2G|APPLY_WLAN_COEX_2G|APPLY_WLAN_REGION)
#define APPLY_WLAN_AP_5G_SETTING            0x00012482 //(APPLY_WLAN_AP_SETTING_5G|APPLY_WLAN_AP_CHAN_5G|APPLY_WLAN_AP_MODE_5G|APPLY_WLAN_AP_BC_5G|APPLY_WLAN_REGION)
#define APPLY_WLAN_AP_5G2_SETTING           0x00014904 //(APPLY_WLAN_AP_SETTING_5G2|APPLY_WLAN_AP_CHAN_5G2|APPLY_WLAN_AP_MODE_5G2|APPLY_WLAN_AP_BC_5G2|APPLY_WLAN_REGION)
#define APPLY_WLAN_BAND_STEER               0x00020000
#define APPLY_WLAN_AUTO_SYNC                0x00040000
#define APPLY_WLAN_SEAMLESS                 0x00080000
#define APPLY_WLAN_RESTART_MASK             0x00800000
#define APPLY_WPS_SETTING                   0x01000000
#define APPLY_WAN_SETTING                   0x02000000
#define APPLY_WLAN_CONVERT_PARAM            0x10000000
#define APPLY_WLAN_CLI_CHECK_ASSOC          0x20000000
/* Foxconn add end, Max Ding, 02/18/2016 */

#if (defined RALINK_SDK)
#include "ralink_wlan_util.h"
#elif (defined U12H092)
#include "mv_wlan_util.h"
#elif (defined U12H083) || (defined ATHEROS_WLAN)
#include "ath_wlan_util.h"
#else
#include "bcm_wlan_util.h"
#endif

extern network_t g_network[MAX_NETWORK_NUM];
extern network_t g_5Gnetwork[MAX_NETWORK_NUM];


#endif
