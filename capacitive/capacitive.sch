EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:stm32f070c6t6
LIBS:tlv9062idr
LIBS:sg7050can_8mhz
LIBS:tlv74133pdbvr
LIBS:capacitive-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 7750 5450 2    60   ~ 0
+1V65
$Comp
L +3V3 #PWR110
U 1 1 5AFFB346
P 4250 4350
F 0 "#PWR110" H 4250 4200 50  0001 C CNN
F 1 "+3V3" H 4250 4490 50  0000 C CNN
F 2 "" H 4250 4350 50  0001 C CNN
F 3 "" H 4250 4350 50  0001 C CNN
	1    4250 4350
	1    0    0    -1  
$EndComp
$Comp
L STM32F070C6T6 U101
U 1 1 5B00207F
P 1450 750
F 0 "U101" H 1450 750 60  0000 C CNN
F 1 "STM32F070C6T6" H 2300 750 60  0000 C CNN
F 2 "" H 1450 750 60  0001 C CNN
F 3 "" H 1450 750 60  0001 C CNN
	1    1450 750 
	1    0    0    -1  
$EndComp
$Comp
L STM32F070C6T6 U101
U 2 1 5B002080
P 4550 750
F 0 "U101" H 4550 750 60  0000 C CNN
F 1 "STM32F070C6T6" H 5500 750 60  0000 C CNN
F 2 "" H 4550 750 60  0001 C CNN
F 3 "" H 4550 750 60  0001 C CNN
	2    4550 750 
	1    0    0    -1  
$EndComp
$Comp
L STM32F070C6T6 U101
U 4 1 5B002082
P 4500 2450
F 0 "U101" H 4500 2450 60  0000 C CNN
F 1 "STM32F070C6T6" H 5350 2450 60  0000 C CNN
F 2 "" H 4500 2450 60  0001 C CNN
F 3 "" H 4500 2450 60  0001 C CNN
	4    4500 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR102
U 1 1 5B002083
P 1000 1600
F 0 "#PWR102" H 1000 1350 50  0001 C CNN
F 1 "GND" H 1000 1450 50  0000 C CNN
F 2 "" H 1000 1600 50  0001 C CNN
F 3 "" H 1000 1600 50  0001 C CNN
	1    1000 1600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR106
U 1 1 5B002084
P 1200 3600
F 0 "#PWR106" H 1200 3350 50  0001 C CNN
F 1 "GND" H 1200 3450 50  0000 C CNN
F 2 "" H 1200 3600 50  0001 C CNN
F 3 "" H 1200 3600 50  0001 C CNN
	1    1200 3600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR104
U 1 1 5B002085
P 4200 1900
F 0 "#PWR104" H 4200 1650 50  0001 C CNN
F 1 "GND" H 4200 1750 50  0000 C CNN
F 2 "" H 4200 1900 50  0001 C CNN
F 3 "" H 4200 1900 50  0001 C CNN
	1    4200 1900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR107
U 1 1 5B002086
P 4150 3600
F 0 "#PWR107" H 4150 3350 50  0001 C CNN
F 1 "GND" H 4150 3450 50  0000 C CNN
F 2 "" H 4150 3600 50  0001 C CNN
F 3 "" H 4150 3600 50  0001 C CNN
	1    4150 3600
	0    1    1    0   
$EndComp
$Comp
L R_Small R107
U 1 1 5B002087
P 6550 6750
F 0 "R107" H 6580 6770 50  0000 L CNN
F 1 "100k 5%" H 6580 6710 50  0000 L CNN
F 2 "" H 6550 6750 50  0001 C CNN
F 3 "" H 6550 6750 50  0001 C CNN
	1    6550 6750
	1    0    0    -1  
$EndComp
$Comp
L C_Small C111
U 1 1 5B002088
P 6550 7150
F 0 "C111" H 6560 7220 50  0000 L CNN
F 1 "10nF 1%" H 6560 7070 50  0000 L CNN
F 2 "" H 6550 7150 50  0001 C CNN
F 3 "" H 6550 7150 50  0001 C CNN
	1    6550 7150
	1    0    0    -1  
$EndComp
Text Label 6250 6900 0    60   ~ 0
NRST
$Comp
L R_Small R103
U 1 1 5B00208A
P 9850 5600
F 0 "R103" H 9880 5620 50  0000 L CNN
F 1 "1.59k 1%" H 9880 5560 50  0000 L CNN
F 2 "" H 9850 5600 50  0001 C CNN
F 3 "" H 9850 5600 50  0001 C CNN
	1    9850 5600
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R104
U 1 1 5B00208B
P 10350 5600
F 0 "R104" H 10380 5620 50  0000 L CNN
F 1 "15.9k 1%" H 10380 5560 50  0000 L CNN
F 2 "" H 10350 5600 50  0001 C CNN
F 3 "" H 10350 5600 50  0001 C CNN
	1    10350 5600
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C108
U 1 1 5B00208C
P 10050 5800
F 0 "C108" H 10060 5870 50  0000 L CNN
F 1 "100nF 1%" H 10060 5720 50  0000 L CNN
F 2 "" H 10050 5800 50  0001 C CNN
F 3 "" H 10050 5800 50  0001 C CNN
	1    10050 5800
	1    0    0    -1  
$EndComp
$Comp
L C_Small C109
U 1 1 5B00208D
P 10550 5800
F 0 "C109" H 10560 5870 50  0000 L CNN
F 1 "10nF 1%" H 10560 5720 50  0000 L CNN
F 2 "" H 10550 5800 50  0001 C CNN
F 3 "" H 10550 5800 50  0001 C CNN
	1    10550 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR121
U 1 1 5B00208E
P 10050 6000
F 0 "#PWR121" H 10050 5750 50  0001 C CNN
F 1 "GND" H 10050 5850 50  0000 C CNN
F 2 "" H 10050 6000 50  0001 C CNN
F 3 "" H 10050 6000 50  0001 C CNN
	1    10050 6000
	1    0    0    -1  
$EndComp
$Comp
L TLV9062IDR U102
U 1 1 5B002090
P 9400 5600
F 0 "U102" H 9400 5600 60  0000 C CNN
F 1 "TLV9062IDR" H 8950 5350 60  0000 C CNN
F 2 "" H 9400 5600 60  0001 C CNN
F 3 "" H 9400 5600 60  0001 C CNN
F 4 "595-TLV9062IDR" H 9400 5600 60  0001 C CNN "Mouser"
	1    9400 5600
	1    0    0    -1  
$EndComp
$Comp
L C_Small C103
U 1 1 5B002093
P 9550 5100
F 0 "C103" H 9560 5170 50  0000 L CNN
F 1 "100nF 5%" H 9560 5020 50  0000 L CNN
F 2 "" H 9550 5100 50  0001 C CNN
F 3 "" H 9550 5100 50  0001 C CNN
	1    9550 5100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR113
U 1 1 5B002094
P 9750 5100
F 0 "#PWR113" H 9750 4850 50  0001 C CNN
F 1 "GND" H 9750 4950 50  0000 C CNN
F 2 "" H 9750 5100 50  0001 C CNN
F 3 "" H 9750 5100 50  0001 C CNN
	1    9750 5100
	0    -1   -1   0   
