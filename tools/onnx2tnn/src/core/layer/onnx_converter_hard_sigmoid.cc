// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include "onnx_op_converter.h"
#include "onnx_utility.h"

DECLARE_OP_CONVERTER(HardSigmoid);

string OnnxOpConverterHardSigmoid::TNNOpType(NodeProto &node,
                                          OnnxNetInfo &net_info) {
    return "HardSigmoid";
}

string OnnxOpConverterHardSigmoid::TNNLayerParam(
    NodeProto &node, OnnxNetInfo &net_info) {
    const std::string &onnx_op = node.op_type();
    ostringstream layer_param;

    float alpha = get_node_attr_f(node, "alpha", 2.f/10.f);
    float beta = get_node_attr_f(node, "beta", 5.f/10.f);
    layer_param << alpha << " " << beta << " ";

    return layer_param.str();
}

bool OnnxOpConverterHardSigmoid::HasLayerResource(NodeProto &node, OnnxNetInfo &net_info) {
    return false;
}

int OnnxOpConverterHardSigmoid::WriteTNNModel(Serializer *net_writer,
                                                      NodeProto &node,
                                                      OnnxNetInfo &net_info) {
    //有权值写入的返回1， 没有的返回0
    return 0;
}

REGISTER_OP_CONVERTER(HardSigmoid, HardSigmoid);


