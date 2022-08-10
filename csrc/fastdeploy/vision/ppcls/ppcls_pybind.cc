// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "fastdeploy/pybind/main.h"

namespace fastdeploy {
void BindPPCls(pybind11::module& m) {
  auto ppcls_module = m.def_submodule("ppcls", "Module to deploy PaddleClas.");
  pybind11::class_<vision::ppcls::Model, FastDeployModel>(ppcls_module, "Model")
      .def(pybind11::init<std::string, std::string, std::string, RuntimeOption,
                          Frontend>())
      .def("predict",
           [](vision::ppcls::Model& self, pybind11::array& data, int topk = 1) {
             auto mat = PyArrayToCvMat(data);
             vision::ClassifyResult res;
             self.Predict(&mat, &res, topk);
             return res;
           });
}
}  // namespace fastdeploy