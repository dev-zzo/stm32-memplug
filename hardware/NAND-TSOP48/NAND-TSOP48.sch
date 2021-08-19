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
L power:GND #PWR017
U 1 1 6028C7C0
P 7050 3200
F 0 "#PWR017" H 7050 2950 50  0001 C CNN
F 1 "GND" H 7055 3027 50  0001 C CNN
F 2 "" H 7050 3200 50  0001 C CNN
F 3 "" H 7050 3200 50  0001 C CNN
	1    7050 3200
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR016
U 1 1 6028D74C
P 7550 3100
F 0 "#PWR016" H 7550 2950 50  0001 C CNN
F 1 "+3V3" V 7565 3228 50  0000 L CNN
F 2 "" H 7550 3100 50  0001 C CNN
F 3 "" H 7550 3100 50  0001 C CNN
	1    7550 3100
	0    1    1    0   
$EndComp
Text GLabel 7050 3000 0    50   Input ~ 0
~CE0
Text GLabel 7550 3000 2    50   Input ~ 0
~CE1
Text GLabel 7550 3200 2    50   Input ~ 0
~CE2
Text GLabel 7050 3300 0    50   Input ~ 0
~CE3
Text GLabel 7550 2900 2    50   Input ~ 0
~RE
Text GLabel 7550 3400 2    50   Input ~ 0
~WE
Text GLabel 7550 3300 2    50   Input ~ 0
CLE
Text GLabel 7050 3400 0    50   Input ~ 0
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
L Device:C_Small C2
U 1 1 602914E1
P 5350 5100
F 0 "C2" H 5258 5054 50  0000 R CNN
F 1 "100n" H 5258 5145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5350 5100 50  0001 C CNN
F 3 "~" H 5350 5100 50  0001 C CNN
	1    5350 5100
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 6029192A
P 5700 5100
F 0 "C3" H 5608 5054 50  0000 R CNN
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
L Connector_Generic:Conn_02x12_Odd_Even J1
U 1 1 60329BE1
P 7250 3100
F 0 "J1" H 7300 3817 50  0000 C CNN
F 1 "Left" H 7300 3726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x12_P2.54mm_Vertical" H 7250 3100 50  0001 C CNN
F 3 "~" H 7250 3100 50  0001 C CNN
	1    7250 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x12_Odd_Even J2
U 1 1 6032A927
P 8800 3100
F 0 "J2" H 8850 3817 50  0000 C CNN
F 1 "Right" H 8850 3726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x12_P2.54mm_Vertical" H 8800 3100 50  0001 C CNN
F 3 "~" H 8800 3100 50  0001 C CNN
	1    8800 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2700 7550 2800
Wire Wire Line
	7050 2800 7050 2900
Text GLabel 7050 2800 0    50   Output ~ 0
R~B
Text GLabel 7550 2700 2    50   Output ~ 0
R~B
Wire Wire Line
	4250 4650 4250 4550
Text Notes 8600 3850 0    50   ~ 0
25
Text Notes 9000 3850 0    50   ~ 0
26
Text Notes 8600 2500 0    50   ~ 0
47
Text Notes 9000 2500 0    50   ~ 0
48
$Comp
L power:GND #PWR05
U 1 1 60338708
P 8600 3700
F 0 "#PWR05" H 8600 3450 50  0001 C CNN
F 1 "GND" H 8605 3527 50  0001 C CNN
F 2 "" H 8600 3700 50  0001 C CNN
F 3 "" H 8600 3700 50  0001 C CNN
	1    8600 3700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 603396CF
P 9100 2600
F 0 "#PWR06" H 9100 2350 50  0001 C CNN
F 1 "GND" H 9105 2427 50  0001 C CNN
F 2 "" H 9100 2600 50  0001 C CNN
F 3 "" H 9100 2600 50  0001 C CNN
	1    9100 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR08
U 1 1 6033AD49
P 9100 3300
F 0 "#PWR08" H 9100 3150 50  0001 C CNN
F 1 "+3V3" V 9115 3428 50  0000 L CNN
F 2 "" H 9100 3300 50  0001 C CNN
F 3 "" H 9100 3300 50  0001 C CNN
	1    9100 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 6033B483
P 9100 3200
F 0 "#PWR07" H 9100 2950 50  0001 C CNN
F 1 "GND" H 9105 3027 50  0001 C CNN
F 2 "" H 9100 3200 50  0001 C CNN
F 3 "" H 9100 3200 50  0001 C CNN
	1    9100 3200
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 6033BF78
P 8600 3100
F 0 "#PWR04" H 8600 2950 50  0001 C CNN
F 1 "+3V3" V 8615 3228 50  0000 L CNN
F 2 "" H 8600 3100 50  0001 C CNN
F 3 "" H 8600 3100 50  0001 C CNN
	1    8600 3100
	0    -1   -1   0   
$EndComp
NoConn ~ 8600 3200
NoConn ~ 9100 3100
$Comp
L power:+3V3 #PWR03
U 1 1 6033DD27
P 8600 3000
F 0 "#PWR03" H 8600 2850 50  0001 C CNN
F 1 "+3V3" V 8615 3128 50  0000 L CNN
F 2 "" H 8600 3000 50  0001 C CNN
F 3 "" H 8600 3000 50  0001 C CNN
	1    8600 3000
	0    -1   -1   0   
