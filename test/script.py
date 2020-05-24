import os

def rename(root, prefix):
    files = os.listdir(root)
    for i, file in enumerate(files):
        print(file)
        if file.find('_') != -1:
            NewName = os.path.join(root, prefix + '_'.join(file.split('_')[1:]))
            OldName = os.path.join(root, file)
            os.rename(OldName, NewName)


def createBW(root, output, scom):
    files = os.listdir(root)
    for i, file in enumerate(files):
        names = file.split('.')
        if file.endswith('.bench'):
            print('read_bench ' + file + '\nstrash\n' + scom +
                  '\nread_library rsfq.genlib\nmap\nwrite_verilog ' + output + '/' + names[0] + '.v\nquit\n')


def upCell(root):
    files = os.listdir(root)
    for i, file in enumerate(files):
        names = file.split('.')
        if file.endswith('.bench'):
            NewName = os.path.join(root,file+'_')
            OldName = os.path.join(root, file)
            with open(OldName, 'r', encoding='utf8') as oldf, open(NewName, 'w', encoding='utf8') as nowf:
                line = oldf.readline()             # 调用文件的 readline()方法
                while line:
                    if line.find('=') != -1:
                        cell = line[line.find('=')+1:line.find('(')].strip().upper()
                        nowf.write(line[:line.find('=')] + '= ' + cell + line[line.find('('):])
                    else:
                        nowf.write(line)
                    line = oldf.readline()
            os.remove(OldName)
            os.rename(NewName, OldName)

#rename('./revise', 'rf_')
rename('./golden', 'gf_')
#createBW('original', '../revise', 'resyn2')
#upCell('original')

