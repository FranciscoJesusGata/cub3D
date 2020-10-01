# This is a script to build and run the the pft_2019 (https://github.com/cclaude42/PFT_2019) (could be use for the normal pft(https://github.com/gavinfielder/pft.git))
# Script created by fgata-va (Github: https://github.com/FranciscoJesusGata)

if [ ! -d "pft_2019" ]; then
	echo "pft_2019 isn't installed"
	git clone https://github.com/gavinfielder/pft.git pft_2019 && echo "pft_2019/" >> .gitignore
	cd pft_2019
	rm unit_tests.c
	rm options-config.ini
	git clone https://github.com/YulonSil/PFT_2019.git temp
	cp temp/unit_tests.c .
	cp temp/options-config.ini .
	rm -rf temp
fi
make re
make clean
make all -C pft_2019
if [ ! -f "pft_2019/test" ]; then
	echo "Error: the test executable didn't compiled"
	exit 0
fi

if [ $# -gt 0 ]; then
	./pft_2019/test $1
	if [ -f "results.txt" ]; then
		cat results.txt
	else
		echo "All tests passed"
	fi
else
	./pft_2019/test
	if [ -f "results.txt" ]; then
		echo "Too see results execute: cat results.txt. On the current directory"
	fi
fi
rm -f history.csv test.libc test.mine

exit