$EndComp
$Comp
L +3.3VA #PWR112
U 1 1 5B002095
P 9300 5000
F 0 "#PWR112" H 9300 4850 50  0001 C CNN
F 1 "+3.3VA" H 9300 5140 50  0000 C CNN
F 2 "" H 9300 5000 50  0001 C CNN
F 3 "" H 9300 5000 50  0001 C CNN
	1    9300 5000
	1    0    0    -1  
$EndComp
Text Label 10900 5600 2    60   ~ 0
ADC_IN
$Comp
L R_Small R102
U 1 1 5B002099
P 6250 5350
F 0 "R102" H 6280 5370 50  0000 L CNN
F 1 "100k 1%" H 6280 5310 50  0000 L CNN
F 2 "" H 6250 5350 50  0001 C CNN
F 3 "" H 6250 5350 50  0001 C CNN
	1    6250 5350
	-1   0    0    -1  
$EndComp
$Comp
L R_Small R105
U 1 1 5B00209A
P 6250 5800
F 0 "R105" H 6280 5820 50  0000 L CNN
F 1 "100k 1%" H 6280 5760 50  0000 L CNN
F 2 "" H 6250 5800 50  0001 C CNN
F 3 "" H 6250 5800 50  0001 C CNN
	1    6250 5800
	-1   0    0    -1  
$EndComp
$Comp
L C_Small C110
U 1 1 5B00209B
P 6400 5800
F 0 "C110" H 6410 5870 50  0000 L CNN
F 1 "100nF 5%" H 6410 5720 50  0000 L CNN
F 2 "" H 6400 5800 50  0001 C CNN
F 3 "" H 6400 5800 50  0001 C CNN
	1    6400 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR125
U 1 1 5B00209C
P 6250 6000
F 0 "#PWR125" H 6250 5750 50  0001 C CNN
F 1 "GND" H 6250 5850 50  0000 C CNN
F 2 "" H 6250 6000 50  0001 C CNN
F 3 "" H 6250 6000 50  0001 C CNN
	1    6250 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR126
U 1 1 5B00209D
P 6400 6000
F 0 "#PWR126" H 6400 5750 50  0001 C CNN
F 1 "GND" H 6400 5850 50  0000 C CNN
F 2 "" H 6400 6000 50  0001 C CNN
F 3 "" H 6400 6000 50  0001 C CNN
	1    6400 6000
	1    0    0    -1  
$EndComp
$Comp
L +3.3VA #PWR116
U 1 1 5B00209E
P 6250 5150
F 0 "#PWR116" H 6250 5000 50  0001 C CNN
F 1 "+3.3VA" H 6250 5290 50  0000 C CNN
F 2 "" H 6250 5150 50  0001 C CNN
F 3 "" H 6250 5150 50  0001 C CNN
	1    6250 5150
	1    0    0    -1  
$EndComp
$Comp
L C_Small C107
U 1 1 5B00209F
P 7350 5700
F 0 "C107" H 7360 5770 50  0000 L CNN
F 1 "100pF 5%" H 7360 5620 50  0000 L CNN
F 2 "" H 7350 5700 50  0001 C CNN
F 3 "" H 7350 5700 50  0001 C CNN
	1    7350 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR124
U 1 1 5B0020A0
P 7350 5950
F 0 "#PWR124" H 7350 5700 50  0001 C CNN
F 1 "GND" H 7350 5800 50  0000 C CNN
F 2 "" H 7350 5950 50  0001 C CNN
F 3 "" H 7350 5950 50  0001 C CNN
	1    7350 5950
	1    0    0    -1  
$EndComp
Text Label 7750 5450 2    60   ~ 0
+1V65
Text Label 3700 3400 0    60   ~ 0
I2C_SCL
Text Label 900  4950 0    60   ~ 0
I2C_SDA
Text Label 3700 3100 0    60   ~ 0
UART_TX
Text Label 3700 3200 0    60   ~ 0
UART_RX
Text Label 850  3000 0    60   ~ 0
PHASE0
Text Label 850  3100 0    60   ~ 0
PHASE1
Text Label 3800 1200 0    60   ~ 0
PHASE4
Text Label 3800 1300 0    60   ~ 0
PHASE5
Text Label 3800 1400 0    60   ~ 0
PHASE6
Text Label 3800 1500 0    60   ~ 0
PHASE7
Text Label 750  2200 0    60   ~ 0
ADC_IN
Text Label 3700 2600 0    60   ~ 0
SWCLK
Text Label 850  3500 0    60   ~ 0
SWDIO
Text Label 5450 6900 0    60   ~ 0
BOOT0
$Comp
L R_Small R108
U 1 1 5B0020A1
P 5850 6750
F 0 "R108" H 5880 6770 50  0000 L CNN
F 1 "DNP" H 5880 6710 50  0000 L CNN
F 2 "" H 5850 6750 50  0001 C CNN
F 3 "" H 5850 6750 50  0001 C CNN
	1    5850 6750
	1    0    0    -1  
$EndComp
Text Label 3700 3300 0    60   ~ 0
BOOT0
Text Label 750  1500 0    60   ~ 0
NRST
$Comp
L +3.3VA #PWR103
U 1 1 5B0020A4
P 850 1700
F 0 "#PWR103" H 850 1550 50  0001 C CNN
F 1 "+3.3VA" H 850 1840 50  0000 C CNN
F 2 "" H 850 1700 50  0001 C CNN
F 3 "" H 850 1700 50  0001 C CNN
	1    850  1700
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR123
U 1 1 5B0020A7
P 6550 6500
F 0 "#PWR123" H 6550 6350 50  0001 C CNN
F 1 "+3V3" H 6550 6640 50  0000 C CNN
F 2 "" H 6550 6500 50  0001 C CNN
F 3 "" H 6550 6500 50  0001 C CNN
	1    6550 6500
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR101
U 1 1 5B0020A8
P 900 900
F 0 "#PWR101" H 900 750 50  0001 C CNN
F 1 "+3V3" H 900 1040 50  0000 C CNN
F 2 "" H 900 900 50  0001 C CNN
F 3 "" H 900 900 50  0001 C CNN
	1    900  900 
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C101
U 1 1 5B0020A9
P 4500 4650
F 0 "C101" H 4510 4720 50  0000 L CNN
F 1 "100nF 5%" H 4510 4570 50  0000 L CNN
F 2 "" H 4500 4650 50  0001 C CNN
F 3 "" H 4500 4650 50  0001 C CNN
	1    4500 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR114
