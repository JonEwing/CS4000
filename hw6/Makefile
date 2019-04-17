map/reduce: mapper.cc
	g++ -o map mapper.cc -I.
	g++ -o reduce reduce.cc -I.
	cat f.csv | ./map 1| ./reduce