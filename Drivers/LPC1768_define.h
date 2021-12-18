
#ifndef __LPC1768_DEFINE_H__
#define __LPC1768_DEFINE_H__


/**************************************************/
/*   КОНСТРУКТОР БАЙТОВ                           */
/**************************************************/
// Использовать для сборки 16- и 32- разрядных чисел
// Например:
// 32-разрядное число 00001111001100110000000011111111
// задается так: (b00001111 byte3) | (b00110011 byte2) | (b00000000 byte1) | (b11111111 byte0)
#define byte0 << 0
#define byte1 << 8
#define byte2 << 16
#define byte3 << 24


/**************************************************/
/*   ДВОИЧНЫЕ ГРУППЫ                              */
/**************************************************/
//использовать вместо двоичных чисел
#define b00 0UL
#define b01 1UL
#define b10 2UL
#define b11 3UL

#define b000 0UL
#define b001 1UL
#define b010 2UL
#define b011 3UL
#define b100 4UL
#define b101 5UL
#define b110 6UL
#define b111 7UL

#define b0000 0UL
#define b0001 1UL
#define b0010 2UL
#define b0011 3UL
#define b0100 4UL
#define b0101 5UL
#define b0110 6UL
#define b0111 7UL
#define b1000 8UL
#define b1001 9UL
#define b1010 10UL
#define b1011 11UL
#define b1100 12UL
#define b1101 13UL
#define b1110 14UL
#define b1111 15UL

#define b00000000 0UL
#define b00000001 1UL
#define b00000010 2UL
#define b00000011 3UL
#define b00000100 4UL
#define b00000101 5UL
#define b00000110 6UL
#define b00000111 7UL
#define b00001000 8UL
#define b00001001 9UL
#define b00001010 10UL
#define b00001011 11UL
#define b00001100 12UL
#define b00001101 13UL
#define b00001110 14UL
#define b00001111 15UL
#define b00010000 16UL
#define b00010001 17UL
#define b00010010 18UL
#define b00010011 19UL
#define b00010100 20UL
#define b00010101 21UL
#define b00010110 22UL
#define b00010111 23UL
#define b00011000 24UL
#define b00011001 25UL
#define b00011010 26UL
#define b00011011 27UL
#define b00011100 28UL
#define b00011101 29UL
#define b00011110 30UL
#define b00011111 31UL
#define b00100000 32UL
#define b00100001 33UL
#define b00100010 34UL
#define b00100011 35UL
#define b00100100 36UL
#define b00100101 37UL
#define b00100110 38UL
#define b00100111 39UL
#define b00101000 40UL
#define b00101001 41UL
#define b00101010 42UL
#define b00101011 43UL
#define b00101100 44UL
#define b00101101 45UL
#define b00101110 46UL
#define b00101111 47UL
#define b00110000 48UL
#define b00110001 49UL
#define b00110010 50UL
#define b00110011 51UL
#define b00110100 52UL
#define b00110101 53UL
#define b00110110 54UL
#define b00110111 55UL
#define b00111000 56UL
#define b00111001 57UL
#define b00111010 58UL
#define b00111011 59UL
#define b00111100 60UL
#define b00111101 61UL
#define b00111110 62UL
#define b00111111 63UL
#define b01000000 64UL
#define b01000001 65UL
#define b01000010 66UL
#define b01000011 67UL
#define b01000100 68UL
#define b01000101 69UL
#define b01000110 70UL
#define b01000111 71UL
#define b01001000 72UL
#define b01001001 73UL
#define b01001010 74UL
#define b01001011 75UL
#define b01001100 76UL
#define b01001101 77UL
#define b01001110 78UL
#define b01001111 79UL
#define b01010000 80UL
#define b01010001 81UL
#define b01010010 82UL
#define b01010011 83UL
#define b01010100 84UL
#define b01010101 85UL
#define b01010110 86UL
#define b01010111 87UL
#define b01011000 88UL
#define b01011001 89UL
#define b01011010 90UL
#define b01011011 91UL
#define b01011100 92UL
#define b01011101 93UL
#define b01011110 94UL
#define b01011111 95UL
#define b01100000 96UL
#define b01100001 97UL
#define b01100010 98UL
#define b01100011 99UL
#define b01100100 100UL
#define b01100101 101UL
#define b01100110 102UL
#define b01100111 103UL
#define b01101000 104UL
#define b01101001 105UL
#define b01101010 106UL
#define b01101011 107UL
#define b01101100 108UL
#define b01101101 109UL
#define b01101110 110UL
#define b01101111 111UL
#define b01110000 112UL
#define b01110001 113UL
#define b01110010 114UL
#define b01110011 115UL
#define b01110100 116UL
#define b01110101 117UL
#define b01110110 118UL
#define b01110111 119UL
#define b01111000 120UL
#define b01111001 121UL
#define b01111010 122UL
#define b01111011 123UL
#define b01111100 124UL
#define b01111101 125UL
#define b01111110 126UL
#define b01111111 127UL
#define b10000000 128UL
#define b10000001 129UL
#define b10000010 130UL
#define b10000011 131UL
#define b10000100 132UL
#define b10000101 133UL
#define b10000110 134UL
#define b10000111 135UL
#define b10001000 136UL
#define b10001001 137UL
#define b10001010 138UL
#define b10001011 139UL
#define b10001100 140UL
#define b10001101 141UL
#define b10001110 142UL
#define b10001111 143UL
#define b10010000 144UL
#define b10010001 145UL
#define b10010010 146UL
#define b10010011 147UL
#define b10010100 148UL
#define b10010101 149UL
#define b10010110 150UL
#define b10010111 151UL
#define b10011000 152UL
#define b10011001 153UL
#define b10011010 154UL
#define b10011011 155UL
#define b10011100 156UL
#define b10011101 157UL
#define b10011110 158UL
#define b10011111 159UL
#define b10100000 160UL
#define b10100001 161UL
#define b10100010 162UL
#define b10100011 163UL
#define b10100100 164UL
#define b10100101 165UL
#define b10100110 166UL
#define b10100111 167UL
#define b10101000 168UL
#define b10101001 169UL
#define b10101010 170UL
#define b10101011 171UL
#define b10101100 172UL
#define b10101101 173UL
#define b10101110 174UL
#define b10101111 175UL
#define b10110000 176UL
#define b10110001 177UL
#define b10110010 178UL
#define b10110011 179UL
#define b10110100 180UL
#define b10110101 181UL
#define b10110110 182UL
#define b10110111 183UL
#define b10111000 184UL
#define b10111001 185UL
#define b10111010 186UL
#define b10111011 187UL
#define b10111100 188UL
#define b10111101 189UL
#define b10111110 190UL
#define b10111111 191UL
#define b11000000 192UL
#define b11000001 193UL
#define b11000010 194UL
#define b11000011 195UL
#define b11000100 196UL
#define b11000101 197UL
#define b11000110 198UL
#define b11000111 199UL
#define b11001000 200UL
#define b11001001 201UL
#define b11001010 202UL
#define b11001011 203UL
#define b11001100 204UL
#define b11001101 205UL
#define b11001110 206UL
#define b11001111 207UL
#define b11010000 208UL
#define b11010001 209UL
#define b11010010 210UL
#define b11010011 211UL
#define b11010100 212UL
#define b11010101 213UL
#define b11010110 214UL
#define b11010111 215UL
#define b11011000 216UL
#define b11011001 217UL
#define b11011010 218UL
#define b11011011 219UL
#define b11011100 220UL
#define b11011101 221UL
#define b11011110 222UL
#define b11011111 223UL
#define b11100000 224UL
#define b11100001 225UL
#define b11100010 226UL
#define b11100011 227UL
#define b11100100 228UL
#define b11100101 229UL
#define b11100110 230UL
#define b11100111 231UL
#define b11101000 232UL
#define b11101001 233UL
#define b11101010 234UL
#define b11101011 235UL
#define b11101100 236UL
#define b11101101 237UL
#define b11101110 238UL
#define b11101111 239UL
#define b11110000 240UL
#define b11110001 241UL
#define b11110010 242UL
#define b11110011 243UL
#define b11110100 244UL
#define b11110101 245UL
#define b11110110 246UL
#define b11110111 247UL
#define b11111000 248UL
#define b11111001 249UL
#define b11111010 250UL
#define b11111011 251UL
#define b11111100 252UL
#define b11111101 253UL
#define b11111110 254UL
#define b11111111 255UL


