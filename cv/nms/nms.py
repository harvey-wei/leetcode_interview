# class Box:
#     def __init__(self, x_tl : float, y_tl : float,
#                  x_br : float, y_br : float, score : float) -> None:
#         self.x_tl = x_tl
#         self.y_tl = y_tl
#         self.x_br = x_br
#         self.y_br = y_br
#         self.score = score

import numpy as np
from functools import cmp_to_key

def get_iou(box_one : np.ndarray, box_two : np.ndarray):
    x_inter_tl = max(box_one[0], box_two[0])
    y_inter_tl = max(box_one[1], box_two[1])

    x_inter_br = min(box_one[2], box_two[2])
    y_inter_br = min(box_one[3], box_two[3])

    inter_area = max(0.0, x_inter_br - x_inter_tl) * max(0.0, y_inter_br - y_inter_tl)
    one_area = (box_one[2] - box_one[0]) * (box_one[3] - box_one[1])
    two_area = (box_two[2] - box_two[0]) * (box_two[3] - box_two[1])

    eps = 1e-9
    iou = inter_area / (one_area + two_area - inter_area + eps)

    return iou

def nms(boxes: list, iou_thres: float):
    # boxes is of shape (N, 5)
    # boxes[4] is the score

    # https://numpy.org/doc/stable/reference/generated/numpy.sort.html
    # sort along axis means sorting across that axis
    # sorte a MxN array, axis = 0 means accros rows -> sort each column.
    # while axis = 1 means crossing columns -> sort each row

    # boxes[:, 4] is of shape (N,) and sort in increasing order and then reverse
    # sorted_idx = np.argsort(boxes[:, 4])[::-1]

    sorted_idx = sorted(range(len(boxes)), key=lambda i : boxes[i][4], reverse=True)

    picked_boxes = []
    while len(sorted_idx) > 0:
        best_idx = sorted_idx[0]
        picked_boxes.append(boxes[best_idx])

        sorted_idx = [i for i in sorted_idx[1:] if get_iou(boxes[best_idx, i] <= iou_thres)]

    return picked_boxes


if __name__ == '__main__':
    pass
