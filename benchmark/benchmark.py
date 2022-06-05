import time
import numpy as np
import nanobbox as nb
import cython_bbox as cb

bboxes = np.random.rand(10000, 4)
query_bboxes = np.random.rand(10000, 4)

start = time.time()
result = nb.bbox_overlaps(bboxes, query_bboxes)
print("nanobbox:", time.time() - start)

start = time.time()
result = cb.bbox_overlaps(bboxes, query_bboxes)
print("cython_bbox:", time.time() - start)
