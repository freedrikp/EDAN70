In this folder we have four programs that we have developed. In order to use our clasifier which is a program of it's own, some other programs Awill need to be run before.

The first program to run is parsermain. It expects one argument and that is the file which contains raw laser range data. parsermain will parse this and output files into the plots and datasets direcotories. plots contains files that can be parsed by matlab in order to plot the measurements and datasets output files that can be parsed by our own programs. When executing parsermain one must enter the angle of the start and end and maximum distance of the points to be included.

The next program to run is linetest. linetest expects three arguments: the size of the bounding box for lines and the angles in degrees for the limit of two parallell lines and for two perpendicular. linetest iterates throught the directories yes and no in order to identify lines. The directories contains examples classified with yes and no. Files in these directories has to be manually classified and moved from the datasets folder. linetest will output a WEKA arrf format file which can be parsed by our decision tree program.

The next program to run is the EDAN70 program located in the subdirectory decision_trees. This program expects two arguments, the file to parse ( the WEKA arrf file) and how positive examples are classified, in our case this is yes. This program will output a decision tree in the console. This output should be redirected into a file.

Finally one can run our offline classifier program. This is called classifier and expects five arguments: the name of the file containing the decision tree, the name of the dataset file to classify as well as the three tolerance thresholds described above. This program outputs a simple yes or no depending on the decision tree and what the tree is trained to classify.

In this folder we have already run these things so the yes and no directories do contain files and there is a file containing a decision tree, called tree.txt.

All programs are compiled by using the Makefile except the EDAN70 program which is coded in java. This have to be compiled on it's own by including the ssj.jar file. This is done like this: javac -cp .:ssj.jar decision trees/*.java and then it can be run like this: java -cp .:ssj.jar decision trees.EDAN70.
