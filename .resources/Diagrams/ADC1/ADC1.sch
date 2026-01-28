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
L power:GND #PWR?
U 1 1 697B8C47
P 4400 5300
F 0 "#PWR?" H 4400 5050 50  0001 C CNN
F 1 "GND" H 4405 5127 50  0000 C CNN
F 2 "" H 4400 5300 50  0001 C CNN
F 3 "" H 4400 5300 50  0001 C CNN
	1    4400 5300
	1    0    0    -1  
$EndComp
$Comp
L MCU_RaspberryPi_and_Boards:Pico U?
U 1 1 697BD979
P 4400 3850
F 0 "U?" H 4400 5065 50  0000 C CNN
F 1 "Pico" H 4400 4974 50  0000 C CNN
F 2 "RPi_Pico:RPi_Pico_SMD_TH" V 4400 3850 50  0001 C CNN
F 3 "" H 4400 3850 50  0001 C CNN
	1    4400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5000 4400 5200
Wire Wire Line
	5100 3700 5700 3700
$Comp
L Device:R_POT RV?
U 1 1 697B539B
P 5850 3700
F 0 "RV?" H 5780 3654 50  0000 R CNN
F 1 "R_POT" H 5780 3745 50  0000 R CNN
F 2 "" H 5850 3700 50  0001 C CNN
F 3 "~" H 5850 3700 50  0001 C CNN
	1    5850 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	5850 3850 5850 5200
Wire Wire Line
	5850 5200 4400 5200
Connection ~ 4400 5200
Wire Wire Line
	4400 5200 4400 5300
Wire Wire Line
	5850 3550 5850 3300
Wire Wire Line
	5850 3300 5100 3300
$EndSCHEMATC
