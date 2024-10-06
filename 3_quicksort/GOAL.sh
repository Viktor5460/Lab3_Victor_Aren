#!/bin/bash
gcc 1_bubble.c -o 1
./1
python3 main.py
touch file_list.txt
file_list.py
ffmpeg -f concat -i file_list.txt -i zvuk.mp3 1_bubble_output.mp4

