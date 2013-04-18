#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "resource_ids.auto.h"



#define MY_UUID { 0xF7, 0xAD, 0x65, 0x1A, 0x67, 0x1F, 0x44, 0x5D, 0x9F, 0x8F, 0x02, 0xB0, 0x1F, 0x9A, 0xB4, 0x89}
PBL_APP_INFO(MY_UUID,
             "SpokenTime", "Viktor Hansson + dotar",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
TextLayer row_1 , row_2 , row_3 , row_4;
GFont font,fontBold;
static char row_1_buffer[10],row_2_buffer[10],row_3_buffer[10],row_4_buffer[10];
static int rows;




/////////////////////////////////////////////////////////////////////////

#include "string.h"
#define BUFFERSIZE 86
static const char* NUMBERS[] = {
    "tolv",
    "ett",
    "två",
    "tre",
    "fyra",
    "fem",
    "sex",
    "sju",
    "åtta",
    "nio",
    "tio",
    "elva",
    "tolv",
    "ett",
};

static int rows;


void GetHourString(int hour,int minute,char* timmeBuffer){
    memset(timmeBuffer,0,BUFFERSIZE);
    
    if (minute > 22)
    {
        hour++;
    }
    
    strcat(timmeBuffer,NUMBERS[hour]);
    ++rows;
}

void GetMinuteString(int minute,char* minutBuffer){
    memset(minutBuffer,0,BUFFERSIZE);
    
    
    //get correct minute
    if ( (minute == 1) || (minute == 59) ||
        (minute == 29) || (minute == 31) )
    {
        strcat(row_1_buffer,"ett");
    }
    else if ( (minute == 2) || (minute == 58) ||
        (minute == 28) || (minute == 32) )
    {
        strcat(row_1_buffer,"två");
    }
    else if ( (minute == 3) || (minute == 57) ||
        (minute == 27) || (minute == 33) )
    {
        strcat(row_1_buffer,"tre");
    }
    else if ( (minute == 4) || (minute == 56) ||
        (minute == 26) || (minute == 34) )
    {
        strcat(row_1_buffer,"fyra");
    }
    else if ( (minute == 5) || (minute == 55) ||
        (minute == 25) || (minute == 35) )
    {
        strcat(row_1_buffer,"fem");
    }
    else if ( (minute == 6) || (minute == 54) ||
        (minute == 36) )
    {
        strcat(row_1_buffer,"sex");
    }
    else if ( (minute == 7) || (minute == 53) ||
        (minute == 37) )
    {
        strcat(row_1_buffer,"sju");
    }
    else if ( (minute == 8) || (minute == 52) ||
        (minute == 38) )
    {
        strcat(row_1_buffer,"åtta");
    }
    else if ( (minute == 9) || (minute == 51) ||
        (minute == 39) )
    {
        strcat(row_1_buffer,"nio");
    }
    else if( (minute == 10) || (minute == 50) )
    {
        strcat(row_1_buffer,"tio");
    }
    else if ( (minute == 11) || (minute == 49) )
    {
        strcat(row_1_buffer,"elva");
    }
    else if ( (minute == 12) || (minute == 48) )
    {
        strcat(row_1_buffer,"tolv");
    }
    else if ( (minute == 13) || (minute == 47) )
    {
        strcat(row_1_buffer,"tretton");
    }
    else if ( (minute == 14) || (minute == 44) )
    {
        strcat(row_1_buffer,"fjorton");
    }
    else if( (minute == 15) || (minute == 45) )
    {
        strcat(row_1_buffer,"kvart");
    }
    else if ( (minute == 16) || (minute == 44) )
    {
        strcat(row_1_buffer,"sexton");
    }
    else if ( (minute == 17) || (minute == 43) )
    {
        strcat(row_1_buffer,"sjutton");
    }
    else if ( (minute == 18) || (minute == 42) )
    {
        strcat(row_1_buffer,"arton");
    }
    else if ( (minute == 19) || (minute == 41) )
    {
        strcat(row_1_buffer,"nitton");
    }
    else if( (minute == 20) || (minute == 40 ) )
    {
        strcat(row_1_buffer,"tjugo");
    }
    else if( (minute == 21) )
    {
        strcat(row_1_buffer,"tjugoett");
    }
    else if( (minute == 22) )
    {
        strcat(row_1_buffer,"tjugotvå");
    }
    else if( (minute == 23) )
    {
        strcat(row_1_buffer,"tjugotre");
    }
    else if( (minute == 24) )
    {
        strcat(row_1_buffer,"tjugofyra");
    }

    
    ++rows;
    
    //Get correct preposition
    if (minute < 25)
    {
        strcat(row_2_buffer,"över");
    }
    else if(minute < 30){
        strcat(row_2_buffer,"i halv");
    }
    else if(minute < 39){
        strcat(row_2_buffer,"över");
        strcat(row_3_buffer,"halv");
        ++rows;
    }
    else{
        strcat(row_2_buffer,"i");
    }
    ++rows;
}

int GetTime(int hours, int minutes){
    //Correct for 24h clock
    hours = (hours > 12) ? hours - 12 : hours ;
    rows = 0;
        
    char timme[BUFFERSIZE];
    GetHourString(hours,minutes,timme);
    
    //////////////////////////////////////////////////////////////////////////
    //Construct the timestring
    
    text_layer_set_font(&row_1,font);
    text_layer_set_font(&row_2,font);
    text_layer_set_font(&row_3,font);

    //First check if it is o'clock something or halv something
    if (minutes == 0)
    {
        text_layer_set_font(&row_1,fontBold);
        strcat(row_1_buffer,timme);
        return 3;
    }
    else if(minutes == 30){
        strcat(row_1_buffer,"halv");
        text_layer_set_font(&row_2,fontBold);
        strcat(row_2_buffer,timme);
        return 2;
    }
    else{
        char minut[BUFFERSIZE];
        GetMinuteString(minutes,minut);
        if(rows == 3){
            text_layer_set_font(&row_3,fontBold);
            strcat(row_3_buffer,timme);
        }else if(rows == 4){
            text_layer_set_font(&row_4,fontBold);
            strcat(row_4_buffer, timme);
        }
        return rows;
        
    }
}



/////////////////////////////////////////////////////////////////////////




void setup_text_layer(TextLayer* row, int y,bool bold){
  text_layer_set_text_color(row, GColorWhite);
  text_layer_set_background_color(row, GColorClear);
  layer_add_child(&window.layer, &row->layer);
 /* if (bold)
  {
    text_layer_set_font(row,fontBold);
  }
  else
  {
    text_layer_set_font(row,font);
  }*/
  layer_set_frame(&row->layer, GRect(5,y,144,100));
}

void setup_two_row_layers(){
  //Row1
  setup_text_layer(&row_1,16,false);

  //Row2
  setup_text_layer(&row_2,53,false);

}

void setup_three_row_layers(){
  setup_two_row_layers();

  //Row3
  setup_text_layer(&row_3,92,false);

}

void setup_four_row_layers(){
    //Setup the text layers
  //Row1
  setup_text_layer(&row_1,0,true);

  //Row2
  setup_text_layer(&row_2,37,false);

  //Row3
  setup_text_layer(&row_3,76,false);

  //Row 4
  setup_text_layer(&row_4,117,false);

}

void update_time(PblTm* t){
  memset(row_1_buffer,0,10);
  memset(row_2_buffer,0,10);
  memset(row_3_buffer,0,10);
  memset(row_4_buffer,0,10);

  rows = GetTime(t->tm_hour,t->tm_min);
  switch(rows){
    case 2:
      setup_two_row_layers();
      break;
    case 3:
      setup_three_row_layers();
      break;
    case 4:
      setup_four_row_layers();
      break;
  }
  text_layer_set_text(&row_1,row_1_buffer);
  text_layer_set_text(&row_2,row_2_buffer);
  text_layer_set_text(&row_3,row_3_buffer);
  text_layer_set_text(&row_4,row_4_buffer);
}

static void handle_minute_tick(AppContextRef app_ctx, PebbleTickEvent* e) {
  update_time(e->tick_time);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  //Setup the window with black background
  window_init(&window, "Clock_Window");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  //Setup the app resources(font)
  resource_init_current_app(&APP_RESOURCES);

  //Load the font
  //GFont font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OSP_DIN_44));
  //fontBold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SANSATION_BOLD_42));
  //font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SANSATION_LIGHT_42));
  fontBold = fonts_get_system_font(FONT_KEY_GOTHAM_42_BOLD);
  font = fonts_get_system_font(FONT_KEY_GOTHAM_42_LIGHT);


  text_layer_init(&row_1, window.layer.frame);
  text_layer_init(&row_2, window.layer.frame);
  text_layer_init(&row_3, window.layer.frame);
  text_layer_init(&row_4, window.layer.frame);


  PblTm t;
  get_time(&t);
  update_time(&t);

}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
