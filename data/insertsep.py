import sys
with open("map_rendu",'r+') as inputfile:
	with open("map_sep",'w+') as outputfile:
		for l in inputfile.readlines():
			for c in l.replace("\n",''):
				sys.stdout.write(c + ':')
			print
		outputfile.close()
	inputfile.close()
