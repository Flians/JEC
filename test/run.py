#!/usr/local/bin/python3
import os
import subprocess

def benchmarks(exePath, root='./', output='./output/'):
    golden = os.path.join(root, 'golden')
    revise = os.path.join(root, 'revise')
    files = os.listdir(os.path.join(root, 'original'))
    if not os.path.exists(os.path.join(root, 'log')):
        os.mkdir(os.path.join(root, 'log'))
    for i, file in enumerate(files):
        names = file.split('.')
        if (file.endswith('.bench') and names[0]!='c17' and names[0]!='c2670' and names[0]!='c6288') or (file.endswith('.blif') and names[0]!='square' and names[0]!='sqrt' and names[0]!='divisor' and names[0]!='multiplier' and names[0]!='log2') or names[0]=='one_bit_full_adder' :
            with open(os.path.join(root, 'log/'+names[0]+'.txt'), 'w', encoding='utf8') as log:
                cmd = [exePath, os.path.join(golden, 'gf_'+names[0]+'.v'), os.path.join(revise, 'rf_'+names[0]+'.v'), os.path.join(output, 'output_' + names[0] + '.txt'), 'CONE', 'i', 'm']
                p = subprocess.Popen(cmd, shell=False, bufsize=0, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                while p.poll() is None:
                    nextline = p.stdout.readline()
                    log.write(nextline.decode())
                    log.flush()
                if p.returncode == 0:
                    print(names[0] + ' success!')
                else:
                    print(names[0] + ' failed!')


benchmarks('../build/JEC')