U 1 1 5B0020AC
P 4500 4850
F 0 "#PWR114" H 4500 4600 50  0001 C CNN
F 1 "GND" H 4500 4700 50  0000 C CNN
F 2 "" H 4500 4850 50  0001 C CNN
F 3 "" H 4500 4850 50  0001 C CNN
	1    4500 4850
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR105
U 1 1 5B0020AD
P 4050 2000
F 0 "#PWR105" H 4050 1850 50  0001 C CNN
F 1 "+3V3" H 4050 2140 50  0000 C CNN
F 2 "" H 4050 2000 50  0001 C CNN
F 3 "" H 4050 2000 50  0001 C CNN
	1    4050 2000
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR109
U 1 1 5B0020AE
P 3950 3700
F 0 "#PWR109" H 3950 3550 50  0001 C CNN
F 1 "+3V3" H 3950 3840 50  0000 C CNN
F 2 "" H 3950 3700 50  0001 C CNN
F 3 "" H 3950 3700 50  0001 C CNN
	1    3950 3700
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR108
U 1 1 5B0020AF
P 1000 3700
F 0 "#PWR108" H 1000 3550 50  0001 C CNN
F 1 "+3V3" H 1000 3840 50  0000 C CNN
F 2 "" H 1000 3700 50  0001 C CNN
F 3 "" H 1000 3700 50  0001 C CNN
	1    1000 3700
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C104
U 1 1 5B0020B2
P 3550 4650
F 0 "C104" H 3560 4720 50  0000 L CNN
F 1 "100nF 5%" H 3560 4570 50  0000 L CNN
F 2 "" H 3550 4650 50  0001 C CNN
F 3 "" H 3550 4650 50  0001 C CNN
	1    3550 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR118
U 1 1 5B0020B3
P 4000 4850
F 0 "#PWR118" H 4000 4600 50  0001 C CNN
F 1 "GND" H 4000 4700 50  0000 C CNN
F 2 "" H 4000 4850 50  0001 C CNN
F 3 "" H 4000 4850 50  0001 C CNN
	1    4000 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR117
U 1 1 5B0020B4
P 3550 4850
F 0 "#PWR117" H 3550 4600 50  0001 C CNN
F 1 "GND" H 3550 4700 50  0000 C CNN
F 2 "" H 3550 4850 50  0001 C CNN
F 3 "" H 3550 4850 50  0001 C CNN
	1    3550 4850
	1    0    0    -1  
$EndComp
$Comp
L +3.3VA #PWR111
U 1 1 5B0020B6
P 3200 4450
F 0 "#PWR111" H 3200 4300 50  0001 C CNN
F 1 "+3.3VA" H 3200 4590 50  0000 C CNN
F 2 "" H 3200 4450 50  0001 C CNN
F 3 "" H 3200 4450 50  0001 C CNN
	1    3200 4450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J102
U 1 1 5B0020B7
P 1550 5900
F 0 "J102" H 1550 6100 50  0000 C CNN
F 1 "UART" H 1550 5600 50  0000 C CNN
F 2 "" H 1550 5900 50  0001 C CNN
F 3 "" H 1550 5900 50  0001 C CNN
	1    1550 5900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J103
U 1 1 5B0020B9
P 1550 7050
F 0 "J103" H 1550 7350 50  0000 C CNN
F 1 "SWD" H 1550 6650 50  0000 C CNN
F 2 "" H 1550 7050 50  0001 C CNN
F 3 "" H 1550 7050 50  0001 C CNN
	1    1550 7050
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR130
U 1 1 5B0020BC
P 1250 6700
F 0 "#PWR130" H 1250 6550 50  0001 C CNN
F 1 "+3V3" H 1250 6840 50  0000 C CNN
F 2 "" H 1250 6700 50  0001 C CNN
F 3 "" H 1250 6700 50  0001 C CNN
	1    1250 6700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR136
U 1 1 5B0020BD
P 1250 7450
F 0 "#PWR136" H 1250 7200 50  0001 C CNN
F 1 "GND" H 1250 7300 50  0000 C CNN
F 2 "" H 1250 7450 50  0001 C CNN
F 3 "" H 1250 7450 50  0001 C CNN
	1    1250 7450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR135
U 1 1 5B0020BE
P 1250 6200
F 0 "#PWR135" H 1250 5950 50  0001 C CNN
F 1 "GND" H 1250 6050 50  0000 C CNN
F 2 "" H 1250 6200 50  0001 C CNN
F 3 "" H 1250 6200 50  0001 C CNN
	1    1250 6200
	1    0    0    -1  
$EndComp
Text Label 1000 6950 0    60   ~ 0
NRST
Text Label 1000 7150 0    60   ~ 0
SWCLK
Text Label 1000 7050 0    60   ~ 0
SWDIO
$Comp
L +5V #PWR133
U 1 1 5B0020C0
P 1000 7250
F 0 "#PWR133" H 1000 7100 50  0001 C CNN
F 1 "+5V" H 1000 7390 50  0000 C CNN
F 2 "" H 1000 7250 50  0001 C CNN
F 3 "" H 1000 7250 50  0001 C CNN
	1    1000 7250
	0    -1   -1   0   
$EndComp
Text Label 900  5900 0    60   ~ 0
UART_TX
Text Label 900  6000 0    60   ~ 0
UART_RX
Text Label 3700 3500 0    60   ~ 0
I2C_SDA
$Comp
L C_Small C105
U 1 1 5B0020B1
P 4000 4650
F 0 "C105" H 4010 4720 50  0000 L CNN
F 1 "100nF 5%" H 4010 4570 50  0000 L CNN
F 2 "" H 4000 4650 50  0001 C CNN
F 3 "" H 4000 4650 50  0001 C CNN
	1    4000 4650
	1    0    0    -1  
$EndComp
$Comp
L C_Small C106
U 1 1 5AFFB3B0
P 3200 4650
F 0 "C106" H 3210 4720 50  0000 L CNN
F 1 "100nF 5%" H 3210 4570 50  0000 L CNN
F 2 "" H 3200 4650 50  0001 C CNN
F 3 "" H 3200 4650 50  0001 C CNN
	1    3200 4650
	-1   0    0    -1  
$EndComp
$Comp
L C_Small C102
U 1 1 5B0020B0
P 4950 4650
F 0 "C102" H 4960 4720 50  0000 L CNN
F 1 "100nF 5%" H 4960 4570 50  0000 L CNN
F 2 "" H 4950 4650 50  0001 C CNN
F 3 "" H 4950 4650 50  0001 C CNN
	1    4950 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR115
U 1 1 5B0020B5
P 4950 4850
F 0 "#PWR115" H 4950 4600 50  0001 C CNN
F 1 "GND" H 4950 4700 50  0000 C CNN
F 2 "" H 4950 4850 50  0001 C CNN
F 3 "" H 4950 4850 50  0001 C CNN
	1    4950 4850
	1    0    0    -1  
$EndComp
$Comp
L STM32F070C6T6 U101
U 3 1 5B002081
P 1550 2450
F 0 "U101" H 1550 2450 60  0000 C CNN
F 1 "STM32F070C6T6" H 2400 2450 60  0000 C CNN
F 2 "" H 1550 2450 60  0001 C CNN
F 3 "" H 1550 2450 60  0001 C CNN
	3    1550 2450
	1    0    0    -1  
