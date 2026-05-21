set PATH=C:\Program Files\SDCC\bin

cd output

::s51 -X 11059200 -V -C program.ihx

::s51 --help
::s51 -X 11059200 program.ihx

::s51 -X 11059200 -V program.ihx 
::> out.txt 2>&1

@echo off
s51 -X 11059200 -V program.ihx 

::| D:\github\dsp_2025\sdcc_c51\cocolor 0e



pause