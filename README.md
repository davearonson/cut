Very lightweight and easy to use C Unit Test framework

This was inspired by my second-favorite plain-old-C unit testing framework,
CuTest.  It had a few shortcomings.  Nothing bad enough to be really a
"problem" per se, but I thought it lacked certain features I'd like to have:
arguments on the user-supplied messages, exit status indicating success or
failure, choice of what to do on failure, and dealing with not only equality
but also such factors as order, string containment, etc.  I also thought the
function/macro names were overly long.  Lastly, I didn't think it really needed
all that organizing into suites and such, and the techniques of setting
longjump targets and so on weren't really needed either, IMHO, as a simple
macro could just invoke "return".

So, I decided to roll my own, with the aim of making it as simple and
lightweight as possible, while fixing the shortcomings of CuTest.  CUT is the
result, cobbled together in the spare time of a few weeks.

Files:

 - cut.c, the code of the harness itself.

 - cut.h, the header file you include in your code

 - cut_PRIVATE.h, further headers you don't need to grok, but do need to have; they get included automagically by cut.h

 - Makefile, the, uh, makefile, in case you didn't guess ;-) -- note how it includes testing CUT automagically when it's built!

 - cut_test.c, using CUT to test CUT itself

 - example.c, an example of how to use CUT in a more general way

It's rather rough at this time.  If you have any suggestions (other than
documentation, which is in progress), feel free to email me... or now that it's
on Github, fork it and submit a patch!
