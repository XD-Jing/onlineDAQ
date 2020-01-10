#include <string>
#include <iostream>
#include <sMDT/sMDT.h>

int main(){

    std::cout << "in DecMDT"<<std::endl;
    //sMDT *dec = new sMDT("/atlas/data19/liji/MDT/backup/run00187691_20190301.dat", "output.root");
    sMDT *dec = new sMDT("/afs/atlas.umich.edu/home/mengxt/public/sMDT_analysis_code/run00187754_20190401.dat", "output.root");
    //dec->set_max_words(100);
    dec->process();
    return 0;

}
