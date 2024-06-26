#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#define PIN_BUTTON1 2
#define PIN_BUTTON2 3
#define PIN_BUTTON3 4
#define PIN_BUZZER  12

#define PIN_LCD_RS  5
#define PIN_LCD_RW  6
#define PIN_LCD_EN  7
#define PIN_LCD_D4  8
#define PIN_LCD_D5  9
#define PIN_LCD_D6  10
#define PIN_LCD_D7  11

#define BTN_PAD_VALUE_INC_TIME 4
#define BTN_PAD_VALUE_DEC_TIME 2
#define BTN_PAD_VALUE_ABRT     6
#define BTN_PAD_VALUE_SP       1

typedef enum{
    NOT_PRESSED,
    BOUNCE,
    PRESSED
}button_state_t;



typedef enum{
    INC_TIME,
    DEC_TIME,
    START_PAUSE,
    ABRT,
    TIME_TICK,

    /*Internal activity signals*/
    ENTRY,
    EXIT
}protimer_sig_t;

typedef enum
{
    EVENT_HANDLED,
    EVENT_IGNORED,
    EVENT_TRANSATION
}event_status_t;

//forward declaration
struct protimer_tag;
struct event_tag;

typedef event_status_t(*protimer_state_t)(struct protimer_tag *const, struct event_tag const *const);

typedef struct protimer_tag
{
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
}protimer_t;

typedef struct event_tag
{
    uint8_t Sig;
}event_t;

/*For user generated event*/
typedef struct 
{
    event_t super;
}protimer_user_event_t;

/*For Tick event*/
typedef struct 
{
    event_t super;
    uint8_t ss;
}protimer_tick_event_t;



void protimer_init(protimer_t *mobj);
event_status_t protimer_state_machine(protimer_t *mobj , event_t *e);




#endif