$EndComp
NoConn ~ 7050 3600
NoConn ~ 7050 3700
NoConn ~ 7550 3500
NoConn ~ 7550 3600
NoConn ~ 7550 3700
NoConn ~ 7050 3100
NoConn ~ 7050 2600
NoConn ~ 7550 2600
$Comp
L Memory:Generic_ONFI_NAND_TSOP48 U1
U 1 1 602ECAB8
P 2950 4950
F 0 "U1" H 3350 7715 50  0000 C CNN
F 1 "Generic_ONFI_NAND_TSOP48" H 3350 7624 50  0000 C CNN
F 2 "Memory:SOP50P2000X120-48N" H 2950 4950 50  0001 L BNN
F 3 "" H 2950 4950 50  0001 L BNN
	1    2950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3950 2750 4050
Connection ~ 2750 4050
Wire Wire Line
	2750 4050 2750 4150
Connection ~ 2750 4150
Wire Wire Line
	2750 4150 2750 4250
Text GLabel 2750 4050 0    50   Output ~ 0
R~B
$Comp
L power:+3V3 #PWR01
U 1 1 602EF292
P 3950 2450
F 0 "#PWR01" H 3950 2300 50  0001 C CNN
F 1 "+3V3" V 3965 2578 50  0000 L CNN
F 2 "" H 3950 2450 50  0001 C CNN
F 3 "" H 3950 2450 50  0001 C CNN
	1    3950 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 2450 3950 2550
Connection ~ 3950 2450
$Comp
L Device:C_Small C4
U 1 1 602EFBBE
P 6050 5100
F 0 "C4" H 5958 5054 50  0000 R CNN
F 1 "100n" H 5958 5145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6050 5100 50  0001 C CNN
F 3 "~" H 6050 5100 50  0001 C CNN
	1    6050 5100
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 602EFF9B
P 6400 5100
F 0 "C5" H 6308 5054 50  0000 R CNN
F 1 "100n" H 6308 5145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6400 5100 50  0001 C CNN
F 3 "~" H 6400 5100 50  0001 C CNN
	1    6400 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 5000 6050 5000
Connection ~ 5700 5000
Connection ~ 6050 5000
Wire Wire Line
	6050 5000 5700 5000
Wire Wire Line
	5700 5200 6050 5200
Connection ~ 5700 5200
Connection ~ 6050 5200
Wire Wire Line
	6050 5200 6400 5200
$Comp
L Device:C_Small C1
U 1 1 602F0D49
P 4250 4750
F 0 "C1" H 4158 4704 50  0000 R CNN
F 1 "100n" H 4158 4795 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4250 4750 50  0001 C CNN
F 3 "~" H 4250 4750 50  0001 C CNN
	1    4250 4750
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 602F194A
P 4250 4850
F 0 "#PWR02" H 4250 4600 50  0001 C CNN
F 1 "GND" H 4255 4677 50  0001 C CNN
F 2 "" H 4250 4850 50  0001 C CNN
F 3 "" H 4250 4850 50  0001 C CNN
	1    4250 4850
	-1   0    0    -1  
$EndComp
Text GLabel 3950 3150 2    50   BiDi ~ 0
IO4
Text GLabel 3950 3350 2    50   BiDi ~ 0
IO6
Text GLabel 3950 4150 2    50   BiDi ~ 0
IO13
Text GLabel 3950 4350 2    50   BiDi ~ 0
IO15
Text GLabel 3950 2750 2    50   BiDi ~ 0
IO0
Text GLabel 3950 2950 2    50   BiDi ~ 0
IO2
Text GLabel 3950 3750 2    50   BiDi ~ 0
IO9
Text GLabel 3950 3950 2    50   BiDi ~ 0
IO11
Text GLabel 3950 4050 2    50   BiDi ~ 0
IO12
Text GLabel 3950 3850 2    50   BiDi ~ 0
IO10
Text GLabel 3950 3650 2    50   BiDi ~ 0
IO8
Text GLabel 3950 3250 2    50   BiDi ~ 0
IO5
Text GLabel 3950 3450 2    50   BiDi ~ 0
IO7
Text GLabel 3950 2850 2    50   BiDi ~ 0
IO1
Text GLabel 3950 3050 2    50   BiDi ~ 0
IO3
Wire Wire Line
	3950 4750 3950 4850
Wire Wire Line
	3950 4850 4250 4850
Connection ~ 3950 4850
Connection ~ 4250 4850
Wire Wire Line
	3950 4550 4250 4550
Text GLabel 2750 2750 0    50   Input ~ 0
~CE0
Text GLabel 2750 3050 0    50   Input ~ 0
~CE3
Text GLabel 2750 2850 0    50   Input ~ 0
~CE1
Text GLabel 2750 2950 0    50   Input ~ 0
~CE2
Text GLabel 2750 3250 0    50   Input ~ 0
~RE
Text GLabel 2750 3550 0    50   Input ~ 0
ALE
Text GLabel 2750 3350 0    50   Input ~ 0
~WE
Text GLabel 2750 3450 0    50   Input ~ 0
CLE
Text GLabel 2750 3750 0    50   Input ~ 0
~WP
Text GLabel 3950 4250 2    50   BiDi ~ 0
IO14
Text GLabel 7050 3500 0    50   Input ~ 0
~WP
NoConn ~ 7050 2700
$EndSCHEMATC
