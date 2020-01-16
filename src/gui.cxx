#include <TApplication.h>
#include <TCanvas.h>
#include <sMDT/monitor.h>

int main(int argc, char** argv) {
    //TApplication theApp("App",&argc, argv);
    //TCanvas canvas ("fCanvas", "fCanvas", 600, 400);
    //canvas.Draw();
    // your code
    // here you can Draw() things
    //theApp.Run();
    monitor *m = new monitor();
    return 0;
}
