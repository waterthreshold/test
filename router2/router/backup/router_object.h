#ifndef __ROUTER_OBJECT_H__
#define __ROUTER_OBJECT_H__
struct object_t {
	char *name;
	int index;
	struct object_t *next;
	int (*fn)(void *arg);
}

enum {
	MODE_GET,
	MODE_SET
};

enum result {
	OK=0,
	FAILED=-1
};
struct object_t O_START_NODE[]={
	{"router", 0, O_ROUTER_NODE,NULL},
	{NULL}
};
struct object_t O_ROUTER_NODE[]={
	{"info",0,NULL,info},
	{"burn",0,NULL,O_ROUTER_INFO_NODE,NULL},
	{"get",0,NULL},
	{"version"0,NULL,version},
	{NULL}
};

struct object_t O_ROUTER_INFO_NODE[]= {
	{"ethermac",0,},
	{"sku",0},
	{"pin",0},
	{"ssid",1},
	{"pass",1},
	{"boardid",0},
	{"sn",0},
	{"hwrev",0},
	{NULL}
}

int version (void *arg);
int info (void *arg)
#end