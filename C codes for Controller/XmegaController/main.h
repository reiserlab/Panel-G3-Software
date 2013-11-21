//in one bytes because function_X and function_Y are int8_t
#define NBYTES_HEADER	  512
#define RINGBUFFER_LENGTH 100

//In the old system OVERFLOW_PERIOD = 16MHz/8(prescaler)/256(timer0)
//In the new system OVERFLOW_PERIOD = 32MHz/8(prescaler)/512(timerE)
//JL03092010 increase OVERFLOW_PERIOD 4 times in order to get a higher resolution clock for the handlers
//#define OVERFLOW_PERIOD 2000000/256
#define OVERFLOW_PERIOD   8000000/256
#define UPDATE_PERIOD     OVERFLOW_PERIOD/400
#define FUNCTION_PERIOD   OVERFLOW_PERIOD/50


#define BAUDRATE	      400000
#define TWI_BAUDSETTING   TWI_BAUD(F_CPU, BAUDRATE)
#define TWI_BUFFER_LENGTH HEADER_SIZE+PAGE_SIZE

#define EEPROM __attribute__((section(".eeprom")))


// Message command ID's.
#define MSG_1_START                    0x20
#define MSG_1_START_W_TRIG             0x25
#define MSG_1_STOP                     0x30
#define MSG_1_STOP_W_TRIG              0x35
#define MSG_1_CLEAR                    0xF0
#define MSG_1_ALL_OFF                  0x00
#define MSG_1_ALL_ON                   0xFF
#define MSG_1_G_LEVEL_0                0x90
#define MSG_1_G_LEVEL_1                0x91
#define MSG_1_G_LEVEL_2                0x92
#define MSG_1_G_LEVEL_3                0x93
#define MSG_1_G_LEVEL_4                0x94
#define MSG_1_G_LEVEL_5                0x95
#define MSG_1_G_LEVEL_6                0x96
#define MSG_1_G_LEVEL_7                0x97
#define MSG_1_G_LEVEL_8                0x98
#define MSG_1_G_LEVEL_9                0x99
#define MSG_1_G_LEVEL_10               0x9A
#define MSG_1_G_LEVEL_11               0x9B
#define MSG_1_G_LEVEL_12               0x9C
#define MSG_1_G_LEVEL_13               0x9D
#define MSG_1_G_LEVEL_14               0x9E
#define MSG_1_G_LEVEL_15               0x9F
#define MSG_1_LED_TOG                  0x50
#define MSG_1_CTR_RESET                0x60
#define MSG_1_BENCH_PATTERN            0x70
#define MSG_1_LASER_ON                 0x10
#define MSG_1_LASER_OFF                0x11
#define MSG_1_IDENT_COMPRESS_ON        0x12
#define MSG_1_IDENT_COMPRESS_OFF       0x13
#define MSG_1_SYNC_SD_INFO             0x14
#define MSG_1_GET_VERSION              0x15
#define MSG_1_SHOW_BUS_NUMBER          0x16
#define MSG_1_QUIET_MODE_ON            0x17
#define MSG_1_QUIET_MODE_OFF           0x18
#define MSG_1_UPDATE_GUI_INFO          0x19
#define MSG_1_CONTROLLER_MODE          0x21
#define MSG_1_PC_DUMPING_MODE          0x22
#define MSG_1_ENABLE_EXTERN_TRIG       0x23
#define MSG_1_DISABLE_EXTERN_TRIG      0x24
#define MSG_1_READ_AND_SET_MAX_VOLTAGE 0x26

#define MSG_2_RESET                    0x01
#define MSG_2_DISPLAY                  0x02
#define MSG_2_SET_PATTERN_ID           0x03
#define MSG_2_ADC_TEST                 0x04
#define MSG_2_DIO_TEST                 0x05
#define MSG_2_SET_TRIGGER_RATE         0x06
#define MSG_2_FLASH_PANEL              0x07
#define MSG_2_EEPROM_PANEL             0x08
#define MSG_2_SET_CONFIG_ID            0x09
#define MSG_2_GET_ADC_VALUE            0x10

#define MSG_3_SET_MODE                 0x10
#define MSG_3_ADDRESS                  0xFF
#define MSG_3_SET_POSFUNC_ID           0x15
#define MSG_3_SET_VELFUNC_ID           0x20
#define MSG_3_SET_FUNCX_FREQ           0x25
#define MSG_3_SET_FUNCY_FREQ           0x30
#define MSG_3_SET_MAX_VOLTAGE          0x35
#define MSG_3_SET_VOLTAGE_RANGE_ADC    0x62

#define MSG_4_SET_AO_POS              0x10
#define MSG_4_SET_AO_NEG              0x11

#define MSG_5_SET_POSITION            0x70
#define MSG_5_SEND_GAIN_BIAS          0x71

