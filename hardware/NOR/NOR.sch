EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector_Generic:Conn_02x33_Odd_Even J1
U 1 1 6023E902
P 1200 3000
F 0 "J1" H 1250 4817 50  0000 C CNN
F 1 "Left" H 1250 4726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x33_P2.54mm_Vertical" H 1200 3000 50  0001 C CNN
F 3 "~" H 1200 3000 50  0001 C CNN
	1    1200 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x33_Odd_Even J2
U 1 1 60241940
P 2500 3000
F 0 "J2" H 2550 4817 50  0000 C CNN
F 1 "Right" H 2550 4726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x33_P2.54mm_Vertical" H 2500 3000 50  0001 C CNN
F 3 "~" H 2500 3000 50  0001 C CNN
	1    2500 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6024323E
P 1000 4700
F 0 "#PWR04" H 1000 4450 50  0001 C CNN
F 1 "GND" H 1005 4527 50  0001 C CNN
F 2 "" H 1000 4700 50  0001 C CNN
F 3 "" H 1000 4700 50  0001 C CNN
	1    1000 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6024383C
P 2800 4700
F 0 "#PWR011" H 2800 4450 50  0001 C CNN
F 1 "GND" H 2805 4527 50  0001 C CNN
F 2 "" H 2800 4700 50  0001 C CNN
F 3 "" H 2800 4700 50  0001 C CNN
	1    2800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4700 2800 4600
Connection ~ 2800 4500
Wire Wire Line
	2800 4500 2800 4400
Connection ~ 2800 4600
Wire Wire Line
	2800 4600 2800 4500
Wire Wire Line
	1000 4700 1000 4600
Connection ~ 1000 4500
Wire Wire Line
	1000 4500 1000 4400
Connection ~ 1000 4600
Wire Wire Line
	1000 4600 1000 4500
$Comp
L power:GND #PWR08
U 1 1 60244ADD
P 2300 4500
F 0 "#PWR08" H 2300 4250 50  0001 C CNN
F 1 "GND" H 2305 4327 50  0001 C CNN
F 2 "" H 2300 4500 50  0001 C CNN
F 3 "" H 2300 4500 50  0001 C CNN
	1    2300 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 4500 2300 4400
Connection ~ 2300 4500
$Comp
L power:GND #PWR010
U 1 1 6024582A
P 2800 1400
F 0 "#PWR010" H 2800 1150 50  0001 C CNN
F 1 "GND" H 2805 1227 50  0001 C CNN
F 2 "" H 2800 1400 50  0001 C CNN
F 3 "" H 2800 1400 50  0001 C CNN
	1    2800 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2800 1500 2800 1400
Connection ~ 2800 1400
$Comp
L power:GND #PWR05
U 1 1 60246956
P 1500 1400
F 0 "#PWR05" H 1500 1150 50  0001 C CNN
F 1 "GND" H 1505 1227 50  0001 C CNN
F 2 "" H 1500 1400 50  0001 C CNN
F 3 "" H 1500 1400 50  0001 C CNN
	1    1500 1400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 60246E6B
P 1000 1400
F 0 "#PWR01" H 1000 1150 50  0001 C CNN
F 1 "GND" H 1005 1227 50  0001 C CNN
F 2 "" H 1000 1400 50  0001 C CNN
F 3 "" H 1000 1400 50  0001 C CNN
	1    1000 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 4400 1500 4500
Connection ~ 1500 4500
Wire Wire Line
	1500 4500 1500 4600
$Comp
L power:+3V3 #PWR07
U 1 1 6024A3DE
P 1500 4400
F 0 "#PWR07" H 1500 4250 50  0001 C CNN
F 1 "+3V3" V 1515 4528 50  0000 L CNN
F 2 "" H 1500 4400 50  0001 C CNN
F 3 "" H 1500 4400 50  0001 C CNN
	1    1500 4400
	0    1    1    0   