$EndComp
Text Label 850  3300 0    60   ~ 0
PHASE3
Text Label 850  3200 0    60   ~ 0
PHASE2
$Comp
L GND #PWR119
U 1 1 5B0020A5
P 3200 4850
F 0 "#PWR119" H 3200 4600 50  0001 C CNN
F 1 "GND" H 3200 4700 50  0000 C CNN
F 2 "" H 3200 4850 50  0001 C CNN
F 3 "" H 3200 4850 50  0001 C CNN
	1    3200 4850
	1    0    0    -1  
$EndComp
$Comp
L TLV9062IDR U102
U 2 1 5B002091
P 6900 5450
F 0 "U102" H 6900 5450 60  0000 C CNN
F 1 "TLV9062IDR" H 6900 5150 60  0000 C CNN
F 2 "" H 6900 5450 60  0001 C CNN
F 3 "" H 6900 5450 60  0001 C CNN
F 4 "595-TLV9062IDR" H 6900 5450 60  0001 C CNN "Mouser"
	2    6900 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR122
U 1 1 5B00208F
P 10550 6000
F 0 "#PWR122" H 10550 5750 50  0001 C CNN
F 1 "GND" H 10550 5850 50  0000 C CNN
F 2 "" H 10550 6000 50  0001 C CNN
F 3 "" H 10550 6000 50  0001 C CNN
	1    10550 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR120
U 1 1 5B002092
P 9300 5950
F 0 "#PWR120" H 9300 5700 50  0001 C CNN
F 1 "GND" H 9300 5800 50  0000 C CNN
F 2 "" H 9300 5950 50  0001 C CNN
F 3 "" H 9300 5950 50  0001 C CNN
	1    9300 5950
	1    0    0    -1  
$EndComp
Text Label 8200 5700 0    60   ~ 0
RX_PAD
$Comp
L R_Small R101
U 1 1 5B002097
P 8400 5200
F 0 "R101" H 8430 5220 50  0000 L CNN
F 1 "100 1%" H 8430 5160 50  0000 L CNN
F 2 "" H 8400 5200 50  0001 C CNN
F 3 "" H 8400 5200 50  0001 C CNN
	1    8400 5200
	0    -1   -1   0   
$EndComp
$Comp
L POT RV101
U 1 1 5B002096
P 8800 5200
F 0 "RV101" V 8625 5200 50  0000 C CNN
F 1 "100k linear" V 8700 5200 50  0000 C CNN
F 2 "" H 8800 5200 50  0001 C CNN
F 3 "" H 8800 5200 50  0001 C CNN
	1    8800 5200
	0    1    1    0   
$EndComp
Text Label 7950 5200 0    60   ~ 0
+1V65
$Comp
L R_Small R106
U 1 1 5B002098
P 8600 5900
F 0 "R106" H 8630 5920 50  0000 L CNN
F 1 "10M 5%" H 8630 5860 50  0000 L CNN
F 2 "" H 8600 5900 50  0001 C CNN
F 3 "" H 8600 5900 50  0001 C CNN
	1    8600 5900
	-1   0    0    -1  
$EndComp
Text Label 8200 6300 0    60   ~ 0
+1V65
$Comp
L R_Small R109
U 1 1 5B0020A2
P 5850 7050
F 0 "R109" H 5880 7070 50  0000 L CNN
F 1 "100k 5%" H 5880 7010 50  0000 L CNN
F 2 "" H 5850 7050 50  0001 C CNN
F 3 "" H 5850 7050 50  0001 C CNN
	1    5850 7050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR128
U 1 1 5B0020A3
P 5850 7250
F 0 "#PWR128" H 5850 7000 50  0001 C CNN
F 1 "GND" H 5850 7100 50  0000 C CNN
F 2 "" H 5850 7250 50  0001 C CNN
F 3 "" H 5850 7250 50  0001 C CNN
	1    5850 7250
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR127
U 1 1 5B0020A6
P 5850 6550
F 0 "#PWR127" H 5850 6400 50  0001 C CNN
F 1 "+3V3" H 5850 6690 50  0000 C CNN
F 2 "" H 5850 6550 50  0001 C CNN
F 3 "" H 5850 6550 50  0001 C CNN
	1    5850 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR129
U 1 1 5B002089
P 6550 7350
F 0 "#PWR129" H 6550 7100 50  0001 C CNN
F 1 "GND" H 6550 7200 50  0000 C CNN
F 2 "" H 6550 7350 50  0001 C CNN
F 3 "" H 6550 7350 50  0001 C CNN
	1    6550 7350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR134
U 1 1 5B0020BF
P 1200 5150
F 0 "#PWR134" H 1200 4900 50  0001 C CNN
F 1 "GND" H 1200 5000 50  0000 C CNN
F 2 "" H 1200 5150 50  0001 C CNN
F 3 "" H 1200 5150 50  0001 C CNN
	1    1200 5150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J101
U 1 1 5B0020B8
P 1550 4850
F 0 "J101" H 1550 5050 50  0000 C CNN
F 1 "I2C" H 1550 4550 50  0000 C CNN
F 2 "" H 1550 4850 50  0001 C CNN
F 3 "" H 1550 4850 50  0001 C CNN
	1    1550 4850
	1    0    0    -1  
$EndComp
Text Label 900  4850 0    60   ~ 0
I2C_SCL
$Comp
L +3V3 #PWR?
U 1 1 5AFFF10F
P 4400 6700
F 0 "#PWR?" H 4400 6550 50  0001 C CNN
F 1 "+3V3" H 4400 6840 50  0000 C CNN
F 2 "" H 4400 6700 50  0001 C CNN
F 3 "" H 4400 6700 50  0001 C CNN
	1    4400 6700
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5AFFF1E0
P 4300 6900
F 0 "C?" H 4310 6970 50  0000 L CNN
F 1 "100nF 5%" H 4310 6820 50  0000 L CNN
F 2 "" H 4300 6900 50  0001 C CNN
F 3 "" H 4300 6900 50  0001 C CNN
	1    4300 6900
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5AFFF258
P 4200 6000
F 0 "C?" H 4210 6070 50  0000 L CNN
F 1 "10uF 10%" H 4210 5920 50  0000 L CNN
F 2 "" H 4200 6000 50  0001 C CNN
F 3 "" H 4200 6000 50  0001 C CNN
	1    4200 6000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5AFFF2E3
P 4600 6000
F 0 "C?" H 4610 6070 50  0000 L CNN
F 1 "100nF 5%" H 4610 5920 50  0000 L CNN
F 2 "" H 4600 6000 50  0001 C CNN
F 3 "" H 4600 6000 50  0001 C CNN
	1    4600 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AFFF58F
P 3850 7100
F 0 "#PWR?" H 3850 6850 50  0001 C CNN
F 1 "GND" H 3850 6950 50  0000 C CNN
F 2 "" H 3850 7100 50  0001 C CNN
F 3 "" H 3850 7100 50  0001 C CNN
	1    3850 7100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AFFF6A9
P 4300 7100
F 0 "#PWR?" H 4300 6850 50  0001 C CNN
F 1 "GND" H 4300 6950 50  0000 C CNN
F 2 "" H 4300 7100 50  0001 C CNN
F 3 "" H 4300 7100 50  0001 C CNN
	1    4300 7100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AFFFA9C
