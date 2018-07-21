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
LIBS:outline
LIBS:scale-cache
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
$Comp
L TEST_1P J101
U 1 1 5B06A702
P 6450 3950
F 0 "J101" H 6450 4220 50  0000 C CNN
F 1 "TEST_1P" H 6450 4150 50  0000 C CNN
F 2 "capacitive:Scale_Drill_Left" H 6650 3950 50  0001 C CNN
F 3 "" H 6650 3950 50  0001 C CNN
	1    6450 3950
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J102
U 1 1 5B06A73D
P 7000 3950
F 0 "J102" H 7000 4220 50  0000 C CNN
F 1 "TEST_1P" H 7000 4150 50  0000 C CNN
F 2 "capacitive:Scale_Drill_Right" H 7200 3950 50  0001 C CNN
F 3 "" H 7200 3950 50  0001 C CNN
	1    7000 3950
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J104
U 1 1 5B06A76E
P 7000 4600
F 0 "J104" H 7000 4870 50  0000 C CNN
F 1 "TEST_1P" H 7000 4800 50  0000 C CNN
F 2 "capacitive:Scale_Drill_Right" H 7200 4600 50  0001 C CNN
F 3 "" H 7200 4600 50  0001 C CNN
	1    7000 4600
	1    0    0    -1  
$EndComp
$Comp
L TEST_1P J103
U 1 1 5B06A7AB
P 6500 4600
F 0 "J103" H 6500 4870 50  0000 C CNN
F 1 "TEST_1P" H 6500 4800 50  0000 C CNN
F 2 "capacitive:Scale_Drill_Left" H 6700 4600 50  0001 C CNN
F 3 "" H 6700 4600 50  0001 C CNN
	1    6500 4600
	1    0    0    -1  
$EndComp
$Comp
L outline U101
U 1 1 5B06A7F4
P 5550 4000
F 0 "U101" H 5550 4000 60  0000 C CNN
F 1 "outline" H 5550 4000 60  0000 C CNN
F 2 "capacitive:Scale_Outline" H 5550 4000 60  0001 C CNN
F 3 "" H 5550 4000 60  0001 C CNN
	1    5550 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR101
U 1 1 5B06A831
P 6450 4000
F 0 "#PWR101" H 6450 3750 50  0001 C CNN
F 1 "GND" H 6450 3850 50  0000 C CNN
F 2 "" H 6450 4000 50  0001 C CNN
F 3 "" H 6450 4000 50  0001 C CNN
	1    6450 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR102
U 1 1 5B06A852
P 7000 4000
F 0 "#PWR102" H 7000 3750 50  0001 C CNN
F 1 "GND" H 7000 3850 50  0000 C CNN
F 2 "" H 7000 4000 50  0001 C CNN
F 3 "" H 7000 4000 50  0001 C CNN
	1    7000 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR104
U 1 1 5B06A86C
P 7000 4650
F 0 "#PWR104" H 7000 4400 50  0001 C CNN
F 1 "GND" H 7000 4500 50  0000 C CNN
F 2 "" H 7000 4650 50  0001 C CNN
F 3 "" H 7000 4650 50  0001 C CNN
	1    7000 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR103
U 1 1 5B06A886
P 6500 4650
F 0 "#PWR103" H 6500 4400 50  0001 C CNN
F 1 "GND" H 6500 4500 50  0000 C CNN
F 2 "" H 6500 4650 50  0001 C CNN
F 3 "" H 6500 4650 50  0001 C CNN
	1    6500 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3950 6450 4000
Wire Wire Line
	6500 4600 6500 4650
Wire Wire Line
	7000 4600 7000 4650
Wire Wire Line
	7000 3950 7000 4000
$Comp
L outline U102
U 1 1 5B06A8D6
P 5550 4250
F 0 "U102" H 5550 4250 60  0000 C CNN
F 1 "scales" H 5550 4250 60  0000 C CNN
F 2 "capacitive:Capacitive_Scales320.00" H 5550 4250 60  0001 C CNN
F 3 "" H 5550 4250 60  0001 C CNN
	1    5550 4250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