$EndComp
Connection ~ 1500 4400
Text Notes 1650 950  0    50   ~ 0
1700 mil between
Text GLabel 1000 1500 0    50   BiDi ~ 0
PE0
Text GLabel 1500 1500 2    50   BiDi ~ 0
PE1
Text GLabel 1000 1600 0    50   BiDi ~ 0
A23
Text GLabel 1500 1600 2    50   BiDi ~ 0
A19
Text GLabel 1000 1700 0    50   BiDi ~ 0
A20
Text GLabel 1500 1700 2    50   BiDi ~ 0
A21
Text GLabel 1000 1800 0    50   BiDi ~ 0
A22
Text GLabel 1500 1800 2    50   BiDi ~ 0
PC13
Text GLabel 1000 1900 0    50   BiDi ~ 0
PC14
Text GLabel 1500 1900 2    50   BiDi ~ 0
PC15
Text GLabel 1000 2000 0    50   BiDi ~ 0
A0
Text GLabel 1500 2000 2    50   BiDi ~ 0
A1
Text GLabel 1000 2100 0    50   BiDi ~ 0
A2
Text GLabel 1500 2100 2    50   BiDi ~ 0
A3
Text GLabel 1000 2200 0    50   BiDi ~ 0
A4
Text GLabel 1500 2200 2    50   BiDi ~ 0
A5
Text GLabel 1000 2300 0    50   BiDi ~ 0
PF6
Text GLabel 1500 2300 2    50   BiDi ~ 0
PF7
Text GLabel 1000 2400 0    50   BiDi ~ 0
PF8
Text GLabel 1500 2400 2    50   BiDi ~ 0
PF9
Text GLabel 1000 2500 0    50   BiDi ~ 0
PF10
Text GLabel 1500 2500 2    50   BiDi ~ 0
PC0
Text GLabel 1000 2600 0    50   BiDi ~ 0
PC1
Text GLabel 1500 2600 2    50   BiDi ~ 0
PC2
Text GLabel 1000 2700 0    50   BiDi ~ 0
PC3
Text GLabel 1500 3100 2    50   BiDi ~ 0
PC4
Text GLabel 1000 3200 0    50   BiDi ~ 0
PC5
Text GLabel 1500 2900 2    50   BiDi ~ 0
PA4
Text GLabel 1000 3000 0    50   BiDi ~ 0
PA5
Text GLabel 1500 3000 2    50   BiDi ~ 0
PA6
Text GLabel 1000 3100 0    50   BiDi ~ 0
PA7
Text GLabel 1500 3200 2    50   BiDi ~ 0
PB0
Text GLabel 1000 3300 0    50   BiDi ~ 0
PB1
Text GLabel 1500 3300 2    50   BiDi ~ 0
PB2
Text GLabel 1000 3400 0    50   BiDi ~ 0
PF11
Text GLabel 1500 3400 2    50   BiDi ~ 0
A6
Text GLabel 1000 3500 0    50   BiDi ~ 0
A7
Text GLabel 1500 3500 2    50   BiDi ~ 0
A8
Text GLabel 1000 3600 0    50   BiDi ~ 0
A9
Text GLabel 1500 3600 2    50   BiDi ~ 0
A10
Text GLabel 1000 3700 0    50   BiDi ~ 0
A11
Text GLabel 1000 3800 0    50   BiDi ~ 0
IO5
Text GLabel 1500 3800 2    50   BiDi ~ 0
IO6
Text GLabel 1000 3900 0    50   BiDi ~ 0
IO7
Text GLabel 1500 3900 2    50   BiDi ~ 0
IO8
Text GLabel 1000 4000 0    50   BiDi ~ 0
IO9
Text GLabel 1500 4000 2    50   BiDi ~ 0
IO10
Text GLabel 1000 4100 0    50   BiDi ~ 0
IO11
Text GLabel 1500 4100 2    50   BiDi ~ 0
IO12
Text GLabel 1000 4200 0    50   BiDi ~ 0
PB10
Text GLabel 1500 4200 2    50   BiDi ~ 0
PB11
Wire Wire Line
	1500 4400 1500 4300
Wire Wire Line
	1000 4300 1000 4400
