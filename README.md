# flooding antivirus softwares via functions by hash

Now I will explain, where did i get hash ("061b4792d0612137b3580832cc6ba7ba").<br>

Step first: Go to the MSDN and we need to find a function description.<br>

Step second: After we found the name of the function, which loads from the dll and the name of dll (IsDebuggerPresent and Kernel32.dll).<br>

Step three: we go to the http://www.md5.cz and paste there a name of our function (IsDebuggerPresent) and we will get 061b4792d0612137b3580832cc6ba7ba.<br>

if you cant rename a.c you dont get to use. <3
