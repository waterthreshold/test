#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "action.h"


const  char Adjectives[][C_MAX_KEY_STR_SIZE] = 
{
    "ancient",      "aquatic",      "basic",    "black",        "blue",
    "brave",        "breezy",       "bright",   "calm",         "cool",
    "classy",       "clever",       "cloudy",   "crispy",       "curly",
    "daily",        "free",         "dizzy",    "dynamic",      "elated",
    "elegant",      "excited",      "exotic",   "fancy",        "bold",
    "festive",      "fluffy",       "fresh",    "chummy",       "fuzzy",
    "gentle",       "hungry",       "gifted",   "grand",        "great",
    "green",        "happy",        "heavy",    "helpful",      "husky",
    "icy",          "manic",        "jagged",   "jolly",        "joyous",
    "kind",         "large",        "little",   "lively",       "lucky",
    "magical",      "melodic",      "mighty",   "misty",        "modern",
    "narrow",       "new",          "nifty",    "noisy",        "odd",
    "orange",       "pastel",       "perfect",  "phobic",       "pink",
    "polite",       "purple",       "quaint",   "quick",        "quiet",
    "rapid",        "red",          "rocky",    "round",        "royal",
    "rustic",       "shiny",        "silent",   "silky",        "silly",
    "smiling",      "slow",         "smooth",   "strong",       "sunny",
    "sweet",        "thirsty",      "tiny",     "deep",         "uneven",
    "unusual",      "vanilla",      "vast",     "watery",       "wide",
    "witty",        "windy",        "yellow",   "young",        "zany",
};

const  char Nouns[][C_MAX_KEY_STR_SIZE] = 
{
    "car",          "apple",        "balloon",  "banana",       "breeze",
    "bird",         "boat",         "box",      "bug",          "butter",
    "cartoon",      "canoe",        "carrot",   "cello",        "chair",
    "cheese",       "coconut",      "comet",    "curtain",      "cream",
    "daisy",        "diamond",      "earth",    "panda",        "fire",
    "finch",        "flower",       "flute",    "giant",        "gadfly",
    "hat",          "hill",         "iris",     "ink",          "jade",
    "jungle",       "hippo",        "kayak",    "lake",         "bolt",
    "lotus",        "mango",        "mint",     "moon",         "mesa",
    "nest",         "ocean",        "onion",    "octopus",      "oboe",
    "owl",          "lotus",        "mango",    "phoenix",      "piano",
    "plum",         "planet",       "pond",     "potato",       "prairie",
    "quail",        "rabbit",       "raccoon",  "raven",        "river",
    "road",         "rosebud",      "sea",      "ship",         "shoe",
    "shrub",        "skates",       "sky",      "socks",        "sparrow",
    "spider",       "squash",       "sheep",    "star",         "street",
    "sun",          "table",        "teapot",   "trail",        "train",
    "tree",         "tomato",       "trumpet",  "tuba",         "tulip",
    "unit",         "unicorn",      "valley",   "vase",         "violet",
    "violin",       "water",        "wind",     "window",       "zoo",
};
static int  block_num[]={911};
   



int is_block_num ( int n ){
	int total = sizeof (block_num) / sizeof (int);
	int i;
	int block = 0;
	for (i=0 ; i < total ; i++) {
		if ( n == block_num[i] ) {
			block = 1;
			break;
		}
	}
	return block;
} 

