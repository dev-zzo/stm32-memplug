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
Text GLabel 7100 3350 2    50   BiDi ~ 0
DAT0
Text GLabel 6600 3250 0    50   BiDi ~ 0
DAT1
Text GLabel 6600 3350 0    50   BiDi ~ 0
DAT2
Text GLabel 7100 3250 2    50   BiDi ~ 0
DAT3
Text GLabel 7100 3150 2    50   Input ~ 0
~RST
Text GLabel 6600 3150 0    50   Input ~ 0
CMD
Text GLabel 6600 3050 0    50   Input ~ 0
CLK
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
L power:GND #PWR02
U 1 1 6024323E
P 1000 4700
F 0 "#PWR02" H 1000 4450 50  0001 C CNN
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
L power:GND #PWR07
U 1 1 60244ADD
P 2300 4500
F 0 "#PWR07" H 2300 4250 50  0001 C CNN
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
L power:GND #PWR04
U 1 1 60246956
P 1500 1400
F 0 "#PWR04" H 1500 1150 50  0001 C CNN
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
L power:+5V #PWR08
U 1 1 60249324
P 2300 4600
F 0 "#PWR08" H 2300 4450 50  0001 C CNN
F 1 "+5V" V 2315 4728 50  0000 L CNN
F 2 "" H 2300 4600 50  0001 C CNN
F 3 "" H 2300 4600 50  0001 C CNN
	1    2300 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR05
U 1 1 6024A3DE
P 1500 4400
F 0 "#PWR05" H 1500 4250 50  0001 C CNN
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
E0
Text GLabel 1500 1500 2    50   BiDi ~ 0
E1
Text GLabel 1000 1600 0    50   BiDi ~ 0
E2
Text GLabel 1500 1600 2    50   BiDi ~ 0
E3
Text GLabel 1000 1700 0    50   BiDi ~ 0
E4
Text GLabel 1500 1700 2    50   BiDi ~ 0
E5
Text GLabel 1000 1800 0    50   BiDi ~ 0
E6
Text GLabel 1500 1800 2    50   BiDi ~ 0
C13
Text GLabel 1000 1900 0    50   BiDi ~ 0
C14
Text GLabel 1500 1900 2    50   BiDi ~ 0
C15
Text GLabel 1000 2000 0    50   BiDi ~ 0
F0
Text GLabel 1500 2000 2    50   BiDi ~ 0
F1
Text GLabel 1000 2100 0    50   BiDi ~ 0
F2
Text GLabel 1500 2100 2    50   BiDi ~ 0
F3
Text GLabel 1000 2200 0    50   BiDi ~ 0
F4
Text GLabel 1500 2200 2    50   BiDi ~ 0
F5
Text GLabel 1000 2300 0    50   BiDi ~ 0
F6
Text GLabel 1500 2300 2    50   BiDi ~ 0
F7
Text GLabel 1000 2400 0    50   BiDi ~ 0
F8
Text GLabel 1500 2400 2    50   BiDi ~ 0
F9
Text GLabel 1000 2500 0    50   BiDi ~ 0
F10
Text GLabel 1500 2500 2    50   BiDi ~ 0
C0
Text GLabel 1000 2600 0    50   BiDi ~ 0
C1
Text GLabel 1500 2600 2    50   BiDi ~ 0
C2
Text GLabel 1000 2700 0    50   BiDi ~ 0
C3
Text GLabel 1500 3100 2    50   BiDi ~ 0
C4
Text GLabel 1000 3200 0    50   BiDi ~ 0
C5
Text GLabel 1500 2900 2    50   BiDi ~ 0
A4
Text GLabel 1000 3000 0    50   BiDi ~ 0
A5
Text GLabel 1500 3000 2    50   BiDi ~ 0
A6
Text GLabel 1000 3100 0    50   BiDi ~ 0
A7
Text GLabel 1500 3200 2    50   BiDi ~ 0
B0
Text GLabel 1000 3300 0    50   BiDi ~ 0
B1
Text GLabel 1500 3300 2    50   BiDi ~ 0
B2
Text GLabel 1000 3400 0    50   BiDi ~ 0
F11
Text GLabel 1500 3400 2    50   BiDi ~ 0
F12
Text GLabel 1000 3500 0    50   BiDi ~ 0
F13
Text GLabel 1500 3500 2    50   BiDi ~ 0
F14
Text GLabel 1000 3600 0    50   BiDi ~ 0
F15
Text GLabel 1500 3600 2    50   BiDi ~ 0
G0
Text GLabel 1000 3700 0    50   BiDi ~ 0
G1
Text GLabel 1500 3700 2    50   BiDi ~ 0
E7
Text GLabel 1000 3800 0    50   BiDi ~ 0
E8
Text GLabel 1500 3800 2    50   BiDi ~ 0
E9
Text GLabel 1000 3900 0    50   BiDi ~ 0
E10
Text GLabel 1500 3900 2    50   BiDi ~ 0
E11
Text GLabel 1000 4000 0    50   BiDi ~ 0
E12
Text GLabel 1500 4000 2    50   BiDi ~ 0
E13
Text GLabel 1000 4100 0    50   BiDi ~ 0
E14
Text GLabel 1500 4100 2    50   BiDi ~ 0
E15
Text GLabel 1000 4200 0    50   BiDi ~ 0
B10
Text GLabel 1500 4200 2    50   BiDi ~ 0
B11
Wire Wire Line
	1500 4400 1500 4300