/**************************************************/
/*   Port Pins                                    */
/**************************************************/
#define PIN0  (1UL << 0)
#define PIN1  (1UL << 1)
#define PIN2  (1UL << 2)
#define PIN3  (1UL << 3)
#define PIN4  (1UL << 4)
#define PIN5  (1UL << 5)
#define PIN6  (1UL << 6)
#define PIN7  (1UL << 7)
#define PIN8  (1UL << 8)
#define PIN9  (1UL << 9)
#define PIN10 (1UL << 10)
#define PIN11 (1UL << 11)
#define PIN12 (1UL << 12)
#define PIN13 (1UL << 13)
#define PIN14 (1UL << 14)
#define PIN15 (1UL << 15)
#define PIN16 (1UL << 16)
#define PIN17 (1UL << 17)
#define PIN18 (1UL << 18)
#define PIN19 (1UL << 19)
#define PIN20 (1UL << 20)
#define PIN21 (1UL << 21)
#define PIN22 (1UL << 22)
#define PIN23 (1UL << 23)
#define PIN24 (1UL << 24)
#define PIN25 (1UL << 25)
#define PIN26 (1UL << 26)
#define PIN27 (1UL << 27)
#define PIN28 (1UL << 28)
#define PIN29 (1UL << 29)
#define PIN30 (1UL << 30)
#define PIN31 (1UL << 31)


/**************************************************/
/*   Rename of Registers                          */
/**************************************************/

// Rename of Pin Function Select Registers (PINSELx)
//--------------------------------------------------
//
#define PORT0_0_to_15_FUNCTION      PINSEL0
#define PORT0_16_to_31_FUNCTION     PINSEL1
#define PORT1_0_to_15_FUNCTION      PINSEL2
#define PORT1_16_to_31_FUNCTION     PINSEL3
#define PORT2_0_to_15_FUNCTION      PINSEL4
#define PORT2_16_to_31_FUNCTION     PINSEL5
#define PORT3_0_to_15_FUNCTION      PINSEL6
#define PORT3_16_to_31_FUNCTION     PINSEL7
#define PORT4_0_to_15_FUNCTION      PINSEL8
#define PORT4_16_to_31_FUNCTION     PINSEL9
#define PORT2_2_to_6_TRACE_FUNCTION PINSEL10

// Rename of Pin Mode Select Registers (PINMODEx)
//--------------------------------------------------
//
#define PORT0_0_to_15_PULL_MODE     PINMODE0
#define PORT0_16_to_31_PULL_MODE    PINMODE1
#define PORT1_0_to_15_PULL_MODE     PINMODE2
#define PORT1_16_to_31_PULL_MODE    PINMODE3
#define PORT2_0_to_15_PULL_MODE     PINMODE4
#define PORT3_16_to_31_PULL_MODE    PINMODE7
#define PORT4_16_to_31_PULL_MODE    PINMODE9

// Rename of Open Drain Pin Mode Select Registes (PINMODE_ODx)
//--------------------------------------------------
//
#define PORT0_OPENDRAIN_MODE        PINMODE_OD0
#define PORT1_OPENDRAIN_MODE        PINMODE_OD1
#define PORT2_OPENDRAIN_MODE        PINMODE_OD2
#define PORT3_OPENDRAIN_MODE        PINMODE_OD3
#define PORT4_OPENDRAIN_MODE        PINMODE_OD4


/**************************************************/
/*   Configure I/O ports                          */
/**************************************************/

// Port0-Port4 Primary functions (reset values)
//---------------------------------
//
#define PIN0_as_GPIO   (b00 << 0)
#define PIN1_as_GPIO   (b00 << 2)
#define PIN2_as_GPIO   (b00 << 4)
#define PIN3_as_GPIO   (b00 << 6)
#define PIN4_as_GPIO   (b00 << 8)
#define PIN5_as_GPIO   (b00 << 10)
#define PIN6_as_GPIO   (b00 << 12)
#define PIN7_as_GPIO   (b00 << 14)
#define PIN8_as_GPIO   (b00 << 16)
#define PIN9_as_GPIO   (b00 << 18)
#define PIN10_as_GPIO  (b00 << 20)
#define PIN11_as_GPIO  (b00 << 22)
#define PIN12_as_GPIO  (b00 << 24)
#define PIN13_as_GPIO  (b00 << 26)
#define PIN14_as_GPIO  (b00 << 28)
#define PIN15_as_GPIO  (b00 << 30)
#define PIN16_as_GPIO  (b00 << 0)
#define PIN17_as_GPIO  (b00 << 2)
#define PIN18_as_GPIO  (b00 << 4)
#define PIN19_as_GPIO  (b00 << 6)
#define PIN20_as_GPIO  (b00 << 8)
#define PIN21_as_GPIO  (b00 << 10)
#define PIN22_as_GPIO  (b00 << 12)
#define PIN23_as_GPIO  (b00 << 14)
#define PIN24_as_GPIO  (b00 << 16)
#define PIN25_as_GPIO  (b00 << 18)
#define PIN26_as_GPIO  (b00 << 20)
#define PIN27_as_GPIO  (b00 << 22)
#define PIN28_as_GPIO  (b00 << 24)
#define PIN29_as_GPIO  (b00 << 26)
#define PIN30_as_GPIO  (b00 << 28)
#define PIN31_as_GPIO  (b00 << 30)


