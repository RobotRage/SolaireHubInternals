import os
import time

try:
    import urllib.request as urllib
except ImportError:
    import urllib

oldlines = open('CSGO_Internals\Adresses.h').read().splitlines()
oldversion = oldlines[3] 
time.sleep(0.1)

#Check if it exists, and delete if it does
if (os.path.isfile("Debug\CSGO_Internals.dll")):
	print("SolaireHubInternals exists, deleting...")
	os.remove("Debug\CSGO_Internals.dll")
	time.sleep(0.1)
	#Check again if it was actually deleted
	if (os.path.isfile("Debug\CSGO_Internals.dll")):
		print("Something went wrong, I might not have the right permissions")
	else:
		print("Deleted successfully!")
else:
	print("SolaireHubInternals does not exist, continuing...")
	
time.sleep(0.1)
#Download new file
print("Downloading offsets...")
urllib.urlretrieve ("https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.hpp", "csgo.hpp.tmp")
print("Download complete!")

time.sleep(0.1)
#Edit the file and save changed version
print("Editing old file...")
lines = open('csgo.hpp.tmp').read().splitlines()
lines[2] = '#include <cstddef>'
open('CSGO_Internals\Adresses.h','w').write('\n'.join(lines))
print("Editing complete!")
os.remove("csgo.hpp.tmp")

time.sleep(0.1)
newlines = open('CSGO_Internals\Adresses.h').read().splitlines()
newversion = newlines[3] 
	
time.sleep(0.1)
#Build new version
print("Buliding new boi...")
open('donttouch.bat','w').write(r'''
@echo off
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe" CSGO_Internals.sln /Build
''')
os.system('donttouch.bat')

print("Cleaning up...")
os.remove('donttouch.bat')

time.sleep(0.1)
#Check if it worked
if (os.path.isfile("Debug\CSGO_Internals.dll")):
	print("Build successful!")
	time.sleep(0.1)
	print("Old vs new build dates:")
	print(oldversion)
	print(newversion)
else:
	print("Build failed... please check Visual Studio for errors")

print("")
input("Press enter to exit ")