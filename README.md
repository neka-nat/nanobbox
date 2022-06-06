# nanobbox

nanobbox is a package that calculates Intersection over Union(IoU).
This is based on [cython_bbox](https://github.com/samson-wang/cython_bbox) and reimplemented using [nanobind](https://github.com/wjakob/nanobind).
Speedup is achieved by using nanobind and openmp.

## Installation

```
git clone https://github.com/neka-nat/nanobbox.git
cd nanobbox
pip install -e .
```

## Usage

```py
from nanobbox import bbox_overlaps
overlaps = bbox_overlaps(
    np.ascontiguousarray(dt, dtype=np.float32),
    np.ascontiguousarray(gt, dtype=np.float32)
)
```
