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
Text GLabel 4800 2000 0    50   Input ~ 0
A0
Text GLabel 4800 2100 0    50   Input ~ 0
A1
Text GLabel 4800 2200 0    50   Input ~ 0
A2
Text GLabel 4800 2300 0    50   Input ~ 0
A3
Text GLabel 4800 2400 0    50   Input ~ 0
A4
Text GLabel 4800 2500 0    50   Input ~ 0
A5
Text GLabel 4800 2600 0    50   Input ~ 0
A6
Text GLabel 4800 2700 0    50   Input ~ 0
A7
Text GLabel 4800 2800 0    50   Input ~ 0
A8
Text GLabel 4800 2900 0    50   Input ~ 0
A9
Text GLabel 4800 3000 0    50   Input ~ 0
A10
Text GLabel 4800 3100 0    50   Input ~ 0
A11
Text GLabel 4800 3200 0    50   Input ~ 0
A12
Text GLabel 4800 3300 0    50   Input ~ 0
A13
Text GLabel 4800 3400 0    50   Input ~ 0
A14
Text GLabel 4800 3500 0    50   Input ~ 0
A15
Text GLabel 4800 3600 0    50   Input ~ 0
A16
Text GLabel 4800 3700 0    50   Input ~ 0
A17
Text GLabel 4800 3800 0    50   Input ~ 0
A18
Text GLabel 4800 3900 0    50   Input ~ 0
A19
Text GLabel 4800 4000 0    50   Input ~ 0
A20
Text GLabel 4800 4100 0    50   Input ~ 0
A21
Text GLabel 4800 4200 0    50   Input ~ 0
A22
Text GLabel 4800 4300 0    50   Input ~ 0
A23
Text GLabel 4800 4400 0    50   Input ~ 0
A24
Text GLabel 4800 4500 0    50   Input ~ 0
A25
Text GLabel 6000 2700 2    50   BiDi ~ 0
DQ0
Text GLabel 6000 2800 2    50   BiDi ~ 0
DQ1
Text GLabel 6000 2900 2    50   BiDi ~ 0
DQ2
Text GLabel 6000 3000 2    50   BiDi ~ 0
DQ3
Text GLabel 6000 3100 2    50   BiDi ~ 0
DQ4
Text GLabel 6000 3200 2    50   BiDi ~ 0
DQ5
Text GLabel 6000 3300 2    50   BiDi ~ 0
DQ6
Text GLabel 6000 3400 2    50   BiDi ~ 0
DQ7
Text GLabel 6000 3500 2    50   BiDi ~ 0
DQ8
Text GLabel 6000 3600 2    50   BiDi ~ 0
DQ9
Text GLabel 6000 3700 2    50   BiDi ~ 0
DQ10
Text GLabel 6000 3800 2    50   BiDi ~ 0
DQ11
Text GLabel 6000 3900 2    50   BiDi ~ 0
DQ12
Text GLabel 6000 4000 2    50   BiDi ~ 0
DQ13
Text GLabel 6000 4100 2    50   BiDi ~ 0
DQ14
Text GLabel 6000 4200 2    50   BiDi ~ 0
DQ15
$Comp
L Connector_Generic:Conn_02x14_Odd_Even J1
U 1 1 603FAC19
P 8000 3400
F 0 "J1" H 8050 4217 50  0000 C CNN
F 1 "Left" H 8050 4126 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x14_P2.54mm_Vertical" H 8000 3400 50  0001 C CNN
F 3 "~" H 8000 3400 50  0001 C CNN
	1    8000 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x14_Odd_Even J2
U 1 1 603FBD94
P 9300 3400
F 0 "J2" H 9350 4217 50  0000 C CNN
F 1 "Right" H 9350 4126 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x14_P2.54mm_Vertical" H 9300 3400 50  0001 C CNN
F 3 "~" H 9300 3400 50  0001 C CNN
	1    9300 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 603FD46F
P 6000 5200
F 0 "#PWR03" H 6000 4950 50  0001 C CNN
F 1 "GND" H 6005 5027 50  0001 C CNN
F 2 "" H 6000 5200 50  0001 C CNN
F 3 "" H 6000 5200 50  0001 C CNN
	1    6000 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR02
