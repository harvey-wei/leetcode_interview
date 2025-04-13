import numpy as np

def nms(boxes, scores, threshold):
    if len(boxes) == 0:
        return []

    # Sort boxes based on their scores in descending order
    indices = np.argsort(scores)[::-1]

    picked_boxes = []
    while len(indices) > 0:
        # Pick the box with the highest score
        best_index = indices[0]
        picked_boxes.append(boxes[best_index])

        # Compute IoU (Intersection over Union) with the picked box
        box = boxes[best_index]
        other_boxes = boxes[indices[1:]]
        iou = calculate_iou(box, other_boxes)

        # Discard boxes with IoU higher than the threshold
        indices = indices[1:][iou < threshold]

    return picked_boxes

def calculate_iou(box: np.array, other_boxes: np.array):
    '''
    box: (4,)
    other_boxes: (N, 4)
    '''
    x_tl, y_tl, x_br, y_br = box

    x_tl_o, y_tl_o, x_br_o, y_br_o = other_boxes.T # (4, N)

    # Calculate intersection area of box to all the other boxes
    # np.maxiumum is elemement-wsie maximum
    # np.max is similiar to python max
    x_tl_i = np.maximum(x_tl, x_tl_o) # (N, )
    y_tl_i = np.maximum(y_tl, y_tl_o) # (N, )
    x_br_i = np.minimum(x_br, x_br_o) # (N, )
    y_br_i = np.minimum(y_br, y_br_o) # (N, )

    # intersection_area (N, )
    intersection_area = np.maximum(x_br_i - x_tl_i, 0) * np.maximum(y_br_i - y_tl_i, 0)

    # Calculate areas of each box
    box_area = (x_br - x_tl) * (y_br - y_tl)

    # (N,) * (N,) -> (N,)
    other_box_area = (x_br_o - x_tl_o) * (y_br_o - y_tl_o)

    # Calculate Union area
    union_area = box_area + other_box_area - intersection_area

    # Calculate IoU
    iou = intersection_area / np.maximum(union_area, 1e-10)

    return iou

# # Example usage:
# boxes = np.array([[100, 100, 200, 200], [150, 150, 250, 250], [300, 300, 400, 400]])
# scores = np.array([0.9, 0.75, 0.8])
# threshold = 0.0
#
# picked_boxes = nms(boxes, scores, threshold)
# print(picked_boxes)



# Test case
boxes = np.array([[100, 100, 200, 200], [150, 150, 250, 250], [300, 300, 400, 400]])
scores = np.array([0.9, 0.75, 0.8])
threshold = 0.5

# Expected output: Only the first box should be picked since the second and third boxes are overlapped with the first one
expected_picked_boxes = np.array([[100, 100, 200, 200]])

# Run NMS
picked_boxes = np.array(nms(boxes, scores, threshold))

# Check if the output matches the expected output
assert np.array_equal(picked_boxes, expected_picked_boxes), "Test failed: NMS did not produce the expected output."

print("Test passed: NMS produced the expected output.")
