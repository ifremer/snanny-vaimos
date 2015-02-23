import time
import datetime
import string
import re
import os



target_directory= "/home/isi-projets/sensorNanny/data/archive/vaimos/swe/obs/tmp"
####
for root, dirs, filenames in os.walk(target_directory):
  for f in filenames:
     print f
     with open(root + '/output/' + f, "wt") as fout:     
       with open(root + '/' + f, "rt") as fin:
         for line in fin:
	   foundPatList = re.findall('[A-Z][a-z][a-z] [A-Z][a-z][a-z] .[0-9] [0-9][0-9]:[0-9][0-9]:[0-9][0-9] [0-9][0-9][0-9][0-9]', line)
  	   for pat in foundPatList:
	     dt_start = datetime.datetime.strptime(pat, "%a %b %d %H:%M:%S %Y")
             print pat, dt_start.isoformat()
             line= line.replace(pat, dt_start.isoformat())
	   fout.write(line)
       fin.close()
     fout.close()
     #break

    
