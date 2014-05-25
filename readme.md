#spark-OF-UDP


prototyping connection between [spark.io](spark.io) and [openFrameworks](openframeworks.cc) through UDP  
  
* ~~I'm using [`sparky`](https://bitbucket.org/xoseperez/spark-util/src) command line tools in exact same folder with each OF apps for easy organization~~
* use "makeSymlinks" in sparky folder to symlink to the common directory (for common code)
* separated `OF` and `spark` for each app, and one "common" folder for types / defines. 
* folder structure then should be place on OF root level along side with `/apps` `/examples` `/libs` etc. 