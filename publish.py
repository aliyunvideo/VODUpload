#!/usr/bin/env python


import os,sys

spec = 'VODUpload.podspec'

if len(sys.argv) == 0:
    print('please input version')
else:
    version = sys.argv[1]
    with open(spec) as f:
        lines = f.readlines()
        for i in range(len(lines)):
            if lines[i].find('s.version      =') != -1:
                lines[i] = "  s.version      = \"" + version + "\"" + "\n"
        f.close
    
    
    with open(spec,'w+') as wf:
        wf.writelines(lines)
        wf.close

    tag = "git tag -a "+version+" -m '"+version+"'" 
    trunk = 'pod trunk push ' + spec +  ' --verbose' + ' --allow-warnings'

    os.system('git add .')
    os.system('git commit -m release')
    os.system('git push')
    os.system(tag)
    os.system('git push --tags')
    os.system(trunk)
    
    













    














