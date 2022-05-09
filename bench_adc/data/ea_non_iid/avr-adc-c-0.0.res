Opening file: '../bin/adc/avr-adc-c-0.0.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 16 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4461695, p-hat = 0.55771187499999997, p_u = 0.55816417823991438
	Most Common Value Estimate (bit string) = 0.841239 / 1 bit(s)
Literal MCV Estimate: mode = 88944, p-hat = 0.088943999999999995, p_u = 0.089677243398055995
	Most Common Value Estimate = 3.479114 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.4413086512959841, sigma-hat = 0.49654345311063408, p = 0.67233382591570345
	Collision Test Estimate (bit string) = 0.572750 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.55771187499999997, P_1 = 0.44228812500000003, P_0,0 = 0.55204199300938317, P_0,1 = 0.44795800699061683, P_1,0 = 0.5648613007813913, P_1,1 = 0.4351386992186087, p_max = 9.4813136079666674e-34
	Markov Test Estimate (bit string) = 0.857035 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 4.2519616229424209, sigma-hat = 1.0087483819170056, p = 0.33174097300062988
	Compression Test Estimate (bit string) = 0.265312 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 41, p-hat_max = 0.74382830146080992, p_u = 0.74422583523913155
Bitstring LRS Estimate: u = 42, v = 83, p-hat = 0.69955243158222791, p_u = 0.69996994130659262
	T-Tuple Test Estimate (bit string) = 0.426188 / 1 bit(s)
Literal t-Tuple Estimate: t = 5, p-hat_max = 0.13260415084011204, p_u = 0.13347773454786491
Literal LRS Estimate: u = 6, v = 10, p-hat = 0.072879256052565608, p_u = 0.073548812831265714
	T-Tuple Test Estimate = 2.905329 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.514635 / 1 bit(s)
	LRS Test Estimate = 3.765154 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.55814257411793688 (C = 4461487) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 0.841294 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.089458043133864379 (C = 88720) Plocal = 0.10141009022342679 (r = 8)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 3.301727 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.67433637483110598 (C = 5391275) Plocal = 0.68960364929711593 (r = 52)
	Lag Prediction Test Estimate (bit string) = 0.536161 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.068166396597985707 (C = 67520) Plocal can't affect result (r = 6)
	Lag Prediction Test Estimate = 3.874795 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.80335579238796084 (C = 6423947) Plocal can't affect result (r = 51)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.315889 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.11323890194208235 (C = 112425) Plocal can't affect result (r = 8)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 3.142558 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.55816311396864504 (C = 4461677) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.841241 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.11323357753904031 (C = 112418) Plocal can't affect result (r = 8)
	LZ78Y Prediction Test Estimate = 3.142626 / 8 bit(s)

H_original: 2.905329
H_bitstring: 0.265312
min(H_original, 8 X H_bitstring): 2.122495
