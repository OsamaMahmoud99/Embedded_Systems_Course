#include "main.h"
#include "lcd.h"


static void display_time(uint32_t time);
static void display_message(String s, uint8_t c , uint8_t r);
static void display_clear(void);
static void do_beep(void);

static event_status_t protimer_state_handler_IDLE(protimer_t *mobj , event_t *e);
static event_status_t protimer_state_handler_TIME_SET(protimer_t *mobj , event_t *e);
static event_status_t protimer_state_handler_COUNTDOWN(protimer_t *mobj , event_t *e);
static event_status_t protimer_state_handler_STAT(protimer_t *mobj , event_t *e);
static event_status_t protimer_state_handler_PAUSE(protimer_t *mobj , event_t *e);

void protimer_init(protimer_t *mobj)
{
    event_t ee;
    ee.Sig = ENTRY;
    mobj->active_state = IDLE;
    mobj->pro_time = 0;
    protimer_state_machine(mobj,&ee);
}

event_status_t protimer_state_machine(protimer_t *mobj , event_t *e)
{
    switch(mobj->active_state){
        case IDLE:{
            return protimer_state_handler_IDLE(mobj , e);
            break;
        }
        case TIME_SET:{
            return protimer_state_handler_TIME_SET(mobj , e);
            break;
        }
        case COUNTDOWN:{
            return protimer_state_handler_COUNTDOWN(mobj , e);
            break;
        }
        case STAT:{
            return protimer_state_handler_STAT(mobj , e);
            break;
        }
        case PAUSE:{
            return protimer_state_handler_PAUSE(mobj , e);
            break;
        }
    }
}

static event_status_t protimer_state_handler_IDLE(protimer_t *mobj , event_t *e)
{
    switch (e->Sig)
    {
        case INC_TIME:{
            mobj->curr_time += 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSATION;
        }
        case ENTRY:{
            mobj->curr_time = 0;
            mobj->elapsed_time = 0;
            display_time(0);
            display_message("Set",0,0);
            display_message("time",0,1);
            return EVENT_HANDLED;
        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;
        }
        case TIME_TICK:{
            if( ((protimer_tick_event_t*)(e))->ss == 5){
                do_beep();
                return EVENT_HANDLED;
            }
            return EVENT_IGNORED;
        }
        case START_PAUSE:{
            mobj->active_state = STAT;
            return EVENT_TRANSATION;
        }
    }

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_TIME_SET(protimer_t *mobj , event_t *e)
{
    switch (e->Sig)
    {
        case INC_TIME:{
            mobj->curr_time += 60;
            display_time(mobj->curr_time);
            return EVENT_HANDLED;
        }
        case ENTRY:{
            display_time(mobj->curr_time);
            return EVENT_HANDLED;
        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;
        }
        case DEC_TIME:{
            if(mobj->curr_time >= 60){
                mobj->curr_time -= 60;
                display_time(mobj->curr_time);
                return EVENT_HANDLED;
            }
            return EVENT_IGNORED;
        }
        case ABRT:{
            mobj->active_state = IDLE;
            return EVENT_TRANSATION;
        }
        case START_PAUSE:{
            if(mobj->curr_time >= 60){
                mobj->active_state = COUNTDOWN;
                return EVENT_TRANSATION;
            }
            return EVENT_IGNORED;
            
        }
    }

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_COUNTDOWN(protimer_t *mobj , event_t *e)
{
    switch (e->Sig)
    {
        case INC_TIME:{
            mobj->curr_time += 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSATION;
        }
        case EXIT:{
            mobj->pro_time += mobj->elapsed_time;
            mobj->elapsed_time = 0;
            return EVENT_HANDLED;
        }
        case ABRT:{
            mobj->active_state = IDLE;
            return EVENT_TRANSATION;
        }
        case TIME_TICK:{
            if( ((protimer_tick_event_t*)(e))->ss == 10){
                --mobj->curr_time;
                ++mobj->elapsed_time;
                display_time(mobj->curr_time);
                if(mobj->curr_time == 0){
                    mobj->active_state = IDLE;
                    return EVENT_TRANSATION;
                }
                return EVENT_HANDLED;
            }
            return EVENT_IGNORED;
        }
        case START_PAUSE:{
            mobj->active_state = PAUSE;
            return EVENT_TRANSATION;
        }
    }

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_STAT(protimer_t *mobj , event_t *e)
{
    static uint8_t tick_count = 0;
    switch (e->Sig)
    {
        case ENTRY:{
            display_time(mobj->pro_time);
            display_message("productive_time",1,1);
            return EVENT_HANDLED;
        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;
        }
        case TIME_TICK:{
            if( ++tick_count == 30){
                tick_count = 0;
                mobj->active_state = IDLE;
                return EVENT_TRANSATION;
            }
            return EVENT_IGNORED;
        }
    }

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_PAUSE(protimer_t *mobj , event_t *e)
{
    switch (e->Sig)
    {
        case ENTRY:{
            display_message("paused",5,1);
            return EVENT_HANDLED;
        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;
        }
        case INC_TIME:{
            mobj->curr_time += 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSATION;
        }
        case DEC_TIME:{
            if(mobj->curr_time >= 60){
                mobj->curr_time -= 60;
                mobj->active_state = TIME_SET;
                return EVENT_TRANSATION;
            }
            return EVENT_IGNORED;
        }
        case START_PAUSE:{
            mobj->active_state = COUNTDOWN;
            return EVENT_TRANSATION;
        }
        case ABRT:{
            mobj->active_state = IDLE;
            return EVENT_TRANSATION;
        }
    }

    return EVENT_IGNORED;
}
//////////////////////////// helper functions //////////////////////////

static void display_time(uint32_t time){
    String time_msg;
    char buf[7];

    uint16_t m = time / 60;
    uint8_t s = time % 60;
    sprintf(buf,"%03d:%02d",m,s);

    time_msg = (String)buf;
    lcd_set_cursor(5,0);
    lcd_print_string(time_msg);
}

static void display_message(String s, uint8_t c , uint8_t r){
    lcd_set_cursor(c , r);
    lcd_print_string(s);
}

static void display_clear(void){
    lcd_clear();
}

static void do_beep(void){
    tone(PIN_BUZZER , 4000 , 25);
}