Connection ~ 1000 4400
Text GLabel 2300 1900 0    50   BiDi ~ 0
PB3
Text GLabel 2800 1800 2    50   BiDi ~ 0
PB4
Text GLabel 2300 1800 0    50   BiDi ~ 0
PB5
Text GLabel 2800 1700 2    50   BiDi ~ 0
PB6
Text GLabel 2300 1700 0    50   BiDi ~ 0
PB7
Text GLabel 2800 1600 2    50   BiDi ~ 0
PB8
Text GLabel 2300 1600 0    50   BiDi ~ 0
PB9
Text GLabel 2800 2200 2    50   BiDi ~ 0
PG9
Text GLabel 2300 2200 0    50   BiDi ~ 0
PG10
Text GLabel 2800 2100 2    50   BiDi ~ 0
PG11
Text GLabel 2300 2100 0    50   BiDi ~ 0
PG12
Text GLabel 2800 2000 2    50   BiDi ~ 0
A24
Text GLabel 2300 2000 0    50   BiDi ~ 0
A25
Text GLabel 2800 1900 2    50   BiDi ~ 0
PG15
Text GLabel 2800 2600 2    50   BiDi ~ 0
IO2
Text GLabel 2300 2600 0    50   BiDi ~ 0
IO3
Text GLabel 2800 2500 2    50   BiDi ~ 0
PD2
Text GLabel 2300 2500 0    50   BiDi ~ 0
PD3
Text GLabel 2800 2400 2    50   BiDi ~ 0
~OE
Text GLabel 2300 2400 0    50   BiDi ~ 0
~WE
Text GLabel 2800 2300 2    50   BiDi ~ 0
R~B
Text GLabel 2300 2300 0    50   BiDi ~ 0
~CE
Text GLabel 2300 2800 0    50   BiDi ~ 0
PC10
Text GLabel 2800 2700 2    50   BiDi ~ 0
PC11
Text GLabel 2300 2700 0    50   BiDi ~ 0
PC12
Text GLabel 2300 3200 0    50   BiDi ~ 0
~RST
Text GLabel 2800 3100 2    50   BiDi ~ 0
PA9
Text GLabel 2300 3100 0    50   BiDi ~ 0
PA10
Text GLabel 2800 3000 2    50   BiDi ~ 0
PA11
Text GLabel 2300 3000 0    50   BiDi ~ 0
PA12
Text GLabel 2800 2900 2    50   BiDi ~ 0
PA13
Text GLabel 2300 2900 0    50   BiDi ~ 0
PA14
Text GLabel 2800 2800 2    50   BiDi ~ 0
PA15
Text GLabel 2800 4300 2    50   BiDi ~ 0
PB12
Text GLabel 2300 4300 0    50   BiDi ~ 0
PB13
Text GLabel 2800 4200 2    50   BiDi ~ 0
PB14
Text GLabel 2300 4200 0    50   BiDi ~ 0
PB15
Text GLabel 2800 4100 2    50   BiDi ~ 0
IO13
Text GLabel 2300 4100 0    50   BiDi ~ 0
IO14
Text GLabel 2800 4000 2    50   BiDi ~ 0
IO15
Text GLabel 2300 4000 0    50   BiDi ~ 0
A16
Text GLabel 2800 3900 2    50   BiDi ~ 0
A17
Text GLabel 2300 3900 0    50   BiDi ~ 0
A18
Text GLabel 2800 3800 2    50   BiDi ~ 0
IO0
Text GLabel 2300 3800 0    50   BiDi ~ 0
IO1
Text GLabel 2800 3700 2    50   BiDi ~ 0
A12
Text GLabel 2300 3700 0    50   BiDi ~ 0
A13
Text GLabel 2800 3600 2    50   BiDi ~ 0
A14
Text GLabel 2300 3600 0    50   BiDi ~ 0
A15
Text GLabel 2800 3500 2    50   BiDi ~ 0
PG6
Text GLabel 2300 3500 0    50   BiDi ~ 0
PG7
Text GLabel 2800 3400 2    50   BiDi ~ 0
PG8
Text GLabel 2300 3400 0    50   BiDi ~ 0
PC6
Text GLabel 2800 3300 2    50   BiDi ~ 0
PC7
Text GLabel 2300 3300 0    50   BiDi ~ 0
PC8
Text GLabel 2800 3200 2    50   BiDi ~ 0
PC9
$Comp
L Device:C_Small C1
U 1 1 602914E1
P 5350 5100
F 0 "C1" H 5258 5054 50  0000 R CNN
F 1 "100n" H 5258 5145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5350 5100 50  0001 C CNN
F 3 "~" H 5350 5100 50  0001 C CNN
	1    5350 5100
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6029192A
P 5700 5100
F 0 "C2" H 5608 5054 50  0000 R CNN
F 1 "100n" H 5608 5145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5700 5100 50  0001 C CNN
F 3 "~" H 5700 5100 50  0001 C CNN
	1    5700 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 5000 5350 5000
