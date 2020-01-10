#ifndef _sMDT_h_
#define _sMDT_h_

#include "TFile.h"
#include "TTree.h"

#include <fstream>

#include <sMDT/FormatTDC.h>

class sMDT
{
    private:

        std::ifstream ifile;

        TFile* root;
        TTree* triggerTree;
        TTree* signalTree;
        int max_words;

        int event;
        int tdc;
        int channel;
        float trigger_adc_time;
        float trigger_tdc_time;
        float signal_adc_time;
        float signal_tdc_time;
        float signal_tdc_time_corr;

        std::vector<double> v_LUT;
        double ADC_correlation(double w);
        void initBranches();

    public:
        sMDT(const std::string &fin, const std::string &fout);
        ~sMDT(){};
        void set_max_words(int max_words){this->max_words = max_words;};
        int process();

};

#endif