// Port0 First alternate functions
//-----------------------------------
//
#define PIN0_as_RD1       (b01 << 0)
#define PIN1_as_TD1       (b01 << 2)
#define PIN2_as_TXD0      (b01 << 4)
#define PIN3_as_RXD0      (b01 << 6)
#define PIN4_as_I2SRX_CLK (b01 << 8)
#define PIN5_as_I2SRX_WS  (b01 << 10)
#define PIN6_as_I2SRX_SDA (b01 << 12)
#define PIN7_as_I2STX_CLK (b01 << 14)
#define PIN8_as_I2STX_WS  (b01 << 16)
#define PIN9_as_I2STX_SDA (b01 << 18)
#define PIN10_as_TXD2     (b01 << 20)
#define PIN11_as_RXD2     (b01 << 22)
// Port0 Pin12 reserved
// Port0 Pin13 reserved
// Port0 Pin14 reserved
#define PIN15_as_TXD1     (b01 << 30)
#define PIN16_as_RXD1     (b01 << 0)
#define PIN17_as_CTS1     (b01 << 2)
#define PIN18_as_DCD1     (b01 << 4)
#define PIN19_as_DSR1     (b01 << 6)
#define PIN20_as_DTR1     (b01 << 8)
#define PIN21_as_RI1      (b01 << 10)
#define PIN22_as_RTS1     (b01 << 12)
#define PIN23_as_AD0_0    (b01 << 14)
#define PIN24_as_AD0_1    (b01 << 16)
#define PIN25_as_AD0_2    (b01 << 18)
#define PIN26_as_AD0_3    (b01 << 20)
#define PIN27_as_SDA0     (b01 << 22)
#define PIN28_as_SCL0     (b01 << 24)
#define PIN29_as_USB_DP   (b01 << 26)
#define PIN30_as_USB_DM   (b01 << 28)
// Port0 Pin31 reserved


// Port0 Second alternate functions
//------------------------------------
//
#define PIN0_as_TXD3       (b10 << 0)
#define PIN1_as_RXD3       (b10 << 2)
#define PIN2_as_AD0_7      (b10 << 4)
#define PIN3_as_AD0_6      (b10 << 6)
#define PIN4_as_RD2        (b10 << 8)
#define PIN5_as_TD2        (b10 << 10)
#define PIN6_as_SSEL1      (b10 << 12)
#define PIN7_as_SCK1       (b10 << 14)
#define PIN8_as_MISO1      (b10 << 16)
#define PIN9_as_MOSI1      (b10 << 18)
#define PIN10_as_SDA2      (b10 << 20)
#define PIN11_as_SCL2      (b10 << 22)
// Port0 Pin12 reserved
// Port0 Pin13 reserved
// Port0 Pin14 reserved
#define PIN15_as_SCK0      (b10 << 30)
#define PIN16_as_SSEL0     (b10 << 0)
#define PIN17_as_MISO0     (b10 << 2)
#define PIN18_as_MOSI0     (b10 << 4)
// Port0 Pin19 reserved
// Port0 Pin20 reserved
// Port0 Pin21 reserved
// Port0 Pin22 reserved
#define PIN23_as_I2SRX_CLK (b10 << 14)
#define PIN24_as_I2SRX_WS  (b10 << 16)
#define PIN25_as_I2SRX_SDA (b10 << 18)
#define PIN26_as_AOUT      (b10 << 20)
#define PIN27_as_USB_SDA   (b10 << 22)
#define PIN28_as_USB_SCL   (b10 << 24)
// Port0 Pin29 reserved
// Port0 Pin30 reserved
// Port0 Pin31 reserved


// Port0 Third alternate functions
//---------------------------------
//
#define PIN0_as_SDA1    (b11 << 0)
#define PIN1_as_SCL1    (b11 << 2)
// Port0 Pin2 reserved
// Port0 Pin3 reserved
#define PIN4_as_CAP2_0  (b11 << 8)
#define PIN5_as_CAP2_1  (b11 << 10)
#define PIN6_as_MAT2_0  (b11 << 12)
#define PIN7_as_MAT2_1  (b11 << 14)
#define PIN8_as_MAT2_2  (b11 << 16)
#define PIN9_as_MAT2_3  (b11 << 18)
#define PIN10_as_MAT3_0 (b11 << 20)
#define PIN11_as_MAT3_1 (b11 << 22)
// Port0 Pin12 reserved
// Port0 Pin13 reserved
// Port0 Pin14 reserved
#define PIN15_as_SCK    (b11 << 30)
#define PIN16_as_SSEL   (b11 << 0)
#define PIN17_as_MISO   (b11 << 2)
#define PIN18_as_MOSI   (b11 << 4)
#define PIN19_as_SDA1   (b11 << 6)
#define PIN20_as_SCL1   (b11 << 8)
#define PIN21_as_RD1    (b11 << 10)
#define PIN22_as_TD1    (b11 << 12)
#define PIN23_as_CAP3_0 (b11 << 14)
#define PIN24_as_CAP3_1 (b11 << 16)
#define PIN25_as_TXD3   (b11 << 18)
#define PIN26_as_RXD3   (b11 << 20)
// Port0 Pin27 reserved
// Port0 Pin28 reserved
// Port0 Pin29 reserved
// Port0 Pin30 reserved
// Port0 Pin31 reserved


