import sys

def add(arr, what):
	arr.append(what)
	return arr
	

def	main():
	av = sys.argv
	ac = len(av)
	arr = []
	arr = add(arr, "bla");
	print(arr)

main()
