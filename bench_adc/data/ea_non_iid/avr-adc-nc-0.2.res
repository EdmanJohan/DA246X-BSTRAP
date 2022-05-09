Opening file: '../bin/adc/avr-adc-nc-0.2.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 16 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4009570, p-hat = 0.50119625000000001, p_u = 0.50165159531717207
	Most Common Value Estimate (bit string) = 0.995242 / 1 bit(s)
Literal MCV Estimate: mode = 960711, p-hat = 0.96071099999999998, p_u = 0.96121143671655052
	Most Common Value Estimate = 0.057074 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.0237955379350403, sigma-hat = 0.15241166682982674, p = 0.98805835694564914
	Collision Test Estimate (bit string) = 0.017332 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.50119625000000001, P_1 = 0.49880374999999999, P_0,0 = 0.49897782030936494, P_0,1 = 0.50102217969063512, P_1,0 = 0.50342519477850756, P_1,1 = 0.49657480522149244, p_max = 5.161243974327228e-39
	Markov Test Estimate (bit string) = 0.993652 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 1.2237178166367477, sigma-hat = 0.63840389791242191, p = 0.86373664433092867
	Compression Test Estimate (bit string) = 0.035223 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 87646, p-hat_max = 0.99990034376246584, p_u = 0.99990943457527837
Bitstring LRS Estimate: u = 87647, v = 91054, p-hat = 0.99974406324633713, p_u = 0.99975863067361259
	T-Tuple Test Estimate (bit string) = 0.000131 / 1 bit(s)
Literal t-Tuple Estimate: t = 10938, p-hat_max = 0.99939305709997373, p_u = 0.9994564965454934
Literal LRS Estimate: u = 10939, v = 11381, p-hat = 0.99817297289588369, p_u = 0.99828297289839363
	T-Tuple Test Estimate = 0.000784 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.000348 / 1 bit(s)
	LRS Test Estimate = 0.002479 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.24215807290888272 (C = 1934130) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 1.000000 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.96121793782470888 (C = 960657) Plocal = 0.99894810965858749 (r = 10973)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 0.001518 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.98482772201302582 (C = 7877727) Plocal = 0.99986843842016793 (r = 87779)
	Lag Prediction Test Estimate (bit string) = 0.000190 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.9322700638027609 (C = 931619) Plocal = 0.99894778838930531 (r = 10970)
	Lag Prediction Test Estimate = 0.001519 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.9925737205173083 (C = 7939959) Plocal = 0.99986844499002936 (r = 87783)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.000190 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.96119446291189303 (C = 960692) Plocal = 0.99894810351867624 (r = 10973)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 0.001518 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.50266803484737954 (C = 4017693) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.992322 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.9611908989343958 (C = 960674) Plocal = 0.99894810502845532 (r = 10973)
	LZ78Y Prediction Test Estimate = 0.001518 / 8 bit(s)

H_original: 0.000784
H_bitstring: 0.000131
min(H_original, 8 X H_bitstring): 0.000784
