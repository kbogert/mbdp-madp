# Introduction #

Here I'll document the steps to create a visual studio project out of MADP and the problems that come up


# Initial Errors #

After adding all .cpp and .h files to the project, and using a vanilla boost folder, I get 323 errors and 2693 warnings.

The errors are all repeats of the following messages:
  * Cannot instantiate abstract class
  * Ambiguous inheritance of Clone() function
  * "std" a namespace with this name does not exist
  * Dynamic array creation related
  * cannot find "sys/times.h"
  * cannot find "sys/time.h"
  * cannot find "argp.h"
  * cannot find "wordexp.h"
  * isnan not found

I'll document my research and how I solve these errors below

# Cannot instantiate abstract class #

Weird, some classes have a virtual function in them called clone().  These shouldn't be created directory, maybe the compiler is using the wrong file?

http://www.cplusplus.com/forum/general/4153/

http://www.cplusplus.com/forum/general/18806/


# Cannot find "sys/time.h" #

This is a posix header:

http://www.opengroup.org/onlinepubs/000095399/basedefs/sys/time.h.html

Looks like it just contains the timeval struct, in windows that's in winsock2.h

http://msdn.microsoft.com/en-us/library/ms740560(VS.85).aspx


# Cannot find "sys/times.h" #

From cygwin?
http://www.gidforums.com/t-8783.html

Or use this instead?
http://msdn.microsoft.com/en-us/library/4e2ess30(vs.71).aspx

# Cannot find "argp.h" #

A Gnu header, hmm, might just have to include this in the project

http://www.gnu.org/s/libc/manual/html_node/Argp.html

# Cannot find "wordexp.h" #

Another posix header

http://www.opengroup.org/onlinepubs/009695399/basedefs/wordexp.h.html

# isnan not found #

Need to include math.h?
http://stackoverflow.com/questions/570669/checking-if-a-double-or-float-is-nan-in-c

Nope, in VS, the function is called _isnan()
http://msdn.microsoft.com/en-us/library/tzthab44(VS.71).aspx_

# Ambiguous Inheritance of Clone() #

This seems to be caused by a diamond inheritance, will have to study the class heirarchy more to see

http://en.wikipedia.org/wiki/Virtual_inheritance


# "std" a namespace with this name does not exist #

Looks like I just need to include a standard header

http://www.pcreview.co.uk/forums/thread-3170870.php


# Dynamic array creation related #

http://social.msdn.microsoft.com/Forums/en/vclanguage/thread/113e900c-eca1-4bfa-a3fe-31fabb4504d6