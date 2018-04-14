crf_learn -p2 -f 3 -c 4.0 template trainData model
crf_test -m model testData >> outputData

crf_learn -a MIRA -f 3 template trainData model
crf_test -m model testData

rm -f model
