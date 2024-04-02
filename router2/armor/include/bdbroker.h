#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define BD_BOX_ERROR_MESSAGE_LENGTH 64
#define BD_BOX_ERROR_DESCRIPTION_LENGTH 188

/**
 * @brief The normal use of bd_error_t is to allocate it
 *        on the stack, and pass a pointer to the function.
 */
typedef struct {
    int code;
    char message[BD_BOX_ERROR_MESSAGE_LENGTH];
    char description[BD_BOX_ERROR_DESCRIPTION_LENGTH];
} bd_box_error_t;

// sync array in bd_box_set_error()
#define BD_BOX_INVALID_PARAMS 1
#define BD_BOX_INVALID_JSON_SCHEMA 2
#define BD_BOX_INTERNAL_ERROR 3

/**
 * Make sure you increment the major number if the protocol is changed.
 */
#define LIBBDBROKER_PROTOCOL    "1.3"

#define VERSION_FILE_PATH       "bdbrokerd.version"
#define BDBROKERD_SOCKET_PATH   ":bdbrokerd-" LIBBDBROKER_PROTOCOL ".skt"

/**
 * init bitdefender library
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_init(void);

/**
 * init bitdefender library
 *
 * @param bdpath: pointer to a 0-terminated char array representing the
 *      install path of the BD agent as an absolute path, e.g. "/opt/bitdefender".
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_init2(const char* bdpath);

/**
 * uninit bitdefender library
 */
void bd_box_uninit(void);

/**
 * send token and mac address to bitdefender for cloud registration purposes
 *
 * @param token: pointer to a 0-terminated char array representing the token to be sent
 * @param mac: pointer to a 0-terminated char array representing the mac address to be sent
 * @param redeem_code: NULL pointer or pointer to a 0-terminated char array representing the redeem_code to be sent
 *
 * if a NULL pointer is provided for 'redeem_code', the cloud registration process will use
 * the value of 'mac' for subscription redeem
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_register_to_cloud(const char *token, const char *mac, const char *redeem_code);

/**
 * @param registration_info: pointer which contains a 0-terminated char array,
 *      representing the router information in JSON format
 * @param error: an pointer to bd_box_error_t to be filled with error information
 *      when the function returns -1. If NULL, no error information is
 *      returned to the caller.
 * @return 0 if successful, -1 otherwise
 */
int bd_box_register(const char *registration_info, bd_box_error_t *error);

/**
 * example of router_info json:
 * {
 *     "name": "<string_value>", // router name
 *     "model": "<string_value>", // router model
 *	   "feature_set_level": "<string_value>",
 *     "interfaces": [
 *         {
 *             "name": <string_value>, // interface name
 *             "type": <string_value>  // interface type
 *         },
 *         {
 *             "name": <string_value>,
 *             "type": <string_value>
 *         },
 *         {
 *             "name": <string_value>,
 *             "type": <string_value>
 *         }
 *     ],
 *     "use_va_cloud_trigger": <boolean_value>
 * }
 *
 * example with real values
 * {
 *     "name": "Netgear R7000P",
 *     "model": "R7000p",
 *     "feature_set_level": "armor-light-1.1",
 *     "interfaces": [
 *         {
 *             "name": "eth0",
 *             "type": "wan"
 *         },
 *         {
 *             "name": "eth1",
 *             "type": "lan"
 *         },
 *         {
 *             "name": "eth2",
 *             "type": "lan"
 *         }
 *     ],
 *     "use_va_cloud_trigger": false
 * }
 */

/**
 * set router info
 *
 * @param router_info: pointer which contains a 0-terminated char array,
 *      representing the router information in json format
 *          - interface type needs to be one of ["wan", "lan"]
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_set_router_info(const char *router_info);

/**
 * get router info
 *
 * @param router_info: pointer which contains a 0-terminated char array,
 *      representing the router information in json format
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_router_info(char **router_info);

/**
 * get version info
 *
 * @param version_info: pointer which contains a 0-terminated char array,
 *      representing the version information in json format
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_version_info(char **version_info);

enum bd_box_event_type {
    BD_BOX_DEVICE_DISCOVERY,
    BD_BOX_SUBSCRIPTION_CHANGED,
    BD_BOX_CLOUD_REGISTRATION_STATUS,
    BD_BOX_DEVICES_LIST_UPDATED,
    BD_BOX_BDAGENT_STARTED,
    BD_BOX_VA_STATUS_CHANGED,
    NUM_EVENTS,
};

/**
 * @brief convert string representation of type to enum
 *
 * @param type_str string representation of enum member; all caps
 * @return enum bd_box_event_type that corresponds to type. NUM_EVENTS is
 *      returned if string does not match any member.
 */
