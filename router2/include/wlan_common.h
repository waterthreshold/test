
#ifndef _WLAN_COMMON_H
#define _WLAN_COMMON_H
typedef enum {
    BAND_TYPE_2G    = 0x0001,
    BAND_TYPE_5G    = 0x0002,
    BAND_TYPE_5G2   = 0x0004,
    BAND_TYPE_NMRP_2G = 0x0008,
    
    BAND_TYPE_ALL   = BAND_TYPE_2G | BAND_TYPE_5G | BAND_TYPE_5G2 | BAND_TYPE_NMRP_2G
} EBAND_TYPE;

typedef enum {
    IF_TYPE_AP      = 0x0001,
    IF_TYPE_CLI     = 0x0002,
    IF_TYPE_AP_GUEST = 0x0004,
    IF_TYPE_AP_GUEST2= 0x0008,
    IF_TYPE_AP_GUEST3= 0x0010,
    IF_TYPE_AP_FH= 0x0020,
    IF_TYPE_AP_BH= 0x0040,
    IF_TYPE_AP_SCHEDULE= 0x0080,
    
    IF_TYPE_ALL     = IF_TYPE_AP | IF_TYPE_CLI | IF_TYPE_AP_GUEST | IF_TYPE_AP_GUEST2 | IF_TYPE_AP_GUEST3 | IF_TYPE_AP_FH | IF_TYPE_AP_BH | IF_TYPE_AP_SCHEDULE
} EIF_TYPE;


/* TODO should be put in ambitUtil.h */
#define WIFI_2G_MAIN_NVRAM_PREFIX         "wla_"
#define WIFI_5G_MAIN_NVRAM_PREFIX         "wlg_"
#define WIFI_5G2_MAIN_NVRAM_PREFIX        "wlh_"
#define WIFI_2G_GUEST_NVRAM_PREFIX        "wla_"
#define WIFI_5G_GUEST_NVRAM_PREFIX        "wlg_"
#define WIFI_5G2_GUEST_NVRAM_PREFIX       "wlh_"
#define WIFI_2G_FH_NVRAM_PREFIX           "wla_"
#define WIFI_5G_FH_NVRAM_PREFIX           "wlg_"
#define WIFI_5G_BH_NVRAM_PREFIX           "wlg_b_"
#define WIFI_2G_SCHEDULE_NVRAM_PREFIX     "wla_"
#define WIFI_5G_SCHEDULE_NVRAM_PREFIX     "wlg_"
#define WIFI_5G2_SCHEDULE_NVRAM_PREFIX    "wlh_"

#define WIFI_2G_MAIN_NVRAM_POSTFIX        ""
#define WIFI_5G_MAIN_NVRAM_POSTFIX        ""
#define WIFI_5G2_MAIN_NVRAM_POSTFIX       ""
#define WIFI_2G_GUEST_NVRAM_POSTFIX       "_2"
#define WIFI_5G_GUEST_NVRAM_POSTFIX       "_2"
#define WIFI_5G2_GUEST_NVRAM_POSTFIX      "_2"
#define WIFI_2G_FH_NVRAM_POSTFIX          ""
#define WIFI_5G_FH_NVRAM_POSTFIX          ""
#define WIFI_5G_BH_NVRAM_POSTFIX          ""
#define WIFI_2G_SCHEDULE_NVRAM_POSTFIX    "_3"
#define WIFI_5G_SCHEDULE_NVRAM_POSTFIX    "_3"
#define WIFI_5G2_SCHEDULE_NVRAM_POSTFIX   "_3"


#endif
