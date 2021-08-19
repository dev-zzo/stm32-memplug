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
F 1 "Conn_02x33_Odd_Even" H 1250 4726 50  0000 C CNN
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
F 1 "Conn_02x33_Odd_Even" H 2550 4726 50  0000 C CNN
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
IO4
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
B8
Text GLabel 2300 1600 0    50   BiDi ~ 0
B9
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
IO2
Text GLabel 2300 2600 0    50   BiDi ~ 0
IO3
Text GLabel 2800 2500 2    50   BiDi ~ 0
D2
Text GLabel 2300 2500 0    50   BiDi ~ 0
D3
Text GLabel 2800 2400 2    50   BiDi ~ 0
~RE
Text GLabel 2300 2400 0    50   BiDi ~ 0
~WE
Text GLabel 2800 2300 2    50   BiDi ~ 0
R~B
Text GLabel 2300 2300 0    50   BiDi ~ 0
D7
Text GLabel 2300 2800 0    50   BiDi ~ 0
C10
Text GLabel 2800 2700 2    50   BiDi ~ 0
C11
Text GLabel 2300 2700 0    50   BiDi ~ 0
C12
Text GLabel 2300 3200 0    50   BiDi ~ 0
A8
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
IO13
Text GLabel 2300 4100 0    50   BiDi ~ 0
IO14
Text GLabel 2800 4000 2    50   BiDi ~ 0
IO15
Text GLabel 2300 4000 0    50   BiDi ~ 0
CLE
Text GLabel 2800 3900 2    50   BiDi ~ 0
ALE
Text GLabel 2300 3900 0    50   BiDi ~ 0
D13
Text GLabel 2800 3800 2    50   BiDi ~ 0
IO0
Text GLabel 2300 3800 0    50   BiDi ~ 0
IO1
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
C6
Text GLabel 2800 3300 2    50   BiDi ~ 0
C7
Text GLabel 2300 3300 0    50   BiDi ~ 0
C8
Text GLabel 2800 3200 2    50   BiDi ~ 0
C9
$Comp
L power:GND #PWR017
U 1 1 6028C7C0
P 7200 3200
F 0 "#PWR017" H 7200 2950 50  0001 C CNN
F 1 "GND" H 7205 3027 50  0001 C CNN
F 2 "" H 7200 3200 50  0001 C CNN
F 3 "" H 7200 3200 50  0001 C CNN
	1    7200 3200
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR016
U 1 1 6028D74C
P 7700 3100
F 0 "#PWR016" H 7700 2950 50  0001 C CNN
F 1 "+3V3" V 7715 3228 50  0000 L CNN
F 2 "" H 7700 3100 50  0001 C CNN
F 3 "" H 7700 3100 50  0001 C CNN
	1    7700 3100
	0    1    1    0   
$EndComp
Text GLabel 7200 3000 0    50   Input ~ 0
~CE0
Text GLabel 7700 3000 2    50   Input ~ 0
~CE1
Text GLabel 7700 3200 2    50   Input ~ 0
~CE2
Text GLabel 7200 3300 0    50   Input ~ 0
~CE3
Text GLabel 7700 2900 2    50   Input ~ 0
~RE
Text GLabel 7700 3400 2    50   Input ~ 0
~WE
Text GLabel 7700 3300 2    50   Input ~ 0
CLE
Text GLabel 7200 3400 0    50   Input ~ 0
ALE
Text GLabel 8600 3500 0    50   BiDi ~ 0
IO0
Text GLabel 9100 3500 2    50   BiDi ~ 0
IO1
Text GLabel 8600 3400 0    50   BiDi ~ 0
IO2
Text GLabel 9100 3400 2    50   BiDi ~ 0
IO3
Text GLabel 8600 2900 0    50   BiDi ~ 0
IO4
Text GLabel 9100 2900 2    50   BiDi ~ 0
IO5
Text GLabel 8600 2800 0    50   BiDi ~ 0
IO6
Text GLabel 9100 2800 2    50   BiDi ~ 0
IO7
Text GLabel 9100 3700 2    50   BiDi ~ 0
IO8
Text GLabel 8600 3600 0    50   BiDi ~ 0
IO9
Text GLabel 9100 3600 2    50   BiDi ~ 0
IO10
Text GLabel 8600 3300 0    50   BiDi ~ 0
IO11
Text GLabel 9100 3000 2    50   BiDi ~ 0
IO12
Text GLabel 8600 2700 0    50   BiDi ~ 0
IO13
Text GLabel 9100 2700 2    50   BiDi ~ 0
IO14
Text GLabel 8600 2600 0    50   BiDi ~ 0
IO15
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
A10
Text GLabel 2400 5400 0    50   Input ~ 0
A9
$Comp
L Device:R_Small R1
U 1 1 60298407
P 5350 1100
F 0 "R1" H 5409 1146 50  0000 L CNN
F 1 "1k" H 5409 1055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5350 1100 50  0001 C CNN
F 3 "~" H 5350 1100 50  0001 C CNN
	1    5350 1100
	1    0    0    -1  
$EndComp
$Comp
L Jumper:Jumper_3_Open JP1
U 1 1 6029A3FA
P 6800 1050
F 0 "JP1" H 6800 1274 50  0000 C CNN
F 1 "CE0 SEL" H 6800 1183 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6800 1050 50  0001 C CNN
F 3 "~" H 6800 1050 50  0001 C CNN
	1    6800 1050
	1    0    0    -1  
