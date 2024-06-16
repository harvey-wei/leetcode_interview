import torch
import torch.nn as nn
import math



# https://github.com/wzlxjtu/PositionalEncoding2D/blob/master/positionalembedding2d.py
class PositionEmbeddingSine(nn.Module):
    """
    This position embedding is adapted from that in the paper: The attention is all you need.
    Here, we generalize it to work on images by distributing half the d_model to height and wdith
    dimension, respectively
    """
    def __init__(
                self,
                d_model_half: int,
                temperature: int = 10000
                ):
        """
        :param d_model_half: half the depth of the feature map
        """
        super().__init__()
        self.d_model_half = d_model_half
        self.temperature = temperature


    def forward(self, x: torch.Tensor):
        """
        :param x: input tensor of shape (N, H, W, C)
        :methods
         P(pos, 2i) = sin(pos / power(temperature, 2i / d))
         P(pos, 2i + 1) = cos(pos / power(temperature, 2i / d))
         Note that d should be even number
         i >=0 and i < d / 2 -> 2i < d and 2i + 1 (< d + 1) <= d - 1

        temperature is often too large and is better to put it in ln term
         1 / (temperature^(2i /d )) = (temperature^(-2i/d))
         = exp(log((temperature^(-2i / d)))) = exp(-2i * log(temperature) / d) = div_term
        """
        n, h, w, c = x.shape

        assert c == 2 * self.d_model_half

        # Both position and dimension of d_model_half should affect the position embedding
        pe_h = torch.zeros(h, self.d_model_half) # shape [h, d_model_half]
        pe_w = torch.zeros(w, self.d_model_half) # shape [w, d_model_half]

        # (h,) must be expanded to be (h, 1) for broadcastability. The same argument for (w,)
        pos_h = torch.arange(0, h, dtype=x.dtype, device=x.device).unsqueeze(1) # [h, 1]
        pos_w = torch.arange(0, w, dtype=x.dtype, device=x.device).unsqueeze(1) # [w, 1]

        # div_term shape (d_model_half // 2)
        div_term = torch.exp(torch.range(0, self.d_model_half, 2).float() *
                             (-math.log(self.temperature) / self.d_model_half))
        div_term = div_term.to(device=x.device)

        # (h, 1) * (d_model_half // 2) -> (h, d_model_half // 2)
        # (d_model_half // 2) is broadcastable to (h, d_model_half // 2)
        # (h, 1) is broadcasted to (h, d_model_half // 2)
        pe_h[:, 0::2] = torch.sin(pos_h * div_term) # even model dimension
        pe_h[:, 1::2] = torch.cos(pos_h * div_term) # odd model dimension

        pe_w[:, 0::2] = torch.sin(pos_w * div_term) # even model dimension
        pe_w[:, 1::2] = torch.cos(pos_w * div_term) # odd model dimension


        # pe should have the same shape as x
        # pe_h (h, d_model_half) should have shape (n, h, w, d_model_half)
        # pe_w (w, d_model_half) should have shape (n, h, w, d_model_half)
        # (h, d_model_half) -> (1, h, d_model_half) -> (1, h, 1, d_model_half)
        pe_h = pe_h.unsqueeze(0).unsqueeze(2).expand(n, h, w, self.d_model_half)

        # (w, d_model_half) -> (1, w, d_model_half) -> (1, 1, w, d_model_half) -> (n, h, w, d_model_half)
        pe_w = pe_w.unsqueeze(0).unsqueeze(0).expand(n, h, w, self.d_model_half)

        pe = torch.cat([pe_h, pe_w], dim=-1)

        return x + pe


"""
Broadcasting two tensors together follows these rules:

If the tensors do not have the same rank, prepend the shape of the lower rank array with 1s until
both shapes have the same length.
The two tensors are said to be compatible in a dimension if they have the same size in the dimension,
or if one of the tensors has size 1 in that dimension.

The tensors can be broadcast together if they are compatible in all dimensions.
After broadcasting, each tensor behaves as if it had shape equal to the elementwise maximum of
shapes of the two input tensors.
In any dimension where one tensor had size 1 and the other tensor had size greater than 1,
the first tensor behaves as if it were copied along that dimension
"""

"""
torch.repeat repeats along the specified dimensions by copying
while torch.expand return a new view of the tensor with singleton dimension expaned to a larger size
"""
