#!/bin/bash

# avr-adc-c-0.0.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-c-0.0.cap > avr-adc-c-0.0.csv

# avr-adc-c-1.0.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-c-1.0.cap > avr-adc-c-1.0.csv

# avr-adc-nc-0.0.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-nc-0.0.cap > avr-adc-nc-0.0.csv

# avr-adc-nc-0.1.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-nc-0.1.cap > avr-adc-nc-0.1.csv

# avr-adc-nc-0.2.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-nc-0.2.cap > avr-adc-nc-0.2.csv

# avr-adc-nc-1.0.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-nc-1.0.cap > avr-adc-nc-1.0.csv


# avr-adc-nc-1.1.cap
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' avr-adc-nc-1.1.cap > avr-adc-nc-1.1.csv

# truerand_8bit.bin
perl -ne 'BEGIN{$/ = \4096};
          $c[$_]++ for unpack("C*");
          END{for ($i=0;$i<256;$i++) {
              printf "%3d, %d\n", $i, $c[$i]}}' truerand_8bit.bin > truerand_8bit.csv