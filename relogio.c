/***************************************************************************
 *
 * $Id: relogio.c 1 2008-02-09 10:36  andrem $
 *
 * Andre O Moura andreoandre [ at ] gmail (dot) com
 * 
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 ****************************************************************************/

#include "plugin.h"
#include "time.h"

PLUGIN_HEADER

/* macro BUTTON_POWER e para e200 e c200 da sansa */
#define STATS_STOP BUTTON_POWER

static struct plugin_api* rb;
static char horario[32];

void data(void)
{
    int hora;
    int minuto;

    struct tm* current_time = rb->get_time();
    hora = current_time->tm_hour;
    minuto = current_time->tm_min;
    
    rb->snprintf(horario, sizeof(horario), "Hora: %d : %d ", hora, minuto);
}

enum plugin_status plugin_start(struct plugin_api* api, void* parameter)
{
    int button;

    (void)parameter;
    rb = api;

    rb->splash(HZ, "Obtendo Horario...");

    data();	

    rb->lcd_clear_display();
    rb->lcd_update();
    rb->lcd_puts(0,0,horario);
    rb->lcd_update();
    
    button = rb->button_get(true);
    while(1)
    {
	if (button == STATS_STOP )
	{ 
	    return PLUGIN_OK;
	    break;
	}
	return PLUGIN_OK;		
    }
}

