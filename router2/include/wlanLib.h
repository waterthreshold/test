#ifndef _WLANLIB_H_
#define _WLANLIB_H_
//#include <net/if.h>

#define UUID_MAX_LEN 36
#define MIN_BSSID_NUM       2
#define MAX_BSSID_NUM       4
#if 0
/* WPS_UI definitions */
#define WPS_UI_CMD_NONE         0
#define WPS_UI_CMD_START        1
#define WPS_UI_CMD_STOP         2

#define WPS_UI_METHOD_NONE      0
#define WPS_UI_METHOD_PIN       1
#define WPS_UI_METHOD_PBC       2

#define WPS_UI_ACT_NONE         0
#define WPS_UI_ACT_ENROLL       1
#define WPS_UI_ACT_CONFIGAP     2
#define WPS_UI_ACT_ADDENROLLEE  3

#define WPS_UI_PBC_NONE         0
#define WPS_UI_PBC_HW           1
#define WPS_UI_PBC_SW           2
#endif

//#define WPS_ENR_DUMP_BUF_LEN (32 * 1024)
#define WPS_ENR_DUMP_BUF_LEN (128 * 1024)

enum {
    WLAN_BSS_SSID,
    WLAN_BSS_RSSI,
    WLAN_BSS_SNR,
    WLAN_BSS_NOISE,
    WLAN_BSS_VIE
};

enum {
    SET_DEFAULT,
    AVAILABLE_ROUTER,
    AVAILABLE_EXTENDER,
    IDLE_EXTEDNER,
    NON_NTGR_ROUTER,
    NOT_SUPPORT
};

typedef struct vie_data {
   unsigned char *data;
} VIE_DATA;

int get_wlan_radio_status(char *band);
int get_wlan_mode(char *band,char *cur_mode);
int get_wlan_channel(char *if_name, int *ctrl_channel, int *ext_channel);
int should_stop_wps(void);
int sync_band_steering_settings(int restore);
#if 0
int is_wps_monitor_up(void);
int get_wps_config_command(void);
#endif

int burn_rf_param(void);
//int load_rf_param(void);
int wireless_configure();
int wireless_tpc_configure(void);

#if 0
typedef struct wps_env_s
{
    int wps_config_command;
    int wps_action;
    char wps_uuid[UUID_MAX_LEN];
    char wps_ifname[IFNAMSIZ];
} wps_env;
#endif

extern int get_bssid_by_if(char *ifname, unsigned char *mac, int len);



#include "wlan_common.h"


extern int wlan_set_wifi_nvram(EBAND_TYPE band, EIF_TYPE wifi_type, char* nvram_mid_name, char* value);
extern char* wlan_get_wifi_nvram(EBAND_TYPE band, EIF_TYPE wifi_type, char* nvram_mid_name);
extern int wlan_get_wifi_nvram_name(EBAND_TYPE band, EIF_TYPE wifi_type, char* nvram_mid_name, char* nvram_name, int len);
extern int wlan_match_wifi_nvram(EBAND_TYPE band, EIF_TYPE wifi_type, char* nvram_mid_name, char* value);

#endif /*_WLANLIB_H_*/
