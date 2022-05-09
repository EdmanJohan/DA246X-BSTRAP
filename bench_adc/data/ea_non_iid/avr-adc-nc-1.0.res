Opening file: '../bin/adc/avr-adc-nc-1.0.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 16 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4382424, p-hat = 0.54780300000000004, p_u = 0.54825626079352885
	Most Common Value Estimate (bit string) = 0.867078 / 1 bit(s)
Literal MCV Estimate: mode = 150834, p-hat = 0.150834, p_u = 0.15175585628171789
	Most Common Value Estimate = 2.720176 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.4338795466777086, sigma-hat = 0.4956088784325125, p = 0.68279031170160032
	Collision Test Estimate (bit string) = 0.550486 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.54780300000000004, P_1 = 0.45219699999999996, P_0,0 = 0.53321530121578864, P_0,1 = 0.46678469878421136, P_1,0 = 0.56547478200872625, P_1,1 = 0.43452521799127375, p_max = 1.1356775734988846e-35
	Markov Test Estimate (bit string) = 0.906906 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 4.1435956890451751, sigma-hat = 1.05722624617108, p = 0.35648814402663287
	Compression Test Estimate (bit string) = 0.248012 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 2783, p-hat_max = 0.99561204345332532, p_u = 0.99567223677959771
Bitstring LRS Estimate: u = 2784, v = 2915, p-hat = 0.99163715979567513, p_u = 0.99172009242007741
	T-Tuple Test Estimate (bit string) = 0.006257 / 1 bit(s)
Literal t-Tuple Estimate: t = 330, p-hat_max = 0.96938793220851771, p_u = 0.96983165571306496
Literal LRS Estimate: u = 331, v = 363, p-hat = 0.93964479099520126, p_u = 0.94025820901698409
	T-Tuple Test Estimate = 0.044194 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.011995 / 1 bit(s)
	LRS Test Estimate = 0.088871 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.54795110073197972 (C = 4379948) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 0.867881 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.15229276546938855 (C = 151360) Plocal = 0.95916667381492249 (r = 365)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 0.060147 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.68108891783802328 (C = 5445314) Plocal = 0.99463901102618357 (r = 2840)
	Lag Prediction Test Estimate (bit string) = 0.007755 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.095177313581760542 (C = 94424) Plocal = 0.95881227770899713 (r = 362)
	Lag Prediction Test Estimate = 0.060680 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.7888694754194937 (C = 6307979) Plocal = 0.9947956066104009 (r = 2920)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.007528 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.15169901624870571 (C = 150777) Plocal = 0.95916650242716661 (r = 365)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 0.060147 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.54825542542783401 (C = 4382408) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.867080 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.15169327029765398 (C = 150769) Plocal = 0.95916654457071293 (r = 365)
	LZ78Y Prediction Test Estimate = 0.060147 / 8 bit(s)

H_original: 0.044194
H_bitstring: 0.006257
min(H_original, 8 X H_bitstring): 0.044194
