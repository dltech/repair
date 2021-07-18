EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "0.9-9V DC-DC with sleep function"
Date "2021-03-21"
Rev ""
Comp ""
Comment1 ""
Comment2 "Mikhail Belkin"
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4950 2900 5100 2900
Connection ~ 4950 3300
Connection ~ 5100 3300
Wire Wire Line
	5100 3300 4950 3300
Wire Wire Line
	4600 3300 4950 3300
$Comp
L Switch:SW_SPST SW2
U 1 1 603BC9A7
P 4950 3100
F 0 "SW2" H 5050 3300 50  0000 R CNN
F 1 "SW_SPST" H 5100 3200 50  0000 R CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 4950 3100 50  0001 C CNN
F 3 "" H 4950 3100 50  0001 C CNN
	1    4950 3100
	0    -1   -1   0   
$EndComp
Connection ~ 6400 2400
Wire Wire Line
	6600 2450 6650 2450
Wire Wire Line
	6600 2400 6600 2450
Wire Wire Line
	6400 2400 6600 2400
Wire Wire Line
	6650 2550 6600 2550
Wire Wire Line
	6150 2400 6400 2400
Wire Wire Line
	6400 2650 6400 2400
Connection ~ 4600 2400
Wire Wire Line
	4600 3300 4100 3300
Connection ~ 4600 3300
Wire Wire Line
	4600 3000 4600 3300
Wire Wire Line
	4600 2400 4600 2700
Wire Wire Line
	4550 2400 4600 2400
$Comp
L device:C C1
U 1 1 603AAE82
P 4600 2850
F 0 "C1" H 4500 2750 50  0000 L CNN
F 1 "10uF" H 4400 2950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4638 2700 50  0001 C CNN
F 3 "" H 4600 2850 50  0001 C CNN
	1    4600 2850
	-1   0    0    1   
$EndComp
$Comp
L device:C C3
U 1 1 603AA968
P 6400 2800
F 0 "C3" H 6300 2700 50  0000 L CNN
F 1 "10uF" H 6200 2900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6438 2650 50  0001 C CNN
F 3 "" H 6400 2800 50  0001 C CNN
	1    6400 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 2400 4100 2800
Wire Wire Line
	4100 2400 4150 2400
Connection ~ 5300 2400
$Comp
L device:Battery_Cell BT1
U 1 1 6036F397
P 4100 3000
F 0 "BT1" H 4218 3096 50  0000 L CNN
F 1 "AA" H 4218 3005 50  0000 L CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" V 4100 3060 50  0001 C CNN
F 3 "" V 4100 3060 50  0001 C CNN
	1    4100 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3100 4100 3300
Wire Wire Line
	5750 3300 5750 3350
Connection ~ 5750 3300
Wire Wire Line
	5100 3300 5750 3300
Wire Wire Line
	5750 3100 5750 3300
Wire Wire Line
	6150 3300 6150 3100
Wire Wire Line
	5100 3250 5100 3300
Wire Wire Line
	5100 2900 5350 2900
Wire Wire Line
	5100 2900 5100 2950
Connection ~ 5100 2900
Wire Wire Line
	5100 2900 5100 2850
$Comp
L device:C C2
U 1 1 60344611
P 5100 2700
F 0 "C2" H 5000 2600 50  0000 L CNN
F 1 "1uF" H 4950 2800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5138 2550 50  0001 C CNN
F 3 "" H 5100 2700 50  0001 C CNN
	1    5100 2700
	-1   0    0    1   
$EndComp
Connection ~ 6150 2400
$Comp
L Connector:Conn_01x02 J1
U 1 1 60391B8C
P 6850 2450
F 0 "J1" H 6930 2442 50  0000 L CNN
F 1 "out 9v" H 6930 2351 50  0000 L CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 6850 2450 50  0001 C CNN
F 3 "~" H 6850 2450 50  0001 C CNN
	1    6850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2400 5300 2700
Wire Wire Line
	5350 2400 5300 2400
Connection ~ 5800 2400
Connection ~ 5700 2400
Wire Wire Line
	5700 2400 5800 2400
Wire Wire Line
	5700 2400 5700 2500
Wire Wire Line
	5650 2400 5700 2400
