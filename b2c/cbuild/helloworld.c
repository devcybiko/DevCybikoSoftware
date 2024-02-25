#include "cybiko.h"

struct module_t main_module;

main() {
init_module( &main_module );

DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
TGraph_set_color( main_module.m_gfx, CLR_BLACK );

DisplayGraphics_draw_text( main_module.m_gfx, "Hello World!", 10, 10 );
DisplayGraphics_show( main_module.m_gfx );

sleep(5000);

return 0;
}