enum bd_box_event_type bd_box_event_type_from_str(const char *type_str);

/**
 * @brief convert enum to string representation
 *
 * @param type enum member
 * @return string represention of enum member
 */
const char *bd_box_event_type_to_str(enum bd_box_event_type type);

/**
 * examples of BD_BOX_DEVICE_DISCOVERY events:
 * {
 *      "did": <string_value>,
 *      "ip": <string_value>,
 *      "mac": <string_value>
 * }
 * or
 * {
 *      "ip": <string_value>,
 *      "mac": <string_value>,
 *      "user_agent": <string_value>
 * }
 * or
 * {
 *      "mac": <string_value>,
 *      "device_type": <string_value>,
 *      "device_os": <string_value>,
 *      "device_os_version": <string_value>
 * }
 */

/**
 * event callback function
 *
 * @param event: pointer to a 0-terminated char array representing the event in json format
 * @param event_cb_arg: pointer specified at subscription
 */
typedef void (*bd_box_event_callback)(const char *event, void *event_cb_arg);

/**
 * subscribe to events
 *
 * @param event_type: event's type
 * @param event_callback: function to be called each time the registered event occurs
 * @param arg: pointer to be passed as the second argument to callback
 * @param event_fd: output pointer to be filled in with read-only notification fd
 *
 * the 'event_fd' parameter determines the method used to wait for events and
 * call the registered callback:
 *      - by providing a NULL pointer then an internal thread is used
 *          to wait for events and call the registered callback
 *      - by providing a non-NULL pointer then a read-only file descriptor
 *          is filled in 'event_fd' parameter and can be used in select/epoll
 *          to know when events are received; one can use 'bd_box_read_event_fd'
 *          in order to have the callbacks for received events called
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_subscribe(const enum bd_box_event_type event_type,
    bd_box_event_callback event_cb, void *event_cb_arg,
    int *event_fd);

/**
 * unsubscribe from events
 *
 * @param event_type: event's type
 */
void bd_box_unsubscribe(const enum bd_box_event_type event_type);

enum bd_box_event_read_mode {
    BD_BOX_READ_ONE,
    BD_BOX_READ_ALL,
};

/**
 * read events synchronously
 * as a side effect, callbacks are called for all read events
 *
 * @param event_fd: notification fd obtained at subscription
 * @param mode: choose to read one or all available events
 *
 * will block if no event is available
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_read_event_fd(const int event_fd, const enum bd_box_event_read_mode mode);

/**
 * enable bitdefender services
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_enable(void);

/**
 * disable bitdefender services
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_disable(void);

/**
 * retrieve status of bitdefender services
 *
 * @param enabled: an output pointer to be filled with:
 *        * 1, if services are enabled
 *        * 0, if services are disabled
 *
 * @return 0 if enabled, -1 otherwise
 */
int bd_box_is_enabled(int *enabled);

/**
 * get subscription status
 *
 * @param subscription_status: output pointer to be filled in with 0-terminated char array,
 *      representing the subscription status in json format; must be freed by caller
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_subscription_status(char **subscription_status);

/**
 * example of device_info json:
 * {
 *     "device_id": "<string_value>" // required. Can be obtained for each device via get_devices.
 *     "name": "<string_value>", // optional. Router name.
 *     "traffic_blocked": <int_value> // optional. 1 if traffic should be blocked, 0 if not.
 * }
 *
 * example with real values
 * {
 *     "device_id": "92c9daca-2db4-11e8-a4c4-d481d7d7860d"
 *     "name": "Mike's Phone",
 *     "traffic_blocked": 1
 * }
 */