// Port1 First alternate functions
//--------------------------------------
//
#define PIN0_as_ENET_TXD0     (b01 << 0)
#define PIN1_as_ENET_TXD1     (b01 << 2)
// Port1 Pin2 reserved
// Port1 Pin3 reserved
#define PIN4_as_ENET_TX_EN    (b01 << 8)
// Port1 Pin5 reserved
// Port1 Pin6 reserved
// Port1 Pin7 reserved
#define PIN8_as_ENET_CRS      (b01 << 16)
#define PIN9_as_ENET_RXD0     (b01 << 18)
#define PIN10_as_ENET_RXD1    (b01 << 20)
// Port1 Pin11 reserved
// Port1 Pin12 reserved
// Port1 Pin13 reserved
#define PIN14_as_ENET_RX_ER   (b01 << 28)
#define PIN15_as_ENET_REF_CLK (b01 << 30)
#define PIN16_as_ENET_MDC     (b01 << 0)
#define PIN17_as_ENET_MDIO    (b01 << 2)
#define PIN18_as_USB_UP_LED   (b01 << 4)
#define PIN19_as_MCOA0        (b01 << 6)
#define PIN20_as_MCI0         (b01 << 8)
#define PIN21_as_nMCABORT     (b01 << 10)
#define PIN22_as_MCOB0        (b01 << 12)
#define PIN23_as_MCI1         (b01 << 14)
#define PIN24_as_MCI2         (b01 << 16)
#define PIN25_as_MCOA1        (b01 << 18)
#define PIN26_as_MCOB1        (b01 << 20)
#define PIN27_as_CLKOUT       (b01 << 22)
#define PIN28_as_MCOA2        (b01 << 24)
#define PIN29_as_MCOB2        (b01 << 26)
// Port1 Pin30 reserved
// Port1 Pin31 reserved


// Port1 Second alternate functions
//------------------------------------
//
// Port1 Pin0 reserved
// Port1 Pin1 reserved
// Port1 Pin2 reserved
// Port1 Pin3 reserved
// Port1 Pin4 reserved
// Port1 Pin5 reserved
// Port1 Pin6 reserved
// Port1 Pin7 reserved
// Port1 Pin8 reserved
// Port1 Pin9 reserved
// Port1 Pin10 reserved
// Port1 Pin11 reserved
// Port1 Pin12 reserved
// Port1 Pin13 reserved
// Port1 Pin14 reserved
// Port1 Pin15 reserved
// Port1 Pin16 reserved
// Port1 Pin17 reserved
#define PIN18_as_PWM1_1     (b10 << 4)
#define PIN19_as_nUSB_PPWR  (b10 << 6)
#define PIN20_as_PWM1_2     (b10 << 8)
#define PIN21_as_PWM1_3     (b10 << 10)
#define PIN22_as_USB_PWRD   (b10 << 12)
#define PIN23_as_PWM1_4     (b10 << 14)
#define PIN24_as_PWM1_5     (b10 << 16)
// Port1 Pin25 reserved
#define PIN26_as_PWM1_6     (b10 << 20)
#define PIN27_as_nUSB_OVRCR (b10 << 22)
#define PIN28_as_PCAP1_0    (b10 << 24)
#define PIN29_as_PCAP1_1    (b10 << 26)
#define PIN30_as_VBUS       (b10 << 28)
#define PIN31_as_SCK1       (b10 << 30)


// Port1 Third alternate functions
//--------------------------------
//
// Port1 Pin0 reserved
// Port1 Pin1 reserved
// Port1 Pin2 reserved
// Port1 Pin3 reserved
// Port1 Pin4 reserved
// Port1 Pin5 reserved
// Port1 Pin6 reserved
// Port1 Pin7 reserved
// Port1 Pin8 reserved
// Port1 Pin9 reserved
// Port1 Pin10 reserved
// Port1 Pin11 reserved
// Port1 Pin12 reserved
// Port1 Pin13 reserved
// Port1 Pin14 reserved
// Port1 Pin15 reserved
// Port1 Pin16 reserved
// Port1 Pin17 reserved
#define PIN18_as_CAP1_0 (b11 << 4)
#define PIN19_as_CAP1_1 (b11 << 6)
#define PIN20_as_SCK0   (b11 << 8)
#define PIN21_as_SSEL0  (b11 << 10)
#define PIN22_as_MAT1_0 (b11 << 12)
#define PIN23_as_MISO0  (b11 << 14)
#define PIN24_as_MOSI0  (b11 << 16)
#define PIN25_as_MAT1_1 (b11 << 18)
#define PIN26_as_CAP0_0 (b11 << 20)
#define PIN27_as_CAP0_1 (b11 << 22)
#define PIN28_as_MAT0_0 (b11 << 24)
#define PIN29_as_MAT0_1 (b11 << 26)
#define PIN30_as_AD0_4  (b11 << 28)
#define PIN31_as_AD0_5  (b11 << 30)


// Port2 First alternate functions
//-------------------------------------
//
#define PIN0_as_PWM1_1      (b01 << 0)
#define PIN1_as_PWM1_2      (b01 << 2)
#define PIN2_as_PWM1_3      (b01 << 4)
#define PIN3_as_PWM1_4      (b01 << 6)
#define PIN4_as_PWM1_5      (b01 << 8)
#define PIN5_as_PWM1_6      (b01 << 10)
#define PIN6_as_PCAP1_0     (b01 << 12)
#define PIN7_as_RD2         (b01 << 14)
#define PIN8_as_TD2         (b01 << 16)
#define PIN9_as_USB_CONNECT (b01 << 18)
#define PIN10_as_nEINT0     (b01 << 20)
#define PIN11_as_nEINT1     (b01 << 22)
#define PIN12_as_nEINT2     (b01 << 24)
#define PIN13_as_nEINT3     (b01 << 26)
// Port2 Pin14 reserved
// Port2 Pin15 reserved
// Port2 Pin16 reserved
// Port2 Pin17 reserved
// Port2 Pin18 reserved
// Port2 Pin19 reserved
// Port2 Pin20 reserved
// Port2 Pin21 reserved
// Port2 Pin22 reserved
// Port2 Pin23 reserved
// Port2 Pin24 reserved
// Port2 Pin25 reserved
// Port2 Pin26 reserved
// Port2 Pin27 reserved
// Port2 Pin28 reserved
// Port2 Pin29 reserved
// Port2 Pin30 reserved
// Port2 Pin31 reserved


