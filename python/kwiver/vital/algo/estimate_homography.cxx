/*ckwg +29
 * Copyright 2020 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <python/kwiver/vital/algo/trampoline/estimate_homography_trampoline.txx>

namespace kwiver {
namespace vital  {
namespace python {
namespace py = pybind11;

void estimate_homography(py::module &m)
{
  py::class_< kwiver::vital::algo::estimate_homography,
              std::shared_ptr<kwiver::vital::algo::estimate_homography>,
              kwiver::vital::algorithm_def<kwiver::vital::algo::estimate_homography>,
              estimate_homography_trampoline<> >( m, "EstimateHomography" )
    .def(py::init())
    .def_static("static_type_name",
                &kwiver::vital::algo::estimate_homography::static_type_name)
    // XXX Well these could be better wrapped
    .def("estimate",
         [](kwiver::vital::algo::estimate_homography const& self,
            kwiver::vital::feature_set_sptr feat1,
            kwiver::vital::feature_set_sptr feat2,
            kwiver::vital::match_set_sptr matches,
            double inlier_scale)
         {
           std::vector<bool> inliers;
           auto h = self.estimate(std::move(feat1), std::move(feat2), std::move(matches), inliers, inlier_scale);
           return h ? py::cast(std::make_pair(std::move(h), std::move(inliers)))
             : py::none();
         },
         py::arg("feat1"), py::arg("feat2"), py::arg("matches"),
         py::arg("inlier_scale") = 1.0)
    .def("estimate",
         [](kwiver::vital::algo::estimate_homography const& self,
            std::vector<kwiver::vital::vector_2d> const& pts1,
            std::vector<kwiver::vital::vector_2d> const& pts2,
            double inlier_scale)
         {
           std::vector<bool> inliers;
           auto h = self.estimate(pts1, pts2, inliers, inlier_scale);
           return h ? py::cast(std::make_pair(std::move(h), std::move(inliers)))
             : py::none();
         },
         py::arg("pts1"), py::arg("pts2"), py::arg("inlier_scale") = 1.0);
}
}
}
}