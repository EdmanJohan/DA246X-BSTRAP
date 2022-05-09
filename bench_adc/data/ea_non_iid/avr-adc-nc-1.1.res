Opening file: '../bin/adc/avr-adc-nc-1.1.cap'
Warning: Symbols appear to be narrower than described.
Loaded 1000000 samples of 16 distinct 8-bit-wide symbols
Number of Binary Symbols: 8000000

Symbols have been translated.

Running non-IID tests...

Running Most Common Value Estimate...
Bitstring MCV Estimate: mode = 4039256, p-hat = 0.50490699999999999, p_u = 0.50536232469159781
	Most Common Value Estimate (bit string) = 0.984610 / 1 bit(s)
Literal MCV Estimate: mode = 852835, p-hat = 0.85283500000000001, p_u = 0.85374754033932676
	Most Common Value Estimate = 0.228119 / 8 bit(s)

Running Entropic Statistic Estimates (bit strings only)...
Bitstring Collision Estimate: X-bar = 2.0863762482725456, sigma-hat = 0.28091887189687437, p = 0.95496883487925888
	Collision Test Estimate (bit string) = 0.066474 / 1 bit(s)
Bitstring Markov Estimate: P_0 = 0.50490699999999999, P_1 = 0.49509300000000001, P_0,0 = 0.49744643504804725, P_0,1 = 0.5025535649519528, P_1,0 = 0.51251532540351008, P_1,1 = 0.48748467459648992, p_max = 1.9517053753138477e-38
	Markov Test Estimate (bit string) = 0.978660 / 1 bit(s)
Bitstring Compression Estimate: X-bar = 1.7363660455400207, sigma-hat = 1.028379184807577, p = 0.79177390542683734
	Compression Test Estimate (bit string) = 0.056140 / 1 bit(s)

Running Tuple Estimates...
Bitstring t-Tuple Estimate: t = 42733, p-hat_max = 0.99978137775639908, p_u = 0.99979484168525934
Bitstring LRS Estimate: u = 42734, v = 42865, p-hat = 0.99945327746763135, p_u = 0.99947456556500303
	T-Tuple Test Estimate (bit string) = 0.000296 / 1 bit(s)
Literal t-Tuple Estimate: t = 5324, p-hat_max = 0.99856825024015961, p_u = 0.99866564592886053
Literal LRS Estimate: u = 5325, v = 5357, p-hat = 0.99613940081730323, p_u = 0.99629913751913546
	T-Tuple Test Estimate = 0.001926 / 8 bit(s)
	LRS Test Estimate (bit string) = 0.000758 / 1 bit(s)
	LRS Test Estimate = 0.005349 / 8 bit(s)

Running Predictor Estimates...
Bitstring MultiMCW Prediction Estimate: N = 7999937, Pglobal' = 0.4355955532642467 (C = 3481125) Plocal can't affect result (r = 7)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = 1.000000 / 1 bit(s)
Literal MultiMCW Prediction Estimate: N = 999937, Pglobal' = 0.85374630087255787 (C = 852780) Plocal = 0.99770081601431049 (r = 5359)
	Multi Most Common in Window (MultiMCW) Prediction Test Estimate = 0.003321 / 8 bit(s)
Bitstring Lag Prediction Estimate: N = 7999999, Pglobal' = 0.94114232278065613 (C = 7527420) Plocal = 0.99971224151969673 (r = 42866)
	Lag Prediction Test Estimate (bit string) = 0.000415 / 1 bit(s)
Literal Lag Prediction Estimate: N = 999999, Pglobal' = 0.7709340118156961 (C = 769849) Plocal = 0.9976994031321913 (r = 5356)
	Lag Prediction Test Estimate = 0.003323 / 8 bit(s)
Bitstring MultiMMC Prediction Estimate: N = 7999998, Pglobal' = 0.97066256342193413 (C = 7764066) Plocal = 0.99971231457362719 (r = 42876)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = 0.000415 / 1 bit(s)
Literal MultiMMC Prediction Estimate: N = 999998, Pglobal' = 0.85367044501508016 (C = 852756) Plocal = 0.99770080359675473 (r = 5359)
	Multi Markov Model with Counting (MultiMMC) Prediction Test Estimate = 0.003321 / 8 bit(s)
Bitstring LZ78Y Prediction Estimate: N = 7999983, Pglobal' = 0.50793837450722712 (C = 4059856) Plocal can't affect result (r = 7)
	LZ78Y Prediction Test Estimate (bit string) = 0.977275 / 1 bit(s)
Literal LZ78Y Prediction Estimate: N = 999983, Pglobal' = 0.8536921877128385 (C = 852765) Plocal = 0.9977008066501819 (r = 5359)
	LZ78Y Prediction Test Estimate = 0.003321 / 8 bit(s)

H_original: 0.001926
H_bitstring: 0.000296
min(H_original, 8 X H_bitstring): 0.001926
