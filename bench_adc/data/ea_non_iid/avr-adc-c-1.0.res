Opening file: '../bin/adc/avr-adc-c-1.0.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 43 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4458326, p-hat = 0.55729074999999995, p_u = 0.55774309763981456
	Most Common Value Estimate (bit string) = 0.842327 / 1 bit(s)
Literal MCV Estimate: mode = 82929, p-hat = 0.082929000000000003, p_u = 0.08363934935600921
	Most Common Value Estimate = 3.579674 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.4343024292515554, sigma-hat = 0.49566511270854835, p = 0.68221121617751856
	Collision Test Estimate (bit string) = 0.551710 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.55729074999999995, P_1 = 0.44270925000000005, P_0,0 = 0.55296103357202542, P_0,1 = 0.44703896642797458, P_1,0 = 0.56274095244226319, P_1,1 = 0.43725904755773681, p_max = 1.1702722842908317e-33
	Markov Test Estimate (bit string) = 0.854662 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 4.2624659392420483, sigma-hat = 1.0058147736635448, p = 0.32930414627546079
	Compression Test Estimate (bit string) = 0.267085 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 41, p-hat_max = 0.7411068493145514, p_u = 0.74150575737066959
Bitstring LRS Estimate: u = 42, v = 158, p-hat = 0.82573956738278576, p_u = 0.82608502363319336
	T-Tuple Test Estimate (bit string) = 0.431470 / 1 bit(s)
Literal t-Tuple Estimate: t = 4, p-hat_max = 0.11921699426929648, p_u = 0.12005167587730819
Literal LRS Estimate: u = 5, v = 19, p-hat = 0.24225100216466827, p_u = 0.24335460491272157
	T-Tuple Test Estimate = 3.058273 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.275638 / 1 bit(s)
	LRS Test Estimate = 2.038868 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.55769461779466833 (C = 4457903) Plocal can't affect result (r = 8)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 0.842453 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.086367241923326871 (C = 85641) Plocal = 0.13126443637525159 (r = 9)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 2.929452 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.67316339459063645 (C = 5381888) Plocal = 0.67897059622160305 (r = 50)
	Lag Prediction Test Estimate (bit string) = 0.558579 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.068535023574597009 (C = 67887) Plocal = 0.10140929302191214 (r = 8)
	Lag Prediction Test Estimate = 3.301738 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.79584752729380404 (C = 6363840) Plocal can't affect result (r = 64)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.329436 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.10310687995071718 (C = 102326) Plocal can't affect result (r = 8)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 3.277787 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.55773953273023924 (C = 4458288) Plocal can't affect result (r = 8)
	LZ78Y Prediction Test Estimate (bit string) = 0.842337 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.10309036476562822 (C = 102308) Plocal can't affect result (r = 8)
	LZ78Y Prediction Test Estimate = 3.278019 / 8 bit(s)

H_original: 2.038868
H_bitstring: 0.267085
min(H_original, 8 X H_bitstring): 2.038868