$EndComp
Text GLabel 6550 1050 0    50   Output ~ 0
~CE0
Text GLabel 7050 1050 2    50   Output ~ 0
~CE2
$Comp
L Jumper:Jumper_3_Open JP2
U 1 1 6029A945
P 7850 1050
F 0 "JP2" H 7850 1274 50  0000 C CNN
F 1 "CE1 SEL" H 7850 1183 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7850 1050 50  0001 C CNN
F 3 "~" H 7850 1050 50  0001 C CNN
	1    7850 1050
	1    0    0    -1  
$EndComp
Text GLabel 7600 1050 0    50   Output ~ 0
~CE1
Text GLabel 8100 1050 2    50   Output ~ 0
~CE3
$Comp
L power:+3V3 #PWR013
U 1 1 6029B40A
P 5350 1000
F 0 "#PWR013" H 5350 850 50  0001 C CNN
F 1 "+3V3" H 5365 1173 50  0000 C CNN
F 2 "" H 5350 1000 50  0001 C CNN
F 3 "" H 5350 1000 50  0001 C CNN
	1    5350 1000
	1    0    0    -1  
$EndComp
Text GLabel 6800 1200 3    50   Input ~ 0
D7
Text GLabel 7850 1200 3    50   Input ~ 0
G9
Text GLabel 5350 1200 3    50   UnSpc ~ 0
R~B
$Comp
L power:GND #PWR02
U 1 1 602ADC21
P 1000 2800
F 0 "#PWR02" H 1000 2550 50  0001 C CNN
F 1 "GND" H 1005 2627 50  0001 C CNN
F 2 "" H 1000 2800 50  0001 C CNN
F 3 "" H 1000 2800 50  0001 C CNN
	1    1000 2800
	0    1    1    0   
$EndComp
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
$Comp
L Connector_Generic:Conn_02x12_Odd_Even J4
U 1 1 60329BE1
P 7400 3100
F 0 "J4" H 7450 3817 50  0000 C CNN
F 1 "Left" H 7450 3726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x12_P2.54mm_Vertical" H 7400 3100 50  0001 C CNN
F 3 "~" H 7400 3100 50  0001 C CNN
	1    7400 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x12_Odd_Even J5
U 1 1 6032A927
P 8800 3100
F 0 "J5" H 8850 3817 50  0000 C CNN
F 1 "Right" H 8850 3726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x12_P2.54mm_Vertical" H 8800 3100 50  0001 C CNN
F 3 "~" H 8800 3100 50  0001 C CNN
	1    8800 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0101
U 1 1 603316AF
P 7200 3500
F 0 "#PWR0101" H 7200 3350 50  0001 C CNN
F 1 "+3V3" V 7215 3628 50  0000 L CNN
F 2 "" H 7200 3500 50  0001 C CNN
F 3 "" H 7200 3500 50  0001 C CNN
	1    7200 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7700 2700 7700 2800
Wire Wire Line
	7200 2800 7200 2900
Text GLabel 7200 2800 0    50   Output ~ 0
R~B
Text GLabel 7700 2700 2    50   Output ~ 0
R~B
Text Notes 8600 3850 0    50   ~ 0
25
Text Notes 9000 3850 0    50   ~ 0
26
Text Notes 8600 2500 0    50   ~ 0
47
Text Notes 9000 2500 0    50   ~ 0
48
$Comp
L power:GND #PWR0103
U 1 1 60338708
P 8600 3700
F 0 "#PWR0103" H 8600 3450 50  0001 C CNN
F 1 "GND" H 8605 3527 50  0001 C CNN
F 2 "" H 8600 3700 50  0001 C CNN
F 3 "" H 8600 3700 50  0001 C CNN
	1    8600 3700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 603396CF
P 9100 2600
F 0 "#PWR0104" H 9100 2350 50  0001 C CNN
F 1 "GND" H 9105 2427 50  0001 C CNN
F 2 "" H 9100 2600 50  0001 C CNN
F 3 "" H 9100 2600 50  0001 C CNN
	1    9100 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 6033AD49
P 9100 3300
F 0 "#PWR0105" H 9100 3150 50  0001 C CNN
F 1 "+3V3" V 9115 3428 50  0000 L CNN
F 2 "" H 9100 3300 50  0001 C CNN
F 3 "" H 9100 3300 50  0001 C CNN
	1    9100 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6033B483
P 9100 3200
F 0 "#PWR0106" H 9100 2950 50  0001 C CNN
F 1 "GND" H 9105 3027 50  0001 C CNN
F 2 "" H 9100 3200 50  0001 C CNN
F 3 "" H 9100 3200 50  0001 C CNN
	1    9100 3200
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR0107
U 1 1 6033BF78
P 8600 3100
F 0 "#PWR0107" H 8600 2950 50  0001 C CNN
F 1 "+3V3" V 8615 3228 50  0000 L CNN
F 2 "" H 8600 3100 50  0001 C CNN
F 3 "" H 8600 3100 50  0001 C CNN
	1    8600 3100
	0    -1   -1   0   
$EndComp
NoConn ~ 8600 3200
NoConn ~ 9100 3100
$Comp
L power:+3V3 #PWR0108
U 1 1 6033DD27
P 8600 3000
F 0 "#PWR0108" H 8600 2850 50  0001 C CNN
F 1 "+3V3" V 8615 3128 50  0000 L CNN
F 2 "" H 8600 3000 50  0001 C CNN
F 3 "" H 8600 3000 50  0001 C CNN
	1    8600 3000
	0    -1   -1   0   
$EndComp
NoConn ~ 7200 3600
NoConn ~ 7200 3700
NoConn ~ 7700 3500
NoConn ~ 7700 3600
NoConn ~ 7700 3700
NoConn ~ 7200 3100
NoConn ~ 7200 2600
NoConn ~ 7700 2600
NoConn ~ 7200 2700
$EndSCHEMATC
