## Compilation

Compilation w.
```sh
make clean all -j8 BOARD=avr-rss2
make flash BOARD=avr-rss2
```

Connect to terminal w. minicom and save output to file,
```sh
minicom ttyUSB1 -C avr-adc.cap
```
Output is saved to `avr-adc.cap`.

## Entropy evaluation
Entropy can be evaluated using [SP800-90B_EntropyAssessment](https://github.com/usnistgov/SP800-90B_EntropyAssessment). More details specified in the standard document [NIST Special Publication 800-90B](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90B.pdf).

Compile binary and run with captured output,
```sh
./ea_non_iid avr-adc.cap
```

Alternatively, translate `avr-adc.cap` to bin format with the following code,
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int cc = 0;

    while (!cin.eof()) {
        char d;
        d = cin.get();
        string res = "";
        for (int i = 0; i < 8; i++) {
            if (d % 2 == 1) {
                res = "1" + res;
            } else {
                res = "0" + res;
            }
            d /= 2;
        }
        cout << res;
        cc++;
        if (cc == 125000) {
            break;
        }
    }
}
```

Compile with,
```sh
g++ ascii-to-bin.cpp -o ascii-to-bin
```

Run with,
```sh
cat avr-adc.cap | ./ascii-to-bin > avr-adc.bin
```

and run instead with,
```sh
./ea_non_iid avr-adc.bin
```

### Image Creation
Conversion according to:  
`(Width x Height) = (Bytes * 8) / (Bits-Per-Channel * Channels)`  

RGB (8-bits / 3 channels):  
`convert -size 577x577+0 -depth 8 RGB:truerand_8bit.bin truerand_8bit-rgb.png`  

Grayscale (8-bits / 1 channel):  
`convert -size 1000x1000+0 -depth 8 gray:truerand_8bit.bin truerand_8bit-gray.png` 

Mono (1-bit / 1 channel):  
`convert -size 2824x2824+0 -depth 1 mono:truerand_8bit.bin truerand_8bit-mono.png`


ImageMagick  
`convert -size 2824x2824+0 -depth 1 mono:avr-adc-c-0.0.cap avr-adc-c-0.0-mono.png`  
`convert -size 577x577+0 -depth 8 RGB:truerand_8bit.bin truerand_8bit.png`  
`convert -size 32x32+0 mono:avr-adc-nc-0.0.cap avr-adc-nc-0.0.png`  
`convert -size 32x32+0 mono:avr-adc-nc-0.0.cap -type bilevel -scale 300x avr-adc-nc-0.0.png`  

### Plotting
`CAP=C1.0 && gnuplot plot.gnuplot && epstopdf $CAP-plot.eps && pdfcrop $CAP-plot.pdf && rm -f $CAP-plot.eps && rm -f $CAP-plot.pdf && pdftk $CAP-plot-crop.pdf cat 1-endeast output $CAP-plot-1M.pdf && rm -f $CAP-plot-crop.pdf`

## References
[SP800-90B_EntropyAssessment](https://github.com/usnistgov/SP800-90B_EntropyAssessment)
[NIST Special Publication 800-90B](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90B.pdf)
[Entropy information theory](https://en.wikipedia.org/wiki/Entropy_(information_theory))
[What is entropy?](https://crypto.stackexchange.com/questions/378/what-is-entropy)
[Calculating the entropy rate of ADCs](https://electronics.stackexchange.com/questions/404590/calculating-the-entropy-rate-of-adcs)
