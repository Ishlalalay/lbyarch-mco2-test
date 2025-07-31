Demo: https://drive.google.com/file/d/18OOY5YtBLyt2-bvvxPcToPYk-RELsnCt/view?usp=drivesdk

In terms of execution time, it was mainly the method of displaying the results which had a noticable outcome to running time.

Based on the test cases provided in the folder, the average running time of the 1000x1000 test is ~0.042(0.041566666666667) seconds with the times below as the different runs.
It is the only one here as the other test cases times were all 0.

If one were to use printf rather than printing straight to a file using fprintf, it would increase the running times, ~0.087(0.088666666666667) secods, roughly taking twice as long.
After completing 30 consecutive runs using printf instead of fprintf, it took around 18 minutes just for printf to be rendered.
While fprintf which took under around 2 seconds to complete running and creating a file with the output.

Running time for 1000x1000 - fprintf into a file

0.031
0.035
0.038
0.051
0.043
0.048
0.039
0.031
0.043
0.034
0.039
0.044
0.054
0.041
0.039
0.054
0.046
0.040
0.046
0.045
0.033
0.038
0.047
0.040
0.038
0.037
0.048
0.037
0.044
0.044 | avg time = ~0.042(0.041566666666667)

Running time for 1000x1000 - printf into command line (which under circumstances with large inputs, would truncate earlier values)

0.089
0.115 
0.093 
0.086 
0.106 
0.084 
0.082 
0.066 
0.089 
0.083 
0.095 
0.093 
0.092 
0.094 
0.085 
0.082 
0.093 
0.086 
0.082 
0.082 
0.105 
0.080 
0.092 
0.084 
0.091 
0.082 
0.084 
0.090 
0.097 
0.078 | avg time = ~0.087(0.088666666666667)