#define MSG_7_SET_MODE_POS_CUSTOM_X    0x63
#define MSG_7_SET_MODE_POS_CUSTOM_Y    0x64
#define MSG_7_SET_MODE_VEL_CUSTOM_X    0x65
#define MSG_7_SET_MODE_VEL_CUSTOM_Y    0x66


// Define mode numbers.
#define MODE_VEL_OPENLOOP              0
#define MODE_VEL_CLOSEDLOOP            1
#define MODE_VEL_CLOSEDLOOP_FUNCTION   2
#define MODE_POS_ADC                   3
#define MODE_POS_FUNCTION              4
#define MODE_POS_DEBUG                 5
#define MODE_VEL_CUSTOM                0x61
#define MODE_POS_CUSTOM                0x62


void init_all(void);

//routines for handling the incomming messages over the UART
void handle_message_length_1(uint8_t *msg_buffer);
void handle_message_length_2(uint8_t *msg_buffer);
void handle_message_length_3(uint8_t *msg_buffer);
void handle_message_length_4(uint8_t *msg_buffer);
void handle_message_length_5(uint8_t *msg_buffer);
void handle_message_length_7(uint8_t *msg_buffer);
void handle_message_length_9(uint8_t *msg_buffer);
void handle_message_length_62(uint8_t *msg_buffer);
void handle_message_length_63(uint8_t *msg_buffer);
void handle_message_length_52(uint8_t *msg_buffer);


//routines for updating display, computing new pattern indices
void update_display_for_rates(void);
void increment_index_x(void);
void increment_index_y(void);
void decrement_index_x(void);
void decrement_index_y(void);
void fetch_and_display_frame(FIL *pFile, uint16_t f_num, uint16_t, uint16_t);
void display_preload_frame(uint16_t f_num, uint16_t, uint16_t);
void update_ANOUT(void);
void update_display_for_position_x(void);
void update_display_for_position_y(void);

//helper utilities
void toggle_trigger(void);
void delay(uint16_t us);
void long_delay(uint16_t ms);
void send_number(uint8_t target_panel_addr, int32_t number);
void set_pattern(uint8_t pat_num);
void benchmark_pattern(void);
void set_hwConfig(uint8_t config_num);
void i2cMasterSend(uint8_t addr, uint8_t len, uint8_t *data);
void set_vel_func(uint8_t func_channel, uint8_t func_id);
void set_pos_func(uint8_t func_channel, uint8_t func_id);
void set_default_func(uint8_t func_channel);

void loadPattern2Panels(uint8_t pat_num);
void display_dumped_frame (uint8_t *msg_buffer);

void dump_mat(void);
void fetch_block_func_x(FIL *pFile, uint8_t fReset, uint8_t);
void fetch_block_func_y(FIL *pFile, uint8_t fReset, uint8_t);
uint8_t difference(uint8_t write_index, uint8_t read_index);

unsigned char work_mode[1] EEPROM = {0xff};
unsigned char arena_config[129] EEPROM;
static uint8_t RESET[2] = {0x00, 0x01};
static uint8_t DISPLAY[2] = {0x00, 0x02};

static uint8_t TEST_BYTE[8][1] = {0x0F, 0xF0, 0xAA, 0x55, 0x03, 0x0C, 0x30, 0xC0};
static uint8_t TEST_3BYTE[9][3] = {{0x00, 0x00, 0x00}, {0x00, 0x00, 0xFF}, {0x00, 0xFF, 0x00}, {0x00, 0xFF, 0xFF},
{0xFF, 0x00, 0x00}, {0xFF, 0x00, 0xFF}, {0xFF, 0xFF, 0x00}, {0xFF, 0xFF, 0xFF} , {0x0F, 0x33, 0x55} };
static uint8_t G_LEVELS_16[16][32] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} };

static uint8_t ALL_OFF[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t ALL_ON[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static uint8_t G_LEVELS[8][24] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} };

static uint8_t ERROR_CODES[8][8] = { {0x80, 0x3F, 0x21, 0x21, 0x00, 0x3F, 0x25, 0x21},
{0x00, 0xBF, 0x21, 0x21, 0x00, 0x3F, 0x25, 0x21},
{0x00, 0x3F, 0xA1, 0x21, 0x00, 0x3F, 0x25, 0x21},
{0x00, 0x3F, 0x21, 0xA1, 0x00, 0x3F, 0x25, 0x21},
{0x00, 0x3F, 0x21, 0x21, 0x80, 0x3F, 0x25, 0x21},
{0x00, 0x3F, 0x21, 0x21, 0x00, 0xBF, 0x25, 0x21},
{0x00, 0x3F, 0x21, 0x21, 0x00, 0x3F, 0xA5, 0x21},
{0x00, 0x3F, 0x21, 0x21, 0x00, 0x3F, 0x25, 0xA1} };
