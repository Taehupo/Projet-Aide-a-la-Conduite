#!/bin/bash
LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "input_file.so -f /home/thor/Desktop/Ptut_test -n test.jpg" -o "output_http.so -w /usr/local/www"