// Port2 Second alternate functions
//---------------------------------
//
#define PIN0_as_TXD1    (b10 << 0)
#define PIN1_as_RXD1    (b10 << 2)
#define PIN2_as_CTS1    (b10 << 4)
#define PIN3_as_DCD1    (b10 << 6)
#define PIN4_as_DSR1    (b10 << 8)
#define PIN5_as_DTR1    (b10 << 10)
#define PIN6_as_RI1     (b10 << 12)
#define PIN7_as_RTS1    (b10 << 14)
#define PIN8_as_TXD2    (b10 << 16)
#define PIN9_as_RXD2    (b10 << 18)
#define PIN10_as_NMI    (b10 << 20)
// Port2 Pin11 reserved
// Port2 Pin12 reserved
// Port2 Pin13 reserved
// Port2 Pin14 reserved
// Port2 Pin15 reserved
// Port2 Pin16 reserved
// Port2 Pin17 reserved
// Port2 Pin18 reserved
// Port2 Pin19 reserved
// Port2 Pin20 reserved
// Port2 Pin21 reserved
// Port2 Pin22 reserved
// Port2 Pin23 reserved
// Port2 Pin24 reserved
// Port2 Pin25 reserved
// Port2 Pin26 reserved
// Port2 Pin27 reserved
// Port2 Pin28 reserved
// Port2 Pin29 reserved
// Port2 Pin30 reserved
// Port2 Pin31 reserved


// Port2 Third alternate functions
//---------------------------------

// Port2 Pin0 reserved
// Port2 Pin1 reserved
// Port2 Pin2 reserved
// Port2 Pin3 reserved
// Port2 Pin4 reserved
// Port2 Pin5 reserved
// Port2 Pin6 reserved
// Port2 Pin7 reserved
#define PIN8_as_ENET_MDC   (b11 << 16)
#define PIN9_as_ENET_MDIO  (b11 << 18)
// Port2 Pin10 reserved
#define PIN11_as_I2STX_CLK (b11 << 22)
#define PIN12_as_I2STX_WS  (b11 << 24)
#define PIN13_as_I2STX_SDA (b11 << 26)
// Port2 Pin14 reserved
// Port2 Pin15 reserved
// Port2 Pin16 reserved
// Port2 Pin17 reserved
// Port2 Pin18 reserved
// Port2 Pin19 reserved
// Port2 Pin20 reserved
// Port2 Pin21 reserved
// Port2 Pin22 reserved
// Port2 Pin23 reserved
// Port2 Pin24 reserved
// Port2 Pin25 reserved
// Port2 Pin26 reserved
// Port2 Pin27 reserved
// Port2 Pin28 reserved
// Port2 Pin29 reserved
// Port2 Pin30 reserved
// Port2 Pin31 reserved


// Port3 First alternate functions
//--------------------------------
//
// Port3 Pin0 reserved
// Port3 Pin1 reserved
// Port3 Pin2 reserved
// Port3 Pin3 reserved
// Port3 Pin4 reserved
// Port3 Pin5 reserved
// Port3 Pin6 reserved
// Port3 Pin7 reserved
// Port3 Pin8 reserved
// Port3 Pin9 reserved
// Port3 Pin10 reserved
// Port3 Pin11 reserved
// Port3 Pin12 reserved
// Port3 Pin13 reserved
// Port3 Pin14 reserved
// Port3 Pin15 reserved
// Port3 Pin16 reserved
// Port3 Pin17 reserved
// Port3 Pin18 reserved
// Port3 Pin19 reserved
// Port3 Pin20 reserved
// Port3 Pin21 reserved
// Port3 Pin22 reserved
// Port3 Pin23 reserved
// Port3 Pin24 reserved
// Port3 Pin25 reserved
#define PIN26_as_STCLK (b01 << 20)
// Port3 Pin27 reserved
// Port3 Pin28 reserved
// Port3 Pin29 reserved
// Port3 Pin30 reserved
// Port3 Pin31 reserved


// Port3 Second alternate functions
//---------------------------------
//
// Port3 Pin0 reserved
// Port3 Pin1 reserved
// Port3 Pin2 reserved
// Port3 Pin3 reserved
// Port3 Pin4 reserved
// Port3 Pin5 reserved
// Port3 Pin6 reserved
// Port3 Pin7 reserved
// Port3 Pin8 reserved
// Port3 Pin9 reserved
// Port3 Pin10 reserved
// Port3 Pin11 reserved
// Port3 Pin12 reserved
// Port3 Pin13 reserved
// Port3 Pin14 reserved
// Port3 Pin15 reserved
// Port3 Pin16 reserved
// Port3 Pin17 reserved
// Port3 Pin18 reserved
// Port3 Pin19 reserved
// Port3 Pin20 reserved
// Port3 Pin21 reserved
// Port3 Pin22 reserved
// Port3 Pin23 reserved
// Port3 Pin24 reserved
#define PIN25_as_MAT0_0 (b10 << 18)
#define PIN26_as_MAT0_1 (b10 << 20)
// Port3 Pin27 reserved
// Port3 Pin28 reserved
// Port3 Pin29 reserved
// Port3 Pin30 reserved
// Port3 Pin31 reserved


// Port3 Third alternate functions
//--------------------------------
//
// Port3 Pin0 reserved
// Port3 Pin1 reserved
// Port3 Pin2 reserved
// Port3 Pin3 reserved
// Port3 Pin4 reserved
// Port3 Pin5 reserved
// Port3 Pin6 reserved
// Port3 Pin7 reserved
// Port3 Pin8 reserved
// Port3 Pin9 reserved
// Port3 Pin10 reserved
// Port3 Pin11 reserved
// Port3 Pin12 reserved
// Port3 Pin13 reserved
// Port3 Pin14 reserved
// Port3 Pin15 reserved
// Port3 Pin16 reserved
// Port3 Pin17 reserved
// Port3 Pin18 reserved
// Port3 Pin19 reserved
// Port3 Pin20 reserved
// Port3 Pin21 reserved
// Port3 Pin22 reserved
// Port3 Pin23 reserved
// Port3 Pin24 reserved
#define PIN25_as_PWM1_2 (b11 << 18)
#define PIN26_as_PWM1_3 (b11 << 20)
// Port3 Pin27 reserved
// Port3 Pin28 reserved
// Port3 Pin29 reserved
// Port3 Pin30 reserved
// Port3 Pin31 reserved


