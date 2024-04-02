#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define C_MAX_KEY_STR_SIZE                  (32)
#define C_MAX_SKU_STR_SIZE                  (8)
static char sku_name [][C_MAX_SKU_STR_SIZE] = {
	"none",
	"NA",
	"WW",
	"GR",
	"PR",
	"RU",
	"BZ",
	"IN",
	"KO",
	"JP",
	"AU",
	"CA",
	"US",
	"MX",
	"AP",
	"PA",
};
static char Adjectives[][C_MAX_KEY_STR_SIZE] = 
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

static char Nouns[][C_MAX_KEY_STR_SIZE] = 
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
static int  block_num[]={ 911};
   


int valid_sku_input (char *str){
	int ret =-1 ;
	
	if (str ==NULL){
		return -1 ;
	}
	int total_sku  = sizeof (sku_name) / sizeof (sku_name[0]);
	int index = atoi (str);
	if (index > 0  && index <= total_sku) {
		ret =0;
	}
	return ret;
	
}
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
int genssid (){
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