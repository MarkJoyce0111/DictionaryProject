# DictionaryProject
Uni Dictionary Project - Console App - C++
The Release Version uses a vector full of pointers to trace the dictionary entries in the heap. This is very fast.  
The debug and x64 version put all enties into a vector/arrray, effectivly copying them twice. This is very slow.  
Not sure if this was the final effort but it works.  
The VS project code above uses pointers and demonstraits why we use them.
