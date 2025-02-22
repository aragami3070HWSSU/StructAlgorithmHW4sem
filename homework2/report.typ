#import "@preview/plotst:0.2.0": *
#set text(size: 8pt)
= Quick sort
- 50к элементов среднее время: $(0.006605 + 0.006466 + 0.006634 + 0.00663 + 0.008369)/5 = 0.0069408$
- 100к элементов среднее время: $(0.018432 + 0.013913 + 0.013745 + 0.014245 + 0.0135)/5 = 0.014767$
- 500к элементов среднее время: $(0.069496 + 0.069624 + 0.07005 + 0.069337 + 0.06953)/5 = 0.0696074$
- 1кк элементов среднее время: $(0.1429 + 0.142575 + 0.144402 + 0.142696 + 0.143043)/5 =  0.1431232$

= Merge sort
- 50к элементов среднее время: $(0.019703 + 0.019812 + 0.022097 + 0.019986 + 0.019569)/5 = 0.0202334$
- 100к элементов среднее время: $(0.040445 + 0.039564 + 0.039936 + 0.041275 + 0.039936)/5 = 0.0402312$
- 500к элементов среднее время: $(0.214523 + 0.214897 + 0.213808 + 0.214235 + 0.214656)/5 = 0.2144238$
- 1кк элементов среднее время: $(0.444262 + 0.44219 + 0.446082 + 0.441017 + 0.443092)/5 = 0.443328599$

= Heap sort
- 50к элементов среднее время: $(0.013965 + 0.014135 + 0.015639 + 0.015727 + 0.015894)/5 = 0.0150713$
- 100к элементов среднее время: $(0.029228 + 0.029386 + 0.028746 + 0.03008 + 0.029135)/5 = 0.0293149$
- 500к элементов среднее время: $(0.16529 + 0.166195 + 0.164846 + 0.164765 + 0.164619)/5 = 0.16514299$
- 1кк элементов среднее время: $(0.354829 + 0.350469 + 0.34971 + 0.348593 + 0.357868)/5 = 0.3522938$

= Результаты
#table(
  columns: 9,
  stroke: none,
  inset: 10pt,
  align: horizon,
  table.hline(),
  table.header(
    [Сортировка], [$t_(50 k)$], [$t_(с р 50 k)$], [$t_(100 k)$], [$t_(с р 100 k)$],[$t_(500 k)$], [$t_(с р 500 k)$],[$t_(1 k k)$],[$t_(с р 1 k  k)$], 
  ),
  table.hline(),
  table.vline(x: 0),
  table.vline(x: 1),
  table.vline(x: 2),
  table.vline(x: 3),
  table.vline(x: 4),
  table.vline(x: 5),
  table.vline(x: 6),
  table.vline(x: 7),
  table.vline(x: 8),
  table.vline(x: 9),
    // Quick sort
    [], [0.006605], [], [0.018432], [], [0.069496], [], [0.1429], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.006466], [], [0.013913], [], [0.069624], [], [0.142575], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [Quick sort], [0.006634], [0.0069408], [0.013745], [0.014767], [0.07005], [0.0696074], [0.144402], [0.1431232],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.00663], [], [0.014245], [], [0.069337], [], [0.142696], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.008369], [], [0.0135], [], [0.06953], [], [0.143043], [],
  table.hline(),
    // Merge sort
    [], [0.019703], [], [0.040445], [], [0.214523], [], [0.444262], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.019812], [], [0.039564], [], [0.214897], [], [0.44219], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [Merge sort], [0.022097], [0.0202334], [0.039936], [0.0402312], [0.213808], [0.2144238], [0.446082], [0.443328599],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.019986], [], [0.041275], [], [0.214235], [], [0.441017], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.019569], [], [0.039936], [], [0.214656], [], [0.443092], [],
  table.hline(),
    // Heap sort
    [], [0.013965], [], [0.029228], [], [0.16529], [], [0.354829], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.014135], [], [0.029386], [], [0.166195], [], [0.350469], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [Heap sort], [0.015639], [0.0150713], [0.028746], [0.0293149], [0.164846], [0.16514299], [0.34971], [0.3522938],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.015727], [], [0.03008], [], [0.164765], [], [0.348593], [],
  table.hline(start:1, end:2),
  table.hline(start:3, end:4),
  table.hline(start:5, end:6),
  table.hline(start:7, end:8),
    [], [0.015894], [], [0.029135], [], [0.164619], [], [0.357868], [],
  table.hline(),
)

#let graph_plot_test() = {
    let data1 = (
      (0.0069408, 50000), (0.014767, 100000), (0.0696074, 500000), (0.1431232, 1000000)
    )
    let data2 = (
      (0.0202334, 50000), (0.0402312, 100000), (0.2144238, 500000), (0.443328599, 1000000)
    )
    let data3 = (
      (0.0150713, 50000), (0.0293149, 100000), (0.16514299, 500000), (0.3522938, 1000000)
    )
    let x_axis = axis(min: 0, max: 0.5, step: 0.055, location: "bottom", helper_lines: true, title: $t_(c p)$)
    let y_axis = axis(min: 0, max: 1005000, step: 50000, location: "left", helper_lines: true, title: $e l e m$)
    let pl1 = plot(data: data1, axes: (x_axis, y_axis))
    let pl2 = plot(data: data2, axes: (x_axis, y_axis))
    let pl3 = plot(data: data3, axes: (x_axis, y_axis))
    let graphDisplay1 = graph_plot(pl1, (100%, 25%), caption: "График \n Синий: Quick sort \n Красный: Merge sort \n Зеленый: Heap sort", markings: [#circle(radius: 2pt, fill: black)], stroke: blue)
    let graphDisplay2 = graph_plot(pl2, (100%, 25%), markings: [#circle(radius: 2pt, fill: black)], stroke: red)
    let graphDisplay3 = graph_plot(pl3, (100%, 25%), markings: [#circle(radius: 2pt, fill: black)], stroke: green)
    overlay((graphDisplay1, graphDisplay3, graphDisplay2), (100%, 60%))
}

#graph_plot_test()
