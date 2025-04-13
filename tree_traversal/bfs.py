from collections import deque
from typing import List, Optional


class TreeNode:
    def __init__(self, val: int, left: Optional['TreeNode'] = None,
                 right: Optional['TreeNode'] = None) -> None:
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        res = []

        if None == root:
            return res

        node_queue = deque()
        node_queue.append(root) # push to back
        curr_level_node_cnt = 1
        next_level_node_cnt = 0
        res.append([])

        while 0 != len(node_queue):
            curr = node_queue.popleft() # remove and return
            curr_level_node_cnt -= 1
            res[-1].append(curr.val)

            if None != curr.left:
                node_queue.append(curr.left)
                next_level_node_cnt += 1

            if None != curr.right:
                node_queue.append(curr.right)
                next_level_node_cnt += 1

            if 0 == curr_level_node_cnt:
                curr_level_node_cnt = next_level_node_cnt
                next_level_node_cnt = 0

                if curr_level_node_cnt > 0:
                    res.append([])

        return res
