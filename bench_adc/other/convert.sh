#!/bin/bash

CAP=avr-adc-c-0.0

convert -size 128x128+0 -depth 1 mono:$CAP.cap $CAP-mono_x128.png
convert -size 512x512+0 -depth 1 mono:$CAP.cap $CAP-mono_x512.png
convert -size 1024x1024+0 -depth 1 mono:$CAP.cap $CAP-mono_x1024.png

convert -size 577x577+0 -depth 8 RGB:$CAP.cap $CAP-RGB-x577.png

#convert -size 512x512+0 -depth 8 gray:$CAP.cap $CAP-GRAY-x512.png
convert -size 1000x1000+0 -depth 8 gray:$CAP.cap $CAP-GRAY-x1000.png