Wire Wire Line
	1000 4300 1000 4400
Connection ~ 1000 4400
Text GLabel 2300 1900 0    50   BiDi ~ 0
B3
Text GLabel 2800 1800 2    50   BiDi ~ 0
B4
Text GLabel 2300 1800 0    50   BiDi ~ 0
B5
Text GLabel 2800 1700 2    50   BiDi ~ 0
B6
Text GLabel 2300 1700 0    50   BiDi ~ 0
B7
Text GLabel 2800 1600 2    50   BiDi ~ 0
DAT4
Text GLabel 2300 1600 0    50   BiDi ~ 0
DAT5
Text GLabel 2800 2200 2    50   BiDi ~ 0
G9
Text GLabel 2300 2200 0    50   BiDi ~ 0
G10
Text GLabel 2800 2100 2    50   BiDi ~ 0
G11
Text GLabel 2300 2100 0    50   BiDi ~ 0
G12
Text GLabel 2800 2000 2    50   BiDi ~ 0
G13
Text GLabel 2300 2000 0    50   BiDi ~ 0
G14
Text GLabel 2800 1900 2    50   BiDi ~ 0
G15
Text GLabel 2800 2600 2    50   BiDi ~ 0
D0
Text GLabel 2300 2600 0    50   BiDi ~ 0
D1
Text GLabel 2800 2500 2    50   BiDi ~ 0
CMD
Text GLabel 2300 2500 0    50   BiDi ~ 0
D3
Text GLabel 2800 2400 2    50   BiDi ~ 0
D4
Text GLabel 2300 2400 0    50   BiDi ~ 0
D5
Text GLabel 2800 2300 2    50   BiDi ~ 0
D6
Text GLabel 2300 2300 0    50   BiDi ~ 0
D7
Text GLabel 2300 2800 0    50   BiDi ~ 0
DAT2
Text GLabel 2800 2700 2    50   BiDi ~ 0
DAT3
Text GLabel 2300 2700 0    50   BiDi ~ 0
CLK
Text GLabel 2300 3200 0    50   BiDi ~ 0
~RST
Text GLabel 2800 3100 2    50   BiDi ~ 0
A9
Text GLabel 2300 3100 0    50   BiDi ~ 0
A10
Text GLabel 2800 3000 2    50   BiDi ~ 0
A11
Text GLabel 2300 3000 0    50   BiDi ~ 0
A12
Text GLabel 2800 2900 2    50   BiDi ~ 0
A13
Text GLabel 2300 2900 0    50   BiDi ~ 0
A14
Text GLabel 2800 2800 2    50   BiDi ~ 0
A15
Text GLabel 2800 4300 2    50   BiDi ~ 0
B12
Text GLabel 2300 4300 0    50   BiDi ~ 0
B13
Text GLabel 2800 4200 2    50   BiDi ~ 0
B14
Text GLabel 2300 4200 0    50   BiDi ~ 0
B15
Text GLabel 2800 4100 2    50   BiDi ~ 0
D8
Text GLabel 2300 4100 0    50   BiDi ~ 0
D9
Text GLabel 2800 4000 2    50   BiDi ~ 0
D10
Text GLabel 2300 4000 0    50   BiDi ~ 0
D11
Text GLabel 2800 3900 2    50   BiDi ~ 0
D12
Text GLabel 2300 3900 0    50   BiDi ~ 0
D13
Text GLabel 2800 3800 2    50   BiDi ~ 0
D14
Text GLabel 2300 3800 0    50   BiDi ~ 0
D15
Text GLabel 2800 3700 2    50   BiDi ~ 0
G2
Text GLabel 2300 3700 0    50   BiDi ~ 0
G3
Text GLabel 2800 3600 2    50   BiDi ~ 0
G4
Text GLabel 2300 3600 0    50   BiDi ~ 0
G5
Text GLabel 2800 3500 2    50   BiDi ~ 0
G6
Text GLabel 2300 3500 0    50   BiDi ~ 0
G7
Text GLabel 2800 3400 2    50   BiDi ~ 0
G8
Text GLabel 2300 3400 0    50   BiDi ~ 0
DAT6
Text GLabel 2800 3300 2    50   BiDi ~ 0
DAT7
Text GLabel 2300 3300 0    50   BiDi ~ 0
DAT0
Text GLabel 2800 3200 2    50   BiDi ~ 0
DAT1
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 6027E630
P 2550 5500
F 0 "J3" H 2630 5542 50  0000 L CNN
F 1 "DBG" H 2630 5451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 2550 5500 50  0001 C CNN
F 3 "~" H 2550 5500 50  0001 C CNN
	1    2550 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 6027F39A
