/*******************************************************************************
 * Copyright 2005  Hon Hai Precision Ind. Co. Ltd.
 * All Rights Reserved.
 * No portions of this material shall be reproduced in any form without the
 * written permission of Hon Hai Precision Ind. Co. Ltd.
 *
 * All information contained in this document is Hon Hai Precision Ind.
 * Co. Ltd. company private, proprietary, and trade secret property and
 * are protected by international intellectual property laws and treaties.
 *
 ******************************************************************************/

#ifndef __BD_UTIL_H
#define __BD_UTIL_H

/* cliff, for 3 hw SKUs */
#if (defined WNDR3400v2)
#define BOARD_ID_MAX_LEN    62
#else
#define BOARD_ID_MAX_LEN    64
#endif

/* added start by EricHuang, 12/04/2006 */
#define SN_MAX_LEN  32
#define PIN_MAX_LEN 8
/* added end by EricHuang, 12/04/2006 */

/* Foxconn added start, zacker, 12/24/2009, @burnsku */
#define BOARD_ID_OFFSET     0

#if (defined WNDR3400v2)
#define HW_REV_OFFSET       (BOARD_ID_OFFSET + BOARD_ID_MAX_LEN)
#define HW_REV_LEN          2
#define LAN_MAC_OFFSET      (HW_REV_OFFSET + HW_REV_LEN)
#else
#define LAN_MAC_OFFSET      BOARD_ID_MAX_LEN
#endif

#define WAN_MAC_OFFSET      (LAN_MAC_OFFSET + 6)
#define SN_OFFSET           (WAN_MAC_OFFSET + 6)
#define WCN_PIN_OFFSET      (SN_OFFSET      + SN_MAX_LEN)     /* added by EricHuang, 12/01/2006 */

#define RF_PARAM_OFFSET     0x100
/* Foxconn added end, zacker, 12/24/2009, @burnsku */

#define REGION_NUM_LEN      2
#define REGION_NUM_OFFSET   (WCN_PIN_OFFSET + PIN_MAX_LEN)
#define HWVER_LEN           32
#define HWVER_OFFSET      (REGION_NUM_OFFSET + REGION_NUM_LEN)

#define HW_REV_OFFSET       (HWVER_OFFSET + HWVER_LEN)
#define HW_REV_LEN          2
#define SW_FEATURE_OFFSET   (HW_REV_OFFSET + HW_REV_LEN)
#define SW_FEATURE_LEN      4

/* Foxconn added start, zacker, 12/24/2009, @burnsku */
#ifdef INCLUDE_BURNSKU
#define SKU_LEN             8
#define LANG_LEN            32
#define WL_REGION_LEN       4
#define TIMEZONE_LEN        8

/* Foxconn add start, Jenny Zhao, 12/29/2009 @burnsku*/
#define MAX_REGION_NUM      0xFFFF
#define NULL_REGION_NUM     0x0000
#define NA_REGION_NUM       0x0001
#define WW_REGION_NUM       0x0002
#define GR_REGION_NUM       0x0003
#define PR_REGION_NUM       0x0004
#define RU_REGION_NUM       0x0005
#define BZ_REGION_NUM       0x0006
#define IN_REGION_NUM       0x0007
#define KO_REGION_NUM       0x0008
#define JP_REGION_NUM       0x0009
#define AU_REGION_NUM       0x000a
#define CA_REGION_NUM       0x000b
#define US_REGION_NUM       0x000c  /* pling modified 07/09/2015, per NTGR's spec */
#define MX_REGION_NUM       0x000d
#define AP_REGION_NUM       0x000e
#define PA_REGION_NUM       0x000f

#define NULL_SKU            ""
#define NA_SKU              "NA"
#define WW_SKU              "WW"
#define GR_SKU              "GR"
#define PR_SKU              "PR"
#define RU_SKU              "RU"
#define BZ_SKU              "BZ"
#define IN_SKU              "IN"
#define KO_SKU              "KO"
#define JP_SKU              "JP"
#define AU_SKU              "AU"
#define CA_SKU              "CA" /*modified by Kathy, 09/23/2015 @ Router Spec rev14 that Negear Raymond Requested */
#define US_SKU              "US"    /* pling modified 07/09/2015, per NTGR's spec */
#define AP_SKU              "AP"
#define PA_SKU              "PA"

