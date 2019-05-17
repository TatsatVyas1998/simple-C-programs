
A cache is a collection of cache lines, each of which may store a block of memory along with some
additional information about the block (for example, which addresses it contains). Each block
contains the same number of bytes, known as the block size. The block size will always be a power of
two. The cache size is the block size multiplied by the number of cache lines (that is, the additional
information is not counted in the cache size).
Consider a system with 48-bit addresses and a block size of 16 bytes. Each block will begin with
an address divisible by 16. Because 16 = 24
, the last 4 bits of an address will determine its offset
within a particular block. For example, the address ffff0000abcd (hexadecimal) will have offset d.
The remaining 44 bits of the address may be considered a block identifier.
If the block size were 8 bytes, then the last 3 bits of the address will be its block offset. The last
three bits of ffff000abcd are 101 (binary) or 5 (hexadecimal). The most-significant 45 bits will be
the block identifier.
For a cache with a single cache line, that cache line will store the 16 bytes of the block along
with the block identifier. Each memory access will first check whether the address is part of the
block currently in the cache (if any). Since we are only simulating memory reads and writes,
cache does not store the actual blocks.
