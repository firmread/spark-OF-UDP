#spark-OF-UDP
prototyping connection between [spark.io](spark.io) and [openFrameworks](openframeworks.cc) through UDP  
  
* ~~I'm using [`sparky`](https://bitbucket.org/xoseperez/spark-util/src) command line tools in exact same folder with each OF apps for easy organization~~
* terrible idea combining them together both `xcode` and `sparky` hate each other (or actually they love each other too much, since they seems to care enough to try to compile stuffs that they shouldn't touch)
* separated `OF` and `spark` for each app
* folder structure then should be place on OF root level along side with `/apps` `/examples` `/libs` etc. 