#include "vizaudio.h"

/* main() is a main method. */
int main( int   argc,
          char *argv[] )
{
    gtk_init (&argc, &argv);

    vizaudio_display(2);

    gtk_main();

    return 0;
}