U 1 1 603FDE5F
P 6000 2000
F 0 "#PWR02" H 6000 1850 50  0001 C CNN
F 1 "+3V3" H 6015 2173 50  0000 C CNN
F 2 "" H 6000 2000 50  0001 C CNN
F 3 "" H 6000 2000 50  0001 C CNN
	1    6000 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 603FE8B2
P 7350 5200
F 0 "C1" H 7442 5246 50  0000 L CNN
F 1 "100n" H 7442 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7350 5200 50  0001 C CNN
F 3 "~" H 7350 5200 50  0001 C CNN
	1    7350 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 603FEBD7
P 7700 5200
F 0 "C2" H 7792 5246 50  0000 L CNN
F 1 "100n" H 7792 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7700 5200 50  0001 C CNN
F 3 "~" H 7700 5200 50  0001 C CNN
	1    7700 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5100 7350 5100
Wire Wire Line
	7350 5300 7700 5300
$Comp
L power:GND #PWR05
U 1 1 603FF18B
P 7350 5300
F 0 "#PWR05" H 7350 5050 50  0001 C CNN
F 1 "GND" H 7355 5127 50  0001 C CNN
F 2 "" H 7350 5300 50  0001 C CNN
F 3 "" H 7350 5300 50  0001 C CNN
	1    7350 5300
	1    0    0    -1  
$EndComp
Connection ~ 7350 5300
$Comp
L power:+3V3 #PWR04
U 1 1 603FF571
P 7350 5100
F 0 "#PWR04" H 7350 4950 50  0001 C CNN
F 1 "+3V3" H 7365 5273 50  0000 C CNN
F 2 "" H 7350 5100 50  0001 C CNN
F 3 "" H 7350 5100 50  0001 C CNN
	1    7350 5100
	1    0    0    -1  
$EndComp
Connection ~ 7350 5100
Text GLabel 8300 2800 2    50   Input ~ 0
A23
Text GLabel 7800 2800 0    50   Input ~ 0
A22
Text GLabel 8300 2900 2    50   Input ~ 0
A15
Text GLabel 8300 3000 2    50   Input ~ 0
A13
Text GLabel 8300 3100 2    50   Input ~ 0
A11
Text GLabel 8300 3200 2    50   Input ~ 0
A9
Text GLabel 7800 2900 0    50   Input ~ 0
A14
Text GLabel 7800 3000 0    50   Input ~ 0
A12
Text GLabel 7800 3100 0    50   Input ~ 0
A10
Text GLabel 7800 3200 0    50   Input ~ 0
A8
Text GLabel 8300 3300 2    50   Input ~ 0
A19
Text GLabel 7800 3300 0    50   Input ~ 0
A20
Text GLabel 4800 4900 0    50   Input ~ 0
~WE
Text GLabel 4800 4700 0    50   Input ~ 0
~CE
Text GLabel 4800 4800 0    50   Input ~ 0
~OE
Text GLabel 4800 5200 0    50   Input ~ 0
~RST
Wire Wire Line
	4800 5000 4800 5100
$Comp
L power:+3V3 #PWR01
U 1 1 60401CFB
P 4800 5000
F 0 "#PWR01" H 4800 4850 50  0001 C CNN
F 1 "+3V3" V 4815 5128 50  0000 L CNN
F 2 "" H 4800 5000 50  0001 C CNN
F 3 "" H 4800 5000 50  0001 C CNN
	1    4800 5000
	0    -1   -1   0   
$EndComp
Text GLabel 6000 4700 2    50   Output ~ 0
R~B
Text GLabel 8300 3400 2    50   Input ~ 0
~WE
Text GLabel 7800 3400 0    50   Input ~ 0
~RST
Text GLabel 8300 3500 2    50   Input ~ 0
A21
Text GLabel 9100 2800 0    50   Input ~ 0
A24
Text GLabel 9600 2800 2    50   Input ~ 0
A25
Text GLabel 9100 2900 0    50   Input ~ 0
A16
$Comp
L power:GND #PWR0101
U 1 1 60403B79
P 9100 3000
F 0 "#PWR0101" H 9100 2750 50  0001 C CNN
F 1 "GND" H 9105 2827 50  0001 C CNN
F 2 "" H 9100 3000 50  0001 C CNN
F 3 "" H 9100 3000 50  0001 C CNN
	1    9100 3000
	0    1    -1   0   
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 60404301
P 9600 4100
F 0 "#PWR0102" H 9600 3950 50  0001 C CNN
F 1 "+3V3" V 9615 4228 50  0000 L CNN
F 2 "" H 9600 4100 50  0001 C CNN
F 3 "" H 9600 4100 50  0001 C CNN
	1    9600 4100
	0    1    -1   0   