// Port4 First alternate functions
//--------------------------------
//
// Port4 Pin0 reserved
// Port4 Pin1 reserved
// Port4 Pin2 reserved
// Port4 Pin3 reserved
// Port4 Pin4 reserved
// Port4 Pin5 reserved
// Port4 Pin6 reserved
// Port4 Pin7 reserved
// Port4 Pin8 reserved
// Port4 Pin9 reserved
// Port4 Pin10 reserved
// Port4 Pin11 reserved
// Port4 Pin12 reserved
// Port4 Pin13 reserved
// Port4 Pin14 reserved
// Port4 Pin15 reserved
// Port4 Pin16 reserved
// Port4 Pin17 reserved
// Port4 Pin18 reserved
// Port4 Pin19 reserved
// Port4 Pin20 reserved
// Port4 Pin21 reserved
// Port4 Pin22 reserved
// Port4 Pin23 reserved
// Port4 Pin24 reserved
// Port4 Pin25 reserved
// Port4 Pin26 reserved
// Port4 Pin27 reserved
#define PIN28_as_RX_MCLK (b01 << 24)
#define PIN29_as_TX_MCLK (b01 << 26)
// Port4 Pin30 reserved
// Port4 Pin31 reserved


// Port4 Second alternate functions
//---------------------------------
//
// Port4 Pin0 reserved
// Port4 Pin1 reserved
// Port4 Pin2 reserved
// Port4 Pin3 reserved
// Port4 Pin4 reserved
// Port4 Pin5 reserved
// Port4 Pin6 reserved
// Port4 Pin7 reserved
// Port4 Pin8 reserved
// Port4 Pin9 reserved
// Port4 Pin10 reserved
// Port4 Pin11 reserved
// Port4 Pin12 reserved
// Port4 Pin13 reserved
// Port4 Pin14 reserved
// Port4 Pin15 reserved
// Port4 Pin16 reserved
// Port4 Pin17 reserved
// Port4 Pin18 reserved
// Port4 Pin19 reserved
// Port4 Pin20 reserved
// Port4 Pin21 reserved
// Port4 Pin22 reserved
// Port4 Pin23 reserved
// Port4 Pin24 reserved
// Port4 Pin25 reserved
// Port4 Pin26 reserved
// Port4 Pin27 reserved
#define PIN28_as_MAT2_0 (b10 << 24)
#define PIN29_as_MAT2_1 (b10 << 26)
// Port4 Pin30 reserved
// Port4 Pin31 reserved


// Port4 Third alternate functions
//--------------------------------
//
// Port4 Pin0 reserved
// Port4 Pin1 reserved
// Port4 Pin2 reserved
// Port4 Pin3 reserved
// Port4 Pin4 reserved
// Port4 Pin5 reserved
// Port4 Pin6 reserved
// Port4 Pin7 reserved
// Port4 Pin8 reserved
// Port4 Pin9 reserved
// Port4 Pin10 reserved
// Port4 Pin11 reserved
// Port4 Pin12 reserved
// Port4 Pin13 reserved
// Port4 Pin14 reserved
// Port4 Pin15 reserved
// Port4 Pin16 reserved
// Port4 Pin17 reserved
// Port4 Pin18 reserved
// Port4 Pin19 reserved
// Port4 Pin20 reserved
// Port4 Pin21 reserved
// Port4 Pin22 reserved
// Port4 Pin23 reserved
// Port4 Pin24 reserved
// Port4 Pin25 reserved
// Port4 Pin26 reserved
// Port4 Pin27 reserved
#define PIN28_as_TXD3 (b11 << 24)
#define PIN29_as_RXD3 (b11 << 26)
// Port4 Pin30 reserved
// Port4 Pin31 reserved


// Port2 Pin2-Pin6 Trace function
//---------------------------------
//
#define TRACE_ENABLED  (1 << 3)
#define TRACE_DISABLED (0 << 3)


// Port0-Port4 on-chip pull-up resistor control (reset values)
//---------------------------------
//
#define PIN0_PULLUP    (b00 << 0)
#define PIN1_PULLUP    (b00 << 2)
#define PIN2_PULLUP    (b00 << 4)
#define PIN3_PULLUP    (b00 << 6)
#define PIN4_PULLUP    (b00 << 8)
#define PIN5_PULLUP    (b00 << 10)
#define PIN6_PULLUP    (b00 << 12)
#define PIN7_PULLUP    (b00 << 14)
#define PIN8_PULLUP    (b00 << 16)
#define PIN9_PULLUP    (b00 << 18)
#define PIN10_PULLUP   (b00 << 20)
#define PIN11_PULLUP   (b00 << 22)
#define PIN12_PULLUP   (b00 << 24)
#define PIN13_PULLUP   (b00 << 26)
#define PIN14_PULLUP   (b00 << 28)
#define PIN15_PULLUP   (b00 << 30)
#define PIN16_PULLUP   (b00 << 0)
#define PIN17_PULLUP   (b00 << 2)
#define PIN18_PULLUP   (b00 << 4)
#define PIN19_PULLUP   (b00 << 6)
#define PIN20_PULLUP   (b00 << 8)
#define PIN21_PULLUP   (b00 << 10)
#define PIN22_PULLUP   (b00 << 12)
#define PIN23_PULLUP   (b00 << 14)
#define PIN24_PULLUP   (b00 << 16)
#define PIN25_PULLUP   (b00 << 18)
#define PIN26_PULLUP   (b00 << 20)
#define PIN27_PULLUP   (b00 << 22)
#define PIN28_PULLUP   (b00 << 24)
#define PIN29_PULLUP   (b00 << 26)
#define PIN30_PULLUP   (b00 << 28)
#define PIN31_PULLUP   (b00 << 30)


// Port0-Port4 on-chip pull-down resistor control
//---------------------------------
//
#define PIN0_PULLDOWN  (b11 << 0)
#define PIN1_PULLDOWN  (b11 << 2)
#define PIN2_PULLDOWN  (b11 << 4)
#define PIN3_PULLDOWN  (b11 << 6)
#define PIN4_PULLDOWN  (b11 << 8)
#define PIN5_PULLDOWN  (b11 << 10)
#define PIN6_PULLDOWN  (b11 << 12)
#define PIN7_PULLDOWN  (b11 << 14)
#define PIN8_PULLDOWN  (b11 << 16)
#define PIN9_PULLDOWN  (b11 << 18)
#define PIN10_PULLDOWN (b11 << 20)
#define PIN11_PULLDOWN (b11 << 22)
#define PIN12_PULLDOWN (b11 << 24)
#define PIN13_PULLDOWN (b11 << 26)
#define PIN14_PULLDOWN (b11 << 28)
#define PIN15_PULLDOWN (b11 << 30)
#define PIN16_PULLDOWN (b11 << 0)
#define PIN17_PULLDOWN (b11 << 2)
#define PIN18_PULLDOWN (b11 << 4)
#define PIN19_PULLDOWN (b11 << 6)
#define PIN20_PULLDOWN (b11 << 8)
#define PIN21_PULLDOWN (b11 << 10)
#define PIN22_PULLDOWN (b11 << 12)
#define PIN23_PULLDOWN (b11 << 14)
#define PIN24_PULLDOWN (b11 << 16)
#define PIN25_PULLDOWN (b11 << 18)
#define PIN26_PULLDOWN (b11 << 20)
#define PIN27_PULLDOWN (b11 << 22)
#define PIN28_PULLDOWN (b11 << 24)
#define PIN29_PULLDOWN (b11 << 26)
#define PIN30_PULLDOWN (b11 << 28)
#define PIN31_PULLDOWN (b11 << 30)