Connection ~ 5350 5000
Wire Wire Line
	5700 5200 5350 5200
Connection ~ 5350 5200
$Comp
L power:GND #PWR015
U 1 1 60293495
P 5350 5200
F 0 "#PWR015" H 5350 4950 50  0001 C CNN
F 1 "GND" H 5355 5027 50  0001 C CNN
F 2 "" H 5350 5200 50  0001 C CNN
F 3 "" H 5350 5200 50  0001 C CNN
	1    5350 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR014
U 1 1 60293DB4
P 5350 5000
F 0 "#PWR014" H 5350 4850 50  0001 C CNN
F 1 "+3V3" H 5365 5173 50  0000 C CNN
F 2 "" H 5350 5000 50  0001 C CNN
F 3 "" H 5350 5000 50  0001 C CNN
	1    5350 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 60296581
P 2600 5400
F 0 "J3" H 2680 5442 50  0000 L CNN
F 1 "DBG" H 2680 5351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 2600 5400 50  0001 C CNN
F 3 "~" H 2600 5400 50  0001 C CNN
	1    2600 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 602969EE
P 2400 5300
F 0 "#PWR09" H 2400 5050 50  0001 C CNN
F 1 "GND" H 2405 5127 50  0001 C CNN
F 2 "" H 2400 5300 50  0001 C CNN
F 3 "" H 2400 5300 50  0001 C CNN
	1    2400 5300
	0    1    1    0   
$EndComp
Text GLabel 2400 5500 0    50   Output ~ 0
PA10
Text GLabel 2400 5400 0    50   Input ~ 0
PA9
$Comp
L power:GND #PWR03
U 1 1 602AE23C
P 1000 2900
F 0 "#PWR03" H 1000 2650 50  0001 C CNN
F 1 "GND" H 1005 2727 50  0001 C CNN
F 2 "" H 1000 2900 50  0001 C CNN
F 3 "" H 1000 2900 50  0001 C CNN
	1    1000 2900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 602AE45B
P 1500 2800
F 0 "#PWR06" H 1500 2550 50  0001 C CNN
F 1 "GND" H 1505 2627 50  0001 C CNN
F 2 "" H 1500 2800 50  0001 C CNN
F 3 "" H 1500 2800 50  0001 C CNN
	1    1500 2800
	0    -1   -1   0   
$EndComp
NoConn ~ 2300 1500
NoConn ~ 1500 2700
NoConn ~ 2300 1400
NoConn ~ 2300 4600
Text GLabel 1500 3700 2    50   BiDi ~ 0
IO4
$Comp
L Connector_Generic:Conn_02x14_Odd_Even J4
U 1 1 603C37E9
P 5750 2650
F 0 "J4" H 5800 3467 50  0000 C CNN
F 1 "Left" H 5800 3376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x14_P2.54mm_Vertical" H 5750 2650 50  0001 C CNN
F 3 "~" H 5750 2650 50  0001 C CNN
	1    5750 2650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x14_Odd_Even J5
U 1 1 603C498A
P 7050 2650
F 0 "J5" H 7100 3467 50  0000 C CNN
F 1 "Right" H 7100 3376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x14_P2.54mm_Vertical" H 7050 2650 50  0001 C CNN
F 3 "~" H 7050 2650 50  0001 C CNN
	1    7050 2650
	1    0    0    -1  
