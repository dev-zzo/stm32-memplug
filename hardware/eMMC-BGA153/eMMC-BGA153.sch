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
L Connector_Generic:Conn_02x06_Odd_Even J1
U 1 1 60360599
P 7350 3450
F 0 "J1" H 7400 3867 50  0000 C CNN
F 1 "Left" H 7400 3776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x06_P2.54mm_Vertical" H 7350 3450 50  0001 C CNN
F 3 "~" H 7350 3450 50  0001 C CNN
	1    7350 3450
	1    0    0    -1  
$EndComp
Text GLabel 4800 3150 0    50   BiDi ~ 0
DAT0
Text GLabel 4800 3250 0    50   BiDi ~ 0
DAT1
Text GLabel 4800 3350 0    50   BiDi ~ 0
DAT2
Text GLabel 4800 3450 0    50   BiDi ~ 0
DAT3
Text GLabel 4800 3550 0    50   BiDi ~ 0
DAT4
Text GLabel 4800 3650 0    50   BiDi ~ 0
DAT5
Text GLabel 4800 3750 0    50   BiDi ~ 0
DAT6
Text GLabel 4800 3850 0    50   BiDi ~ 0
DAT7
Wire Wire Line
	6000 2750 6000 2850
Wire Wire Line
	6000 3750 6000 3850
$Comp
L power:GND #PWR0101
U 1 1 603624EC
P 6000 3850
F 0 "#PWR0101" H 6000 3600 50  0001 C CNN
F 1 "GND" H 6005 3677 50  0000 C CNN
F 2 "" H 6000 3850 50  0001 C CNN
F 3 "" H 6000 3850 50  0001 C CNN
	1    6000 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 60362C04
P 6000 2750
F 0 "#PWR0102" H 6000 2600 50  0001 C CNN
F 1 "+3V3" H 6015 2923 50  0000 C CNN
F 2 "" H 6000 2750 50  0001 C CNN
F 3 "" H 6000 2750 50  0001 C CNN
	1    6000 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J2
U 1 1 60360DCD
P 8650 3450
F 0 "J2" H 8700 3867 50  0000 C CNN
F 1 "Right" H 8700 3776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x06_P2.54mm_Vertical" H 8650 3450 50  0001 C CNN
F 3 "~" H 8650 3450 50  0001 C CNN
	1    8650 3450
	1    0    0    -1  
$EndComp
Text GLabel 8950 3750 2    50   BiDi ~ 0
DAT0
Text GLabel 8450 3750 0    50   BiDi ~ 0
DAT2
Text GLabel 8950 3250 2    50   BiDi ~ 0
DAT7
Text GLabel 8450 3250 0    50   BiDi ~ 0
DAT5
Text GLabel 8450 3350 0    50   BiDi ~ 0
DAT6
Text GLabel 8950 3350 2    50   BiDi ~ 0
DAT4
Text GLabel 8450 3650 0    50   BiDi ~ 0
DAT1
Text GLabel 8950 3650 2    50   BiDi ~ 0
DAT3
NoConn ~ 6000 3150
$Comp
L Device:C_Small C1
U 1 1 603649A7
P 6000 3650
F 0 "C1" H 6092 3696 50  0000 L CNN
F 1 "100n" H 6092 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6000 3650 50  0001 C CNN
F 3 "~" H 6000 3650 50  0001 C CNN
	1    6000 3650
	1    0    0    -1  
$EndComp
Text GLabel 4800 2750 0    50   Input ~ 0
~RST
Text GLabel 4800 2850 0    50   BiDi ~ 0
CMD
Text GLabel 4800 2950 0    50   Input ~ 0
CLK
Text GLabel 8450 3450 0    50   Output ~ 0
CLK
Text GLabel 8450 3550 0    50   BiDi ~ 0
CMD
Text GLabel 8950 3550 2    50   Output ~ 0
~RST
$Comp
L Device:C_Small C2
U 1 1 6036A62D
P 6550 4500
F 0 "C2" H 6642 4546 50  0000 L CNN
F 1 "100n" H 6642 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6550 4500 50  0001 C CNN
F 3 "~" H 6550 4500 50  0001 C CNN
	1    6550 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 6036AE2E
