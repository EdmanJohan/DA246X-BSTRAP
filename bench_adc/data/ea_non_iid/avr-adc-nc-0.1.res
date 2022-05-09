Opening file: '../bin/adc/avr-adc-nc-0.1.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 16 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4382299, p-hat = 0.54778737499999997, p_u = 0.54824063715999716
	Most Common Value Estimate (bit string) = 0.867119 / 1 bit(s)
Literal MCV Estimate: mode = 480024, p-hat = 0.48002400000000001, p_u = 0.48131088702432351
	Most Common Value Estimate = 1.054959 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.2241349783035633, sigma-hat = 0.41701143647525074, p = 0.87177371625274824
	Collision Test Estimate (bit string) = 0.197974 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.54778737499999997, P_1 = 0.45221262500000003, P_0,0 = 0.55862335240551875, P_0,1 = 0.44137664759448125, P_1,0 = 0.5346611010694361, P_1,1 = 0.4653388989305639, p_max = 4.1950393453527122e-33
	Markov Test Estimate (bit string) = 0.840273 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 2.9387629196000375, sigma-hat = 1.2854400284711061, p = 0.59643209693224319
	Compression Test Estimate (bit string) = 0.124262 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 4888, p-hat_max = 0.99756370814116724, p_u = 0.99760860408341223
Bitstring LRS Estimate: u = 4889, v = 5020, p-hat = 0.99522935016236858, p_u = 0.99529210142535951
	T-Tuple Test Estimate (bit string) = 0.003454 / 1 bit(s)
Literal t-Tuple Estimate: t = 593, p-hat_max = 0.98303244324396732, p_u = 0.98336511112936076
Literal LRS Estimate: u = 594, v = 626, p-hat = 0.96590300239568394, p_u = 0.96637045988726356
	T-Tuple Test Estimate = 0.024201 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.006808 / 1 bit(s)
	LRS Test Estimate = 0.049352 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.54647359049485456 (C = 4368127) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 0.871776 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.56624263071532199 (C = 564930) Plocal = 0.97694984814680741 (r = 628)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 0.033644 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.83328931171473164 (C = 6663596) Plocal = 0.99708520280575363 (r = 5021)
	Lag Prediction Test Estimate (bit string) = 0.004211 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.44428596460400355 (C = 443006) Plocal = 0.97683245775970473 (r = 625)
	Lag Prediction Test Estimate = 0.033817 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.90213577927796962 (C = 7214917) Plocal = 0.99708644647888633 (r = 5023)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.004210 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.5636419838955613 (C = 562363) Plocal = 0.97694974632218456 (r = 628)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 0.033644 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.54822692785933491 (C = 4382180) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.867155 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.55371221685327565 (C = 552422) Plocal = 0.97694977136044381 (r = 628)
	LZ78Y Prediction Test Estimate = 0.033644 / 8 bit(s)

H_original: 0.024201
H_bitstring: 0.003454
min(H_original, 8 X H_bitstring): 0.024201
