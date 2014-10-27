#CDN

##Ejecutar
```rm main ; clear ; make```

##Gráficos

  ###Querys

  - Ver gráfico
  ```gnuplot query_charts.plot -p```
  - query_charts.plot
  ```plot "query_chart" with lines```

##Grafos
 ###Mostrar Grafo Simulador:
 	dot ./grafo.dot -o ./grafodot && xdot ./grafodot
 	dot ./grafo.dot -o ./grafodot && xdot -f "neato" ./grafodot

  ###Grafo Archivos:
   ```
    perl grafo.pl --quotetypes=quote >> grafo/grafo.dot
    dot grafo/grafo.dot -o grafo/grafo
    xdot grafo/grafo
    perl grafo.pl --quotetypes=quote >> ./grafo/grafo.dot && dot  ./grafo/grafo.dot -o ./grafo/grafo && xdot ./grafo/grafo
    ```
