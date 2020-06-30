import os, fnmatch

for dir in [x for x in next(os.walk('.'))[1] if x[0] != '.']:
	for subDir in [x for x in next(os.walk(f'./{dir}'))[1] if x[0] != '.']:
		ss = [x for x in next(os.walk(f'./{dir}/{subDir}'))[2] if fnmatch.fnmatch(x, 'snap_screen*')]
		if len(ss) == 1:
			os.rename(f'./{dir}/{subDir}/{ss[0]}', f'./{dir}/{subDir}/res.png')
		elif len(ss) > 1:
			for i, x in enumerate(ss):
				os.rename(f'./{dir}/{subDir}/{x}', f'./{dir}/{subDir}/{i + 1}.png')