/* Foxconn add end, Jenny Zhao, 12/29/2009 */
/* Foxconn add start, Tony W.Y. Wang, 03/26/2010 @Single Firmware Implementation */
#ifdef SINGLE_FIRMWARE
#define NA_SKU_LANG         "English"
#define WW_SKU_LANG         "English"
#define GR_SKU_LANG         "German"
#define PR_SKU_LANG         "SimplifiedChinese"
#define RU_SKU_LANG         "Russian"
#define BZ_SKU_LANG         "Portuguese"
#define IN_SKU_LANG         "Indic"
#define KO_SKU_LANG         "Korean"
#define JP_SKU_LANG         "Japanese"
#endif
/* Foxconn add end, Tony W.Y. Wang, 03/26/2010 @Single Firmware Implementation */

struct sku_mapping_s
{
    unsigned short region_num;
    unsigned char sku_name[SKU_LEN];
    unsigned char def_lang[LANG_LEN];
    unsigned char def_wl_region[WL_REGION_LEN];
    unsigned char def_timezone[TIMEZONE_LEN];
};
#endif
/* Foxconn added end, zacker, 12/24/2009, @burnsku */

/* Foxconn added start, zacker, 01/26/2010, @get_st_chksum */
#ifdef INCLUDE_GET_ST_CHKSUM
#define MAX_FILE_PATH       256
/* foxconn modified start, zacker, 09/07/2010, @128K_ST */
#ifdef ST_ML_SIZE_128K
#define ML_BLOCK_SIZE       0x20000
#else
#define ML_BLOCK_SIZE       0x10000
#endif
/* foxconn modified end, zacker, 09/07/2010, @128K_ST */

struct string_table_header
{
    unsigned long size;
    unsigned long chksum;
    unsigned char version[4];
    unsigned char reserv[4];
};
#endif
/* Foxconn added end, zacker, 01/26/2010, @get_st_chksum */

#ifdef BD_SIZE_4K
#define BD_SIZE             0x1000 /* changed from 0x10000 to 0x1000, for WGRv9 */
#else
#ifdef FLASH_SECTOR_128K  /* Foxconn added by Silver for 16M,32M */
#define BD_SIZE             0x20000
#else
#define BD_SIZE             0x10000
#endif
#endif

/* foxconn added start, zacker, 08/23/2010, @preset_wl_security */
#define BD_RECORD_START_ADDR    (BD_SIZE >> 1)

#define BD_RECORD_MAGIC         (0xBD0D0BBD) /* magic */

#define WL_MODE_2G              (1)
#define WL_MODE_5G              (2)
#if (defined R8000) || (defined R7800) || defined(BCA_HNDROUTER)
#define WL_MODE_5G_2            (3)
#endif

#define SSID_MAX_SIZE           (33)  /* strlen(ssid) = 32 */
#define PASSPHRASE_MAX_SIZE     (64)  /* strlen(passphrase) = 63 */

typedef struct bd_record_s
{
    unsigned int magic;
    unsigned short type;
    unsigned short val_len; /* length of val */
    unsigned char val[];
} bd_record;

typedef enum bd_record_type_e
{
    BD_RECORD_TYPE_NONE                     = (0x0000),
    BD_RECORD_TYPE_START                    = (0x0001),

    BD_RECORD_TYPE_PRESET_SSID_2G           = (0x0001),
    BD_RECORD_TYPE_PRESET_PASSPHRASE_2G     = (0x0002),
    BD_RECORD_TYPE_PRESET_SSID_5G           = (0x0003),
    BD_RECORD_TYPE_PRESET_PASSPHRASE_5G     = (0x0004),
    BD_RECORD_TYPE_PRESET_SSID_5G_2         = (0x0005),
    BD_RECORD_TYPE_PRESET_PASSPHRASE_5G_2   = (0x0006),
    BD_RECORD_TYPE_HTTPSENABLE  = (0x0007),

    BD_RECORD_TYPE_END
} bd_record_type;
/* foxconn added end, zacker, 08/23/2010, @preset_wl_security */
extern int read_board_data(char *buf);
extern int write_board_data(char *buf);

