#include "Dmesonana.cc"

//decaychannel 2 is D0

void run_Dmesonana(int startFile, int endFile, char *filelist, int decaychannel)
{
    Dmesonana *a = new Dmesonana;

    a->LoopOverFile(startFile, endFile, filelist, decaychannel);

    //delete a; 
}
