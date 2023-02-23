Progression:

When I first started this project I was determined to write it in C to get familiar with coding in the C language as it is by far
my weakest language. Sadly, I was not able to complete that goal has I greatly underestimated how little I had retained. So I switched to C++ and with it had to re-write my Makefile. In order to compile the make you will need to compile it using the "make all clean" command. This will generate 2 executables, OSS and Worker.

Syntax to run the project:

./oss -h -n [#] -s [#] -t [#]

run ./oss for more detail on syntax and what each tak does.

Difficulties:

I struggled with what seemed like the simplesest concepts of writing this project and worked on it up to the very last minute. Thanks to a fellow classmate explaining to be what argc and argv stood for I was finally able to make large progress on the last day and able to complete this project on time. Another issue I ran into was that there is not a good easy way to convert an integer to a string as C seems to not like strings. Once I figured out how to accomplish that conversion to allow the argument to be passed in the exec it was smooth sailing from there. Finally, the last hardship was figuring out how to kill all the child processes that would have ended up orphans. I found an article on stackoverflow that showed a way to do it using socketpair() however I felt that making my own way of keeping track would have been better practice so that is what I ended up doing. In conclusion this project was hard to make for me but I understand the concept of what we were trying to achive and have a good grasp on how fork and exec work now.

-Matthew Knibb
# OSproject2