$EndComp
Text GLabel 9600 4000 2    50   Input ~ 0
A0
Text GLabel 9600 3000 2    50   BiDi ~ 0
DQ15
Text GLabel 9100 3100 0    50   BiDi ~ 0
DQ7
Text GLabel 9600 3100 2    50   BiDi ~ 0
DQ14
Text GLabel 9600 3200 2    50   BiDi ~ 0
DQ13
Text GLabel 9600 3300 2    50   BiDi ~ 0
DQ12
Text GLabel 9100 3200 0    50   BiDi ~ 0
DQ6
Text GLabel 9100 3300 0    50   BiDi ~ 0
DQ5
Text GLabel 9100 3400 0    50   BiDi ~ 0
DQ4
$Comp
L power:+3V3 #PWR0103
U 1 1 604052B8
P 9600 3400
F 0 "#PWR0103" H 9600 3250 50  0001 C CNN
F 1 "+3V3" V 9615 3528 50  0000 L CNN
F 2 "" H 9600 3400 50  0001 C CNN
F 3 "" H 9600 3400 50  0001 C CNN
	1    9600 3400
	0    1    -1   0   
$EndComp
Text GLabel 9100 3500 0    50   BiDi ~ 0
DQ11
Text GLabel 9100 3600 0    50   BiDi ~ 0
DQ10
Text GLabel 9100 3700 0    50   BiDi ~ 0
DQ9
Text GLabel 9100 3800 0    50   BiDi ~ 0
DQ8
Text GLabel 9600 3500 2    50   BiDi ~ 0
DQ3
Text GLabel 9600 3600 2    50   BiDi ~ 0
DQ2
Text GLabel 9600 3700 2    50   BiDi ~ 0
DQ1
Text GLabel 9600 3800 2    50   BiDi ~ 0
DQ0
Text GLabel 9100 3900 0    50   Input ~ 0
~OE
$Comp
L power:GND #PWR0104
U 1 1 60405CCA
P 9600 3900
F 0 "#PWR0104" H 9600 3650 50  0001 C CNN
F 1 "GND" H 9605 3727 50  0001 C CNN
F 2 "" H 9600 3900 50  0001 C CNN
F 3 "" H 9600 3900 50  0001 C CNN
	1    9600 3900
	0    -1   1    0   
$EndComp
Text GLabel 9100 4000 0    50   Input ~ 0
~CE
NoConn ~ 8300 4100
NoConn ~ 7800 4100
Text GLabel 8300 4000 2    50   Input ~ 0
A2
Text GLabel 8300 3900 2    50   Input ~ 0
A4
Text GLabel 8300 3800 2    50   Input ~ 0
A6
Text GLabel 8300 3700 2    50   Input ~ 0
A17
Text GLabel 8300 3600 2    50   Output ~ 0
R~B
Text GLabel 7800 3800 0    50   Input ~ 0
A5
Text GLabel 7800 3900 0    50   Input ~ 0
A3
Text GLabel 7800 4000 0    50   Input ~ 0
A1
Text GLabel 7800 3700 0    50   Input ~ 0
A7
Text GLabel 7800 3600 0    50   Input ~ 0
A18
Wire Wire Line
	6000 2000 6000 2100
$Comp
L Memory:Generic_NOR_BGA64 U1
U 1 1 611430BB
P 5400 3200
F 0 "U1" H 5400 4667 50  0000 C CNN
F 1 "Generic_NOR_BGA64" H 5400 4576 50  0000 C CNN
F 2 "Memory:BGA64C100P8X8_1300X1100X130N" H 5400 950 50  0001 C CNN
F 3 "" H 5400 3450 50  0001 C CNN
	1    5400 3200
	1    0    0    -1  
$EndComp
Connection ~ 4800 5000
Wire Wire Line
	6000 5100 6000 5200
Connection ~ 6000 2000
Connection ~ 6000 5200
Wire Wire Line
	6000 2200 6000 2100
Connection ~ 6000 2100
Wire Wire Line
	6000 5000 6000 5100
Connection ~ 6000 5100
$EndSCHEMATC