/**
 * set device info
 *
 * @param device_info: pointer which contains a 0-terminated char array,
 *      representing device information in json format. Devices are identified
 *      by setting the mandatory device_id key in the json.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_set_device_info(const char *device_info);

/**
 * set device online status
 *
 * @param device_online_status: pointer which contains a 0-terminated char array,
 *      representing device information in json format. Devices are identified
 *      by setting the mandatory mac key in the json.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_set_device_online_status(const char *device_online_status);

/**
 * get a list of discovered devices
 *
 * @param requested_device_ids: pointer which contains a 0-terminated char array,
 *      representing an array of device ids in json format
 *      for which device information must be retrieved:
 * [
 *      "<string-value>", ...
 * ]
 * example:
 * [
 *      "12c9daca-2db4-11e8-a4c4-d481d7d7860d",
 *      "22c9daca-2db4-11e8-a4c4-d481d7d7860d"
 * ]
 *
 * use one of the following options to retrieve all devices:
 *      - provide a NULL pointer for 'requested_device_ids'
 *      - provide an empty json array
 *
 * @param devices: output pointer to be filled in with 0-terminated char array,
 *      representing a json array of json objects, where each object represents a
 *      discovered device. The pointer must be freed by caller.
 *      Each device contains all the fields specified in the documentation for the
 *      BD_BOX_DEVICE_DISCOVERY event.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_devices(const char *requested_device_ids, char **devices);

/**
 * Remove a discovered satellite.
 *
 * This function does not ban the device from being connected. That is:
 * 1) An offline device that is removed will remain removed until the next time
 *    it comes online, when it will be reconnected.
 * 2) An online device that is removed will be shortly reconnected unless its
 *    status is also set to offline. At that point, it will be reconnected the
 *    next time it comes online, similarly to case above.
 *
 * @param device: pointer to a null-terminated char array representing a stringified
 *        JSON object containing the identifier info of the device to be removed.
 *        The JSON object keys: "mac" - <string_value>.
 *
 * Example:
 * {
 *   "mac": "aa:bb:cc:dd:ee:ff"
 * }
 *
 * @return 0 if successful, -2 if device not found, -1 otherwise
 */
int bd_box_remove_satellite(const char *satellite_data);

/**
 * start VA network scan
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_va_start(void);

/**
 * stop all scheduled VA scans
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_va_stop(void);

/**
 * retrieve VA scanning status
 *
 * @param running: an output pointer to be filled with:
 *        * 1, if VA is currently running a scan
 *        * 0, if VA is not running a scan
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_va_status(int *running);

/**
 * start a router self assessment scan
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_va_self_scan_start(void);

/**
 * set a VA schedule
 *
 * @param schedule: pointer which contains a 0-terminated char array,
 *      representing a VA schedule in JSON format. Format:
 *  {
 *      "at": "09:00", // 00:00 - 23:59
 *      "every": {
 *          "num": 1,
 *          "unit": "day" // day, week, month
 *      },
 *      "on": { // only FOR week and month
 *          "prefix": "first", // (FOR week) none or omitted, (FOR month) -> first, second, third, fourth, fifth, last
 *          "day": "monday", // monday, tuesday, wednesday, thursday, friday, saturday, sunday, 1-7 (FOR week), 1-31 (FOR month)
 *      }
 *  }
 *
 * @param error: a output pointer to be filled with error information
 *      when the function returns -1. If NULL, no error information is
 *      returned to the caller. Must be freed by caller.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_va_set_schedule(const char *schedule, char **error);

/**
 * enable pro features
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_pro_features_enable(void);

/**
 * disable pro features
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_pro_features_disable(void);

/**
 * reapply firewall rules
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_reapply_firewall_rules(void);

/**
 * get feature status
 *
 * @param features: pointer which contains a 0-terminated char array,
 *      representing a list of feature names to query.
 *      Example:
 *      [
 *          "ip_reputation",
 *          "device_scan"
 *      ]
 *
 * @param feature_info: output pointer to be filled with a 0-terminated
 *      char array, representing the status of the queried features.
 *      Possible statuses are one of ["on", "off", "error"].
 *      Format:
 *      {
 *          "ip_reputation" : "on",
 *          "device_scan" : "off"
 *      }
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_feature(const char *features, char **feature_info);

/**
 * set feature status
 *
 * @param feature_info: pointer which contains a 0-terminated char array,
 *      representing status information for the targeted features in
 *      json format. Valid statuses are one of ["on", "off", "default"].
 *      Format:
 *      {
 *          "ip_reputation" : "default",
 *          "device_scan" : "off"
 *      }
 *
 * @param feature_info_success: pointer which contains a 0-terminated char
 *      array, representing status information for the targeted features
 *      after the requested update in json format. Possible statuses are one
 *      of ["on", "off", "error"].
 *      Format:
 *      {
 *          "ip_reputation" : "on",
 *          "device_scan" : "off"
 *      }
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_set_feature(const char *feature_info, char **feature_info_success);

/**
 * Get the BD agent diagnosis report
 *
 * @param diagnosis_report: output pointer to be filled in with a 0-terminated char array,
 *      representing the BD agent diagnosis report in json format. To be freed by the caller.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_diagnosis_report(char **diagnosis_report);

/**
 * Get the BD agent status report
 *
 * @param status_report: output pointer to be filled in with a 0-terminated char array,
 *      representing the BD agent status report in json format. To be freed by the caller.
 *
 * @return 0 if successful, -1 otherwise
 */
int bd_box_get_status_report(char **status_report);

#ifdef __cplusplus
};
#endif
