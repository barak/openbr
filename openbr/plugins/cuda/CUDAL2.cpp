/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2012 The MITRE Corporation                                      *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
using namespace std;

#include <openbr/plugins/openbr_internal.h>

namespace br { namespace cuda { namespace L2{
  void wrapper(float* cudaAPtr, float* cudaBPtr, int length, float* outPtr);
}}}

namespace br
{

/*!
 * \ingroup distances
 * \brief L2 distance computed using eigen.
 * \author Josh Klontz \cite jklontz
 */
class CUDAL2Distance : public UntrainableDistance
{
    Q_OBJECT

    float compare(const cv::Mat &a, const cv::Mat &b) const
    {
      void* const* srcDataPtr = a.ptr<void*>();
      float* cudaAPtr = (float*)srcDataPtr[0];
      int rows = *((int*)srcDataPtr[1]);
      int cols = *((int*)srcDataPtr[2]);

      float* cudaBPtr = (float*)b.ptr<void*>()[0];

      float out;
      br::cuda::L2::wrapper(cudaAPtr, cudaBPtr, rows*cols, &out);

      return out;
    }
};

BR_REGISTER(Distance, CUDAL2Distance)

} // namespace br

#include "cuda/CUDAL2.moc"