P 3400 7100
F 0 "#PWR?" H 3400 6850 50  0001 C CNN
F 1 "GND" H 3400 6950 50  0000 C CNN
F 2 "" H 3400 7100 50  0001 C CNN
F 3 "" H 3400 7100 50  0001 C CNN
	1    3400 7100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B000180
P 4200 6200
F 0 "#PWR?" H 4200 5950 50  0001 C CNN
F 1 "GND" H 4200 6050 50  0000 C CNN
F 2 "" H 4200 6200 50  0001 C CNN
F 3 "" H 4200 6200 50  0001 C CNN
	1    4200 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B00029F
P 4600 6200
F 0 "#PWR?" H 4600 5950 50  0001 C CNN
F 1 "GND" H 4600 6050 50  0000 C CNN
F 2 "" H 4600 6200 50  0001 C CNN
F 3 "" H 4600 6200 50  0001 C CNN
	1    4600 6200
	1    0    0    -1  
$EndComp
$Comp
L +3.3VA #PWR?
U 1 1 5B00067D
P 4600 5600
F 0 "#PWR?" H 4600 5450 50  0001 C CNN
F 1 "+3.3VA" H 4600 5740 50  0000 C CNN
F 2 "" H 4600 5600 50  0001 C CNN
F 3 "" H 4600 5600 50  0001 C CNN
	1    4600 5600
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J?
U 1 1 5B001CB8
P 2350 4750
F 0 "J?" H 2350 4850 50  0000 C CNN
F 1 "POWER" H 2350 4550 50  0000 C CNN
F 2 "" H 2350 4750 50  0001 C CNN
F 3 "" H 2350 4750 50  0001 C CNN
	1    2350 4750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B001F47
P 2050 4950
F 0 "#PWR?" H 2050 4700 50  0001 C CNN
F 1 "GND" H 2050 4800 50  0000 C CNN
F 2 "" H 2050 4950 50  0001 C CNN
F 3 "" H 2050 4950 50  0001 C CNN
	1    2050 4950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B002244
P 2050 4650
F 0 "#PWR?" H 2050 4500 50  0001 C CNN
F 1 "+5V" H 2050 4790 50  0000 C CNN
F 2 "" H 2050 4650 50  0001 C CNN
F 3 "" H 2050 4650 50  0001 C CNN
	1    2050 4650
	1    0    0    -1  
$EndComp
$Comp
L TEST TP?
U 1 1 5B00268D
P 4700 5750
F 0 "TP?" H 4700 6050 50  0000 C BNN
F 1 "TEST" H 4700 6000 50  0000 C CNN
F 2 "" H 4700 5750 50  0001 C CNN
F 3 "" H 4700 5750 50  0001 C CNN
	1    4700 5750
	0    1    1    0   
$EndComp
$Comp
L TEST TP?
U 1 1 5B002977
P 4450 6750
F 0 "TP?" H 4450 7050 50  0000 C BNN
F 1 "TEST" H 4450 7000 50  0000 C CNN
F 2 "" H 4450 6750 50  0001 C CNN
F 3 "" H 4450 6750 50  0001 C CNN
	1    4450 6750
	0    1    1    0   
$EndComp
$Comp
L TEST TP?
U 1 1 5B002E59
P 8750 6050
F 0 "TP?" H 8750 6350 50  0000 C BNN
F 1 "TEST" H 8750 6300 50  0000 C CNN
F 2 "" H 8750 6050 50  0001 C CNN
F 3 "" H 8750 6050 50  0001 C CNN
	1    8750 6050
	-1   0    0    1   
$EndComp
$Comp
L TEST TP?
U 1 1 5B0031FC
P 7300 5050
F 0 "TP?" H 7300 5350 50  0000 C BNN
F 1 "TEST" H 7300 5300 50  0000 C CNN
F 2 "" H 7300 5050 50  0001 C CNN
F 3 "" H 7300 5050 50  0001 C CNN
	1    7300 5050
	0    1    1    0   
$EndComp
$Comp
L TEST TP?
U 1 1 5B0035C8
P 9700 5750
F 0 "TP?" H 9700 6050 50  0000 C BNN
F 1 "TEST" H 9700 6000 50  0000 C CNN
F 2 "" H 9700 5750 50  0001 C CNN
F 3 "" H 9700 5750 50  0001 C CNN
	1    9700 5750
	-1   0    0    1   
$EndComp
$Comp
L TEST TP?
U 1 1 5B00379E
P 10050 5500
F 0 "TP?" H 10050 5800 50  0000 C BNN
F 1 "TEST" H 10050 5750 50  0000 C CNN
F 2 "" H 10050 5500 50  0001 C CNN
F 3 "" H 10050 5500 50  0001 C CNN
	1    10050 5500
	1    0    0    -1  
$EndComp
$Comp
L TEST TP?
U 1 1 5B003AC1
P 10550 5450
F 0 "TP?" H 10550 5750 50  0000 C BNN
F 1 "TEST" H 10550 5700 50  0000 C CNN
F 2 "" H 10550 5450 50  0001 C CNN
F 3 "" H 10550 5450 50  0001 C CNN
	1    10550 5450
	1    0    0    -1  
$EndComp
Text Label 750  1300 0    60   ~ 0
OSC_8MHz
$Comp
L SG7050CAN_8.000000M-TJGA3 U?
U 1 1 5B005A80
P 8500 3850
F 0 "U?" H 8450 4050 60  0000 C CNN
F 1 "SG7050CAN_8.000000M-TJGA3" H 8500 3600 60  0000 C CNN
F 2 "" H 8450 3850 60  0001 C CNN
F 3 "" H 8450 3850 60  0001 C CNN
F 4 "732-7050CA8.00TJGA3" H 8500 3850 60  0001 C CNN "Mouser"
	1    8500 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B005F51
P 8900 3950
F 0 "#PWR?" H 8900 3700 50  0001 C CNN
F 1 "GND" H 8900 3800 50  0000 C CNN
F 2 "" H 8900 3950 50  0001 C CNN
F 3 "" H 8900 3950 50  0001 C CNN
	1    8900 3950
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5B00612A
P 8100 3650
F 0 "#PWR?" H 8100 3500 50  0001 C CNN
F 1 "+3V3" H 8100 3790 50  0000 C CNN
F 2 "" H 8100 3650 50  0001 C CNN
F 3 "" H 8100 3650 50  0001 C CNN
	1    8100 3650
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5B006297
P 7900 3750
F 0 "C?" H 7910 3820 50  0000 L CNN
F 1 "100nF 5%" H 7910 3670 50  0000 L CNN
F 2 "" H 7900 3750 50  0001 C CNN
F 3 "" H 7900 3750 50  0001 C CNN
	1    7900 3750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5B00666F
P 7700 3750
F 0 "#PWR?" H 7700 3500 50  0001 C CNN
F 1 "GND" H 7700 3600 50  0000 C CNN
F 2 "" H 7700 3750 50  0001 C CNN
F 3 "" H 7700 3750 50  0001 C CNN
	1    7700 3750
	0    1    1    0   
