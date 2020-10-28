import heapq
from dataclasses import dataclass, field
from typing import Any
import sys

test1 = """3
7 4
2 4 6
8 5 9 3
"""

test2 = """75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
"""

class Node:
    def __init__(self, row, col, value):
        self.row = row
        self.col = col
        self.value = value
    
    def __repr__(self) -> str:
        return "(({},{}), {})".format(self.row, self.col, self.value)

def create_graph(data):
    rows = list(map(lambda x: list(map(int, x.split(' '))), data.splitlines()))
    graph = []
    for row_i in range(len(rows)):
        tagged_row = []
        for col_i in range(len(rows[row_i])):
            tagged_row.append(Node(row_i, col_i, rows[row_i][col_i]))
        graph.append(tagged_row)

    return graph


def neighbours(graph, item):
    row = item.row
    col = item.col
    return [graph[row + 1][col], graph[row + 1][col + 1]]


def is_end_node(graph, item):
    return len(graph) - 1 == item.row


def print_path(item):
    if item is None:
        return ""
    
    return print_path(item.parent) + " " + str(item.item.value)

def final_sum(item):
    if item is None:
        return 0
    
    return final_sum(item.parent) + item.item.value


@dataclass(order=True)
class PrioritizedItem:
    priority: int
    item: Any=field(compare=False)
    parent: Any=field(compare=False)

    def __init__(self, priority, item, parent) -> None:
        self.priority = priority
        self.item = item
        self.parent = parent


if __name__ == "__main__":
    graph = create_graph(test2)

    open_nodes = [PrioritizedItem(priority=0, item=graph[0][0], parent=None)]
    end_nodes = []

    while open_nodes:
        item = heapq.heappop(open_nodes)
        if is_end_node(graph, item.item):
            end_nodes.append(item)
            continue

        for node in neighbours(graph, item.item):
            x = PrioritizedItem(priority=item.priority - node.value,
                                item=node, parent=item)
            heapq.heappush(open_nodes, x)

    maxelem = end_nodes[0]
    for node in end_nodes:
        if final_sum(node) > final_sum(maxelem):
            maxelem = node

    print(print_path(maxelem))
    print(final_sum(maxelem))
