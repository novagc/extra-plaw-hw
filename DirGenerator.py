import os
temp = [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r', encoding='utf-8').readlines()]
inDir = ''
for dir in temp:
	if dir[0] == '-':
		dir = dir[1:]
		if not os.path.exists(f'./{dir}'):
			os.mkdir(f'./{dir}')
		inDir = dir
	else:
		if not os.path.exists(f'./{inDir}/{dir}'):
			os.mkdir(f'./{inDir}/{dir}')
		if not os.path.exists(f'./{inDir}/{dir}/Source.cpp'):
			open(f'./{inDir}/{dir}/Source.cpp', 'w').close()