P 2350 5400
F 0 "#PWR09" H 2350 5150 50  0001 C CNN
F 1 "GND" H 2355 5227 50  0001 C CNN
F 2 "" H 2350 5400 50  0001 C CNN
F 3 "" H 2350 5400 50  0001 C CNN
	1    2350 5400
	0    1    1    0   
$EndComp
Text GLabel 2350 5500 0    50   Input ~ 0
A9
Text GLabel 2350 5600 0    50   Output ~ 0
A10
$Comp
L power:GND #PWR03
U 1 1 60285D46
P 1000 2800
F 0 "#PWR03" H 1000 2550 50  0001 C CNN
F 1 "GND" H 1005 2627 50  0001 C CNN
F 2 "" H 1000 2800 50  0001 C CNN
F 3 "" H 1000 2800 50  0001 C CNN
	1    1000 2800
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 6028E2F6
P 1500 4600
F 0 "#FLG02" H 1500 4675 50  0001 C CNN
F 1 "PWR_FLAG" V 1500 4728 50  0001 L CNN
F 2 "" H 1500 4600 50  0001 C CNN
F 3 "~" H 1500 4600 50  0001 C CNN
	1    1500 4600
	0    1    1    0   
$EndComp
Connection ~ 1500 4600
$Comp
L power:PWR_FLAG #FLG01
U 1 1 6028F199
P 1000 4600
F 0 "#FLG01" H 1000 4675 50  0001 C CNN
F 1 "PWR_FLAG" V 1000 4727 50  0001 L CNN
F 2 "" H 1000 4600 50  0001 C CNN
F 3 "~" H 1000 4600 50  0001 C CNN
	1    1000 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 60248808
P 4550 3150
F 0 "C3" V 4321 3150 50  0000 C CNN
F 1 "100n" V 4412 3150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4550 3150 50  0001 C CNN
F 3 "~" H 4550 3150 50  0001 C CNN
	1    4550 3150
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 6024C0F8
P 4550 3050
F 0 "#PWR0102" H 4550 2900 50  0001 C CNN
F 1 "+3V3" H 4565 3223 50  0000 C CNN
F 2 "" H 4550 3050 50  0001 C CNN
F 3 "" H 4550 3050 50  0001 C CNN
	1    4550 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6024C2D1
P 4550 3250
F 0 "#PWR0103" H 4550 3000 50  0001 C CNN
F 1 "GND" H 4555 3077 50  0001 C CNN
F 2 "" H 4550 3250 50  0001 C CNN
F 3 "" H 4550 3250 50  0001 C CNN
	1    4550 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 602628BE
P 5800 1450
F 0 "R1" H 5859 1496 50  0000 L CNN
F 1 "10k" H 5859 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5800 1450 50  0001 C CNN
F 3 "~" H 5800 1450 50  0001 C CNN
	1    5800 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 60263186
P 6050 1450
F 0 "R2" H 6109 1496 50  0000 L CNN
F 1 "10k" H 6109 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6050 1450 50  0001 C CNN
F 3 "~" H 6050 1450 50  0001 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 602634D1
P 6300 1450
F 0 "R3" H 6359 1496 50  0000 L CNN
F 1 "10k" H 6359 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6300 1450 50  0001 C CNN
F 3 "~" H 6300 1450 50  0001 C CNN
	1    6300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1350 6050 1350
Connection ~ 6050 1350
Wire Wire Line
	6050 1350 6300 1350