$EndComp
Text Label 9350 3750 2    60   ~ 0
OSC_8MHz
$Comp
L TEST TP?
U 1 1 5B0080E0
P 8850 3700
F 0 "TP?" H 8850 4000 50  0000 C BNN
F 1 "TEST" H 8850 3950 50  0000 C CNN
F 2 "" H 8850 3700 50  0001 C CNN
F 3 "" H 8850 3700 50  0001 C CNN
	1    8850 3700
	1    0    0    -1  
$EndComp
$Comp
L Q_PMOS_DGS Q?
U 1 1 5B009335
P 2250 5800
F 0 "Q?" H 2450 5850 50  0000 L CNN
F 1 "Q_PMOS_DGS" H 2450 5750 50  0000 L CNN
F 2 "" H 2450 5900 50  0001 C CNN
F 3 "" H 2250 5800 50  0001 C CNN
	1    2250 5800
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B00958A
P 1900 5600
F 0 "#PWR?" H 1900 5450 50  0001 C CNN
F 1 "+5V" H 1900 5740 50  0000 C CNN
F 2 "" H 1900 5600 50  0001 C CNN
F 3 "" H 1900 5600 50  0001 C CNN
	1    1900 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B0098F6
P 2250 6100
F 0 "#PWR?" H 2250 5850 50  0001 C CNN
F 1 "GND" H 2250 5950 50  0000 C CNN
F 2 "" H 2250 6100 50  0001 C CNN
F 3 "" H 2250 6100 50  0001 C CNN
	1    2250 6100
	1    0    0    -1  
$EndComp
Text Label 9400 1650 0    60   ~ 0
PHASE4
Text Label 9400 1750 0    60   ~ 0
PHASE5
Text Label 9400 1850 0    60   ~ 0
PHASE6
Text Label 9400 1950 0    60   ~ 0
PHASE7
Text Label 9400 1250 0    60   ~ 0
PHASE0
Text Label 9400 1350 0    60   ~ 0
PHASE1
Text Label 9400 1550 0    60   ~ 0
PHASE3
Text Label 9400 1450 0    60   ~ 0
PHASE2
$Comp
L TLV74133PDBVR U?
U 1 1 5B00DE52
P 3750 5800
F 0 "U?" H 3750 6000 60  0000 C CNN
F 1 "TLV74133PDBVR" H 3750 5600 60  0000 C CNN
F 2 "" H 3750 5800 60  0001 C CNN
F 3 "" H 3750 5800 60  0001 C CNN
F 4 "595-TLV74133PDBVR" H 3750 5800 60  0001 C CNN "Mouser"
	1    3750 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B00F064
P 3300 6050
F 0 "#PWR?" H 3300 5800 50  0001 C CNN
F 1 "GND" H 3300 5900 50  0000 C CNN
F 2 "" H 3300 6050 50  0001 C CNN
F 3 "" H 3300 6050 50  0001 C CNN
	1    3300 6050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B00F2B8
P 2500 7050
F 0 "#PWR?" H 2500 6800 50  0001 C CNN
F 1 "GND" H 2500 6900 50  0000 C CNN
F 2 "" H 2500 7050 50  0001 C CNN
F 3 "" H 2500 7050 50  0001 C CNN
	1    2500 7050
	1    0    0    -1  
$EndComp
$Comp
L TLV74133PDBVR U?
U 1 1 5AFF970A
P 2950 6850
F 0 "U?" H 2950 7050 60  0000 C CNN
F 1 "TLV74133PDBVR" H 2950 6650 60  0000 C CNN
F 2 "" H 2950 6850 60  0001 C CNN
F 3 "" H 2950 6850 60  0001 C CNN
F 4 "595-TLV74133PDBVR" H 2950 6850 60  0001 C CNN "Mouser"
	1    2950 6850
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5AFFB1C5
P 3400 6900
F 0 "C?" H 3410 6970 50  0000 L CNN
F 1 "10uF 10%" H 3410 6820 50  0000 L CNN
F 2 "" H 3400 6900 50  0001 C CNN
F 3 "" H 3400 6900 50  0001 C CNN
	1    3400 6900
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5AFFB2DA
P 3850 6900
F 0 "C?" H 3860 6970 50  0000 L CNN
F 1 "10uF 10%" H 3860 6820 50  0000 L CNN
F 2 "" H 3850 6900 50  0001 C CNN
F 3 "" H 3850 6900 50  0001 C CNN
	1    3850 6900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5AFFFA75
P 1200 4650
F 0 "#PWR?" H 1200 4500 50  0001 C CNN
F 1 "+5V" H 1200 4790 50  0000 C CNN
F 2 "" H 1200 4650 50  0001 C CNN
F 3 "" H 1200 4650 50  0001 C CNN
	1    1200 4650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5AFFFB9D
P 1250 5700
F 0 "#PWR?" H 1250 5550 50  0001 C CNN
F 1 "+5V" H 1250 5840 50  0000 C CNN
F 2 "" H 1250 5700 50  0001 C CNN
F 3 "" H 1250 5700 50  0001 C CNN
	1    1250 5700
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky_Small D?
U 1 1 5B000654
P 2550 6350
F 0 "D?" H 2500 6430 50  0000 L CNN
F 1 "D_Schottky_Small" H 2270 6270 50  0000 L CNN
F 2 "" V 2550 6350 50  0001 C CNN
F 3 "" V 2550 6350 50  0001 C CNN
	1    2550 6350
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C?
U 1 1 5B002997
P 2850 5900
F 0 "C?" H 2860 5970 50  0000 L CNN
F 1 "10uF 10%" H 2860 5820 50  0000 L CNN
F 2 "" H 2850 5900 50  0001 C CNN
F 3 "" H 2850 5900 50  0001 C CNN
	1    2850 5900
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5B002BC5
P 2250 6850
F 0 "C?" H 2260 6920 50  0000 L CNN
F 1 "10uF 10%" H 2260 6770 50  0000 L CNN
F 2 "" H 2250 6850 50  0001 C CNN
F 3 "" H 2250 6850 50  0001 C CNN
	1    2250 6850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B0030AB
P 2850 6100
F 0 "#PWR?" H 2850 5850 50  0001 C CNN
F 1 "GND" H 2850 5950 50  0000 C CNN
F 2 "" H 2850 6100 50  0001 C CNN
F 3 "" H 2850 6100 50  0001 C CNN
	1    2850 6100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B003262
P 2250 7050
F 0 "#PWR?" H 2250 6800 50  0001 C CNN
F 1 "GND" H 2250 6900 50  0000 C CNN
F 2 "" H 2250 7050 50  0001 C CNN
F 3 "" H 2250 7050 50  0001 C CNN
	1    2250 7050
	1    0    0    -1  
$EndComp
Text Notes 2550 6600 2    60   ~ 0
3.6V min
$Comp
L Conn_01x08 J?
U 1 1 5B0060DE
P 10700 1550
F 0 "J?" H 10700 1950 50  0000 C CNN
F 1 "TX_PADS" H 10700 1050 50  0000 C CNN
F 2 "" H 10700 1550 50  0001 C CNN
F 3 "" H 10700 1550 50  0001 C CNN
	1    10700 1550
	1    0    0    -1  
