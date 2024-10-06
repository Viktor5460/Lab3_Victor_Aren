#!/bin/bash
gcc 4_insertion.c -o 1
./1
python3 main.py
touch file_list.txt
python3 file_list.py
ffmpeg -f concat -i file_list.txt -i zvuk.mp3 4_insertion_output.mp4