// Port0-Port4 repeater mode control
//---------------------------------
//
#define PIN0_REPEATER  (b01 << 0)
#define PIN1_REPEATER  (b01 << 2)
#define PIN2_REPEATER  (b01 << 4)
#define PIN3_REPEATER  (b01 << 6)
#define PIN4_REPEATER  (b01 << 8)
#define PIN5_REPEATER  (b01 << 10)
#define PIN6_REPEATER  (b01 << 12)
#define PIN7_REPEATER  (b01 << 14)
#define PIN8_REPEATER  (b01 << 16)
#define PIN9_REPEATER  (b01 << 18)
#define PIN10_REPEATER (b01 << 20)
#define PIN11_REPEATER (b01 << 22)
#define PIN12_REPEATER (b01 << 24)
#define PIN13_REPEATER (b01 << 26)
#define PIN14_REPEATER (b01 << 28)
#define PIN15_REPEATER (b01 << 30)
#define PIN16_REPEATER (b01 << 0)
#define PIN17_REPEATER (b01 << 2)
#define PIN18_REPEATER (b01 << 4)
#define PIN19_REPEATER (b01 << 6)
#define PIN20_REPEATER (b01 << 8)
#define PIN21_REPEATER (b01 << 10)
#define PIN22_REPEATER (b01 << 12)
#define PIN23_REPEATER (b01 << 14)
#define PIN24_REPEATER (b01 << 16)
#define PIN25_REPEATER (b01 << 18)
#define PIN26_REPEATER (b01 << 20)
#define PIN27_REPEATER (b01 << 22)
#define PIN28_REPEATER (b01 << 24)
#define PIN29_REPEATER (b01 << 26)
#define PIN30_REPEATER (b01 << 28)
#define PIN31_REPEATER (b01 << 30)


// Port0-Port4 neither pull-up nor pull-down control
//---------------------------------
//
#define PIN0_NOPULL    (b10 << 0)
#define PIN1_NOPULL    (b10 << 2)
#define PIN2_NOPULL    (b10 << 4)
#define PIN3_NOPULL    (b10 << 6)
#define PIN4_NOPULL    (b10 << 8)
#define PIN5_NOPULL    (b10 << 10)
#define PIN6_NOPULL    (b10 << 12)
#define PIN7_NOPULL    (b10 << 14)
#define PIN8_NOPULL    (b10 << 16)
#define PIN9_NOPULL    (b10 << 18)
#define PIN10_NOPULL   (b10 << 20)
#define PIN11_NOPULL   (b10 << 22)
#define PIN12_NOPULL   (b10 << 24)
#define PIN13_NOPULL   (b10 << 26)
#define PIN14_NOPULL   (b10 << 28)
#define PIN15_NOPULL   (b10 << 30)
#define PIN16_NOPULL   (b10 << 0)
#define PIN17_NOPULL   (b10 << 2)
#define PIN18_NOPULL   (b10 << 4)
#define PIN19_NOPULL   (b10 << 6)
#define PIN20_NOPULL   (b10 << 8)
#define PIN21_NOPULL   (b10 << 10)
#define PIN22_NOPULL   (b10 << 12)
#define PIN23_NOPULL   (b10 << 14)
#define PIN24_NOPULL   (b10 << 16)
#define PIN25_NOPULL   (b10 << 18)
#define PIN26_NOPULL   (b10 << 20)
#define PIN27_NOPULL   (b10 << 22)
#define PIN28_NOPULL   (b10 << 24)
#define PIN29_NOPULL   (b10 << 26)
#define PIN30_NOPULL   (b10 << 28)
#define PIN31_NOPULL   (b10 << 30)


// Port0-Port4 Open-Drain mode control
//---------------------------------
//
#define PIN0_OPENDRAIN_ENABLED  (1UL << 0)
#define PIN1_OPENDRAIN_ENABLED  (1UL << 1)
#define PIN2_OPENDRAIN_ENABLED  (1UL << 2)
#define PIN3_OPENDRAIN_ENABLED  (1UL << 3)
#define PIN4_OPENDRAIN_ENABLED  (1UL << 4)
#define PIN5_OPENDRAIN_ENABLED  (1UL << 5)
#define PIN6_OPENDRAIN_ENABLED  (1UL << 6)
#define PIN7_OPENDRAIN_ENABLED  (1UL << 7)
#define PIN8_OPENDRAIN_ENABLED  (1UL << 8)
#define PIN9_OPENDRAIN_ENABLED  (1UL << 9)
#define PIN10_OPENDRAIN_ENABLED (1UL << 10)
#define PIN11_OPENDRAIN_ENABLED (1UL << 11)
#define PIN12_OPENDRAIN_ENABLED (1UL << 12)
#define PIN13_OPENDRAIN_ENABLED (1UL << 13)
#define PIN14_OPENDRAIN_ENABLED (1UL << 14)
#define PIN15_OPENDRAIN_ENABLED (1UL << 15)
#define PIN16_OPENDRAIN_ENABLED (1UL << 16)
#define PIN17_OPENDRAIN_ENABLED (1UL << 17)
#define PIN18_OPENDRAIN_ENABLED (1UL << 18)
#define PIN19_OPENDRAIN_ENABLED (1UL << 19)
#define PIN20_OPENDRAIN_ENABLED (1UL << 20)
#define PIN21_OPENDRAIN_ENABLED (1UL << 21)
#define PIN22_OPENDRAIN_ENABLED (1UL << 22)
#define PIN23_OPENDRAIN_ENABLED (1UL << 23)
#define PIN24_OPENDRAIN_ENABLED (1UL << 24)
#define PIN25_OPENDRAIN_ENABLED (1UL << 25)
#define PIN26_OPENDRAIN_ENABLED (1UL << 26)
#define PIN27_OPENDRAIN_ENABLED (1UL << 27)
#define PIN28_OPENDRAIN_ENABLED (1UL << 28)
#define PIN29_OPENDRAIN_ENABLED (1UL << 29)
#define PIN30_OPENDRAIN_ENABLED (1UL << 30)
#define PIN31_OPENDRAIN_ENABLED (1UL << 31)


