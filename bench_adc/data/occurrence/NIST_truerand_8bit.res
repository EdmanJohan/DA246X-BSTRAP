Opening file: '../bin/truerand_8bit.bin'
Loaded 1000000 samples of 256 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4001353, p-hat = 0.50016912499999999, p_u = 0.50062447159433998
	Most Common Value Estimate (bit string) = 0.998199 / 1 bit(s)
Literal MCV Estimate: mode = 4124, p-hat = 0.0041240000000000001, p_u = 0.0042890742216425554
	Most Common Value Estimate = 7.865118 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.5002922216534058, sigma-hat = 0.49999999274063472, p = 0.51462509129029099
	Collision Test Estimate (bit string) = 0.958406 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.49983087500000001, P_1 = 0.50016912499999999, P_0,0 = 0.49985620132414821, P_0,1 = 0.50014379867585179, P_1,0 = 0.49980544080964612, P_1,1 = 0.50019455919035383, p_max = 3.088625376674869e-39
	Markov Test Estimate (bit string) = 0.999439 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 5.2177128660275782, sigma-hat = 1.0157985743570801, p = 0.023269820763614391
	Compression Test Estimate (bit string) = 0.904233 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 19, p-hat_max = 0.5231065809785963, p_u = 0.52356144110715352
Bitstring LRS Estimate: u = 20, v = 43, p-hat = 0.50000543138094466, p_u = 0.50046077800130662
	T-Tuple Test Estimate (bit string) = 0.933569 / 1 bit(s)
Literal t-Tuple Estimate: t = 1, p-hat_max = 0.0041240000000000001, p_u = 0.0042890742216425554
Literal LRS Estimate: u = 2, v = 4, p-hat = 0.0039135687726790267, p_u = 0.0040743933037668822
	T-Tuple Test Estimate = 7.865118 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.998671 / 1 bit(s)
	LRS Test Estimate = 7.939199 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.50015153343672414 (C = 3997538) Plocal can't affect result (r = 24)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 0.999563 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.0039372940597956173 (C = 3779) Plocal can't affect result (r = 3)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 7.988580 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.50055428415230074 (C = 4000791) Plocal can't affect result (r = 23)
	Lag Prediction Test Estimate (bit string) = 0.998402 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.0040727964933169767 (C = 3912) Plocal can't affect result (r = 3)
	Lag Prediction Test Estimate = 7.939765 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.50011772148909028 (C = 3997298) Plocal can't affect result (r = 21)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.999660 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.0041095358683948232 (C = 3948) Plocal can't affect result (r = 3)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 7.926809 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.50053215976204901 (C = 4000606) Plocal can't affect result (r = 20)
	LZ78Y Prediction Test Estimate (bit string) = 0.998465 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.004109597507680046 (C = 3948) Plocal can't affect result (r = 3)
	LZ78Y Prediction Test Estimate = 7.926787 / 8 bit(s)

H_original: 7.865118
H_bitstring: 0.904233
min(H_original, 8 X H_bitstring): 7.233861
