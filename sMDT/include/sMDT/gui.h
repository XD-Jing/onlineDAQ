#ifndef _gui_h_
#define _gui_h_

#include <stdio.h>
#include <string.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <sMDT/format.h>


class gui
{
    private:

        TApplication *app;
        TCanvas *c;
        TH1F *h;


    public:
        gui();
        ~gui();

        void update(buffXDC);
};

#endif