/**************************************************/
/*   GPIO CONFIGURE CONTROL                       */
/**************************************************/

// Rename of GPIO port Direction register (FIODIR)

#define PORT_DIRECTION FIODIR

// Direction Control bits for GPIO
//---------------------------------
//
#define PIN0_INPUT   (0UL << 0)
#define PIN1_INPUT   (0UL << 1)
#define PIN2_INPUT   (0UL << 2)
#define PIN3_INPUT   (0UL << 3)
#define PIN4_INPUT   (0UL << 4)
#define PIN5_INPUT   (0UL << 5)
#define PIN6_INPUT   (0UL << 6)
#define PIN7_INPUT   (0UL << 7)
#define PIN8_INPUT   (0UL << 8)
#define PIN9_INPUT   (0UL << 9)
#define PIN10_INPUT  (0UL << 10)
#define PIN11_INPUT  (0UL << 11)
#define PIN12_INPUT  (0UL << 12)
#define PIN13_INPUT  (0UL << 13)
#define PIN14_INPUT  (0UL << 14)
#define PIN15_INPUT  (0UL << 15)
#define PIN16_INPUT  (0UL << 16)
#define PIN17_INPUT  (0UL << 17)
#define PIN18_INPUT  (0UL << 18)
#define PIN19_INPUT  (0UL << 19)
#define PIN20_INPUT  (0UL << 20)
#define PIN21_INPUT  (0UL << 21)
#define PIN22_INPUT  (0UL << 22)
#define PIN23_INPUT  (0UL << 23)
#define PIN24_INPUT  (0UL << 24)
#define PIN25_INPUT  (0UL << 25)
#define PIN26_INPUT  (0UL << 26)
#define PIN27_INPUT  (0UL << 27)
#define PIN28_INPUT  (0UL << 28)
#define PIN29_INPUT  (0UL << 29)
#define PIN30_INPUT  (0UL << 30)
#define PIN31_INPUT  (0UL << 31)

#define PIN0_OUTPUT  (1UL << 0)
#define PIN1_OUTPUT  (1UL << 1)
#define PIN2_OUTPUT  (1UL << 2)
#define PIN3_OUTPUT  (1UL << 3)
#define PIN4_OUTPUT  (1UL << 4)
#define PIN5_OUTPUT  (1UL << 5)
#define PIN6_OUTPUT  (1UL << 6)
#define PIN7_OUTPUT  (1UL << 7)
#define PIN8_OUTPUT  (1UL << 8)
#define PIN9_OUTPUT  (1UL << 9)
#define PIN10_OUTPUT (1UL << 10)
#define PIN11_OUTPUT (1UL << 11)
#define PIN12_OUTPUT (1UL << 12)
#define PIN13_OUTPUT (1UL << 13)
#define PIN14_OUTPUT (1UL << 14)
#define PIN15_OUTPUT (1UL << 15)
#define PIN16_OUTPUT (1UL << 16)
#define PIN17_OUTPUT (1UL << 17)
#define PIN18_OUTPUT (1UL << 18)
#define PIN19_OUTPUT (1UL << 19)
#define PIN20_OUTPUT (1UL << 20)
#define PIN21_OUTPUT (1UL << 21)
#define PIN22_OUTPUT (1UL << 22)
#define PIN23_OUTPUT (1UL << 23)
#define PIN24_OUTPUT (1UL << 24)
#define PIN25_OUTPUT (1UL << 25)
#define PIN26_OUTPUT (1UL << 26)
#define PIN27_OUTPUT (1UL << 27)
#define PIN28_OUTPUT (1UL << 28)
#define PIN29_OUTPUT (1UL << 29)
#define PIN30_OUTPUT (1UL << 30)
#define PIN31_OUTPUT (1UL << 31)


/**************************************************/
/*   GPIO PORT OUTPUT SET/CLEAR CONTROL           */
/**************************************************/

// Rename of GPIO port output Set register (FIOSET)
// Rename of GPIO port output Clear register (FIOCLR)

#define PORT_SET FIOSET
#define PORT_CLEAR FIOCLR


/**************************************************/
/*   POWER CONTROL                                */
/**************************************************/

// Rename of Power Control for Peripherals register (PCONP)

#define POWER_CONTROL PCONP

// Power/Clock Control bits for Peripherals
//---------------------------------
//

// 0 - Reserved
#define TIMER0_POWERED    (1UL << 1)
#define TIMER1_POWERED    (1UL << 2)
#define UART0_POWERED     (1UL << 3)
#define UART1_POWERED     (1UL << 4)
// 5 - Reserved
#define PWM1_POWERED      (1UL << 6)
#define I2C0_POWERED      (1UL << 7)
#define SPI_POWERED       (1UL << 8)
#define RTC_POWERED       (1UL << 9)
#define SSP1_POWERED      (1UL << 10)
// 11 - Reserved
#define ADC_POWERED       (1UL << 12)
//Note:Clear the PDN bit in the AD0CR before clearing this bit, and set 
//this bit before setting PDN.
#define CAN1_POWERED      (1UL << 13)
#define CAN2_POWERED      (1UL << 14)
#define GPIO_POWERED      (1UL << 15)
#define INT_TIMER_POWERED (1UL << 16)
#define MOTORPWM_POWERED  (1UL << 17)
#define ENCODER_POWERED   (1UL << 18)
#define I2C1_POWERED      (1UL << 19)
// 20 - Reserved
#define SSP0_POWERED      (1UL << 21)
#define TIMER2_POWERED    (1UL << 22)
#define TIMER3_POWERED    (1UL << 23)
#define UART2_POWERED     (1UL << 24)
#define UART3_POWERED     (1UL << 25)
#define I2C_POWERED       (1UL << 26)
#define I2S_POWERED       (1UL << 27)
// 28 - Reserved
#define GPDMA_POWERED     (1UL << 29)
#define ETHERNET_POWERED  (1UL << 30)
#define USB_POWERED       (1UL << 31)





#endif  // __LPC1768_DEFINE_H__
