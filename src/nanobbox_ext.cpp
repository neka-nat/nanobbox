#include <nanobind/nanobind.h>
#include <nanobind/tensor.h>

namespace nb = nanobind;

using namespace nb::literals;

using bbox_array = nb::tensor<nb::numpy, float, nb::shape<nb::any, 4>, nb::c_contig, nb::device::cpu>;
using cpu_matrix = nb::tensor<nb::numpy, float, nb::shape<nb::any, nb::any>, nb::c_contig, nb::device::cpu>;

cpu_matrix bbox_overlaps(bbox_array& boxes, bbox_array& query_boxes) {
    float *data = new float[boxes.shape(0) * query_boxes.shape(0)] { 0 };
    size_t shape[2] = { boxes.shape(0), query_boxes.shape(0) };
    nb::capsule owner(data, [](void *p) noexcept {
        delete[] (float *) p;
    });
    cpu_matrix overlaps(data, 2, shape, owner);
    #pragma omp parallel for
    for (size_t k = 0; k < query_boxes.shape(0); ++k) {
        const float box_area = (query_boxes(k, 2) - query_boxes(k, 0) + 1) * (query_boxes(k, 3) - query_boxes(k, 1) + 1);
        for (size_t n = 0; n < boxes.shape(0); ++n) {
            const float iw = std::min(boxes(n, 2), query_boxes(k, 2)) - std::max(boxes(n, 0), query_boxes(k, 0)) + 1;
            if (iw <= 0) continue;
            const float ih = std::min(boxes(n, 3), query_boxes(k, 3)) - std::max(boxes(n, 1), query_boxes(k, 1)) + 1;
            if (ih <= 0) continue;
            const float ua = (boxes(n, 2) - boxes(n, 0) + 1) * (boxes(n, 3) - boxes(n, 1) + 1) + box_area - iw * ih;
            overlaps(n, k) = iw * ih / ua;
        }
    }
    return overlaps;
}

NB_MODULE(nanobbox_ext, m) {
    m.def("bbox_overlaps", &bbox_overlaps,
          nb::raw_doc(
          "Parameters\n"
          "----------\n"
          "boxes: (N, 4) ndarray of float\n"
          "query_boxes: (K, 4) ndarray of float\n"
          "Returns\n"
          "-------\n"
          "overlaps: (N, K) ndarray of overlap between boxes and query_boxes"),
          "boxes"_a, "query_boxes"_a);
}
