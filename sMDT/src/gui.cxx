#include "sMDT/gui.h"
#include "sMDT/format.h"
#include <iostream>
#include <unistd.h>

gui::gui(){
    //app = new TApplication("onlineDAQ");
    app = new TApplication("onlineDAQ", 0, NULL);
    //app = new TApplication();
    c = new TCanvas("c", "c", 800, 600);
    h = new TH1F("TDC", "TDC", 1024, -400, 400);
    h->Draw();
    c->Modified();
    c->Update();
    app->Run();
}

gui::~gui(){
}

void gui::update(buffXDC buff){
    if (buff.isTDC){
        if (buff.indexXDC == 1 && buff.channel == 1){
            for (int nb=1; nb<=1024; nb++){
                h->SetBinContent(nb, buff.binContents[nb-1]);
                c->Modified();
                c->Update();
            }
        }
    }
}