P 6900 4500
F 0 "C3" H 6992 4546 50  0000 L CNN
F 1 "100n" H 6992 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6900 4500 50  0001 C CNN
F 3 "~" H 6900 4500 50  0001 C CNN
	1    6900 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 6036B17D
P 7250 4500
F 0 "C4" H 7342 4546 50  0000 L CNN
F 1 "100n" H 7342 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7250 4500 50  0001 C CNN
F 3 "~" H 7250 4500 50  0001 C CNN
	1    7250 4500
	1    0    0    -1  
$EndComp
Connection ~ 6900 4400
Wire Wire Line
	6900 4400 6550 4400
Wire Wire Line
	7250 4400 6900 4400
Wire Wire Line
	6550 4600 6900 4600
Connection ~ 6900 4600
Wire Wire Line
	6900 4600 7250 4600
$Comp
L power:GND #PWR0103
U 1 1 6036BB1F
P 6550 4600
F 0 "#PWR0103" H 6550 4350 50  0001 C CNN
F 1 "GND" H 6555 4427 50  0000 C CNN
F 2 "" H 6550 4600 50  0001 C CNN
F 3 "" H 6550 4600 50  0001 C CNN
	1    6550 4600
	1    0    0    -1  
$EndComp
Connection ~ 6550 4600
$Comp
L power:+3V3 #PWR0104
U 1 1 6036BDFE
P 6550 4400
F 0 "#PWR0104" H 6550 4250 50  0001 C CNN
F 1 "+3V3" H 6565 4573 50  0000 C CNN
F 2 "" H 6550 4400 50  0001 C CNN
F 3 "" H 6550 4400 50  0001 C CNN
	1    6550 4400
	1    0    0    -1  
$EndComp
Connection ~ 6550 4400
Wire Wire Line
	7650 3450 7650 3500
Wire Wire Line
	7150 3250 7150 3350
Connection ~ 7150 3350
Wire Wire Line
	7150 3350 7150 3450
Connection ~ 7150 3450
Wire Wire Line
	7150 3450 7150 3550
Connection ~ 7150 3550
Wire Wire Line
	7150 3550 7150 3650
Connection ~ 7150 3650
Wire Wire Line
	7150 3650 7150 3750
$Comp
L power:GND #PWR0105
U 1 1 6036C8D9
P 7150 3750
F 0 "#PWR0105" H 7150 3500 50  0001 C CNN
F 1 "GND" V 7155 3622 50  0000 R CNN
F 2 "" H 7150 3750 50  0001 C CNN
F 3 "" H 7150 3750 50  0001 C CNN
	1    7150 3750
	0    1    1    0   
$EndComp
Connection ~ 7150 3750
$Comp
L power:+3V3 #PWR0106
U 1 1 6036D106
P 7650 3500
F 0 "#PWR0106" H 7650 3350 50  0001 C CNN
F 1 "+3V3" V 7665 3628 50  0000 L CNN
F 2 "" H 7650 3500 50  0001 C CNN
F 3 "" H 7650 3500 50  0001 C CNN
	1    7650 3500
	0    1    1    0   
$EndComp
Connection ~ 7650 3500
Wire Wire Line
	7650 3500 7650 3550
$Comp
L power:GND #PWR0107
U 1 1 6036DCE4
P 8950 3450
F 0 "#PWR0107" H 8950 3200 50  0001 C CNN
F 1 "GND" V 8955 3322 50  0000 R CNN
F 2 "" H 8950 3450 50  0001 C CNN
F 3 "" H 8950 3450 50  0001 C CNN
	1    8950 3450
	0    -1   -1   0   
$EndComp
$Comp
L Memory:Generic_eMMC_BGA153 U1
U 1 1 603886B1
P 5400 3750
F 0 "U1" H 5400 5017 50  0000 C CNN
F 1 "Generic_eMMC_BGA153" H 5400 4926 50  0000 C CNN
F 2 "Memory:BGA153N50P14X14_1150X1300X100" H 5400 3350 50  0001 C BNN
F 3 "" H 5400 3750 50  0001 L BNN
	1    5400 3750
	1    0    0    -1  
$EndComp
Connection ~ 6000 3850
Connection ~ 6000 3750
Connection ~ 6000 2750
$EndSCHEMATC