Wire Wire Line
	5800 2400 5850 2400
Wire Wire Line
	5800 2500 5800 2400
Wire Wire Line
	6150 2400 6150 2450
$Comp
L Diode:1N5822 D2
U 1 1 6038A153
P 6000 2400
F 0 "D2" H 6000 2500 50  0000 C CNN
F 1 "1N5822" H 6000 2275 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 6000 2225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88526/1n5820.pdf" H 6000 2400 50  0001 C CNN
	1    6000 2400
	-1   0    0    1   
$EndComp
$Comp
L device:L L1
U 1 1 60388B21
P 5500 2400
F 0 "L1" V 5600 2200 50  0000 C CNN
F 1 "4.7mH" V 5599 2400 50  0000 C CNN
F 2 "Inductor_SMD:L_7.3x7.3_H4.5" H 5500 2400 50  0001 C CNN
F 3 "" H 5500 2400 50  0001 C CNN
	1    5500 2400
	0    -1   -1   0   
$EndComp
Connection ~ 6150 2750
Wire Wire Line
	6150 2750 6150 2800
Wire Wire Line
	6100 2750 6150 2750
$Comp
L device:R R3
U 1 1 60386895
P 6150 2950
F 0 "R3" H 6220 2996 50  0000 L CNN
F 1 "6k" H 6220 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 2950 50  0001 C CNN
F 3 "" H 6150 2950 50  0001 C CNN
	1    6150 2950
	1    0    0    -1  
$EndComp
$Comp
L device:R R2
U 1 1 60385FB9
P 6150 2600
F 0 "R2" H 6220 2646 50  0000 L CNN
F 1 "1k" H 6220 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 2600 50  0001 C CNN
F 3 "" H 6150 2600 50  0001 C CNN
	1    6150 2600
	1    0    0    -1  
$EndComp
$Comp
L device:R R1
U 1 1 6037F926
P 5100 3100
F 0 "R1" H 5170 3146 50  0000 L CNN
F 1 "10M" H 5170 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5030 3100 50  0001 C CNN
F 3 "" H 5100 3100 50  0001 C CNN
	1    5100 3100
	1    0    0    -1  
$EndComp
Connection ~ 5300 2700
$Comp
L Switch:SW_SPST SW1
U 1 1 603761C7
P 4350 2400
F 0 "SW1" H 4350 2635 50  0000 C CNN
F 1 "SW_SPST" H 4350 2544 50  0000 C CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 4350 2400 50  0001 C CNN
F 3 "" H 4350 2400 50  0001 C CNN
	1    4350 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 6036CC40
P 5750 3350
F 0 "#PWR01" H 5750 3100 50  0001 C CNN
F 1 "GND" H 5850 3250 50  0000 C CNN
F 2 "" H 5750 3350 50  0001 C CNN
F 3 "" H 5750 3350 50  0001 C CNN
	1    5750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2800 5300 2800
Wire Wire Line
	5300 2700 5300 2800
Wire Wire Line
	5350 2700 5300 2700
$Comp
L belk:ME2149 D1
U 1 1 6033E44A
P 5750 2800
F 0 "D1" H 5900 3050 50  0000 C CNN
F 1 "ME2149" H 5950 2550 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 5750 2800 50  0001 C CNN
F 3 "" H 5750 2800 50  0001 C CNN
	1    5750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3300 6400 3300
Wire Wire Line
	6400 3300 6400 2950
Wire Wire Line
	6400 3300 6600 3300
Wire Wire Line
	6600 3300 6600 2550
Connection ~ 6400 3300
Wire Wire Line
	6150 3300 5750 3300
Connection ~ 6150 3300
Wire Wire Line
	4600 2400 4750 2400
$Comp
L device:R R4
U 1 1 60363F0A
P 4950 2500
F 0 "R4" V 5050 2450 50  0000 L CNN
F 1 "1k" V 4950 2450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4880 2500 50  0001 C CNN
F 3 "" H 4950 2500 50  0001 C CNN
	1    4950 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 2550 5100 2500
Wire Wire Line
	4800 2500 4750 2500
Wire Wire Line
	4750 2500 4750 2400
Connection ~ 4750 2400
Wire Wire Line
	4750 2400 5300 2400
$EndSCHEMATC