$Comp
L power:+3V3 #PWR0107
U 1 1 60264D47
P 5800 1350
F 0 "#PWR0107" H 5800 1200 50  0001 C CNN
F 1 "+3V3" H 5815 1523 50  0000 C CNN
F 2 "" H 5800 1350 50  0001 C CNN
F 3 "" H 5800 1350 50  0001 C CNN
	1    5800 1350
	1    0    0    -1  
$EndComp
Connection ~ 5800 1350
Text GLabel 5800 1550 3    50   Input ~ 0
~RST
Text GLabel 6050 1550 3    50   Input ~ 0
CMD
Text GLabel 6300 1550 3    50   Input ~ 0
CLK
$Comp
L power:GND #PWR0104
U 1 1 603F7EE6
P 1000 2900
F 0 "#PWR0104" H 1000 2650 50  0001 C CNN
F 1 "GND" H 1005 2727 50  0001 C CNN
F 2 "" H 1000 2900 50  0001 C CNN
F 3 "" H 1000 2900 50  0001 C CNN
	1    1000 2900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 603F8132
P 1500 2700
F 0 "#PWR0108" H 1500 2450 50  0001 C CNN
F 1 "GND" H 1505 2527 50  0001 C CNN
F 2 "" H 1500 2700 50  0001 C CNN
F 3 "" H 1500 2700 50  0001 C CNN
	1    1500 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 603F8735
P 1500 2800
F 0 "#PWR0109" H 1500 2550 50  0001 C CNN
F 1 "GND" H 1505 2627 50  0001 C CNN
F 2 "" H 1500 2800 50  0001 C CNN
F 3 "" H 1500 2800 50  0001 C CNN
	1    1500 2800
	0    -1   -1   0   
$EndComp
NoConn ~ 2300 1400
NoConn ~ 2300 1500
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J4
U 1 1 603AA7D6
P 5450 3050
F 0 "J4" H 5500 3467 50  0000 C CNN
F 1 "Left" H 5500 3376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x06_P2.54mm_Vertical" H 5450 3050 50  0001 C CNN
F 3 "~" H 5450 3050 50  0001 C CNN
	1    5450 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J5
U 1 1 603ABA69
P 6800 3050
F 0 "J5" H 6850 3467 50  0000 C CNN
F 1 "Right" H 6850 3376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x06_P2.54mm_Vertical" H 6800 3050 50  0001 C CNN
F 3 "~" H 6800 3050 50  0001 C CNN
	1    6800 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 603ACDAC
P 7100 3050
F 0 "#PWR0101" H 7100 2800 50  0001 C CNN
F 1 "GND" H 7105 2877 50  0001 C CNN
F 2 "" H 7100 3050 50  0001 C CNN
F 3 "" H 7100 3050 50  0001 C CNN
	1    7100 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5250 2850 5250 2950
Connection ~ 5250 2950
Wire Wire Line
	5250 2950 5250 3050
Connection ~ 5250 3050
Wire Wire Line
	5250 3050 5250 3100
Connection ~ 5250 3150
Wire Wire Line
	5250 3150 5250 3250
Connection ~ 5250 3250
Wire Wire Line
	5250 3250 5250 3350
Wire Wire Line
	5750 3150 5750 3100
$Comp
L power:+3V3 #PWR0105
U 1 1 603B1F55
P 5750 3100
F 0 "#PWR0105" H 5750 2950 50  0001 C CNN
F 1 "+3V3" V 5765 3228 50  0000 L CNN
F 2 "" H 5750 3100 50  0001 C CNN
F 3 "" H 5750 3100 50  0001 C CNN
	1    5750 3100
	0    1    1    0   
$EndComp
Connection ~ 5750 3100
Wire Wire Line
	5750 3100 5750 3050
$Comp
L power:GND #PWR0106
U 1 1 603B2462
P 5250 3100
F 0 "#PWR0106" H 5250 2850 50  0001 C CNN
F 1 "GND" H 5255 2927 50  0001 C CNN
F 2 "" H 5250 3100 50  0001 C CNN
F 3 "" H 5250 3100 50  0001 C CNN
	1    5250 3100
	0    1    1    0   
$EndComp
Connection ~ 5250 3100
Wire Wire Line
	5250 3100 5250 3150
Text GLabel 7100 2950 2    50   BiDi ~ 0
DAT4
Text GLabel 6600 2850 0    50   BiDi ~ 0
DAT5
Text GLabel 6600 2950 0    50   BiDi ~ 0
DAT6
Text GLabel 7100 2850 2    50   BiDi ~ 0
DAT7
$EndSCHEMATC