$EndComp
Text GLabel 5550 2050 0    50   BiDi ~ 0
A22
Text GLabel 5550 2150 0    50   BiDi ~ 0
A14
Text GLabel 5550 2250 0    50   BiDi ~ 0
A12
Text GLabel 5550 2350 0    50   BiDi ~ 0
A10
Text GLabel 5550 2450 0    50   BiDi ~ 0
A8
Text GLabel 5550 2550 0    50   BiDi ~ 0
A20
Text GLabel 5550 2650 0    50   BiDi ~ 0
~RST
Text GLabel 5550 2850 0    50   BiDi ~ 0
A18
Text GLabel 5550 2950 0    50   BiDi ~ 0
A7
Text GLabel 5550 3050 0    50   BiDi ~ 0
A5
Text GLabel 5550 3150 0    50   BiDi ~ 0
A3
Text GLabel 5550 3250 0    50   BiDi ~ 0
A1
Text GLabel 6050 2050 2    50   BiDi ~ 0
A23
Text GLabel 6050 2150 2    50   BiDi ~ 0
A15
Text GLabel 6050 2250 2    50   BiDi ~ 0
A13
Text GLabel 6050 2350 2    50   BiDi ~ 0
A11
Text GLabel 6050 2450 2    50   BiDi ~ 0
A9
Text GLabel 6050 2550 2    50   BiDi ~ 0
A19
Text GLabel 6050 2650 2    50   BiDi ~ 0
~WE
Text GLabel 6050 2750 2    50   BiDi ~ 0
A21
Text GLabel 6050 2850 2    50   BiDi ~ 0
R~B
Text GLabel 6050 2950 2    50   BiDi ~ 0
A17
Text GLabel 6050 3050 2    50   BiDi ~ 0
A6
Text GLabel 6050 3150 2    50   BiDi ~ 0
A4
Text GLabel 6050 3250 2    50   BiDi ~ 0
A2
Text GLabel 7350 2050 2    50   BiDi ~ 0
A25
Text GLabel 7350 2250 2    50   BiDi ~ 0
IO15
Text GLabel 7350 2350 2    50   BiDi ~ 0
IO14
Text GLabel 7350 2450 2    50   BiDi ~ 0
IO13
Text GLabel 7350 2550 2    50   BiDi ~ 0
IO12
Text GLabel 7350 2750 2    50   BiDi ~ 0
IO3
Text GLabel 7350 2850 2    50   BiDi ~ 0
IO2
Text GLabel 7350 2950 2    50   BiDi ~ 0
IO1
Text GLabel 7350 3050 2    50   BiDi ~ 0
IO0
Text GLabel 7350 3250 2    50   BiDi ~ 0
A0
Text GLabel 6850 2050 0    50   BiDi ~ 0
A24
Text GLabel 6850 2150 0    50   BiDi ~ 0
A16
Text GLabel 6850 2350 0    50   BiDi ~ 0
IO7
Text GLabel 6850 2450 0    50   BiDi ~ 0
IO6
Text GLabel 6850 2550 0    50   BiDi ~ 0
IO5
Text GLabel 6850 2650 0    50   BiDi ~ 0
IO4
Text GLabel 6850 2750 0    50   BiDi ~ 0
IO11
Text GLabel 6850 2850 0    50   BiDi ~ 0
IO10
Text GLabel 6850 2950 0    50   BiDi ~ 0
IO9
Text GLabel 6850 3050 0    50   BiDi ~ 0
IO8
Text GLabel 6850 3150 0    50   BiDi ~ 0
~OE
Text GLabel 6850 3250 0    50   BiDi ~ 0
~CE
$Comp
L power:+3V3 #PWR017
U 1 1 603D48C4
P 7350 3350
F 0 "#PWR017" H 7350 3200 50  0001 C CNN
F 1 "+3V3" V 7365 3478 50  0000 L CNN
F 2 "" H 7350 3350 50  0001 C CNN
F 3 "" H 7350 3350 50  0001 C CNN
	1    7350 3350
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR013
U 1 1 603D4EE4
P 7350 2650
F 0 "#PWR013" H 7350 2500 50  0001 C CNN
F 1 "+3V3" V 7365 2778 50  0000 L CNN
F 2 "" H 7350 2650 50  0001 C CNN
F 3 "" H 7350 2650 50  0001 C CNN
	1    7350 2650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 603D52BB
P 7350 3150
F 0 "#PWR016" H 7350 2900 50  0001 C CNN
F 1 "GND" H 7355 2977 50  0001 C CNN
F 2 "" H 7350 3150 50  0001 C CNN
F 3 "" H 7350 3150 50  0001 C CNN
	1    7350 3150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 603D5887
P 6850 2250
F 0 "#PWR012" H 6850 2000 50  0001 C CNN
F 1 "GND" H 6855 2077 50  0001 C CNN
F 2 "" H 6850 2250 50  0001 C CNN
F 3 "" H 6850 2250 50  0001 C CNN
	1    6850 2250
	0    1    1    0   
$EndComp
NoConn ~ 1000 2800
$EndSCHEMATC