extern int bd_read_eth_mac(unsigned char *lan_mac, unsigned char *wan_mac);
extern int bd_write_eth_mac(unsigned char *lan_mac, unsigned char *wan_mac);

extern int bd_read_board_id(char *board_id, int len);
extern int bd_write_board_id(char *board_id);

extern int bd_read_pin(char *pin, int len);
extern int bd_write_pin(unsigned char *pin);

/* for SmartWizard 2.0 */
extern int bd_read_sn(char *sn, int len);
extern int bd_write_sn(char *sn);
extern int macAddr_shift(unsigned char *macaddr, int offset);

#if 0
extern int bd_read_hw_rev(char *hw_rev, int len);
extern int bd_write_hw_rev(char *hw_rev);
#endif
#if (defined INCLUDE_ROUTER_ANALYTICS)
extern int bd_read_sw_feature(char *hw_rev, int len);
extern int bd_write_sw_feature(char *hw_rev);
#endif
/* Foxconn added start, zacker, 12/24/2009, @burnsku */
#ifdef INCLUDE_BURNSKU
extern int bd_read_sku_info(unsigned short *region_num,
                         unsigned char *sku_name, unsigned int sku_name_len,
                         unsigned char *lang, unsigned int lang_len,
                         unsigned char *wl_region, unsigned int wl_region_len,
                         unsigned char *tz, unsigned int tz_len);

extern int bd_write_sku_info(unsigned short region_num);
extern int bd_write_init_5G_channel(char *sku_name, char *wl_region);
#endif
/* Foxconn added end, zacker, 12/24/2009, @burnsku */

/* Foxconn added start, zacker, 01/26/2010, @get_st_chksum */
#ifdef INCLUDE_GET_ST_CHKSUM
extern int cal_st_chksum(int mtd_index, unsigned long *st_cal_chksum);
#endif
/* Foxconn added end, zacker, 01/26/2010, @get_st_chksum */

extern int bd_read_httpsEnable(char *httpsEnable, int len);
extern int bd_write_httpsEnable(char *httpsEnable);

/* foxconn added start, zacker, 08/23/2010, @preset_wl_security */
#ifdef PRESET_WL_SECURITY
extern int bd_read_ssid(char *ssid, int len, int mode);
extern int bd_write_ssid(char *ssid, int mode);
extern int bd_read_passphrase(char *passphrase, int len, int mode);
extern int bd_write_passphrase(char *passphrase, int mode);
/*added by dennis start,01/14/2013,@burn_all_bd command*/
extern int bd_read_record_2(unsigned short type, char *value_buf, char *bd_buf,
                        unsigned int *value_len, unsigned int buf_size);

extern int bd_write_record_2(unsigned short type, char *value_buf, char *new_bd_buf,
                        unsigned int value_len);
/*added by dennis end,01/14/2013,@burn_all_bd command*/
#endif
/* foxconn added end, zacker, 08/23/2010, @preset_wl_security */

extern int is_russia_specific_support (void);   /* Foxconn added, Wins, 05/16/2011, @RU_IPTV */
extern int is_china_specific_support (void); /* Foxconn add, Edward zhang, 09/05/2012, @add IPTV support for PR SKU*/
extern int is_ru_region(void);
extern int is_wave_or_flat(void); /*Foxconn Jimmy Hong added, 12/10/2015, for identify R8500 housing*/

extern int bd_enable_wl_manufacturer(int enable); /*foxconn Han edited, 05/25/2021*/
#if defined(_XDSL_PRODUCT) && defined(D6400)
extern int is_pes_specific_support (void);
#endif
#if defined(BCA_HNDROUTER)
extern int is_en_load_default(void);
#if defined(CIRCLE_PARENTAL_CONTROL)
extern int is_circle_disable_region(void);
#endif
#endif
#endif