$EndComp
Text Label 9400 2500 0    60   ~ 0
RX_PAD
$Comp
L Conn_01x01 J?
U 1 1 5B0083C9
P 10700 2500
F 0 "J?" H 10700 2600 50  0000 C CNN
F 1 "RX_PAD" H 10700 2400 50  0000 C CNN
F 2 "" H 10700 2500 50  0001 C CNN
F 3 "" H 10700 2500 50  0001 C CNN
	1    10700 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1600 1250 1600
Wire Wire Line
	1200 3600 1350 3600
Wire Wire Line
	4200 1900 4350 1900
Wire Wire Line
	850  3000 1350 3000
Wire Wire Line
	850  3100 1350 3100
Wire Wire Line
	850  3200 1350 3200
Wire Wire Line
	850  3300 1350 3300
Wire Wire Line
	3800 1200 4350 1200
Wire Wire Line
	3800 1400 4350 1400
Wire Wire Line
	3800 1500 4350 1500
Wire Wire Line
	6550 6850 6550 7050
Wire Wire Line
	6550 7250 6550 7350
Connection ~ 6550 6900
Wire Wire Line
	750  2200 1100 2200
Wire Wire Line
	1100 1800 1250 1800
Wire Wire Line
	9950 5600 10250 5600
Wire Wire Line
	10050 5500 10050 5700
Connection ~ 10050 5600
Wire Wire Line
	10450 5600 10900 5600
Wire Wire Line
	10550 5450 10550 5700
Wire Wire Line
	10050 5900 10050 6000
Wire Wire Line
	10550 5900 10550 6000
Wire Wire Line
	9300 5850 9300 5950
Wire Wire Line
	9650 5100 9750 5100
Wire Wire Line
	9300 5000 9300 5350
Wire Wire Line
	9450 5100 9300 5100
Connection ~ 9300 5100
Wire Wire Line
	9650 5600 9750 5600
Wire Wire Line
	8950 5200 9700 5200
Wire Wire Line
	9700 5200 9700 5750
Connection ~ 9700 5600
Wire Wire Line
	8800 5350 8800 5500
Wire Wire Line
	8800 5500 9100 5500
Wire Wire Line
	7950 5200 8300 5200
Wire Wire Line
	8500 5200 8650 5200
Wire Wire Line
	8200 5700 9100 5700
Wire Wire Line
	8600 5700 8600 5800
Connection ~ 8600 5700
Wire Wire Line
	8600 6300 8600 6000
Connection ~ 10550 5600
Wire Wire Line
	8200 6300 8600 6300
Wire Wire Line
	6250 5450 6250 5700
Wire Wire Line
	6400 5700 6400 5550
Connection ~ 6400 5550
Connection ~ 6250 5550
Wire Wire Line
	6400 6000 6400 5900
Wire Wire Line
	6250 5900 6250 6000
Wire Wire Line
	6250 5150 6250 5250
Wire Wire Line
	6600 5350 6500 5350
Wire Wire Line
	6500 5350 6500 5150
Wire Wire Line
	7250 5150 7250 5450
Wire Wire Line
	7150 5450 7750 5450
Connection ~ 7250 5450
Connection ~ 7350 5450
Wire Wire Line
	7350 5600 7350 5450
Wire Wire Line
	7350 5800 7350 5950
Wire Wire Line
	850  3500 1350 3500
Wire Wire Line
	6550 6500 6550 6650
Wire Wire Line
	5850 6850 5850 6950
Wire Wire Line
	5850 6650 5850 6550
Connection ~ 5850 6900
Wire Wire Line
	5850 7150 5850 7250
Wire Wire Line
	5450 6900 5850 6900
Wire Wire Line
	750  1500 1250 1500
Wire Wire Line
	850  1700 1250 1700
Wire Wire Line
	900  900  1250 900 
Wire Wire Line
	1000 3700 1350 3700
Wire Wire Line
	4950 4400 4950 4550
Wire Wire Line
	3550 4400 3550 4550
Wire Wire Line
	6250 6900 6550 6900
Wire Wire Line
	1200 4650 1200 4750
Wire Wire Line
	1200 4750 1350 4750
Wire Wire Line
	1250 6700 1250 6850
Wire Wire Line
	1250 6850 1350 6850
Wire Wire Line
	1250 6200 1250 6100
Wire Wire Line
	1250 6100 1350 6100
Wire Wire Line
	1250 5700 1250 5800
Wire Wire Line
	1250 5800 1350 5800
Wire Wire Line
	1200 5150 1200 5050
Wire Wire Line
	1200 5050 1350 5050
Wire Wire Line
	1000 6950 1350 6950
Wire Wire Line
	1000 7050 1350 7050
Wire Wire Line
	1000 7150 1350 7150
Wire Wire Line
	1350 7350 1250 7350
Wire Wire Line
	1250 7350 1250 7450
Wire Wire Line
	1000 7250 1350 7250
Wire Wire Line
	900  4950 1350 4950
Wire Wire Line
	900  4850 1350 4850
Wire Wire Line
	900  6000 1350 6000
Wire Wire Line
	900  5900 1350 5900
Wire Wire Line
	4150 3600 4300 3600
Wire Wire Line
	3700 3300 4300 3300
Wire Wire Line
	7350 5450 7250 5450
Wire Wire Line
	3700 3500 4300 3500
Wire Wire Line
	3950 3700 4300 3700
Wire Wire Line
	3700 3400 4300 3400
Wire Wire Line
	3700 3200 4300 3200
Wire Wire Line
	3700 3100 4300 3100
Wire Wire Line
	3700 2600 4300 2600
Wire Wire Line
	3200 4450 3200 4550
Wire Wire Line
	3200 4750 3200 4850
Wire Wire Line
	3550 4750 3550 4850
Wire Wire Line
	4000 4750 4000 4850
Wire Wire Line
	4000 4400 4000 4550
Wire Wire Line
	4250 4400 4250 4350
Connection ~ 4250 4400
Wire Wire Line
	4500 4400 4500 4550
Wire Wire Line
	3800 1300 4350 1300
Wire Wire Line
	4050 2000 4350 2000
Wire Wire Line
	1100 2200 1100 1800
Wire Wire Line
	6250 5550 6600 5550
Wire Wire Line
	3850 7000 3850 7100
Wire Wire Line
	4300 7000 4300 7100
Wire Wire Line
	4200 5700 4200 5900
Connection ~ 4200 5700
Wire Wire Line
	4600 5600 4600 5900
Wire Wire Line
	4200 6100 4200 6200
Wire Wire Line
	4600 6100 4600 6200
Connection ~ 4600 5700
Wire Wire Line
	3850 6750 3850 6800
Connection ~ 3850 6750
Wire Wire Line
	2050 4950 2050 4850
Wire Wire Line
	2050 4850 2150 4850
