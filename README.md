# DTW - Dynamic Time Warping in Python / C (using ctypes)
The Dynamic Time Warping (DTW)[1,2] is a time-normalisation algorithm initially designed to eliminate timing differences between two speech patterns. This normalisation, or correction, is done by warping the time axis of one time series to match the other. The  correction (time warping) makes it easier to compare two signals in a similar way to the method human beings[3].

![DTW example](https://github.com/ricardodeazambuja/DTW/blob/master/dtw_cardioid.png)
*Example of 2D trajectory-matching generated by the DTW method. Although looking perfect in the figure on the left, the cardioid was modified to have a constant value zone from time step $50$ to $150$. The DTW correctly matches the values as can be seen as a straight blue line in the Accumulated Distance plot (right).*

Above is presented an example where a cardioid is compared to a circle. The cardioid also had a time delay inserted (values were kept constant). The DTW calculates the distance (here the Euclidean one) between all the points of the two time series and, then, generates another matrix with the accumulated distances. The total distance defined by the path formed with the minimum values of the accumulated distance (right-hand side of the figure) can be easily applied to compare different shapes. 


This version of the algorithm uses a C kernel, supporting multidimensional arrays and Euclidean distance, to speed up the calculations with a Python wrapper as the user interface. More details and sample code can be found in this Jupyter notebook:  
- [Dynamic_Time_Warping.ipynb](https://github.com/ricardodeazambuja/DTW/blob/master/Dynamic_Time_Warping.ipynb)

if you are not happy with my explanations above, one of the best explanations about how the DTW works I've found on a [presentation by Elena Tsiporkova](http://www.mathcs.emory.edu/~lxiong/cs730_s13/share/slides/searching_sigkdd2012_DTW.pdf).

## Related works:  
- [Graceful Degradation under Noise on Brain Inspired Robot Controllers](https://github.com/ricardodeazambuja/ICONIP2016)
- [Diverse, Noisy and Parallel: a New Spiking Neural Network Approach for Humanoid Robot Control](https://github.com/ricardodeazambuja/IJCNN2016)
- [Short-Term Plasticity in a Liquid State Machine Biomimetic Robot Arm Controller](https://github.com/ricardodeazambuja/IJCNN2017)
- [Neurorobotic Simulations on the Degradation of Multiple Column Liquid State Machines](https://github.com/ricardodeazambuja/IJCNN2017-2)
- [Sensor Fusion Approach Using Liquid StateMachines for Positioning Control](https://github.com/ricardodeazambuja/I2MTC2017-LSMFusion)


## References:
1. Sakoe, H., and S. Chiba. “Dynamic Programming Algorithm Optimization for Spoken Word Recognition.” IEEE Transactions on Acoustics, Speech and Signal Processing 26, no. 1 (February 1978): 43–49.
2. Meinard Müller. “Dynamic Time Warping.” In Information Retrieval for Music and Motion, ch. 4, 69-82. New York: Springer-Verlag, 2007.
3. Ratcliff, Roger. “Continuous versus Discrete Information Processing: Modeling Accumulation of Partial Information.” Master Thesis, Radboud University Nijmegen, 2004.  


http://ricardodeazambuja.com/

