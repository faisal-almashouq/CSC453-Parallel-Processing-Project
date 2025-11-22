This is a project for my CSC453 Parallel Processing course. Acknowledgement: Thank you Dr. Sofien Gannouni for this opportunity.

You can read the journal for this project on this google docs link:
https://docs.google.com/document/d/1yXXVxGknHjpkKU-PKfMZc-pyPwdt-9pch3542H3eBUU/edit?tab=t.0

Note: To run .cu file, you must have the following:
nvcc compiler (MSVC)
cl (CUDA kit)

This tiny piece of information took me 2 hours to learn and understand.


The structure of the project:
bitonicsort.c -> language c file with no CUDA parallelism
bitonicsort.cu -> language cu file with CUDA parallelism
