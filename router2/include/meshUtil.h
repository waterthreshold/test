#ifndef _MESHUTIL_H_
#define _MESHUTIL_H_

#define MESH_BUF_LEN 512

typedef enum mesh_role {
    MESH_BASE = 0,
    MESH_SATALLITE
} mesh_role_t;

typedef enum mesh_operation {
    MESH_OP_INIT = 0,
    MESH_OP_RESTART
} mesh_operation_t;

enum {
    MESH_MAP_VAL_BRCM = 0,
    MESH_MAP_VAL_FXCN = 1,
    MESH_MAP_VAL_DEFAULT = 2,
};

typedef struct mesh_map {
    char *nvramVar_brcm;
    char *nvramVar_fxcn;
    char *val_init;
    int optionFlag;
    void (*cb_handler)(struct mesh_map*);
} mesh_map_t;

int mesh_nvram_convert(mesh_map_t *arr, int arrLen);
int mesh_cfg(mesh_role_t role);

#endif
