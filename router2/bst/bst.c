/* Background speed test */
#include<bstapi.h> 
#include <stdlib.h>
#include <stdio.h>
void help(){

}
int main (int argc, char* argv[] ){
	struct bstresults bst;
	if ( bst_Init() < 0 ){
		goto L_FAILED;
		ret =-1;
	}
	bst_Start();
	sleep(10);
	bst.uplinkresult=123;
	bst.downlinkresult=456;
	bst.serveridresult=1;
	bst.latencyresult=12;
	bst.locationresult="london";
	bst.ISPresult="london ISP";
	bstResults_Update(bst.uplinkresult,bst.downlinkresult,bst.uplinkresult,bst.locationresult,bst.serveridresult,bst.ISPresult);
	bstResults_get(bst);
	printf ("%d ISP=%s\n",bst.downlinkresult,bst.ISPresult );
	bst_Stop();
	if ( bst_Uninit() < 0 ){
		goto L_FAILED;
		ret =-1;
	}	
L_FAILED:
	return ret;
}
