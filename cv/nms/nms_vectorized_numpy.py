import numpy as np

def nms(boxes: np.array, scores: np.array, iou_thres: float):
    # sort the box indices in descreasing order of score
    sorted_idx = np.argsort(scores)[::-1]
    picked_boxes = []

    while len(sorted_idx) > 0:
        best_idx = sorted_idx[0]
        picked_boxes.append(boxes[best_idx, :])

        other_boxes = boxes[sorted_idx[1:]]
        print(f'other_boxes.size {len(other_boxes)}')
        iou = calculate_iou(boxes[best_idx], other_boxes)

        print(f'iou size {iou.shape}')
        print(iou)

        sorted_idx = sorted_idx[1:][iou < iou_thres]

        print(f'sorted_idx size: {len(sorted_idx)}')


    return picked_boxes



def calculate_iou(box: np.array, other_boxes: np.array):
    '''
    box: shape (4,)
    other_boxes: shape (N, 4)
    '''
    assert box.shape == (4,), "box's shape must be of (4, )"
    assert other_boxes.shape[1] == 4, "other_boxes's shape must be of (N, 4)"

    x_tl, y_tl, x_br, y_br = box

    # x_tl_o is of shape (N,)
    x_tl_o, y_tl_o, x_br_o, y_br_o = other_boxes.T

    x_tl_inter = np.maximum(x_tl, x_tl_o) # (N,)
    y_tl_inter = np.maximum(y_tl, y_tl_o) # (N,)

    x_br_inter = np.minimum(x_br, x_br_o) # (N,)
    y_br_inter = np.minimum(y_br, y_br_o) # (N,)

    inter_area = np.maximum(0.0, x_br_inter - x_tl_inter) * np.maximum(0.0, y_br_inter - y_tl_inter)

    box_area = (x_br - x_tl) * (y_br - y_tl)
    box_areas_other = (x_br_o - x_tl_o) * (y_br_o - y_tl_o) # (N,)

    return inter_area / (box_area + box_areas_other - inter_area + 1e-9)


# Test cases
def test_nms():
    # Test case 1: Basic case
    boxes = np.array([[100, 100, 200, 200],
                      [120, 120, 220, 220],
                      [300, 300, 400, 400]])
    scores = np.array([0.9, 0.8, 0.7])
    threshold = 0.5
    assert len(nms(boxes, scores, threshold)) == 1

    # Test case 2: No overlapping boxes
    # boxes = np.array([[100, 100, 200, 200],
    #                   [300, 300, 400, 400]])
    # scores = np.array([0.9, 0.8])
    # threshold = 0.5
    # assert len(nms(boxes, scores, threshold)) == 2

    # Test case 3: All overlapping boxes
    # boxes = np.array([[100, 100, 200, 200],
    #                   [120, 120, 220, 220]])
    # scores = np.array([0.9, 0.8])
    # threshold = 0.5
    # assert len(nms(boxes, scores, threshold)) == 1

    # Add more test cases as needed...

# Run the test cases
test_nms()

# Test case
# boxes = np.array([[100, 100, 200, 200], [150, 150, 250, 250], [300, 300, 400, 400]])
# scores = np.array([0.9, 0.75, 0.8])
# threshold = 0.5
#
# # Expected output: Only the first box should be picked since the second and third boxes are overlapped with the first one
# expected_picked_boxes = np.array([[100, 100, 200, 200]])
#
# # Run NMS
# picked_boxes = np.array(nms(boxes, scores, threshold))
#
# # Check if the output matches the expected output
# assert np.array_equal(picked_boxes, expected_picked_boxes), "Test failed: NMS did not produce the expected output."
#
# print("Test passed: NMS produced the expected output.")
