#!/bin/bash
gcc 2_merge.c -o 1
./1
python3 main.py
touch file_list.txt
python3 file_list.py
ffmpeg -f concat -i file_list.txt -i zvuk.mp3 2_merge_output.mp4
