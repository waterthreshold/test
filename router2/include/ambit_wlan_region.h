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

#ifndef _AMBIT_WLAN_REGION_H
#define _AMBIT_WLAN_REGION_H

/* region define:
 * value    -- region
 * 0        -- Select Region
 * 1        -- Africa
 * 2        -- Asia
 * 3        -- Australia
 * 4        -- Canada
 * 5        -- Europe
 * 6        -- Israel
 * 7        -- Japan
 * 8        -- Korea
 * 9        -- Mexico
 * 10       -- South America
 * 11       -- US -- North America (include Canada)
 * 12       -- Middle East (Saudi Arabia)
 * 13       -- Reserve1 (U12H081_PR treat it as Australia)
 * 14       -- Russia
 * 15       -- Reserve2
 * 16       -- China
 * 17       -- India
 * 18       -- Malaysia
 * 19       -- Middle East (Iran/Lebanon/Qatar)
 * 20       -- Middle East (Turkey/Egypt/Tunisia/Kuwait)
 * 21       -- Middle East (Algeria/Syria/Yemen)
 * 22       -- Middle East (United Arab Emirates)
 * 23       -- Singapore
 * 24       -- Taiwan
 * 25       -- Vietnam
 * 26       -- Hong Kong
 */

typedef enum wl_region_e
{
    WL_REGION_SELECT = 0,
    WL_REGION_AFRICA,
    WL_REGION_ASIA,
    WL_REGION_AUSTRALIA,
    WL_REGION_CANADA,
    WL_REGION_EUROPE,
    WL_REGION_ISRAEL,
    WL_REGION_JAPAN,
    WL_REGION_KOREA,
    WL_REGION_MEXICO,
    WL_REGION_SOUTH_AMERICA, //10
    WL_REGION_NORTH_AMERICA,
    WL_REGION_MIDDLE_EAST_SA,
    WL_REGION_RESERVE1, /* U12H081_PR treat it as Australia */
    WL_REGION_RUSSIA,
    WL_REGION_RESERVE2, //15
    WL_REGION_CHINA,
    WL_REGION_INDIA,
    WL_REGION_MALAYSIA,
    WL_REGION_MIDDLE_EAST_ILQ,
    WL_REGION_MIDDLE_EAST_TETK, //20
    WL_REGION_MIDDLE_EAST_ASY,
    WL_REGION_MIDDLE_EAST_UAE,
    WL_REGION_SINGAPORE,
    WL_REGION_TAIWAN,
    WL_REGION_VIETNAM,
    WL_REGION_HONG_KONG,    //26
    WL_REGION_LAST
} wl_region_E;

typedef struct s_region_list
{
    int num;
    wl_region_E region[WL_REGION_LAST];
} S_region_list;

typedef struct s_region_info
{
    //int auto_ch_2g; // auto ch of 2g is always enabled
    //int start_ch_2g; //always start from 1
    int end_ch_2g;
    int dfs_enable_5g; /* don't use single nvram to control since it will vary with region */
    int auto_ch_5g; /* don't use compile flag to control since it will vary with region */
    int ch_list_5g_ht20_len;
    int ch_list_5g_ht20[32]; /* the 1st one is the default display channel in GUI when switching region and when the region doesn't support auto channel */
    int ch_list_5g_ht40_len;
    int ch_list_5g_ht40[32]; /* the 1st one is the default display channel in GUI when switching region and when the region doesn't support auto channel */
    int ch_list_5g_ht80_len;
    int ch_list_5g_ht80[32]; /* the 1st one is the default display channel in GUI when switching region and when the region doesn't support auto channel */
    char ccode_2g[8]; /* 2.4G country code, e.g. "EU", "Q1" of EU/32, Q1/14 */
    int regrev_2g; /* 2.4G regrev, e.g. 32, 14 of EU/32, Q1/14 */
    char ccode_5g[8]; /* 5G country code, e.g. "EU", "Q1" of EU/32, Q1/14 */
    int regrev_5g; /* 5G regrev, e.g. 32, 14 of EU/32, Q1/14 */
} S_region_info;

/* defined in project/product -> wlan_region.c */
extern char *region_str_id[];
extern S_region_list region_list;
extern S_region_info g_region_info[];
//extern void init_region_list(); /*Foxconn add by Gene Chen, 2015/09/21@FCC new rule*/

#endif
