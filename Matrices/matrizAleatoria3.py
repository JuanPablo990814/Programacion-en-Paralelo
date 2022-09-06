import numpy as np
import sys
size = int(sys.argv[1])
a=np.random.randint(9, size=(size, size))
for i in a:
    for j in i:
        print (j,end=''+" 	")
    print ("")
#python3 ./randomMatrix_python3.py tamañomatriz > nombrearchivo.txt
