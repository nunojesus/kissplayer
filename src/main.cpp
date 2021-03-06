#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>

#include "configuration.h"
#include "context.h"
#include "sound.h"
#include "locale.h"
#include "window_main.h"
#include "os_specific.h"
#include "dao.h"

int main(int argc, char** argv)
{
    Fl::scheme("GTK+");

    Fl::background(50, 50, 50);
    Fl::background2(90, 90, 90);
    Fl::foreground(255, 255, 255);

    fl_message_title_default(_("Warning"));

    Context* context = new Context();

    if (context->dao->init(context->osSpecific) != 0) {
        fl_alert(_("Error while initializing database"));
        delete context;
        return -1;
    }

    if (context->sound->init() != 0) {
        fl_alert(_("Error while sound system"));
        delete context;
        return -1;
    }

    context->locale->init(context->dao, argc, argv);

    WindowMain windowMain(context);
    windowMain.init(argc, argv);
    context->osSpecific->set_app_icon(&windowMain);
    windowMain.show();

    context->osSpecific->init(&windowMain);

    Fl::lock();

    int fl_result = Fl::run();

    delete context;

    return fl_result;
}
