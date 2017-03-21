EESchema Schematic File Version 2
LIBS:KERISEv3-rescue
LIBS:power
LIBS:device
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
LIBS:KERISEv3
LIBS:KERISEv3-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 14
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
L AS5145 U11
U 1 1 589E87BF
P 5600 3550
AR Path="/589E8312/589E87BF" Ref="U11"  Part="1" 
AR Path="/589F1140/589E87BF" Ref="U12"  Part="1" 
F 0 "U11" H 5600 4050 60  0000 C CNN
F 1 "AS5145" H 5600 3050 60  0000 C CNN
F 2 "Housings_SSOP:SSOP-16_5.3x6.2mm_Pitch0.65mm" H 5600 4050 60  0001 C CNN
F 3 "" H 5600 4050 60  0000 C CNN
	1    5600 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P13
U 1 1 589E8902
P 5800 2350
AR Path="/589E8312/589E8902" Ref="P13"  Part="1" 
AR Path="/589F1140/589E8902" Ref="P15"  Part="1" 
F 0 "P13" H 5800 2700 50  0000 C CNN
F 1 "ENC_Slave" V 5900 2350 50  0000 C CNN
F 2 "mouse:STAND_AS_SLAVE" H 5800 2350 50  0001 C CNN
F 3 "" H 5800 2350 50  0000 C CNN
	1    5800 2350
	-1   0    0    -1  
$EndComp
Text Label 6100 2100 0    60   ~ 0
s_3.3V
Text Label 6100 2600 0    60   ~ 0
s_VSS
Text Label 6100 2300 0    60   ~ 0
s_MOSI
Text Label 6100 2400 0    60   ~ 0
s_MISO
Text Label 6100 2500 0    60   ~ 0
s_CSn
Text Label 6100 2200 0    60   ~ 0
s_SCLK
NoConn ~ 4900 3200
NoConn ~ 4900 3300
NoConn ~ 4900 3400
NoConn ~ 4900 3500
NoConn ~ 4900 3700
Wire Wire Line
	6000 2100 6700 2100
Wire Wire Line
	6000 2600 6700 2600
Wire Wire Line
	6100 2300 6000 2300
Wire Wire Line
	6000 2500 6100 2500
Wire Wire Line
	6100 2200 6000 2200
Wire Wire Line
	6000 2400 6100 2400
Text Label 6400 3200 0    60   ~ 0
s_3.3V
Wire Wire Line
	6300 3200 6400 3200
NoConn ~ 6300 3600
Text Label 4800 3800 2    60   ~ 0
s_VSS
Wire Wire Line
	4800 3800 4900 3800
Text Label 6400 3800 0    60   ~ 0
s_SCLK
Wire Wire Line
	6400 3800 6300 3800
Text Label 4800 3900 2    60   ~ 0
s_MOSI
Wire Wire Line
	4800 3900 4900 3900
Text Label 6400 3900 0    60   ~ 0
s_MISO
Wire Wire Line
	6400 3900 6300 3900
Text Label 6400 3700 0    60   ~ 0
s_CSn
Wire Wire Line
	6400 3700 6300 3700
$Comp
L CONN_01X06 P12
U 1 1 589E9420
P 5400 2350
AR Path="/589E8312/589E9420" Ref="P12"  Part="1" 
AR Path="/589F1140/589E9420" Ref="P14"  Part="1" 
F 0 "P12" H 5400 2700 50  0000 C CNN
F 1 "ENC_Host" V 5500 2350 50  0000 C CNN
F 2 "mouse:STAND_AS_HOST" H 5400 2350 50  0001 C CNN
F 3 "" H 5400 2350 50  0000 C CNN
	1    5400 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR055
U 1 1 589E94E9
P 5100 2700
AR Path="/589E8312/589E94E9" Ref="#PWR055"  Part="1" 
AR Path="/589F1140/589E94E9" Ref="#PWR059"  Part="1" 
F 0 "#PWR059" H 5100 2450 50  0001 C CNN
F 1 "GND" H 5100 2550 50  0000 C CNN
F 2 "" H 5100 2700 50  0000 C CNN
F 3 "" H 5100 2700 50  0000 C CNN
	1    5100 2700
	1    0    0    -1  
$EndComp
Text HLabel 5000 2200 0    60   Input ~ 0
SCLK
Text HLabel 5000 2300 0    60   Input ~ 0
MOSI
Text HLabel 5000 2400 0    60   Input ~ 0
MISO
Text HLabel 5000 2500 0    60   Input ~ 0
CSn
Wire Wire Line
	5000 2300 5200 2300
Wire Wire Line
	5000 2200 5200 2200
Wire Wire Line
	5200 2400 5000 2400
$Comp
L PWR_FLAG #FLG056
U 1 1 58CB39A3
P 6700 2100
AR Path="/589E8312/58CB39A3" Ref="#FLG056"  Part="1" 
AR Path="/589F1140/58CB39A3" Ref="#FLG060"  Part="1" 
F 0 "#FLG060" H 6700 2195 50  0001 C CNN
F 1 "PWR_FLAG" H 6700 2280 50  0000 C CNN
F 2 "" H 6700 2100 50  0000 C CNN
F 3 "" H 6700 2100 50  0000 C CNN
	1    6700 2100
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG057
U 1 1 58CB39EE
P 6700 2600
AR Path="/589E8312/58CB39EE" Ref="#FLG057"  Part="1" 
AR Path="/589F1140/58CB39EE" Ref="#FLG061"  Part="1" 
F 0 "#FLG061" H 6700 2695 50  0001 C CNN
F 1 "PWR_FLAG" H 6700 2780 50  0000 C CNN
F 2 "" H 6700 2600 50  0000 C CNN
F 3 "" H 6700 2600 50  0000 C CNN
	1    6700 2600
	-1   0    0    1   
$EndComp
Text Label 6400 3300 0    60   ~ 0
s_3.3V
Wire Wire Line
	6400 3300 6300 3300
$Comp
L +3.3V #PWR058
U 1 1 589CCACF
P 5100 2000
AR Path="/589E8312/589CCACF" Ref="#PWR058"  Part="1" 
AR Path="/589F1140/589CCACF" Ref="#PWR062"  Part="1" 
F 0 "#PWR062" H 5100 1850 50  0001 C CNN
F 1 "+3.3V" H 5100 2140 50  0000 C CNN
F 2 "" H 5100 2000 50  0000 C CNN
F 3 "" H 5100 2000 50  0000 C CNN
	1    5100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2500 5200 2500
Wire Wire Line
	5200 2100 5100 2100
Wire Wire Line
	5100 2100 5100 2000
Wire Wire Line
	5100 2700 5100 2600
Wire Wire Line
	5100 2600 5200 2600
$EndSCHEMATC
