Opening file: '../bin/adc/avr-adc-nc-0.0.cap'
Loaded 1000000 samples of 19 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4008047, p-hat = 0.50100587500000004, p_u = 0.5014612206989626
	Most Common Value Estimate (bit string) = 0.995790 / 1 bit(s)
Literal MCV Estimate: mode = 980551, p-hat = 0.98055099999999995, p_u = 0.98090671405741858
	Most Common Value Estimate = 0.027812 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.0101022714909456, sigma-hat = 0.10000109056581141, p = 0.99498830604581134
	Collision Test Estimate (bit string) = 0.007249 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.50100587500000004, P_1 = 0.49899412499999996, P_0,0 = 0.50049325781191134, P_0,1 = 0.49950674218808866, P_1,0 = 0.5015204337325615, P_1,1 = 0.4984795662674385, p_max = 3.3471359634370879e-39
	Markov Test Estimate (bit string) = 0.998533 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 1.1266454179293817, sigma-hat = 0.55789888330808113, p = 0.87657345017826427
	Compression Test Estimate (bit string) = 0.031676 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 38606, p-hat_max = 0.99975029051115782, p_u = 0.99976467966995863
Bitstring LRS Estimate: u = 38607, v = 38738, p-hat = 0.99939482492148191, p_u = 0.99941722147431178
	T-Tuple Test Estimate (bit string) = 0.000340 / 1 bit(s)
Literal t-Tuple Estimate: t = 4808, p-hat_max = 0.99834136921182226, p_u = 0.9984461862037306
Literal LRS Estimate: u = 4809, v = 4841, p-hat = 0.99572583475066034, p_u = 0.99589387481490022
	T-Tuple Test Estimate = 0.002243 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.000841 / 1 bit(s)
	LRS Test Estimate = 0.005936 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.3355546440307226 (C = 2680977) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 1.000000 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.98145751457881081 (C = 981045) Plocal = 0.9974334031074803 (r = 4843)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 0.003708 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.99199904126021798 (C = 7935339) Plocal = 0.999678736175865 (r = 38739)
	Lag Prediction Test Estimate (bit string) = 0.000464 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.97036788478458547 (C = 969927) Plocal = 0.99743281337734235 (r = 4842)
	Lag Prediction Test Estimate = 0.003708 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.99590879266796539 (C = 7966800) Plocal = 0.99967877225184698 (r = 38743)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.000464 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.9814546822788246 (C = 981102) Plocal = 0.99743338938782955 (r = 4843)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 0.003708 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.50144003581363839 (C = 4007869) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.995851 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.98145440404366924 (C = 981087) Plocal = 0.99743339276143583 (r = 4843)
	LZ78Y Prediction Test Estimate = 0.003708 / 8 bit(s)

H_original: 0.002243
H_bitstring: 0.000340
min(H_original, 8 X H_bitstring): 0.002243
