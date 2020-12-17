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

#include "tnn/network/tensorrt/layer_builder/tensorrt_layer_builder.h"
#include "tnn/network/tensorrt/utils.h"

namespace TNN_NS {

DECLARE_TENSORRT_LAYER_BUILDER(Unsqueeze, LAYER_UNSQUEEZE);

ILayer* UnsqueezeTRTLayerBuilder::AddToNetwork(INetworkDefinition* network) {
    Blob* output_blob  = output_blobs_[0];
    auto output_dims = output_blob->GetBlobDesc().dims;
    Dims reshape_dims = ConvertToTRTDims(output_dims);
    auto input_foreign_tensor = dynamic_cast<ForeignBlob*>(input_blobs_[0])->GetForeignTensor();
    auto output_foreign_tensor = dynamic_cast<ForeignBlob*>(output_blobs_[0])->GetForeignTensor();
    auto input_tensor = std::dynamic_pointer_cast<TensorRTTensor>(input_foreign_tensor)->GetTensor();
    IShuffleLayer* layer = network->addShuffle(*input_tensor);
    if (layer != nullptr) {
        layer->setName(layer_name_.c_str());
        layer->setReshapeDimensions(reshape_dims);
    }
    if (std::dynamic_pointer_cast<TensorRTTensor>(input_foreign_tensor)->IsQuantized()) {
        std::dynamic_pointer_cast<TensorRTTensor>(output_foreign_tensor)->SetQuantized();
    }

    return layer;
}

REGISTER_TENSORRT_LAYER_BUILDER(Unsqueeze, LAYER_UNSQUEEZE);

}  //  namespace TNN_NS