Wire Wire Line
	2050 4650 2050 4750
Wire Wire Line
	2050 4750 2150 4750
Wire Wire Line
	4700 5750 4600 5750
Connection ~ 4600 5750
Wire Wire Line
	8750 6050 8750 5700
Connection ~ 8750 5700
Wire Wire Line
	6500 5150 7250 5150
Wire Wire Line
	7300 5050 7100 5050
Wire Wire Line
	7100 5050 7100 5150
Connection ~ 7100 5150
Wire Wire Line
	750  1300 1250 1300
Wire Wire Line
	8900 3950 8800 3950
Wire Wire Line
	8100 3750 8100 3650
Wire Wire Line
	8000 3750 8200 3750
Connection ~ 8100 3750
Wire Wire Line
	7700 3750 7800 3750
Wire Wire Line
	8800 3750 9350 3750
Wire Wire Line
	8050 3750 8050 3950
Wire Wire Line
	8050 3950 8200 3950
Connection ~ 8050 3750
Wire Wire Line
	8850 3700 8850 3750
Connection ~ 8850 3750
Wire Wire Line
	1900 5600 1900 5700
Wire Wire Line
	1900 5700 2050 5700
Wire Wire Line
	2250 6000 2250 6100
Wire Wire Line
	9400 1850 10500 1850
Wire Wire Line
	9400 1950 10500 1950
Wire Wire Line
	9400 1750 10500 1750
Wire Wire Line
	9400 1450 10500 1450
Wire Wire Line
	9400 1550 10500 1550
Wire Wire Line
	9400 1350 10500 1350
Wire Wire Line
	9400 1250 10500 1250
Wire Wire Line
	2450 5700 3400 5700
Wire Wire Line
	2550 6750 2600 6750
Connection ~ 2550 5700
Wire Wire Line
	2550 6850 2600 6850
Connection ~ 2550 6750
Wire Wire Line
	3300 5900 3400 5900
Wire Wire Line
	2500 7050 2500 6950
Wire Wire Line
	2500 6950 2600 6950
Wire Wire Line
	4500 4750 4500 4850
Wire Wire Line
	4950 4750 4950 4850
Wire Wire Line
	3250 6750 4450 6750
Wire Wire Line
	4300 6800 4300 6750
Connection ~ 4300 6750
Wire Wire Line
	4400 6700 4400 6750
Connection ~ 4400 6750
Wire Wire Line
	3400 6750 3400 6800
Wire Wire Line
	3400 7000 3400 7100
Connection ~ 3400 6750
Wire Wire Line
	3550 4400 4950 4400
Connection ~ 4000 4400
Connection ~ 4500 4400
Wire Wire Line
	3350 5700 3350 5800
Wire Wire Line
	3350 5800 3400 5800
Connection ~ 3350 5700
Wire Wire Line
	3300 6050 3300 5900
Wire Wire Line
	4050 5700 4600 5700
Wire Wire Line
	2550 5700 2550 6250
Wire Wire Line
	2550 6450 2550 6850
Wire Wire Line
	2850 5700 2850 5800
Connection ~ 2850 5700
Wire Wire Line
	2850 6000 2850 6100
Wire Wire Line
	2250 6750 2250 6650
Wire Wire Line
	2250 6650 2550 6650
Connection ~ 2550 6650
Wire Wire Line
	2250 6950 2250 7050
Wire Wire Line
	9400 2500 10500 2500
Wire Wire Line
	9400 1650 10500 1650
Text Notes 8650 5600 2    60   ~ 0
40uV RMS noise\n@10kHz BW
Text Notes 8950 1050 0    60   ~ 0
Cpad=24*8.854e-12*(0.5e-3*10e-3/0.5e-3)\n=2.125pF
Text Notes 9600 2300 0    60   ~ 0
Crx=8*Cpad*0.8=13.6pF
Wire Wire Line
	3800 900  4350 900 
Text Label 3800 900  0    60   ~ 0
ZERO
NoConn ~ 4300 2700
NoConn ~ 4300 2800
NoConn ~ 4300 2900
NoConn ~ 4300 3000
NoConn ~ 1350 3400
NoConn ~ 1350 2900
NoConn ~ 1350 2800
NoConn ~ 1350 2700
NoConn ~ 1350 2600
NoConn ~ 1250 1900
NoConn ~ 1250 2000
NoConn ~ 1250 1400
NoConn ~ 1250 1200
NoConn ~ 1250 1000
NoConn ~ 4350 1000
NoConn ~ 4350 1100
NoConn ~ 4350 1600
NoConn ~ 4350 1700
NoConn ~ 4350 1800
$Comp
L R_Small R?
U 1 1 5B010870
P 10150 3600
F 0 "R?" H 10180 3620 50  0000 L CNN
F 1 "100k 5%" H 10180 3560 50  0000 L CNN
F 2 "" H 10150 3600 50  0001 C CNN
F 3 "" H 10150 3600 50  0001 C CNN
	1    10150 3600
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW?
U 1 1 5B01096F
P 10150 4000
F 0 "SW?" H 10200 4100 50  0000 L CNN
F 1 "SW_Push" H 10150 3940 50  0000 C CNN
F 2 "" H 10150 4200 50  0001 C CNN
F 3 "" H 10150 4200 50  0001 C CNN
	1    10150 4000
	0    -1   1    0   
$EndComp
$Comp
L C_Small C?
U 1 1 5B0109FC
P 10400 4000
F 0 "C?" H 10410 4070 50  0000 L CNN
F 1 "10nF 1%" H 10410 3920 50  0000 L CNN
F 2 "" H 10400 4000 50  0001 C CNN
F 3 "" H 10400 4000 50  0001 C CNN
	1    10400 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B010AA9
P 10150 4250
F 0 "#PWR?" H 10150 4000 50  0001 C CNN
F 1 "GND" H 10150 4100 50  0000 C CNN
F 2 "" H 10150 4250 50  0001 C CNN
F 3 "" H 10150 4250 50  0001 C CNN
	1    10150 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B010B66
P 10400 4250
F 0 "#PWR?" H 10400 4000 50  0001 C CNN
F 1 "GND" H 10400 4100 50  0000 C CNN
F 2 "" H 10400 4250 50  0001 C CNN
F 3 "" H 10400 4250 50  0001 C CNN
	1    10400 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 4100 10400 4250
Wire Wire Line
	10150 3700 10150 3800
Wire Wire Line
	10150 3750 10850 3750
Wire Wire Line
	10400 3750 10400 3900
Connection ~ 10150 3750
$Comp
L +3V3 #PWR?
U 1 1 5B010F86
P 10150 3400
F 0 "#PWR?" H 10150 3250 50  0001 C CNN
F 1 "+3V3" H 10150 3540 50  0000 C CNN
F 2 "" H 10150 3400 50  0001 C CNN
F 3 "" H 10150 3400 50  0001 C CNN
	1    10150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3400 10150 3500
Connection ~ 10400 3750
Wire Wire Line
	10150 4200 10150 4250
Text Label 10850 3750 2    60   ~ 0
ZERO
$EndSCHEMATC
