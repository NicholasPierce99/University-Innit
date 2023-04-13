all written work in class files


run to setup rmi 

ps eaf | grep rmiregistry
rmiregistry 5697 &

I was doing all of this by hand on the command line without an IDE, so I simply used javac *.java for compiling, I know the rubric requested a makefile and I can make one if necessary, though I thought this was much easier.
I did make the two jar files, they did work for me but if they do not work, after compiling run java RemoteHotel (run this first) for the back server and for the UI server run java HotelDriver