# Pluton Project Generator
--------------------------

A simple command line project generator to make the files I make every time I
make a project.

##### Running / use

To use it simply use the following command in the directory you wish to generate
in:  
``ppg``

alternatively you can pass in the path to the project:  
``ppg <directory>``

If you want to add more default files or modify how a specific file is generated
you can modify or add files into the templates directory

template variables (replaced with actual values):  
``$$PROJECT_NAME$$`` - the name of the project  
``$$PROJECT_ALIAS$$`` - the alias for the project (the name used for filenames)

to use these in filenames simply include in your filename the variable
(excluding the $$)  
I.E.:   
``PROJECT_NAME.cpp``   
``somethingPROJECT_NAMEsomethingelse.h``

##### Building

To build the project you will need C++ and make.  Once you have those you can
simply use:   
``make``
