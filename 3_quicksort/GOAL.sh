#!/bin/bash
gcc 3_quicksort.c -o 1
./1
python3 main.py
touch file_list.txt
file_list.py
ffmpeg -f concat -i file_list.txt -i zvuk.mp3 3_quicksort_output.mp4
