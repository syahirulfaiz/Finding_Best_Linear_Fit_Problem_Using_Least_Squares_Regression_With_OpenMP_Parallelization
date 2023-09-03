# Finding_Best_Linear_Fit_Problem_Using_Least_Squares_Regression_With_OpenMP_Parallelization
The simulation of finding the best linear fit using Least Squares Regression with OpenMP Parallelization

## Task ##
Given a set of vectors $X$ and $Y$, we require to find $m$ and $c$ in order to get the best linear fit formula:

$$y = m x + c$$

Following are the formula to find each $m$ and $c$:

$$m=\frac{N\Sigma xy - \Sigma x \Sigma y}{N\Sigma x^2 - (\Sigma x)^2}$$

$$c=\frac{\Sigma y - m \Sigma x }{N}$$

## Result ##

we did five trials each for serial, data-parallelism, and task-parallelism version. For each trial, we assign the minimum execution time as our timings to be compared relative to each version, number of threads, and with the specific region (‘loop region’ or ‘parallel region’). We use these timings for further calculation and comparison in speedup and efficiency.

With regards to the timings, we compare by using execution time in our five trials. We use #threads=1 in both parallel versions to compare with the serial. We compare both ‘whole code’ and ‘loop/parallel region’. As we can see in the [Table 2](#tabletimingsserialvdatavtask), both serial and data-parallelism version have relatively similar execution time. Still, in general, the data-parallelism was faster than the serial one in our trials. Obviously, the task-parallelism has the least execution time among all versions. 

| |i-th trial (seconds)|||||
| :- | :-: | :- | :- | :- | :- |
|WHOLE CODE|1|2|3|4|5|
|SERIAL|7\.058364|7\.127359|7\.030211|7\.02489|7\.036299|
|DATA PARALLELISM|7\.09394|7\.095614|7\.082554|7\.085936|7\.098313|
|TASK PARALLELISM|6\.50269|6\.499319|6\.50337|6\.759964|6\.50204|

<a name="tabletimingsserialvdatavtask"></a>*Table 2: Time Comparison Serial vs Data-Parallelism vs Task-Parallelism WHOLE CODE (1 thread)*

| |i-th trial (seconds)|||||
| :- | :-: | :- | :- | :- | :- |
|LOOP/PARALLEL REGION|1|2|3|4|5|
|SERIAL |7\.050738|7\.125401|7\.028212|7\.022793|7\.035918|
|DATA PARALLELISM |7\.093659|7\.093469|7\.08057|7\.084092|7\.09799|
|TASK PARALLELISM |6\.502509|6\.497315|6\.501378|6\.758227|6\.502016|

*Table 3: Time Comparison Serial vs Data-Parallelism vs Task-Parallelism LOOP/PARALLEL REGION (1 thread)*
![](Aspose.Words.12aa5e9e-e68e-4ffb-8cd1-1de4303ec275.001.png)