static char *generate_ssid(mode) {
	time_t t ;
	srand ((unsigned ) time (&t));
	int adj_num= sizeof (Adjectives)/ sizeof (Adjectives[0]);
	int Nouns_num= sizeof (Nouns)/ sizeof (Nouns[0]);
	//char passphrase[128]={0};
	char* ssid_5g=malloc(SSID_MAX_SIZE);
	//char ssid_5g[128]={0};
	int adj_idx =  rand() % adj_num;
	int Noun_idx =  rand() % Nouns_num;
	int num = rand ()  % 999 +1;
	while (is_block_num (num)){
		num = rand ()  % 999 +1;
	}
	int ssid_num = rand () % 99 +1;
	//printf ("%d %d %d %d \n ",adj_idx,Noun_idx ,num,ssid_num);
	//snprintf (passphrase,sizeof (passphrase) ,"%s%s%03d",Adjectives[adj_idx],Nouns[Noun_idx],num);
	// snprintf (ssid_2g,sizeof (ssid_2g) ,"NETGEAR%02d",ssid_num);
	snprintf (ssid_5g,SSID_MAX_SIZE ,"NETGEAR%02d",ssid_num);
	if (mode == WL_MODE_5G ){
		strncat (ssid_5g,"-5G",SSID_MAX_SIZE);
	}
	return ssid_5g;
}
char* gen_ssid (){
	
	int mode = WL_MODE_2G;
	return generate_ssid(mode);
}
char* gen_ssid5G (){
	int mode = WL_MODE_5G;
	return generate_ssid(mode);
}
int set_ssid5G(char* value){
	int ret = -1 ;
	ret = bd_write_ssid(value,WL_MODE_5G);
	
	return ret;
	
}
int set_ssid(char* value){
	int ret = -1 ;
	ret = bd_write_ssid(value,WL_MODE_2G);
	
	return ret;
	
}
char* get_ssid5G(){
	char* ssid=malloc (SSID_MAX_SIZE) ;
	bd_read_ssid(ssid, SSID_MAX_SIZE, WL_MODE_5G);
	return ssid;
}
char* get_ssid(){
	char* ssid=malloc (SSID_MAX_SIZE) ;
	bd_read_ssid(ssid, SSID_MAX_SIZE, WL_MODE_2G);
	return ssid;
}

char* get_pass (){
	char* pass=malloc (PASSPHRASE_MAX_SIZE) ;
	bd_read_passphrase(pass, PASSPHRASE_MAX_SIZE, WL_MODE_2G);
	return pass;
}
int set_pass(char *value){
	int ret=-1;
	ret = bd_write_passphrase (value,WL_MODE_2G );
	return ret;
}
char* gen_pass(){
	time_t t ;
	srand ((unsigned ) time (&t));
	int adj_num= sizeof (Adjectives)/ sizeof (Adjectives[0]);
	int Nouns_num= sizeof (Nouns)/ sizeof (Nouns[0]);
	//char passphrase[128]={0};
	char* pass_2g=malloc(PASSPHRASE_MAX_SIZE);
	//char ssid_5g[128]={0};
	int adj_idx =  rand() % adj_num;
	int Noun_idx =  rand() % Nouns_num;
	int num = rand ()  % 999 +1;
	while (is_block_num (num)){
		num = rand ()  % 999 +1;
	}
	snprintf (pass_2g,PASSPHRASE_MAX_SIZE ,"%s%s%03d",Adjectives[adj_idx],Nouns[Noun_idx],num);
	
	return pass_2g;
}
char* get_pass5g (){
	char* pass=malloc (PASSPHRASE_MAX_SIZE) ;
	bd_read_passphrase(pass, PASSPHRASE_MAX_SIZE, WL_MODE_5G);
	return pass;
}
int set_pass5g(char *value){
	int ret=-1;
	ret = bd_write_passphrase (value,WL_MODE_5G );
	return ret;
}

/*
int main (int argc , char *argv[]) {
	int ret = 0;
	time_t t ;
	srand ((unsigned ) time (&t));
	int adj_num= sizeof (Adjectives)/ sizeof (Adjectives[0]);
	int Nouns_num= sizeof (Nouns)/ sizeof (Nouns[0]);
	char passphrase[128]={0};
	char ssid_2g[128]={0};
	char ssid_5g[128]={0};
	int adj_idx =  rand() % adj_num;
	int Noun_idx =  rand() % Nouns_num;
	int num = rand ()  % 999 +1;
	while (is_block_num (num)){
		num = rand ()  % 999 +1;
	}
	int ssid_num = rand () % 99 +1;
	//printf ("%d %d %d %d \n ",adj_idx,Noun_idx ,num,ssid_num);
	snprintf (passphrase,sizeof (passphrase) ,"%s%s%03d",Adjectives[adj_idx],Nouns[Noun_idx],num);
	snprintf (ssid_2g,sizeof (ssid_2g) ,"NETGEAR%02d",ssid_num);
	snprintf (ssid_5g,sizeof (ssid_5g) ,"NETGEAR%02d-5G",ssid_num);
	printf ("%s,%s,%s\n",ssid_2g,ssid_5g,passphrase);
	return ret ;
}
*/