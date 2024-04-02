#ifndef _WPSUTIL_H_
#define _WPSUTIL_H_

/* From main/components/router/shared/wlif_utils.h */
typedef enum wps_ui_status_code_id {
    WPS_UI_INVALID          = -1,
    WPS_UI_INIT             = 0,
    WPS_UI_FINDING_PBC_STA  = 1,
    WPS_UI_OK               = 2,
    WPS_UI_ERR              = 3,
    WPS_UI_TIMEOUT          = 4,
    WPS_UI_PBCOVERLAP       = 5,
    WPS_UI_FIND_PBC_AP      = 6,
    WPS_UI_FIND_PIN_AP      = 7
} wps_ui_status_code_id_t;

// WPS Status id and code value pairs
typedef struct wps_ui_status {
	wps_ui_status_code_id_t idx;
	char *val;
} wps_ui_status_t;

// Array of wps ui status codes
static wps_ui_status_t wps_ui_status_arr[] =
{
    {WPS_UI_INIT, "0"},
    {WPS_UI_FINDING_PBC_STA, "1"},
    {WPS_UI_OK, "2"},
    {WPS_UI_ERR, "3"},
    {WPS_UI_TIMEOUT, "4"},
    {WPS_UI_PBCOVERLAP, "8"},
    {WPS_UI_FIND_PBC_AP, "9"},
    {WPS_UI_FIND_PIN_AP, "11"}
};

typedef enum {
    WPS_JOIN_PBC = 1,
    WPS_JOIN_STA_PIN = 2,
    WPS_CANCEL = 3
}WPS_ACTION;

int turn_off_ongoing_wps();
int wps_ui_pbc();
int wps_ui_client_pin(char *pin);

#endif
