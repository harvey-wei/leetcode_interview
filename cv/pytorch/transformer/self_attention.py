import torch
import torch.nn as nn
import torch.nn.functional as F
import math
from typing import Optional
from .position_embedding import PositionEmbeddingSine


class SelfAttention(nn.Module):
    """
    Standard Self Attention with residual connection
    """
    def __init__(self,
                 in_channels,
                 has_pos_embed=False,
                 ) -> None:
        super().__init__()
        self.has_pos_embed = has_pos_embed

        if self.has_pos_embed:
            # TODO: implementation position embeding
            self.position_embeding = PositionEmbeddingSine

        self.query_mat = nn.Linear(in_channels, in_channels, bias=False)
        self.key_mat = nn.Linear(in_channels, in_channels, bias=False)
        self.value_mat = nn.Linear(in_channels, in_channels, bias=False)


    def forward(self, x):
        """
        params: x, the input feature map of shape [N, H, W, C]
        Note: for nn.Linear, channel dim is the last dim
        for nn.conv2d feature map shape should be [N, C, H, W]
        """
        if self.has_pos_embed:
            # position embeding is added to x
            x = self.position_embeding(x)

        n, h, w, c = x.shape

        # x: [N, H, W, C] -> queries: [N, H, W, C]
        queries = self.query_mat(x)

        # x: [N, H, W, C] -> keys: [N, H, W, C]
        keys = self.key_mat(x)

        # x: [N, H, W, C] -> values: [N, H, W, C]
        values = self.key_mat(x)

        # https://rockt.github.io/2018/04/30/einsum
        # [N, H, W, C] [N, H=K, W=L, C] -> [N, H, W, H, W]
        sim_mat = torch.einsum('nhwc, nklc->nhwkl', queries, keys) / (c ** 0.5)
        sim_mat = F.softmax(sim_mat.reshape(n, h, w, -1)).reshape(n, h, w, h, w)

        # values [N, H=K, W=L, C], sim_mat [N, H, W, H=K, W=L] -> [N, H, W, C]
        x = torch.einsum('nklc, nhwkl -> nhwc', values, sim_mat)

