## Test de la bibliothèque

#Pour un quantum de 0.3 seconde :

PID	FUNCTION	REAL-TIME	CPU-TIME	WAITING-TIME
--------------------------------------------------------------------
0	Function0	1.834s		0.732s		1.102s
1	Function1	1.402s		0.732s		0.670s
2	Function2	0.370s		0.181s		0.189s
3	Function3	0.189s		0.189s		0.000s
--------------------------------------------------------------------
Average:		0.949s		0.459s		0.490s
--------------------------------------------------------------------

#Pour un quantum de 1 seconde :

PID	FUNCTION	REAL-TIME	CPU-TIME	WAITING-TIME
--------------------------------------------------------------------
0	Function0	1.100s		0.727s		0.373s
1	Function1	1.829s		0.729s		1.100s
2	Function2	0.373s		0.181s		0.192s
3	Function3	0.192s		0.192s		0.000s
--------------------------------------------------------------------
Average:		0.873s		0.457s		0.416s
--------------------------------------------------------------------

#Avec RandomElect :

PID	FUNCTION	REAL-TIME	CPU-TIME	WAITING-TIME
--------------------------------------------------------------------
0	Function0	4.926s		2.012s		2.915s
1	Function1	3.257s		1.993s		1.265s
2	Function2	1.132s		0.132s		1.000s
3	Function3	0.749s		0.132s		0.617s
4	Function4	3.387s		0.131s		3.256s
5	Function5	3.021s		0.132s		2.889s
6	Function6	1.127s		0.131s		0.996s
7	Function7	2.155s		0.131s		2.024s
8	Function8	1.655s		0.130s		1.524s
9	Function9	0.620s		0.132s		0.487s
--------------------------------------------------------------------
Average:		2.203s		0.506s		1.697s
--------------------------------------------------------------------

#Avec SJF election :

PID	FUNCTION	REAL-TIME	CPU-TIME	WAITING-TIME
--------------------------------------------------------------------
0	Function0	2.526s		2.004s		0.522s
1	Function1	4.902s		1.982s		2.920s
2	Function2	1.130s		0.130s		1.000s
3	Function3	0.743s		0.130s		0.613s
4	Function4	1.119s		0.131s		0.987s
5	Function5	0.752s		0.130s		0.622s
6	Function6	1.131s		0.131s		1.000s
7	Function7	0.766s		0.131s		0.635s
8	Function8	0.401s		0.131s		0.270s
9	Function9	0.625s		0.131s		0.494s
--------------------------------------------------------------------
Average:		1.410s		0.503s		0.906s
--------------------------------------------------------------------


#Avec APROXSJF election :

PID	FUNCTION	REAL-TIME	CPU-TIME	WAITING-TIME
--------------------------------------------------------------------
0	Function0	3.655s		2.000s		1.656s
1	Function1	4.906s		1.990s		2.915s
2	Function2	2.131s		0.131s		2.000s
3	Function3	1.753s		0.131s		1.622s
4	Function4	1.395s		0.132s		1.262s
5	Function5	1.026s		0.130s		0.895s
6	Function6	0.656s		0.130s		0.526s
7	Function7	1.121s		0.130s		0.991s
8	Function8	0.756s		0.130s		0.625s
9	Function9	0.626s		0.131s		0.495s
--------------------------------------------------------------------
Average:		1.802s		0.504s		1.299s
