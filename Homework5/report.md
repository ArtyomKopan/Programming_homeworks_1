1) В первой части эксперимента в АВЛ-дерево добавлялись случайные элементы, которые генерировались с помощью функции rand(). После каждой операции добавления элемента вычислялся максимум отношения height(tree) / log2(count_elements(tree)). При этом значения максимума при количестве элементов в дереве <= 100 не учитывались.
В итоге максимум оказался равен 1.280446.

2) Во второй части эксперимента в АВЛ-дерево добавлялись элементы по возрастанию (от 0 до 1000). После каждой операции добавления элемента вычислялся максимум отношения height(tree) / log2(count_elements(tree)). При этом значения максимума при количестве элементов в дереве <= 100 не учитывались.
В итоге максимум оказался равен 1.142857.

По результатам эксперимента можно сделать вывод: отношение высоты АВЛ-дерева к количеству элементов в нём при добавлении элементов по возрастанию меньше, чем при добавлении случайных элементов.
