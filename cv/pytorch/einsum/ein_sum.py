import torch
import numpy as np
import torch.nn.functional as F

# https://rockt.github.io/2018/04/30/einsum
# Both PyTorch and Numpy implement einsum. Both of the two einsum functions share the same
# signature.

# Matrix trace and diagonal
a = torch.tensor([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
a_trace = torch.einsum('ii->', a)
a_diag = torch.einsum('ii->i', a)
print(f"a's trace {a_trace}")
print(f"a's diag {a_diag}")

# Matrix transpose
b = torch.arange(6).reshape(2, 3)
b_transpose = torch.einsum('ij->ji', b)
print(f"b:\n {b}")
print(f"b'T: \n {b_transpose}")

# Sum of all elements of a Tensor
b_sum = torch.einsum('ij->', b)
print(f"b_sum:\n {b_sum}")

# column sum (row dim is reduced)
b_col_sum = torch.einsum('ij->j', b)
print(f"b_col_sum: {b_col_sum}")

# row sum (col dim is reduced)
b_row_sum = torch.einsum('ij->i', b)
print(f"b_row_sum: {b_row_sum}")

# Matrix-vector multiplication
c = torch.arange(3) # shape (3, )
print(f"Shape of c: {c.shape}")
# Just image the sigma notation.
b_times_c = torch.einsum('ij, j->i', b, c)

# Matrix-matrix multiplication
a = torch.arange(6).reshape(2, 3)
b = torch.arange(15).reshape(5, 3)
a_times_b_transpose = torch.einsum('ij, kj->ik', a, b)
print(f"a_times_b_transpose:\n {a_times_b_transpose}")

# Dot Product
a = torch.arange(3)
b = torch.arange(3, 6) # a vector of length 3 containing [3, 4, 5]
a_dot_b = torch.einsum('i, i->', a, b)
print(f"a_dot_b: {a_dot_b}")

a = torch.arange(6).reshape(2, 3)
b = torch.arange(6,12).reshape(2, 3)
mat_a_b = torch.einsum('ij,ij->', [a, b])
print(f"mat_a_b: {mat_a_b}")

# Element-wise Product. Hadamard Product
a = torch.arange(6).reshape(2, 3)
b = torch.arange(6,12).reshape(2, 3)
a_ele_prod_b = torch.einsum('ij, ij->ij', a, b)
print(f"a_ele_prod_b:\n {a_ele_prod_b}")


# permute dim of the tensor
# a = torch.rand(3, 4, 5)
a = torch.randint(0, 10, (3, 4, 5))  # uniform distribution
print(f"a shape: {a.shape}")
a_perm = torch.einsum('ijk->kij', a)
print(f"a_perm shape: {a_perm.shape}")

a = torch.arange(6).reshape(2, 3)
a_perm = torch.einsum('ij->ji', a)  # a_perm is a view is possible
a_perm[0, 0] = 100
print(f"a\n {a}")
print(f"a_perm\n {a_perm}")


# Outer Product
# a = torch.randint(0, 10, (3,))
a = torch.arange(3)
b = torch.arange(3,7)  # -- a vector of length 4 containing [3, 4, 5, 6]
a_out_b = torch.einsum('i, j -> ij', a, b)
print(f"a_out_b: {a_out_b}")


# Batch Matrix Multiplication
a = torch.randn(3, 2, 5)
b = torch.randn(3, 5, 3)

# Note ijk order matters and
# sum a(b, i, k)b(b, k, j) over same index  k
a_bmm_b = torch.einsum('bik, bkj -> bij ', a, b)
print(f"a_bmm_b {a_bmm_b}")

