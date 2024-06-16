import torch
import torch.nn.functional as F
from typing import List


def random_tensors(shape: List, num: int = 1, requires_grad: bool = False):
    tensors = [torch.randn(shape, requires_grad=requires_grad) for _ in range(num)]

    return tensors[0] if 1 == num else tensors

