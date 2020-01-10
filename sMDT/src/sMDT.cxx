//#include <AsgTools/MessageCheck.h>
#include <sMDT/sMDT.h>
#include <bitset>
#include <iostream>

#define MSG(str) std::cout << str << std::endl;

sMDT :: sMDT (const std::string& fin, const std::string& fout) : max_words(-1)
{
    this->root = new TFile(fout.c_str(), "recreate");
    this->ifile.open(fin.c_str(), std::fstream::binary);

    this->v_LUT.clear();
    for (int i=0; i<400; i++) this->v_LUT.push_back(109./ std::exp(1.11925 + 2.08708e-2 * i));

    this->triggerTree = new TTree("Trigger", "Trigger");
    this->triggerTree->Branch("event"           , &event           , "event/I"           );
    this->triggerTree->Branch("tdc"             , &tdc             , "tdc/I"             );
    this->triggerTree->Branch("channel"         , &channel         , "channel/I"         );
    this->triggerTree->Branch("trigger_adc_time", &trigger_adc_time, "trigger_adc_time/F");
    this->triggerTree->Branch("trigger_tdc_time", &trigger_tdc_time, "trigger_tdc_time/F");

    this->signalTree = new TTree("Signal", "Signal");
    this->signalTree->Branch("event"               , &event               , "event/I"               );
    this->signalTree->Branch("tdc"                 , &tdc                 , "tdc/I"                 );
    this->signalTree->Branch("channel"             , &channel             , "channel/I"             );
    this->signalTree->Branch("trigger_adc_time"    , &trigger_adc_time    , "trigger_adc_time/F"    );
    this->signalTree->Branch("trigger_tdc_time"    , &trigger_tdc_time    , "trigger_tdc_time/F"    );
    this->signalTree->Branch("signal_adc_time"     , &signal_adc_time     , "signal_adc_time/F"     );
    this->signalTree->Branch("signal_tdc_time"     , &signal_tdc_time     , "signal_tdc_time/F"     );
    this->signalTree->Branch("signal_tdc_time_corr", &signal_tdc_time_corr, "signal_tdc_time_corr/F");
}

double sMDT :: ADC_correlation(double w){
    if (w>400.0 || w<0) return 0;
    return this->v_LUT[static_cast<int>(w)];
}

void sMDT :: initBranches(){
    this->tdc = -999e3;
    this->channel = -999e3;
    this->trigger_adc_time = -999.e3;
    this->trigger_tdc_time = -999.e3;
    this->signal_adc_time = -999.e3;
    this->signal_tdc_time = -999.e3;
    this->signal_tdc_time_corr = -999.e3;
}

int sMDT :: process(){

    std::vector<WORD> vSignalHead, vSignalTrail, vTriggerHead, vTriggerTrail;
    vSignalHead.clear(); vSignalTrail.clear(); vTriggerHead.clear(); vTriggerTrail.clear();

    WORD word;
    int loop = 0;
    event = 0;
    while (ifile.read((char*)&word, sizeof(WORD)) && (loop<this->max_words || this->max_words==-1)){
        loop ++;
        if (word.packet() == PACKET::MEASURE_HEAD){ // store head words
            //MSG("   " << word.coarse() << "   "<< word.fine());
            if (word.tdc()==1 && word.channel()==23) vTriggerHead.push_back(word);
            else if(word.tdc()!=1) vSignalHead.push_back(word);
        }
        else if(word.packet() == PACKET::MEASURE_TRAIL){ // store trail words
            //MSG("   " << word.coarse() << "   "<< word.fine());
            if (word.tdc()==1 && word.channel()==23) vTriggerTrail.push_back(word);
            else if(word.tdc()!=1) vSignalTrail.push_back(word);
        }
        else if(word.packet() == PACKET::GROUP_HEAD || word.packet() == PACKET::TDC_HEAD || word.packet() == PACKET::TDC_TRAIL){ // analysis
            initBranches();
            if (vTriggerHead.size()>0){
                WORD trigger = vTriggerHead[0];
                if (vTriggerHead.size()>1){
                    float total_coarse = 0.0;
                    for (auto w : vTriggerHead) total_coarse += w.coarse();
                    float mean_coarse = total_coarse / vTriggerHead.size();
                    for (auto w : vTriggerHead){
                        if (fabs(w.coarse()-mean_coarse) < fabs(trigger.coarse()-mean_coarse)) trigger = w;
                    }
                }

                trigger_tdc_time = trigger.time();
                tdc = trigger.tdc();
                channel = trigger.channel();

                for (auto w : vTriggerTrail){
                    if (w.tdc()==trigger.tdc() && w.channel()==trigger.channel()) trigger_adc_time = w.time() - trigger_tdc_time;
                }
                this->triggerTree->Fill();

                for (auto wHead : vSignalHead){
                    signal_tdc_time = wHead.time();
                    tdc = wHead.tdc();
                    channel = wHead.channel();
                    for (auto wTrail : vSignalTrail){
                        if (wTrail.tdc()==wHead.tdc() && wTrail.channel()==wHead.channel()){
                            signal_adc_time = wTrail.time() - signal_tdc_time;
                            signal_tdc_time_corr = signal_tdc_time - trigger_tdc_time - ADC_correlation(signal_adc_time);
                        }
                    }
                    //MSG(signal_adc_time);
                    this->signalTree->Fill();
                }
                event++;
            }
            vSignalHead.clear(); vSignalTrail.clear(); vTriggerHead.clear(); vTriggerTrail.clear();
        }
        else continue;
    }
    this->root->cd();
    this->signalTree->Write();
    this->triggerTree->Write();
    this->root->Close();
    return 0;
}
